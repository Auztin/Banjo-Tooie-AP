#include "ap_menu.h"
#include "ap_menu_data.h"
#include "ap.h"
#include "save.h"

#include <string.h>
#include <stdlib.h>

ap_menu_t ap_menu = {.title_y = -20, 0, };

bt_zoombox_t* ap_menu_new_zoombox(bt_zoombox_t* zb, u16 icon, u16 x, u16 y, float size, float length, u8 lines, char** text) {
  if (zb) {
    bt_fn_zoombox_icon(zb, icon);
    bt_fn_zoombox_clear_text(zb);
  }
  else {
    zb = bt_fn_zoombox_new(y, icon, 2, 0);
    bt_fn_zoombox_x_size_length(zb, x, size, length);
    bt_fn_zoombox_text_speed(zb, 50);
    bt_fn_zoombox_init(zb);
  }
  bt_fn_zoombox_append_lines(zb, lines, text);
  return zb;
}

void ap_menu_add_entry(u16 icon, u8 lines, char** text) {
  float zoombox_width = 214;
  u16 column_width = 290;
  u16 left_margin = (304-column_width)/2;
  u16 x = (column_width-zoombox_width)/2;
  u16 height = 40;
  float size = 1;
  float length = 1;
  if (ap_menu.last_zb) {
    switch (ap_menu.columns) {
      case 1:
        size = 0.75;
        length = 1.0;
        break;
      case 2:
        size = 0.65;
        length = 0.85;
        break;
      case 3:
        size = 0.65;
        length = 0.50;
        break;
      case 4:
        size = 0.60;
        length = 0.40;
        break;
    }
    height *= size;
    zoombox_width *= size;
    zoombox_width *= length;
    column_width /= ap_menu.columns;
    x = (column_width-zoombox_width)/2;
  }
  if (ap_menu.last_zb) {
    if (ap_menu.column == ap_menu.columns) {
      ap_menu.column = 0;
      ap_menu.last_y += height;
    }
    x += ap_menu.column * column_width;
    ap_menu.column++;
  }
  else ap_menu.last_y += height;
  bt_zoombox_t* zb = ap_menu.zoombox[ap_menu.last_zb];
  zb = ap_menu_new_zoombox(zb, icon, x+left_margin, ap_menu.last_y, size, length, lines, text);
  ap_menu.zoombox[ap_menu.last_zb++] = zb;
  if (size == 1) ap_menu.last_y += 35;
  else if (ap_menu.selected) bt_fn_zoombox_selected(zb, false);
}

void ap_menu_draw(bt_draw_ctx_t* draw_ctx) {
  if (ap_menu.title) {
    bt_fn_text_reset_options();
    bt_text_options.appearance = BT_TEXT_TEXTURE_BLUE;
    bt_fn_text_big_draw_centered(draw_ctx, ap_menu.title_y, ap_menu.title);
  }
  for (int i = 0; i < sizeof(ap_menu.zoombox)/4; i++) {
    bt_zoombox_t* zoombox = ap_menu.zoombox[i];
    if (!zoombox) continue;
    bt_fn_zoombox_draw(zoombox, draw_ctx);
  }
}

