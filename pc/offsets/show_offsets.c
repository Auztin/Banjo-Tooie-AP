#include <stdio.h>
#include <util.h>

ap_memory_t ap_memory;
ap_memory_ptr_t ap_memory_ptr;

#define mem (void*)&ap_memory
#define ptr (void*)&ap_memory_ptr
#define calc(base, offset) offset-base

int main() {
  printf("    base_index = 0x%X,\n",                      0x400000);
  printf("        version = 0x%X,\n",                     calc(ptr, ptr.version));
  printf("    pc = 0x%X,\n",                              calc(ptr, ptr.pc));
  printf("        pc_death_us = 0x%X,\n",                 calc(mem.pc.misc, mem.pc.misc.death_link_us));
  printf("        pc_death_ap = 0x%X,\n",                 calc(mem.pc.misc, mem.pc.misc.death_link_ap));
  printf("        pc_tag_us = 0x%X,\n",                   calc(mem.pc.misc, mem.pc.misc.tag_link_us));
  printf("        pc_tag_ap = 0x%X,\n",                   calc(mem.pc.misc, mem.pc.misc.tag_link_ap));
  printf("        pc_show_txt = 0x%X,\n",                 calc(mem.pc.misc, mem.pc.misc.show_message));
  printf("    pc_messages = 0x%X,\n",                     calc(ptr, ptr.pc_message));
  printf("    signpost_messages = 0x%X,\n",               calc(ptr, ptr.signpost_messages));
  printf("    pc_settings = 0x%X,\n",                     calc(ptr, ptr.pc_settings));
  printf("        setting_seed = 0x%X,\n",                calc(mem.pc.settings, mem.pc.settings.seed));
  printf("        setting_victory_condition = 0x%X,\n",   calc(mem.pc.settings, mem.pc.settings.victory_condition));
  printf("        setting_chuffy = 0x%X,\n",              calc(mem.pc.settings, mem.pc.settings.randomize_chuffy));
  printf("        setting_nests = 0x%X,\n",               calc(mem.pc.settings, mem.pc.settings.randomize_nests));
  printf("        setting_warppads = 0x%X,\n",            calc(mem.pc.settings, mem.pc.settings.randomize_warppads));
  printf("        setting_warpsilos = 0x%X,\n",           calc(mem.pc.settings, mem.pc.settings.randomize_warpsilos));
  printf("        setting_honeyb_rewards = 0x%X,\n",      calc(mem.pc.settings, mem.pc.settings.honeyb_rewards));
  printf("        setting_cheato_rewards = 0x%X,\n",      calc(mem.pc.settings, mem.pc.settings.cheato_rewards));
  printf("        setting_randomize_tickets = 0x%X,\n",   calc(mem.pc.settings, mem.pc.settings.randomize_tickets));
  printf("        setting_randomize_green_relics = 0x%X,\n", calc(mem.pc.settings, mem.pc.settings.randomize_green_relics));
  printf("        setting_randomize_beans = 0x%X,\n",     calc(mem.pc.settings, mem.pc.settings.randomize_beans));
  printf("        setting_puzzle = 0x%X,\n",              calc(mem.pc.settings, mem.pc.settings.skip_puzzles));
  printf("        setting_backdoors = 0x%X,\n",           calc(mem.pc.settings, mem.pc.settings.backdoors));
  printf("        setting_gi_open_frontdoor = 0x%X,\n",   calc(mem.pc.settings, mem.pc.settings.gi_open_frontdoor));
  printf("        setting_klungo = 0x%X,\n",              calc(mem.pc.settings, mem.pc.settings.skip_klungo));
  printf("        setting_tot = 0x%X,\n",                 calc(mem.pc.settings, mem.pc.settings.skip_tower_of_tragedy));
  printf("        setting_minigames = 0x%X,\n",           calc(mem.pc.settings, mem.pc.settings.speed_up_minigames));
  printf("        setting_dialog_character = 0x%X,\n",    calc(mem.pc.settings, mem.pc.settings.dialog_character));
  printf("        setting_max_mumbo_tokens = 0x%X,\n",    calc(mem.pc.settings, mem.pc.settings.max_mumbo_tokens));
  printf("        setting_signpost_hints = 0x%X,\n",      calc(mem.pc.settings, mem.pc.settings.signpost_hints));
  printf("        setting_extra_cheats = 0x%X,\n",        calc(mem.pc.settings, mem.pc.settings.extra_cheats));
  printf("        setting_automatic_cheats = 0x%X,\n",    calc(mem.pc.settings, mem.pc.settings.automatic_cheats));
  printf("        setting_easy_canary = 0x%X,\n",         calc(mem.pc.settings, mem.pc.settings.easy_canary));
  printf("        setting_jiggy_requirements = 0x%X,\n",  calc(mem.pc.settings, mem.pc.settings.jiggy_requirements));
  printf("        setting_silo_requirements = 0x%X,\n",   calc(mem.pc.settings, mem.pc.settings.silo_requirements));
  printf("    pc_items = 0x%X,\n",                        calc(ptr, ptr.pc_items));
  printf("    pc_traps = 0x%X,\n",                        calc(ptr, ptr.pc_traps));
  printf("    pc_exit_map = 0x%X,\n",                     calc(ptr, ptr.pc_exit_map));
  printf("        exit_on_map = 0x%X,\n",                 calc(mem.pc.exit_map[0], mem.pc.exit_map[0].on_map));
  printf("        exit_og_map = 0x%X,\n",                 calc(mem.pc.exit_map[0], mem.pc.exit_map[0].og_map));
  printf("        exit_to_map = 0x%X,\n",                 calc(mem.pc.exit_map[0], mem.pc.exit_map[0].to_map));
  printf("        exit_og_exit = 0x%X,\n",                calc(mem.pc.exit_map[0], mem.pc.exit_map[0].og_exit));
  printf("        exit_to_exit = 0x%X,\n",                calc(mem.pc.exit_map[0], mem.pc.exit_map[0].to_exit));
  printf("        exit_access_rules = 0x%X,\n",           calc(mem.pc.exit_map[0], mem.pc.exit_map[0].access_rules));
  printf("        exit_access_rules_size = 0x%X,\n",      sizeof(ap_memory.pc.exit_map[0].access_rules));
  printf("        exit_map_struct_size = 0x%X,\n",        sizeof(*ap_memory.pc.exit_map));
  printf("        world_index = %X,\n",                   0);
  printf("    n64 = 0x%X,\n",                             calc(ptr, ptr.n64));
  printf("        n64_show_text = 0x%X,\n",               calc(mem.n64.misc, mem.n64.misc.show_message));
  printf("        n64_death_us = 0x%X,\n",                calc(mem.n64.misc, mem.n64.misc.death_link_us));
  printf("        n64_death_ap = 0x%X,\n",                calc(mem.n64.misc, mem.n64.misc.death_link_ap));
  printf("        n64_tag_us = 0x%X,\n",                  calc(mem.n64.misc, mem.n64.misc.tag_link_us));
  printf("        n64_tag_ap = 0x%X,\n",                  calc(mem.n64.misc, mem.n64.misc.tag_link_ap));
  printf("        current_map = 0x%X,\n",                 calc(mem.n64.misc, mem.n64.misc.current_map));
  printf("    real_flags = 0x%X,\n",                      calc(ptr, ptr.n64_saves_real));
  printf("    fake_flags = 0x%X,\n",                      calc(ptr, ptr.n64_saves_fake));
  printf("    nest_flags = 0x%X,\n",                      calc(ptr, ptr.n64_saves_nests));
  printf("    signpost_flags = 0x%X,\n",                  calc(ptr, ptr.n64_saves_signposts));
  return 0;
}
