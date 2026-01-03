import sys, typing, json, re, math, Options
sys.path.insert(0, "../ap")
from options import BanjoTooieOptionsList
import data, options

class Version(typing.NamedTuple):
	major: int
	minor: int
	build: int
with open("../ap/archipelago.json", "r") as f:
	version = Version(*(int(piece) for piece in json.load(f).get("world_version").split(".")))

commands = {cmd:value for value, cmd in enumerate([
	"NONE",
	"HANDSHAKE",
	"PING",
	"PONG",
	"STATE",
	"INFO",
	"OPTIONS",
	"LOCATIONS",
	"ITEMS",
	"MESSAGE",
	"DEATH_LINK",
	"TAG_LINK",
])}
states = {
	"DISCONNECTED":	0,
	"CONNECTING":		1,
	"CONNECTED":		2,
	"PINGED":				4,
}
slot_data = set()
option_ids = {}
option_types = {
	"small": {},
	"bits": {},
	"numbers": set(),
	"arrays": {},
}
option_keys = {}
option_set = {}
option_names = {cls:name for name, cls in typing.get_type_hints(BanjoTooieOptionsList).items()}
item_name_to_id = {}
location_name_to_id = {"Completion Condition":0}

class Id:
	id: int
	def __init__(self, id=0): self.id = id
	def __call__(self):
		self.id += 1
		return self.id - 1
next_id = Id()

def header(f, t=0):
	msg = "Automatically generated using gen_constants.py"
	if t:
		f.write(f"# {msg}\n\n")
	else:
		f.write(f"// {msg}\n\n")

def c_header(f):
	f.write("#pragma once\n\n")
	header(f)
	f.write(f"#include <n64/types.h>\n")

def c_enum(f, enums, prefix, name):
	f.write("\ntypedef enum {\n")
	f.write(f"\t{prefix}_INVALID = -1,\n")
	value = 0
	for key, value in enums.items():
		f.write(f"\t{prefix}_{data.option_name(key).upper()} = {value},\n")
	f.write(f"\t{prefix}_MAX = {value+1},\n")
	f.write(f"}} {name}_t;\n")

def process_option(f, option):
	def fwrite(data: str):
		if option.visibility != Options.Visibility.none:
			f.write(data)
	fwrite("\n")
	if option.__doc__:
		prepended_newline = False
		for line in option.__doc__.strip().split("\n"):
			line = re.sub("\\*\\*(.*?)\\*\\*", "\\1", line.strip())
			if not line: continue
			if line.startswith("* "):
				if not prepended_newline:
					fwrite(f"  #\n")
					prepended_newline = True
			else: prepended_newline = False
			fwrite(f"  # {line}\n")
	name = option_names[option]
	slot_data.add(name)
	cls_vars = vars(option)
	comment = ""
	default = 0
	if "default" in cls_vars: default = option.default
	valid_keys = []
	if "valid_keys" in cls_vars:
		valid_keys = option.valid_keys
		if isinstance(valid_keys, set): valid_keys = sorted(valid_keys)
	if issubclass(option, Options.Toggle):
		default = "false"
		comment = " # You can use either: true or false"
		option_types["small"][name] = 1
		option_ids[name] = next_id()
	if issubclass(option, Options.DefaultOnToggle):
		default = "true"
		comment = " # You can use either: true or false"
		option_types["small"][name] = 1
		option_ids[name] = next_id()
	if issubclass(option, Options.Range):
		fwrite("  #\n")
		fwrite(f"  # Minimum value is: {option.range_start}\n")
		fwrite(f"  # Maximum value is: {option.range_end}\n")
		option_types["numbers"].add(name)
		option_ids[name] = next_id()
	if issubclass(option, Options.Choice):
		fwrite("  #\n")
		fwrite(f"  # You can use the following numbers or names:\n")
		option_keys[name] = {}
		highest = 0
		for var, value in cls_vars.items():
			if not var.startswith("option_"): continue
			highest = max(highest, value)
			option_name = re.sub("^option_", "", var)
			option_keys[name][option_name] = value
			if default == value: default = option_name
			fwrite(f"  # {value} or {option_name}\n")
		option_types["small"][name] = int(math.log2(highest))+1
		option_ids[name] = next_id()
	if issubclass(option, Options.OptionSet):
		fwrite("  #\n")
		fwrite(f"  # You can enable options below by removing the # before it. This is known as 'uncommenting'.\n")
		fwrite(f"  # You can also disable an option by placing a # before it. This is known as 'commenting'.\n")
		if default == 0: default = []
		default = list(default)
		option_types["bits"][name] = len(valid_keys)
		option_set[name] = valid_keys
		for option_name in valid_keys:
			option_ids[f"{name}_{data.option_name(option_name)}"] = next_id()
	if issubclass(option, Options.OptionCounter):
		option_types["arrays"][name] = len(valid_keys)
		option_keys[name] = {}
		for value, key in enumerate(valid_keys):
			key = data.option_name(key)
			option_keys[name][key] = value
			option_ids[f"{name}_{key}"] = next_id()
	fwrite(f"  {name}:")
	if isinstance(default, list):
		if not len(default):
			comment = f" [] # Remove the [] here if you uncomment any option below."
		fwrite(f"{comment}\n")
		for option_name in valid_keys:
			if option_name in default:
				fwrite(f"    - {option_name}\n")
			else:
				fwrite(f"    # - {option_name}\n")
	elif isinstance(default, dict):
		if len(default):
			fwrite(f"{comment}\n")
			for key, value in default.items():
				fwrite(f"    {key}: {value}\n")
		else: fwrite(f" {{}}{comment}\n")
	else: fwrite(f" {default}{comment}\n")