void ap_menu_select() {
  ap_menu_data_t* data;
  switch (ap_menu.id) {
    case AP_MENU_MAIN:
      switch (ap_menu.selected) {
        case AP_MENU_MAIN_OPTIONS:
          ap_menu.id = AP_MENU_OPTIONS;
          break;
        case AP_MENU_MAIN_MOVES_KAZOOIE:
          ap_menu.id = AP_MENU_RECEIVED_MOVES_BK;
          break;
        case AP_MENU_MAIN_ENTRANCES:
          ap_menu.id = AP_MENU_WORLD_ENTRANCES;
          break;
        case AP_MENU_MAIN_MOVES_TOOIE:
          ap_menu.id = AP_MENU_RECEIVED_MOVES_BT;
          break;
        case AP_MENU_MAIN_TOTALS:
          ap_menu.id = AP_MENU_TOTOTALS;
          break;
        case AP_MENU_MAIN_MUMBO_AND_HUMBA:
          ap_menu.id = AP_MENU_RECEIVED_MUMBO_HUMBA;
          break;
        case AP_MENU_MAIN_CHEATS:
          ap_menu.id = AP_MENU_CHEATS;
          break;
        case AP_MENU_MAIN_CHUFFY:
          ap_menu.id = AP_MENU_RECEIVED_TRAIN_STATIONS;
          break;
        case AP_MENU_MAIN_WARP_SILOS:
          ap_menu.id = AP_MENU_RECEIVED_WARP_SILOS;
          break;
        case AP_MENU_MAIN_WARP_PADS:
          ap_menu.id = AP_MENU_RECEIVED_WARP_PADS;
          break;
        default: return;
      }
      break;
    case AP_MENU_OPTIONS:
      data = &ap_menu_options_data[ap_menu.selected-1];
      switch (data->item) {
        case AP_MENU_OPTION_DRAGON_KAZOOIE:
          if (bt_flags.humba_dragon_kazooie && bt_fake_flags.humba_dragon_kazooie) {
            if (!bt_flags.dragon_kazooie) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.dragon_kazooie = !bt_flags.dragon_kazooie;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_OPTION_SMOOTH_BANJO:
          if (!ap.smooth_banjo) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
          else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
          ap.smooth_banjo = !ap.smooth_banjo;
          BT_FPS = (ap.smooth_banjo && bt_player_chars.control_type != BT_PLAYER_CHAR_WASHER) ? 1 : 2;
          break;
        case AP_MENU_OPTION_RESPAWN:
          if (bt_fn_character_touching_ground(bt_current_player_char) || bt_fn_character_in_water(bt_current_player_char)) {
            bt_fn_play_sound(BT_SOUND_COLLECTED_ITEM1, -1, 1, -1);
            ap_memory.n64.misc.death_link_ap--;
            ap_menu.id = AP_MENU_UNPAUSE;
            ap_menu.state = AP_MENU_STATE_CLEAR;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_OPTION_RESET:
          if (
               bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE && bt_flags.jukebox_jv
            && (bt_fn_character_touching_ground(bt_current_player_char) || bt_fn_character_in_water(bt_current_player_char))
          ) {
            bt_fn_play_sound(BT_SOUND_COLLECTED_ITEM1, -1, 1, -1);
            bt_xyz_t point = {0, 0, 0};
            bt_fn_increase_health(bt_current_player_char, 100);
            bt_fn_character_move_to(&point, 0, 0);
            bt_fn_load_scene(BT_MAP_JV, 3, 1);
            ap_menu.id = AP_MENU_UNPAUSE;
            ap_menu.state = AP_MENU_STATE_CLEAR;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
      }
      return;
    case AP_MENU_CHEATS:
      data = &ap_menu_cheats_data[ap_menu.selected-1];
      switch (data->item) {
        case AP_MENU_CHEATS_FEATHERS:
          if (bt_flags.cheats_feathers_received) {
            if (!bt_flags.cheats_feathers_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_feathers_enabled = !bt_flags.cheats_feathers_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_EGGS:
          if (bt_flags.cheats_eggs_received) {
            if (!bt_flags.cheats_eggs_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_eggs_enabled = !bt_flags.cheats_eggs_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_FALLPROOF:
          if (bt_flags.cheats_fallproof_received) {
            if (!bt_flags.cheats_fallproof_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_fallproof_enabled = !bt_flags.cheats_fallproof_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_HONEYBACK:
          if (bt_flags.cheats_honeyback_received) {
            if (!bt_flags.cheats_honeyback_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_honeyback_enabled = !bt_flags.cheats_honeyback_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_HOMING_EGGS:
          if (bt_flags.cheats_homing_eggs_received) {
            if (!bt_flags.cheats_homing_eggs_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_homing_eggs_enabled = !bt_flags.cheats_homing_eggs_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_NESTKING:
          if (ap_memory.pc.settings.extra_cheats) {
            if (!bt_flags.cheats_nestking_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_nestking_enabled = !bt_flags.cheats_nestking_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_HONEYKING:
          if (ap_memory.pc.settings.extra_cheats) {
            if (!bt_flags.cheats_honeyking_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_honeyking_enabled = !bt_flags.cheats_honeyking_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_SUPER_BANJO:
          if (ap_memory.pc.settings.extra_cheats) {
            if (!bt_flags.cheats_superbanjo_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_superbanjo_enabled = !bt_flags.cheats_superbanjo_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
        case AP_MENU_CHEATS_SUPERBADDY:
          if (ap_memory.pc.settings.extra_cheats) {
            if (!bt_flags.cheats_superbaddy_enabled) bt_fn_play_sound(BT_SOUND_INCREASE, -1, 1, -1);
            else bt_fn_play_sound(BT_SOUND_DECREASE, -1, 1, -1);
            bt_flags.cheats_superbaddy_enabled = !bt_flags.cheats_superbaddy_enabled;
          }
          else bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
          break;
      }
      if (bt_flags.cheats_nestking_enabled) {
        bt_fn_item_infinite(BT_ITEM_BLUE_EGGS);
        bt_fn_item_infinite(BT_ITEM_FIRE_EGGS);
        bt_fn_item_infinite(BT_ITEM_ICE_EGGS);
        bt_fn_item_infinite(BT_ITEM_GRENADE_EGGS);
        bt_fn_item_infinite(BT_ITEM_CLOCKWORK_EGGS);
      }
      else if (bt_flags.cheats_eggs_enabled) {
        bt_fn_item_double_max(BT_ITEM_BLUE_EGGS);
        bt_fn_item_double_max(BT_ITEM_FIRE_EGGS);
        bt_fn_item_double_max(BT_ITEM_ICE_EGGS);
        bt_fn_item_double_max(BT_ITEM_GRENADE_EGGS);
        bt_fn_item_double_max(BT_ITEM_CLOCKWORK_EGGS);
      }
      else {
        bt_fn_item_restore_max(BT_ITEM_BLUE_EGGS);
        bt_fn_item_restore_max(BT_ITEM_FIRE_EGGS);
        bt_fn_item_restore_max(BT_ITEM_ICE_EGGS);
        bt_fn_item_restore_max(BT_ITEM_GRENADE_EGGS);
        bt_fn_item_restore_max(BT_ITEM_CLOCKWORK_EGGS);
      }
      if (bt_flags.cheats_nestking_enabled) {
        bt_fn_item_infinite(BT_ITEM_RED_FEATHERS);
        bt_fn_item_infinite(BT_ITEM_GOLD_FEATHERS);
      }
      else if (bt_flags.cheats_feathers_enabled) {
        bt_fn_item_double_max(BT_ITEM_RED_FEATHERS);
        bt_fn_item_double_max(BT_ITEM_GOLD_FEATHERS);
      }
      else {
        bt_fn_item_restore_max(BT_ITEM_RED_FEATHERS);
        bt_fn_item_restore_max(BT_ITEM_GOLD_FEATHERS);
      }
      return;
    default: return;
  }
  ap_menu.progress = 0xFF;
  ap_menu.state = AP_MENU_STATE_CLEAR;
}

void ap_menu_update_zoombox(int i, bt_zoombox_t* zb) {
  bt_color_t white = {.red=0xFF, .green=0xFF, .blue=0xFF};
  bt_color_t red = {.red=0xFF, .green=0x30, .blue=0x30};
  bt_color_t green = {.red=0x30, .green=0xFF, .blue=0x30};
  ap_menu_data_t* data;
  u16* item = 0;
  if (i) {
    switch (ap_menu.id) {
      case AP_MENU_RECEIVED_MOVES_BK:
        item = &ap_menu_received_moves_bk_data[i-1].item;
        break;
      case AP_MENU_RECEIVED_MOVES_BT:
        switch (ap_menu.page) {
          case 1:
            item = &ap_menu_received_moves_bt1_data[i-1].item;
            break;
          case 2:
            item = &ap_menu_received_moves_bt2_data[i-1].item;
            break;
        }
        break;
      case AP_MENU_RECEIVED_MUMBO_HUMBA:
        item = &ap_menu_received_mumbo_humba_data[i-1].item;
        break;
      case AP_MENU_RECEIVED_TRAIN_STATIONS:
        item = &ap_menu_received_train_stations_data[i-1].item;
        break;
      case AP_MENU_WORLD_ENTRANCES:
        item = &ap_menu_world_entrances_data[i-1].item;
        break;
      case AP_MENU_OPTIONS:
        data = &ap_menu_options_data[i-1];
        switch (data->item) {
          case AP_MENU_OPTION_DRAGON_KAZOOIE:
            if (bt_flags.humba_dragon_kazooie && bt_fake_flags.humba_dragon_kazooie) {
              if (bt_flags.dragon_kazooie) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_OPTION_SMOOTH_BANJO:
            if (ap.smooth_banjo) bt_fn_zoombox_text_color(zb, &green);
            else bt_fn_zoombox_text_color(zb, &white);
            break;
          case AP_MENU_OPTION_RESPAWN:
            if (bt_fn_character_touching_ground(bt_current_player_char) || bt_fn_character_in_water(bt_current_player_char)) {
              bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_OPTION_RESET:
            if (
                 bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE && bt_flags.jukebox_jv
              && (bt_fn_character_touching_ground(bt_current_player_char) || bt_fn_character_in_water(bt_current_player_char))
            ) bt_fn_zoombox_text_color(zb, &white);
            else bt_fn_zoombox_text_color(zb, &red);
            break;
        }
        break;
      case AP_MENU_CHEATS:
        data = &ap_menu_cheats_data[i-1];
        switch (data->item) {
          case AP_MENU_CHEATS_FEATHERS:
            if (bt_flags.cheats_feathers_received) {
              if (bt_flags.cheats_feathers_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_EGGS:
            if (bt_flags.cheats_eggs_received) {
              if (bt_flags.cheats_eggs_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_FALLPROOF:
            if (bt_flags.cheats_fallproof_received) {
              if (bt_flags.cheats_fallproof_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_HONEYBACK:
            if (bt_flags.cheats_honeyback_received) {
              if (bt_flags.cheats_honeyback_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_HOMING_EGGS:
            if (bt_flags.cheats_homing_eggs_received) {
              if (bt_flags.cheats_homing_eggs_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_NESTKING:
            if (ap_memory.pc.settings.extra_cheats) {
              if (bt_flags.cheats_nestking_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_HONEYKING:
            if (ap_memory.pc.settings.extra_cheats) {
              if (bt_flags.cheats_honeyking_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_SUPER_BANJO:
            if (ap_memory.pc.settings.extra_cheats) {
              if (bt_flags.cheats_superbanjo_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
          case AP_MENU_CHEATS_SUPERBADDY:
            if (ap_memory.pc.settings.extra_cheats) {
              if (bt_flags.cheats_superbaddy_enabled) bt_fn_zoombox_text_color(zb, &green);
              else bt_fn_zoombox_text_color(zb, &white);
            }
            else bt_fn_zoombox_text_color(zb, &red);
            break;
        }
        break;
      case AP_MENU_RECEIVED_WARP_SILOS:
        item = &ap_menu_received_warp_silos_data[i-1].item;
        break;
      case AP_MENU_RECEIVED_WARP_PADS:
        switch (ap_menu.page) {
          case 1:
            item = &ap_menu_received_warp_pads_mt_data[i-1].item;
            break;
          case 2:
            item = &ap_menu_received_warp_pads_ggm_data[i-1].item;
            break;
          case 3:
            item = &ap_menu_received_warp_pads_ww_data[i-1].item;
            break;
          case 4:
            item = &ap_menu_received_warp_pads_jrl_data[i-1].item;
            break;
          case 5:
            item = &ap_menu_received_warp_pads_tdl_data[i-1].item;
            break;
          case 6:
            item = &ap_menu_received_warp_pads_gi_data[i-1].item;
            break;
          case 7:
            item = &ap_menu_received_warp_pads_hfp_data[i-1].item;
            break;
          case 8:
            item = &ap_menu_received_warp_pads_ccl_data[i-1].item;
            break;
          case 9:
            item = &ap_menu_received_warp_pads_ck_data[i-1].item;
            break;
        }
        break;
    }
  }
  if (item) {
    if (ap_memory.pc.items[*item]) bt_fn_zoombox_text_color(zb, &green);
    else bt_fn_zoombox_text_color(zb, &red);
  }
}

void ap_menu_change_page() {
  if (ap_menu.page < 1) ap_menu.page = ap_menu.page_max;
  if (ap_menu.page > ap_menu.page_max) ap_menu.page = 1;
  ap_menu.state = AP_MENU_STATE_PAGE_SWITCH;
}

void ap_menu_page_text(u16 icon) {
  static char text[37];
  char* index = text;
  strcpy(index, "PAGE ");
  index = itoa(ap_menu.page, index+5, 10);
  for (; *index != 0; index++);
  strcpy(index, " OF ");
  index = itoa(ap_menu.page_max, index+4, 10);
  for (; *index != 0; index++);
  strcpy(index, ". \x81 AND \x80 CHANGE PAGES.");
  ap_menu_add_entry(icon, 1, (char*[]){text});
}

void ap_menu_update_world_entrances() {
  ap_menu_data_t* data = ap_menu_world_entrances_data;
  for (int i = 0; i < sizeof(ap_menu_world_entrances_data)/sizeof(*data); i++) {
    ap_menu_data_t* entry = &data[i];
    for (int i = 0; i < AP_MEMORY_EXIT_MAP_MAX; i++) {
      ap_memory_pc_exit_map_t* mapping = &(ap_memory.pc.exit_map[i]);
      if (!mapping->on_map) break;
      if (mapping->on_map != entry->exit_map.on_map) continue;
      if (mapping->og_map == entry->exit_map.og_map && mapping->og_exit == entry->exit_map.og_exit) {
        char world[3] = "???";
        switch (mapping->to_map) {
          case 0x0B8:
            if (bt_fake_flags.mt_visited) memcpy(world, " MT", 3);
            break;
          case 0x0C7:
            if (bt_fake_flags.ggm_visited) memcpy(world, "GGM", 3);
            break;
          case 0x0D6:
            if (bt_fake_flags.ww_visited) memcpy(world, " WW", 3);
            break;
          case 0x1A7:
            if (bt_fake_flags.jrl_visited) memcpy(world, "JRL", 3);
            break;
          case 0x112:
            if (bt_fake_flags.tdl_visited) memcpy(world, "TDL", 3);
            break;
          case 0x100:
            if (bt_fake_flags.gi_visited) memcpy(world, " GI", 3);
            break;
          case 0x127:
            if (bt_fake_flags.hfp_visited) memcpy(world, "HFP", 3);
            break;
          case 0x136:
            if (bt_fake_flags.ccl_visited) memcpy(world, "CCL", 3);
            break;
          case 0x15D:
            if (bt_fake_flags.ck_visited) memcpy(world, " CK", 3);
            break;
        }
        memcpy(entry->zb.text[0]+6, world, 3);
        break;
      }
    }
  }
}

void ap_menu_update() {
  char* page_text;
  switch (ap_menu.state) {
    case AP_MENU_STATE_INIT:
    case AP_MENU_STATE_PAGE_SWITCH:
      if (ap_menu.state == AP_MENU_STATE_INIT) {
        ap_menu.progress = 0;
        ap_menu.page = 0;
        ap_menu.page_max = 0;
      }
      ap_menu.last_zb = 0;
      ap_menu.last_y = 0;
      ap_menu.column = 0;
      ap_menu.columns = 1;
      ap_menu.title = 0;
      switch (ap_menu.last_id) {
        // AP_MENU_MAIN
        case AP_MENU_OPTIONS:
          ap_menu.selected = AP_MENU_MAIN_OPTIONS;
          break;
        case AP_MENU_RECEIVED_MOVES_BK:
          ap_menu.selected = AP_MENU_MAIN_MOVES_KAZOOIE;
          break;
        case AP_MENU_WORLD_ENTRANCES:
          ap_menu.selected = AP_MENU_MAIN_ENTRANCES;
          break;
        case AP_MENU_RECEIVED_MOVES_BT:
          ap_menu.selected = AP_MENU_MAIN_MOVES_TOOIE;
          break;
        case AP_MENU_TOTOTALS:
          ap_menu.selected = AP_MENU_MAIN_TOTALS;
          break;
        case AP_MENU_RECEIVED_MUMBO_HUMBA:
          ap_menu.selected = AP_MENU_MAIN_MUMBO_AND_HUMBA;
          break;
        case AP_MENU_CHEATS:
          ap_menu.selected = AP_MENU_MAIN_CHEATS;
          break;
        case AP_MENU_RECEIVED_TRAIN_STATIONS:
          ap_menu.selected = AP_MENU_MAIN_CHUFFY;
          break;
        case AP_MENU_RECEIVED_WARP_SILOS:
          ap_menu.selected = AP_MENU_MAIN_WARP_SILOS;
          break;
        case AP_MENU_RECEIVED_WARP_PADS:
          ap_menu.selected = AP_MENU_MAIN_WARP_PADS;
          break;
        default:
          ap_menu.selected = 1;
      }
      ap_menu_data_t* opt_data = 0;
      ap_menu_zb_data_t* zb_data = 0;
      u16 data_size = 0;
      switch (ap_menu.id) {
        case AP_MENU_NONE:
          ap_menu.state = AP_MENU_STATE_NONE;
          ap_menu.last_id = AP_MENU_NONE;
          return;
        case AP_MENU_TOPAUSE:
          ap_menu.id = AP_MENU_NONE;
          if (&bt_pause_ctx) {
            bt_pause_ctx.current_menu = 0;
            bt_pause_ctx.load_state = 1;
            bt_pause_ctx.menu_state = 1;
            bt_pause_ctx.progress1 = 0;
            bt_pause_ctx.progress2 = 0;
            bt_pause_ctx.progress3 = 0;
          }
          return;
        case AP_MENU_TOTOTALS:
          if (&bt_pause_ctx) {
            switch (bt_pause_ctx.menu_state) {
              case 13:
                bt_pause_ctx.menu_state = 1;
                break;
              case 3:
                bt_pause_ctx.menu_state = 6;
                ap_menu.id = AP_MENU_WAITTOTALS;
                break;
            }
          }
          return;
        case AP_MENU_WAITTOTALS:
          if (bt_pause_ctx.pause_state == 2 && bt_pause_ctx.current_menu >= 2 && bt_pause_ctx.menu_state == 3) {
            bt_pause_ctx.menu_state = 6;
            bt_pause_ctx.load_state = 0;
            ap_menu.id = AP_MENU_NONE;
            ap_menu.state = AP_MENU_STATE_NONE;
            ap_menu.last_id = AP_MENU_TOTOTALS;
          }
          return;
        case AP_MENU_UNPAUSE:
          ap_menu.id = AP_MENU_NONE;
          if (&bt_pause_ctx) {
            bt_pause_ctx.current_menu = 0;
            bt_pause_ctx.unpause = 1;
          }
          return;
        case AP_MENU_MAIN:
          ap_menu.columns = 2;
          opt_data = ap_menu_main_data;
          data_size = sizeof(ap_menu_main_data);
          break;
        case AP_MENU_RECEIVED_MOVES_BK:
          ap_menu.columns = 3;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.selected = 0;
          ap_menu.title = "BANJO-KAZOOIE MOVES";
          opt_data = ap_menu_received_moves_bk_data;
          data_size = sizeof(ap_menu_received_moves_bk_data);
          break;
        case AP_MENU_RECEIVED_MOVES_BT:
          ap_menu.columns = 3;
          ap_menu.selected = 0;
          ap_menu.title = "BANJO-TOOIE MOVES";
          if (!ap_menu.page) ap_menu.page = 1;
          ap_menu.page_max = 2;
          switch (ap_menu.page) {
            case 1:
              opt_data = ap_menu_received_moves_bt1_data;
              data_size = sizeof(ap_menu_received_moves_bt1_data);
              break;
            case 2:
              opt_data = ap_menu_received_moves_bt2_data;
              data_size = sizeof(ap_menu_received_moves_bt2_data);
              break;
          }
          ap_menu.last_y = 160;
          ap_menu_page_text(BT_ZOOMBOX_ICON_JIGGYWIGGY);
          ap_menu.last_y = 50;
          break;
        case AP_MENU_RECEIVED_MUMBO_HUMBA:
          ap_menu.columns = 3;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.selected = 0;
          ap_menu.title = "MUMBO AND HUMBA";
          opt_data = ap_menu_received_mumbo_humba_data;
          data_size = sizeof(ap_menu_received_mumbo_humba_data);
          break;
        case AP_MENU_RECEIVED_TRAIN_STATIONS:
          ap_menu.columns = 2;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.selected = 0;
          ap_menu.title = "TRAIN STATIONS AND CHUFFY";
          opt_data = ap_menu_received_train_stations_data;
          data_size = sizeof(ap_menu_received_train_stations_data);
          break;
        case AP_MENU_WORLD_ENTRANCES:
          ap_menu.columns = 2;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.selected = 0;
          ap_menu.title = "WORLD ENTRANCES";
          opt_data = ap_menu_world_entrances_data;
          data_size = sizeof(ap_menu_world_entrances_data);
          ap_menu_update_world_entrances();
          break;
        case AP_MENU_OPTIONS:
          ap_menu.columns = 2;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.title = "OPTIONS";
          opt_data = ap_menu_options_data;
          data_size = sizeof(ap_menu_options_data);
          break;
        case AP_MENU_CHEATS:
          ap_menu.columns = 2;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.title = "CHEATS";
          opt_data = ap_menu_cheats_data;
          data_size = sizeof(ap_menu_cheats_data);
          if (!ap_memory.pc.settings.extra_cheats) data_size -= sizeof(ap_menu_data_t)*4;
          break;
        case AP_MENU_RECEIVED_WARP_SILOS:
          ap_menu.columns = 2;
          ap_menu.last_zb = 1;
          ap_menu.last_y = 60;
          ap_menu.selected = 0;
          ap_menu.title = "WARP SILOS";
          opt_data = ap_menu_received_warp_silos_data;
          data_size = sizeof(ap_menu_received_warp_silos_data);
          if (!ap_memory.pc.settings.randomize_warpsilos) {
            ap_memory.pc.items[AP_ITEM_WARPMT_HUMBA] = bt_flags.mt_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_SILO_JINJO_VILLAGE] = bt_flags.silo_jinjo_village;
            ap_memory.pc.items[AP_ITEM_SILO_WOODED_HOLLOW] = bt_flags.silo_wooded_hollow;
            ap_memory.pc.items[AP_ITEM_SILO_PLATEAU] = bt_flags.silo_plateau;
            ap_memory.pc.items[AP_ITEM_SILO_PINE_GROVE] = bt_flags.silo_pine_grove;
            ap_memory.pc.items[AP_ITEM_SILO_CLIFF_TOP] = bt_flags.silo_cliff_top;
            ap_memory.pc.items[AP_ITEM_SILO_WASTELAND] = bt_flags.silo_wasteland;
            ap_memory.pc.items[AP_ITEM_SILO_QUAGMIRE] = bt_flags.silo_quagmire;
          }
          break;
        case AP_MENU_RECEIVED_WARP_PADS:
          ap_menu.columns = 1;
          ap_menu.selected = 0;
          if (!ap_menu.page) ap_menu.page = 1;
          ap_menu.page_max = 9;
          switch (ap_menu.page) {
            case 1:
              ap_menu.title = "WARP PADS - MT";
              opt_data = ap_menu_received_warp_pads_mt_data;
              data_size = sizeof(ap_menu_received_warp_pads_mt_data);
              break;
            case 2:
              ap_menu.title = "WARP PADS - GGM";
              opt_data = ap_menu_received_warp_pads_ggm_data;
              data_size = sizeof(ap_menu_received_warp_pads_ggm_data);
              break;
            case 3:
              ap_menu.title = "WARP PADS - WW";
              opt_data = ap_menu_received_warp_pads_ww_data;
              data_size = sizeof(ap_menu_received_warp_pads_ww_data);
              break;
            case 4:
              ap_menu.title = "WARP PADS - JRL";
              opt_data = ap_menu_received_warp_pads_jrl_data;
              data_size = sizeof(ap_menu_received_warp_pads_jrl_data);
              break;
            case 5:
              ap_menu.title = "WARP PADS - TDL";
              opt_data = ap_menu_received_warp_pads_tdl_data;
              data_size = sizeof(ap_menu_received_warp_pads_tdl_data);
              break;
            case 6:
              ap_menu.title = "WARP PADS - GI";
              opt_data = ap_menu_received_warp_pads_gi_data;
              data_size = sizeof(ap_menu_received_warp_pads_gi_data);
              break;
            case 7:
              ap_menu.title = "WARP PADS - HFP";
              opt_data = ap_menu_received_warp_pads_hfp_data;
              data_size = sizeof(ap_menu_received_warp_pads_hfp_data);
              break;
            case 8:
              ap_menu.title = "WARP PADS - CCL";
              opt_data = ap_menu_received_warp_pads_ccl_data;
              data_size = sizeof(ap_menu_received_warp_pads_ccl_data);
              break;
            case 9:
              ap_menu.title = "WARP PADS - CK";
              opt_data = ap_menu_received_warp_pads_ck_data;
              data_size = sizeof(ap_menu_received_warp_pads_ck_data);
              break;
          }
          ap_menu.last_y = 165;
          ap_menu_page_text(BT_ZOOMBOX_ICON_JIGGYWIGGY);
          ap_menu.last_y = 50;
          if (!ap_memory.pc.settings.randomize_warppads) {
            ap_memory.pc.items[AP_ITEM_WARPMT_HUMBA] = bt_flags.mt_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_WARPMT_PRISON] = bt_flags.mt_warp_pad_prison_compound;
            ap_memory.pc.items[AP_ITEM_WARPMT_MUMBO] = bt_flags.mt_warp_pad_mumbo;
            ap_memory.pc.items[AP_ITEM_WARPMT_ENTRANCE] = bt_flags.mt_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPMT_KICKBALL] = bt_flags.mt_warp_pad_kickball;
            ap_memory.pc.items[AP_ITEM_WARPGG_TRAIN] = bt_flags.ggm_warp_pad_train_station;
            ap_memory.pc.items[AP_ITEM_WARPGG_CRUSHING] = bt_flags.ggm_warp_pad_crushing_shed;
            ap_memory.pc.items[AP_ITEM_WARPGG_HUMBA] = bt_flags.ggm_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_WARPGG_MUMBO] = bt_flags.ggm_warp_pad_mumbo;
            ap_memory.pc.items[AP_ITEM_WARPGG_ENTRANCE] = bt_flags.ggm_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPWW_BIGTOP] = bt_flags.ww_warp_pad_behind_big_top;
            ap_memory.pc.items[AP_ITEM_WARPWW_ENTRANCE] = bt_flags.ww_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPWW_MUMBO] = bt_flags.ww_warp_pad_mumbo;
            ap_memory.pc.items[AP_ITEM_WARPWW_HUMBA] = bt_flags.ww_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_WARPWW_SPACE] = bt_flags.ww_warp_pad_space;
            ap_memory.pc.items[AP_ITEM_WARPJR_LOCKERS] = bt_flags.jrl_warp_pad_lockers_cavern;
            ap_memory.pc.items[AP_ITEM_WARPJR_BIGFISH] = bt_flags.jrl_warp_pad_big_fish_cavern;
            ap_memory.pc.items[AP_ITEM_WARPJR_SHIP] = bt_flags.jrl_warp_pad_sunken_ship;
            ap_memory.pc.items[AP_ITEM_WARPJR_ATLANTIS] = bt_flags.jrl_warp_pad_atlantis;
            ap_memory.pc.items[AP_ITEM_WARPJR_ENTRANCE] = bt_flags.jrl_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPGI_MUMBO] = bt_flags.gi_floor3_warp_pad_mumbo;
            ap_memory.pc.items[AP_ITEM_WARPGI_HUMBA] = bt_flags.gi_floor2_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_WARPGI_ENTRANCE] = bt_flags.gi_floor1_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPGI_ROOF] = bt_flags.gi_roof_warp_pad;
            ap_memory.pc.items[AP_ITEM_WARPGI_CRUSHER] = bt_flags.gi_floor4_warp_pad_crushers;
            ap_memory.pc.items[AP_ITEM_WARPTD_TOP] = bt_flags.tdl_warp_pad_stomping_plains;
            ap_memory.pc.items[AP_ITEM_WARPTD_HUMBA] = bt_flags.tdl_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_WARPTD_MUMBO] = bt_flags.tdl_warp_pad_mumbo;
            ap_memory.pc.items[AP_ITEM_WARPTD_STOMPING] = bt_flags.tdl_warp_pad_stomping_plains;
            ap_memory.pc.items[AP_ITEM_WARPTD_ENTRANCE] = bt_flags.tdl_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPCC_ENTRANCE] = bt_flags.ccl_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPCC_CENTER] = bt_flags.ccl_warp_pad_center;
            ap_memory.pc.items[AP_ITEM_WARPHF_ICICLE] = bt_flags.hfp_icy_warp_pad_icicle_grotto;
            ap_memory.pc.items[AP_ITEM_WARPHF_HUMBA] = bt_flags.hfp_icy_warp_pad_humba;
            ap_memory.pc.items[AP_ITEM_WARPHF_ICYUPPER] = bt_flags.hfp_icy_warp_pad_upper;
            ap_memory.pc.items[AP_ITEM_WARPHF_LAVAUPPER] = bt_flags.hfp_lava_warp_pad_upper;
            ap_memory.pc.items[AP_ITEM_WARPHF_ENTRANCE] = bt_flags.hfp_lava_warp_pad_entrance;
            ap_memory.pc.items[AP_ITEM_WARPCK_HAG1] = bt_flags.ck_warp_pad_hag1;
            ap_memory.pc.items[AP_ITEM_WARPCK_ENTRANCE] = bt_flags.ck_warp_pad_entrance;
          }
          break;
        default: return;
      }
      ap_menu.state = AP_MENU_STATE_SHOW;
      ap_menu.last_id = ap_menu.id;
      int start_offset = ap_menu.last_zb;
      int i;
      if (zb_data) {
        for (i = 0; i < data_size/sizeof(ap_menu_zb_data_t); i++) {
          ap_menu_zb_data_t* data = &zb_data[i];
          ap_menu_add_entry(data->icon, data->lines, data->text);
        }
      }
      if (opt_data) {
        for (i = 0; i < data_size/sizeof(ap_menu_data_t); i++) {
          ap_menu_zb_data_t* data = &opt_data[i].zb;
          ap_menu_add_entry(data->icon, data->lines, data->text);
        }
      }
      i += start_offset;
      for (; i < sizeof(ap_menu.zoombox)/4; i++) {
        bt_zoombox_t* zb = ap_menu.zoombox[i];
        if (!zb) continue;
        bt_fn_zoombox_close(zb);
      }
      if (ap_menu.selected && ap_menu.zoombox[ap_menu.selected]) bt_fn_zoomboxdata_play_sound(ap_menu.zoombox[ap_menu.selected]->icon);
      break;
    case AP_MENU_STATE_SHOW:
      if (ap_menu.title_y < 20) ap_menu.title_y += 10;
      if (bt_controllers[0].pressed.a) ap_menu_select();
      if (bt_controllers[0].pressed.z && ap_menu.page) {
        ap_menu.page--;
        ap_menu_change_page();
      }
      if (bt_controllers[0].pressed.r && ap_menu.page) {
        ap_menu.page++;
        ap_menu_change_page();
      }
      if (bt_controllers[0].pressed.b) {
        ap_menu.progress = 0xFF;
        ap_menu.state = AP_MENU_STATE_CLEAR;
        switch (ap_menu.id) {
          case AP_MENU_MAIN:
            ap_menu.id = AP_MENU_TOPAUSE;
            break;
          case AP_MENU_WORLD_ENTRANCES:
          case AP_MENU_OPTIONS:
          case AP_MENU_CHEATS:
          case AP_MENU_RECEIVED_MOVES_BK:
          case AP_MENU_RECEIVED_MOVES_BT:
          case AP_MENU_RECEIVED_MUMBO_HUMBA:
          case AP_MENU_RECEIVED_TRAIN_STATIONS:
          case AP_MENU_RECEIVED_WARP_SILOS:
          case AP_MENU_RECEIVED_WARP_PADS:
            ap_menu.id = AP_MENU_MAIN;
            break;
        }
      }
      if (bt_controllers[0].pressed.start) {
        ap_menu.progress = 0xFF;
        ap_menu.state = AP_MENU_STATE_CLEAR;
        ap_menu.id = AP_MENU_UNPAUSE;
      }
      bt_controller_t pad = bt_controllers[0];
      const float deadzone = 0.75;
      if (ap_menu.delay_select) {
        if (
             !pad.held.dup
          && !pad.held.ddown
          && !pad.held.dleft
          && !pad.held.dright
          && (pad.joystick.x < deadzone && pad.joystick.x > -deadzone)
          && (pad.joystick.y < deadzone && pad.joystick.y > -deadzone)
        ) ap_menu.delay_select = 0;
        else ap_menu.delay_select--;
      }
      else if (ap_menu.selected) {
        u8 selected = ap_menu.selected;
        if (ap_menu.columns > 1) {
          if (pad.joystick.x > deadzone) {
            if (selected % ap_menu.columns) selected++;
          }
          if (pad.joystick.x < -deadzone) {
            if ((selected % ap_menu.columns) != 1) selected--;
          }
        }
        if (pad.joystick.y < -deadzone) {
          selected += ap_menu.columns;
        }
        if (pad.joystick.y > deadzone) {
          selected -= ap_menu.columns;
        }
        if (selected && ap_menu.selected != selected && selected < sizeof(ap_menu.zoombox)/4 && ap_menu.zoombox[selected]) {
          ap_menu.selected = selected;
          ap_menu.delay_select = 5 * (ap.smooth_banjo ? 2 : 1);
          if (ap_menu.zoombox[selected]) bt_fn_zoomboxdata_play_sound(ap_menu.zoombox[selected]->icon);
        }
      }
      break;
    case AP_MENU_STATE_CLEAR:
      if (ap_menu.title_y > -20) ap_menu.title_y -= 10;
      break;
  }
  bool empty = true;
  for (int i = 0; i < sizeof(ap_menu.zoombox)/4; i++) {
    bt_zoombox_t* zb = ap_menu.zoombox[i];
    if (!zb) continue;
    empty = false;
    ap_menu_update_zoombox(i, zb);
    if (i && ap_menu.selected) bt_fn_zoombox_selected(zb, ap_menu.selected == i);
    if (ap_menu.progress < i) {
      ap_menu.delay_zb++;
      if (ap_menu.delay_zb == 2) {
        ap_menu.delay_zb = 0;
        ap_menu.progress++;
      }
      break;
    }
    bt_fn_zoombox_update(zb);
    if (ap_menu.state == AP_MENU_STATE_CLEAR) bt_fn_zoombox_close(zb);
    switch (bt_fn_zoombox_state(zb)) {
      case BT_ZOOMBOX_STATE_READY:
        bt_fn_zoombox_open(zb);
        break;
      case BT_ZOOMBOX_STATE_CLOSED:
        bt_fn_zoombox_leave(zb);
        break;
      case BT_ZOOMBOX_STATE_DONE:
        bt_fn_zoombox_free(zb);
        ap_menu.zoombox[i] = 0;
        break;
    }
  }
  if (ap_menu.state == AP_MENU_STATE_CLEAR && empty) ap_menu.state = AP_MENU_STATE_INIT;
}
