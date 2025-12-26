# Dummy Options for gen_constants.py
from typing import NamedTuple, Any

class Visibility:
	none = 0b0000
	template = 0b0001
	simple_ui = 0b0010  # show option in simple menus, such as player-options
	complex_ui = 0b0100  # show option in complex menus, such as weighted-options
	spoiler = 0b1000
	all = 0b1111

class Option:
	visibility = Visibility.all
class PerGameCommonOptions(Option): pass
class ProgressionBalancing(Option): pass
class Accessibility(Option): pass
class StartInventoryPool(Option): pass
class Toggle(Option): pass
class DefaultOnToggle(Option): pass
class Choice(Option): pass
class Range(Option): pass
class OptionSet(Option): pass
class OptionCounter(Option): pass

class OptionGroup(NamedTuple):
	name: str
	options: list[Any]
	hidden: bool = False

class DeathLink(Toggle):
	"""When you die, everyone who enabled death link dies. Of course, the reverse is true too."""