next_id.id = 0
with open("../ap/template.yaml", "w", encoding="utf8") as f:
	with open("gen_constants/template_header.yaml", "r", encoding="utf8") as template_header:
		f.write(template_header.read())
	for group in options.groups:
		if group.name != "Game Options": f.write(f"\n  ### {group.name} ###\n")
		for option in group.options:
			if option not in option_names: continue
			process_option(f, option)
	group_header = False
	for option, name in sorted(option_names.items(), key=lambda e: e[1]):
		if name in slot_data: continue
		if option.visibility != Options.Visibility.none:
			print("*** WARNING ***")
			print(f"*** OPTION NOT GROUPED: {name}, {option}")
			if not group_header:
				f.write(f"\n  ### Other Options ###\n")
				group_header = True
		process_option(f, option)

next_id.id = 1
for item_option, items in data.items.items():
	for item_name, classification in items.items():
		item_name_to_id[item_name] = 1
for item_name, items in data.progressives.items():
	item_name_to_id[item_name] = 1
item_name_to_id = {name:next_id() if num == 1 else num for name, num in sorted(item_name_to_id.items(), key=lambda e: e[0])}

item_names: dict[str, str] = {}
for item, value in item_name_to_id.items():
	if value > 0:
		item_names[data.item_name(item)] = item
item_groups = {group:{item_names[item] for item in items} for group, items in data.item_groups.items() if not group.startswith("_")}

next_id.id = 1
for region_name, region in data.regions.items():
	if region.get("major_region", None) == "Menu": continue
	for location_name, location in region.get("locations", {}).items():
		location_name_to_id[location_name] = 1
location_name_to_id = {name:next_id() if num == 1 else num for name, num in sorted(location_name_to_id.items(), key=lambda e: e[0])}

with open("../ap/ids.py", "w") as f:
	f.write("# Automatically generated using gen_constants.py\n\n")
	f.write(f"slot_data_names = {json.dumps(sorted(list(slot_data)), indent="\t")}\n\n")
	f.write(f"option_name_to_id = {json.dumps(option_ids, indent="\t")}\n\n")
	f.write(f"item_name_to_id = {json.dumps(item_name_to_id, indent="\t")}\n\n")
	f.write(f"location_name_to_id = {json.dumps(location_name_to_id, indent="\t")}\n\n")
	f.write(f"class AP_CMD:\n")
	for cmd, value in commands.items():
		f.write(f"\t{cmd} = {value}\n")
	f.write("\n")
	f.write(f"class AP_STATE:\n")
	for state, value in states.items():
		f.write(f"\t{state} = {value}\n")

