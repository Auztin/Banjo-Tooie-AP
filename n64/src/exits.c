#include "exits.h"
#include "save.h"
#include "ap.h"
#include <string.h>

char* exits_item_names(int id) {
  switch (id) {
    case AP_ITEM_GGRAB: return "GRIP GRAB";
    case AP_ITEM_BBLASTER: return "BREEGULL BLASTER";
    case AP_ITEM_EGGAIM: return "EGG AIMING";
    case AP_ITEM_BDRILL: return "BILL DRILL";
    case AP_ITEM_BBAYONET: return "BEAK BAYONET";
    case AP_ITEM_AIREAIM: return "AIR AIMING";
    case AP_ITEM_SPLITUP: return "SPLIT UP";
    case AP_ITEM_WWHACK: return "WING WHACK";
    case AP_ITEM_TTORP: return "TALON TORPEDO";
    case AP_ITEM_AUQAIM: return "AQUA AIMING";
    case AP_ITEM_SHPACK: return "SHACK PACK";
    case AP_ITEM_GLIDE: return "GLIDE";
    case AP_ITEM_SNPACK: return "SNOOZE PACK";
    case AP_ITEM_LSPRING: return "LEG SPRING";
    case AP_ITEM_CLAWBTS: return "CLAW CLAMBER BOOTS";
    case AP_ITEM_SPRINGB: return "SPRINGY STEP SHOES";
    case AP_ITEM_TAXPACK: return "TAXI PACK";
    case AP_ITEM_HATCH: return "HATCH";
    case AP_ITEM_PACKWH: return "PACK WHACK";
    case AP_ITEM_SAPACK: return "SACK PACK";
    case AP_ITEM_FEGGS: return "FIRE EGGS";
    case AP_ITEM_GEGGS: return "GRENADE EGGS";
    case AP_ITEM_CEGGS: return "CLOCKWORK KAZOOIE EGGS";
    case AP_ITEM_IEGGS: return "ICE EGGS";
    case AP_ITEM_FSWIM: return "FAST SWIMMING";
    case AP_ITEM_DAIR: return "EXTRA BUBBLES";
    case AP_ITEM_BBASH: return "BREGULL BASH";
    case AP_ITEM_AMAZEOGAZE: return "AMAZE O GAZE";
    case AP_ITEM_ROAR: return "BABY DINO ROAR";
    case AP_ITEM_DIVE: return "DIVE";
    case AP_ITEM_FPAD: return "FLIGHT PAD";
    case AP_ITEM_GRAT: return "GROUND RAT A TAT";
    case AP_ITEM_ROLL: return "ROLL";
    case AP_ITEM_ARAT: return "AIR RAT A TAT";
    case AP_ITEM_BBARGE: return "BEAK BARGE";
    case AP_ITEM_TJUMP: return "TALL JUMP";
    case AP_ITEM_FLUTTER: return "FLUTTER";
    case AP_ITEM_FFLIP: return "FLAP FLIP";
    case AP_ITEM_CLIMB: return "CLIMB";
    case AP_ITEM_BEGGS: return "BLUE EGGS";
    case AP_ITEM_TTROT: return "TALON TROT";
    case AP_ITEM_BBUST: return "BEAK BUSTER";
    case AP_ITEM_WWING: return "WONDERWING";
    case AP_ITEM_SSTRIDE: return "STILT STRIDE BOOTS";
    case AP_ITEM_TTRAIN: return "TURBO TRAINERS";
    case AP_ITEM_BBOMB: return "BEAK BOMB";
    case AP_ITEM_EGGSHOOT: return "EGG SHOOTING";
    default: return "AN UNKNOWN ITEM";
  }
}