with open("../ap/data/region_names.py", "w") as f:
	f.write("# Automatically generated using gen_constants.py\n\n")
	f.write("from typing import Literal\n\n")
	f.write(f"RegionName = Literal{json.dumps(
		[region for region in data.regions.keys() if not region.startswith("Location | ")],
		indent="\t"
	)}\n\n")

with open("../n64/src/ap/version.h", "w") as f:
	c_header(f)
	f.write(
f"""
typedef union {{
	struct {{
		u16 major;
		u8 minor;
		u8 build;
	}};
	u32 as_int;
}} ap_version_t;
static const ap_version_t AP_VERSION = {{.major = {version.major}, .minor = {version.minor}, .build = {version.build}}};
"""
	)

with open("../n64/src/ap/options.h", "w") as f:
	c_header(f)
	# struct ap_options_t
	f.write("\ntypedef struct {\n")
	for key, value in sorted(option_types["small"].items(), key=lambda e: (e[1], e[0])):
		f.write(f"\tu32 {data.option_name(key)} : {value};\n")
	for key, value in sorted(option_types["bits"].items(), key=lambda e: (e[1], e[0])):
		f.write("\tstruct {\n")
		for value in sorted(option_set[key]):
			f.write(f"\t\tu8 {data.option_name(value)} : 1;\n")
		f.write(f"\t}} {data.option_name(key)};\n")
	for key in sorted(option_types["numbers"]):
		f.write(f"\ts32 {data.option_name(key)};\n")
	for key, value in sorted(option_types["arrays"].items(), key=lambda e: (e[1], e[0])):
		f.write(f"\ts32 {data.option_name(key)}[{value}];\n")
	f.write("} ap_options_t;\n")
	# enum ap_option
	c_enum(f, option_ids, "APO", "ap_option")
	# enum ap_option_key_<option>
	for option_name, names in option_keys.items():
		option_name = data.option_name(option_name)
		c_enum(f, option_keys[option_name], f"APOK_{option_name.upper()}", f"ap_option_key_{option_name}")
	# ap_option_set()
	f.write("\nvoid ap_options_set(ap_option_t option, s32 value);\n")

with open("../n64/src/ap/options.c", "w") as f:
	header(f)
	f.write("#include <ap/ap.h>\n\n")
	f.write("#include <ap/options.h>\n")
	# ap_option_set()
	f.write("void ap_options_set(ap_option_t option, s32 value) {\n")
	f.write("\tswitch (option) {\n")
	for key, value in sorted(option_types["small"].items(), key=lambda e: (e[1], e[0])):
		key = data.option_name(key)
		f.write(f"\tcase APO_{key.upper()}: ap.options.{key} = value; return;\n")
	for key, value in sorted(option_types["bits"].items(), key=lambda e: (e[1], e[0])):
		key = data.option_name(key)
		for value in sorted(option_set[key]):
			value = data.option_name(value)
			f.write(f"\tcase APO_{key.upper()}_{value.upper()}: ap.options.{key}.{value} = value; return;\n")
	for key in sorted(option_types["numbers"]):
		f.write(f"\tcase APO_{key.upper()}: ap.options.{key} = value; return;\n")
	for key, value in sorted(option_types["arrays"].items(), key=lambda e: (e[1], e[0])):
		name = data.option_name(key)
		for key, value in option_keys[key].items():
			key = data.option_name(key)
			f.write(f"\tcase APO_{name.upper()}_{key.upper()}: ap.options.{name}[{value}] = value; return;\n")
	f.write(f"\tdefault: return;\n")
	f.write("\t}\n")
	f.write("}\n")