u32 exits_can_pass(u16* scene, u16* exit, u16* current_map) {
  if (!current_map) current_map = &bt_current_map;
  enum {
    VANILLA,
    PARTIAL_ALLOW = 0x0024, // still checks transform/split up
    ALLOW = 0x080C, // allows anything
    REFUSE = 0x0528,
  };
  u32 ret = VANILLA;
  for (int i = 0; i < AP_MEMORY_EXIT_MAP_MAX; i++) {
    ap_memory_pc_exit_map_t* mapping = &(ap_memory.pc.exit_map[i]);
    if (!mapping->on_map) break;
    if (mapping->on_map != *current_map) continue;
    if (mapping->og_map == *scene && mapping->og_exit == *exit) {
      switch ((*scene << 8) | *exit) {
        case (BT_MAP_TDL                     << 8) | 20:
        case (BT_MAP_TDL_TERRYS_NEST         << 8) |  2:
        case (BT_MAP_TDL_TERRYS_NEST         << 8) |  5:
        case (BT_MAP_TDL_INSIDE_THE_MOUNTAIN << 8) |  4:
          if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO) goto end_loop;
        default:
          *scene = mapping->to_map;
          *exit = mapping->to_exit;
      }
      u8 missing[15];
      int n = 0;
      for (int i = 0; i <= AP_ITEM_EGGSHOOT; i++) {
        if (
          n < sizeof(missing)
          && save_custom_get_bit(mapping->access_rules, i)
          && !ap_memory.pc.items[i]
        ) missing[n++] = i;
      }
      if (n) {
        if (!ap.internal_message[0] && !ap.message[0]) {
          ap.internal_icon = BT_ZOOMBOX_ICON_JAMJARS;
          strcpy(ap.internal_message, "YOU ARE MISSING ");
          for (int i = 0; i < n; i++) {
            strcat(ap.internal_message, exits_item_names(missing[i]));
            if (n == 1) strcat(ap.internal_message, "!");
            else if (i + 1 == n) strcat(ap.internal_message, "!");
            else if (i + 2 == n) strcat(ap.internal_message, " AND ");
            else strcat(ap.internal_message, ", ");
          }
        }
        return REFUSE;
      }
      if (*scene == BT_MAP_CHUFFYS_CAB && !bt_flags.ggm_mumbo_train) {
        if (!ap.internal_message[0] && !ap.message[0]) {
          ap.internal_icon = BT_ZOOMBOX_ICON_OLD_KING_COAL;
          strcpy(ap.internal_message, "YOU CAN'T ENTER THE CHUFFIN' TRAIN WHILE IT'S DERAILED!");
        }
        return REFUSE;
      }
      ret = bt_player_chars.control_type == BT_PLAYER_CHAR_BREEGULL_BLASTER ? ALLOW : PARTIAL_ALLOW;
      break;
    }
  }
  end_loop:
  switch (*scene) {
    case BT_MAP_DIGGER_TUNNEL:
      if (
        bt_flags.ioh_defeated_klungo1
        && (
          !ap_memory.pc.settings.randomize_nests
          || save_custom_get_bit(bt_custom_save.nests, 0x019)
        )
      ) {
        u16 map = *scene;
        if (*exit == 1) {
          *scene = BT_MAP_JV;
          *exit = 3;
        }
        else {
          *scene = BT_MAP_SM;
          *exit = 3;
        }
        return exits_can_pass(scene, exit, &map);
      }
      if (ret == VANILLA) ret = PARTIAL_ALLOW;
      break;
    case BT_MAP_ANOTHER_DIGGER_TUNNEL:
      if (
        bt_flags.ioh_defeated_klungo2
        && (
          !ap_memory.pc.settings.randomize_nests
          || (save_custom_get_bit(bt_custom_save.nests, 0x051) && save_custom_get_bit(bt_custom_save.nests, 0x052))
        )
      ) {
        u16 map = *scene;
        if (*exit == 1) {
          *scene = BT_MAP_IOH_WL;
          *exit = 3;
        }
        else {
          *scene = BT_MAP_IOH_PG;
          *exit = 1;
        }
        return exits_can_pass(scene, exit, &map);
      }
      if (ret == VANILLA) ret = PARTIAL_ALLOW;
      break;
    case BT_MAP_CCL:
      if (bt_flags.ccl_mumbo_location == 1) {
        switch (*exit) {
          case 0x09:
            *exit = 0x16;
            break;
          case 0x16:
            *exit = 0x09;
            break;
        }
      }
      break;
    case BT_MAP_SEA_BOTTOM:
      if (ret != VANILLA && *exit == 0x28) {
        if (!bt_flags.jrl_locker_names) {
          u32 v;
          while (!(v = bt_fn_random() & 0xF) || v >= 0xA) bt_fn_save_set_bits(0x39F, bt_fn_random() & 0x1F, 5);
          bt_fn_save_set_bits(0x3A4, v, 4);
        }
        const static u8 exits[] = {0x28, 0x16, 0x23, 0x28, 0x17, 0x13, 0x24, 0x25, 0x15, 0x14};
        *exit = exits[bt_fn_save_get_bits(0x3A4, 4)];
      }
      break;
  }
  return ret;
}

u32 exits_check(bt_exit_info_t* info) {
  switch (info->type) {
    case 3:
      if (info->scene == 4) {
        u32 scene;
        u32 exit;
        bt_fn_mt_get_sacred_chamber(info, &scene, &exit);
        info->type = 5;
        info->check_type = 0;
        info->scene = scene - 0xA0;
        info->exit = exit;
      }
      break;
    case 5:
      if (info->check_type == 0x0C) {
        info->check_type = 0;
        check_mumbo_location:
        switch (bt_flags.ccl_mumbo_location) {
          case 1:
            if (bt_current_map == BT_MAP_CCL) {
              if (info->scene == 0x9F) info->scene--;
              else info->scene++;
            }
            break;
          case 3: break;
          default:
            bt_flags.ccl_mumbo_location = (bt_fn_random() % 2) ? 1 : 3;
            goto check_mumbo_location;
        }
      }
      break;
  }
  return info->type;
}

void exits_ccl_bubble(u16 scene, u16 exit) {
  exits_can_pass(&scene, &exit, 0);
  bt_fn_load_scene_ccl_bubble(scene, exit);
}