with open("../n64/src/ap/items.h", "w") as f:
	c_header(f)
	# enum ap_item
	c_enum(f, item_name_to_id, "API", "ap_item")
	# enum ap_item_group
	c_enum(f, {group:i for i, group in enumerate(sorted(data.item_groups))}, "APIG", "ap_item_group")
	# ap_item_group()
	f.write("\nbool ap_items_in_group(ap_item_t item, ap_item_group_t group);\n")

with open("../n64/src/ap/items.c", "w") as f:
	header(f)
	f.write("#include <ap/items.h>\n\n")
	f.write("bool ap_items_in_group(ap_item_t item, ap_item_group_t group) {\n")
	f.write("\tswitch (group) {\n")
	for group_name, items in sorted(item_groups.items()):
		f.write(f"\tcase APIG_{data.option_name(group_name).upper()}:\n")
		f.write("\t\tswitch (item) {\n")
		for item in sorted(items):
			f.write(f"\t\tcase API_{data.option_name(item).upper()}:\n")
		f.write("\t\t\treturn true;\n")
		f.write("\t\tdefault: return false;\n")
		f.write("\t\t}\n")
	f.write(f"\tdefault: return false;\n")
	f.write("\t}\n")
	f.write("}\n")

with open("../n64/src/ap/locations.h", "w") as f:
	c_header(f)
	# enum ap_location
	c_enum(f, location_name_to_id, "APL", "ap_location")
	f.write(f"#define APL_MAX_BYTES (((APL_MAX - 1) - (APL_MAX - 1) % 8 + 8) / 8)\n")
	# struct ap_locations_t
	f.write("\ntypedef union {\n")
	f.write("\tstruct {\n")
	for key, value in location_name_to_id.items():
		f.write(f"\t\tu8 {data.option_name(key)} : 1;\n")
	f.write("\t};\n")
	f.write(f"\tu8 raw[APL_MAX_BYTES];\n")
	f.write("} ap_locations_t;\n")
	# enum ap_location_group
	c_enum(f, {group:i for i, group in enumerate(sorted(data.location_groups))}, "APLG", "ap_location_group")
	# ap_locations_in_group()
	f.write("\nbool ap_locations_in_group(ap_location_t location, ap_location_group_t group);\n")

with open("../n64/src/ap/locations.c", "w") as f:
	header(f)
	f.write("#include <ap/locations.h>\n\n")
	f.write("bool ap_locations_in_group(ap_location_t location, ap_location_group_t group) {\n")
	f.write("\tswitch (group) {\n")
	for group_name, locations in sorted(data.location_groups.items()):
		f.write(f"\tcase APLG_{data.option_name(group_name).upper()}:\n")
		f.write("\t\tswitch (location) {\n")
		for location in sorted(locations):
			f.write(f"\t\tcase APL_{data.option_name(location).upper()}:\n")
		f.write("\t\t\treturn true;\n")
		f.write("\t\tdefault: return false;\n")
		f.write("\t\t}\n")
	f.write(f"\tdefault: return false;\n")
	f.write("\t}\n")
	f.write("}\n")

with open("../n64/src/ap/commands.h", "w") as f:
	c_header(f)
	# enum ap_cmd
	c_enum(f, commands, "APC", "ap_cmd")

with open("../n64/src/ap/states.h", "w") as f:
	c_header(f)
	# enum ap_state
	c_enum(f, states, "APS", "ap_state")

with open("gen_constants/short_constants.txt", "w") as f:
	names = set()
	for name in item_name_to_id: names.add(data.item_name(name))
	for name in location_name_to_id: names.add(data.item_name(name))
	for tricks in data.tricks.values():
		for name in tricks: names.add(data.item_name(name))
	for name in data.alias: names.add(data.item_name(name))
	for cls in option_names:
		names.add(data.item_name(cls.__name__))
		if issubclass(cls, Options.OptionCounter):
			for key in cls.valid_keys: names.add(data.item_name(f"{cls.__name__} {key}"))
	for name in sorted(names):
		f.write(f"{name}\n")
