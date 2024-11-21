#include "main.h"
#include "dma.h"
#include "usb.h"
#include "save.h"
#include "ap.h"

#include <string.h>
#include <stdlib.h>

main_t main = {0, };

void pre_init() {
  main.is_emulator = io_read(0xA4100010) == 0 ? 1 : 0;
}

void post_init() {
  // allow immediately pressing start to skip title screen
  (*(u8*)0x8012C78D) = 0x40;
  util_inject(UTIL_INJECT_RAW, 0x800D0C24, 0, 0); // dont show amount of notes when collected
  util_inject(UTIL_INJECT_RAW, 0x800D0C44, 0, 0); // dont show amount of jiggies when collected
  usb_init();
}

void pre_loop() {
  usb_check();
}

void post_loop() {
  if (BT_IN_GAME) ap_check();
}

void pre_load_scene(u16 *scene, u16 *exit) {
  if (!BT_IN_GAME && bt_current_map != BT_MAP_FILE_SELECT) return;
  bt_temp_flags.bubble_cutscene = 0;
  bt_flags.ccl_open = ap_memory.pc.items[AP_ITEM_CCA] > 0;
  if (bt_flags.ck_opened_gun_chamber) bt_flags.tower_of_tragedy_completed = 0;
  if (ap_memory.pc.settings.randomize_chuffy && !save_data.custom[bt_save_slot].fake_flags.ggm_defeated_chuffy) {
    bt_flags.train_at_ggm = 1;
    bt_flags.train_at_ioh = 0;
  }
  for (int i = 0; i < AP_MEMORY_EXIT_MAP_MAX; i++) {
    ap_memory_pc_exit_map_t* mapping = &(ap_memory.pc.exit_map[i]);
    if (!mapping->on_map) break;
    if (mapping->on_map != bt_current_map) continue;
    if (mapping->og_map == *scene && mapping->og_exit == *exit) {
      *scene = mapping->to_map;
      *exit = mapping->to_exit;
      break;
    }
  }
  switch (*scene) {
    case BT_MAP_CUTSCENE_OPENING:
      main.new_file = 1;
      *scene = BT_MAP_SPIRAL_MOUNTAIN;
      *exit = 0x0004;
      break;
    case BT_MAP_CUTSCENE_REVIVAL:
      if (bt_current_map == BT_MAP_FILE_SELECT) {
        *scene = BT_MAP_JINJO_VILLAGE;
        *exit = 0x0003;
      }
      else {
        *scene = BT_MAP_CK_GUN_CHAMBER;
        *exit = 0x0001;
      }
      break;
    case BT_MAP_TOT_QUIZ_ROOM:
      if (bt_flags.ck_opened_gun_chamber) bt_flags.tower_of_tragedy_completed = 1;
      break;
    case BT_MAP_TRAIN_STATION_GGM:
      if (ap_memory.pc.settings.randomize_chuffy && !save_data.custom[bt_save_slot].fake_flags.ggm_defeated_chuffy) {
        bt_flags.train_at_ggm = 0;
        bt_flags.train_at_ioh = 1;
      }
      break;
    case BT_MAP_CLOUD_CUCKOOLAND:
      bt_flags.ccl_open = 1; // needed for bubble to spawn
      break;
  }
}

void post_load_scene(u16 scene, u16 exit) {
  BT_FPS = ap.smooth_banjo ? 1 : 2;
}

void pre_load_save() {
}

void post_load_save() {
  if (!BT_IN_GAME && bt_current_map != BT_MAP_FILE_SELECT) return;
  if (main.new_file) {
    main.new_file = 0;
    ap_new_file();
  }
  ap_load_file();
  bt_temp_flags.hag1_phase4_intro = 1;
  bt_temp_flags.hag1_phase3_intro = 1;
  bt_temp_flags.hag1_phase2_intro = 1;
  bt_temp_flags.hag1_quiz_incorrect = 1;
  bt_temp_flags.hag1_quiz_correct = 1;
  bt_temp_flags.hag1_breegull_blaster_intro = 1;
  bt_temp_flags.hag1_quiz_intro = 1;
  bt_temp_flags.hag1_phase1_intro = 1;
  bt_temp_flags.hag1_phase8_intro = 1;
  bt_temp_flags.hag1_phase7_intro = 1;
  bt_temp_flags.hag1_phase6_intro = 1;
  bt_temp_flags.hag1_phase9_intro = 1;
  bt_temp_flags.hag1_phase5_intro = 1;
}

void main_increase_item(u32 _unknown_A0, u16 type, s32 amount) {
  if (type == BT_ITEM_BLUE_EGGS+0x40 && !bt_flags.blue_eggs) return;
  _bt_fn_increase_item(type, amount);
}

void main_train_change_station(u16 station) {
  bt_respawn_point.map = station;
  bt_respawn_point.exit = 2;
  u8 cutscene = 0;
  switch (station) {
    case BT_MAP_TRAIN_STATION_WW:
      if (
           !bt_flags.tdl_missing_dino_on_train
        && !bt_flags.tdl_returned_missing_dino
        && bt_flags.ww_opened_cave_of_horrors_dino
      ) {
        bt_temp_flags.train_cutscene_ww = 1;
        cutscene = 1;
      }
      break;
    case BT_MAP_TRAIN_STATION_TDL:
      if (bt_flags.tdl_sick_dino_on_train || bt_flags.tdl_missing_dino_on_train) {
        bt_temp_flags.train_cutscene_tdl = 1;
        cutscene = 1;
      }
      break;
  }
  if (cutscene) {
    bt_fn_train_cutscene1(0);
    bt_fn_train_cutscene2(station);
    bt_fn_train_cutscene3(BT_MAP_CHUFFYS_CAB);
    bt_fn_train_cutscene4(0x6f);
    bt_fn_train_cutscene5(0);
    return;
  }
  bt_flags.train_at_ggm = 0;
  bt_flags.train_at_ww = 0;
  bt_flags.train_at_ioh = 0;
  bt_flags.train_at_tdl = 0;
  bt_flags.train_at_gi = 0;
  bt_flags.train_at_hfp_lava = 0;
  bt_flags.train_at_hfp_icy = 0;
  u16 dialog = 0;
  switch (station) {
    case BT_MAP_TRAIN_STATION_GGM:
      bt_flags.train_at_ggm = 1;
      dialog = 0x0CF5;
      break;
    case BT_MAP_TRAIN_STATION_WW:
      bt_flags.train_at_ww = 1;
      dialog = 0x0CF6;
      break;
    case BT_MAP_TRAIN_STATION_IOH:
      bt_flags.train_at_ioh = 1;
      dialog = 0x0CFB;
      break;
    case BT_MAP_TRAIN_STATION_TDL:
      bt_flags.train_at_tdl = 1;
      dialog = 0x0CF8;
      break;
    case BT_MAP_TRAIN_STATION_GI:
      bt_flags.train_at_gi = 1;
      dialog = 0x0CF7;
      break;
    case BT_MAP_TRAIN_STATION_HFP_LAVA:
      bt_flags.train_at_hfp_lava = 1;
      dialog = 0x0CF9;
      break;
    case BT_MAP_TRAIN_STATION_HFP_ICY:
      bt_flags.train_at_hfp_icy = 1;
      dialog = 0x0CFA;
      break;
  }
  main.override_text = 1;
  if (bt_fn_load_dialog(dialog, 0xF, 0, 0)) bt_dialog.callbackPtr = 0;
  else main.override_text = 0;
}

void main_train_summon(u32 _unknown_A0, u16 from, u16 to) {
  switch (to) {
    case BT_MAP_TRAIN_STATION_GGM:
      bt_temp_flags.train_cutscene_ggm = 1;
      break;
    case BT_MAP_TRAIN_STATION_WW:
      bt_temp_flags.train_cutscene_ww = 1;
      break;
    case BT_MAP_TRAIN_STATION_IOH:
      bt_temp_flags.train_cutscene_ioh = 1;
      break;
    case BT_MAP_TRAIN_STATION_TDL:
      bt_temp_flags.train_cutscene_tdl = 1;
      break;
    case BT_MAP_TRAIN_STATION_GI:
      bt_temp_flags.train_cutscene_gi = 1;
      break;
    case BT_MAP_TRAIN_STATION_HFP_LAVA:
      bt_temp_flags.train_cutscene_hfp_lava = 1;
      break;
    case BT_MAP_TRAIN_STATION_HFP_ICY:
      bt_temp_flags.train_cutscene_hfp_icy = 1;
      break;
  }
  bt_fn_train_cutscene1(0);
  bt_fn_train_cutscene2(from);
  bt_fn_train_cutscene3(to);
  bt_fn_train_cutscene4(0x72);
  bt_fn_train_cutscene5(0);
  bt_fn_load_scene(to, 0, 0);
}

extern void main_bt_paused_displaced(u32 _unknown, u8 is_paused);
void main_bt_paused(u32 _unknown, u8 is_paused) {
  if (bt_save_slot > 2) return;
  if (is_paused) {
    bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].position = BT_UI_NUMBER_POSITION_SHARED_BOTTOM_LEFT_LOWER;
    bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].icon = BT_UI_ICONS_MINGY_JONGO;
    bt_fn_ui_show_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER, save_data.custom[bt_save_slot].totals.mumbo_tokens, 0);
  }
  else {
    bt_fn_ui_hide_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER);
  }
}

extern void main_bt_file_select_cursor_displaced(bt_obj_file_select_ctx_t* ctx, u8 operation, u8 selected);
u8 main_bt_file_select_cursor(bt_obj_file_select_ctx_t* ctx, u8 operation, u8 selected) {
  switch (operation) {
    case 0x07: // select
      switch (selected) {
        case 0:
        case 1:
        case 2:
          switch (ctx->cursor_state) {
            case 0x04: // normal
              u32 pc_seed = ap_memory.pc.settings.seed;
              u32* n64_seed = &save_data.custom[selected].seed;
              if (pc_seed == 0 || (pc_seed != *n64_seed && *n64_seed != 0)) {
                if (!(bt_controllers[0].held.l && bt_controllers[0].held.r)) return 0;
              }
              *n64_seed = pc_seed;
              break;
            case 0x0C: // copy
              if (ctx->operation_state == 2) {
                if (ctx->block_selection) break;
                // copy custom save data
                u8* from = (u8*)&(save_data.custom[ctx->selection1]);
                u8* to = (u8*)&(save_data.custom[ctx->selection2]);
                for (int i = 0; i < sizeof(save_data.custom[ctx->selection2]); i++) to[i] = from[i];
              }
              break;
            case 0x10: // delete
              if (ctx->operation_state == 1) {
                if (ctx->block_selection) break;
                // delete custom save data
                u8* data = (u8*)&(save_data.custom[ctx->selection1]);
                for (int i = 0; i < sizeof(save_data.custom[ctx->selection1]); i++) data[i] = 0;
              }
              break;
          }
          break;
      }
      break;
  }
  return 1;
}

extern void main_bt_file_select_bottom_text_displaced(char* text, u16 dialog_id, u8 id);
u8 main_bt_file_select_bottom_text(char* text, u16 dialog_id, u8 id) {
  if (dialog_id != 0x18F3) return 1;
  switch (id) {
    case 0:
      if (ap_memory.pc.settings.seed == 0) strcpy(text, "BTCLIENT DISCONNECTED.");
      else strcpy(text, "BTCLIENT READY.");
      return 0;
    case 2:
    case 3: {
      u8 slot = bt_save_slot == 0xFF ? 0 : bt_save_slot;
      u8 jiggies = save_data.custom[slot].totals.jiggies;
      strcpy(text, "JIGGIES: ");
      text = itoa(jiggies, text+9, 10);
      for (; *text != 0; text++);
      if (ap_memory.pc.settings.seed != save_data.custom[slot].seed) strcpy(text, ", SEED: WRONG");
      else strcpy(text, ", SEED: MATCH");
      return 0;
    }
  }
  return 1;
}

void pre_object_init(bt_object_t *obj) {
  if (!BT_IN_GAME && bt_current_map != BT_MAP_FILE_SELECT) return;
  switch (obj->objType) {
    case BT_OBJ_PAGE:
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0234, 0, 0); // dont increment amount
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0270, 0, 0); // dont comment on first 5 page milestone
      break;
    case BT_OBJ_GLOWBO:
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0A88, 0, 0); // dont increment amount
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0A60, 0, 0); // dont increment mega glowbo amount
      break;
    case BT_OBJ_JINJO:
      // prevent collecting jinjos from giving a jiggy by convincing them that they always have 0 in their family
      util_inject(UTIL_INJECT_RETVALUE, (u32)obj + 0x01E4, 0, 0);
      util_inject(UTIL_INJECT_RETVALUE, (u32)obj + 0x0F0C, 0, 0);
      util_inject(UTIL_INJECT_RETVALUE, (u32)obj + 0x1240, 0, 0);

      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0F2C, 0, 0); // dont show amount collected
      break;
    case BT_OBJ_HONEYCOMB_PIECE:
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0100, 0, 0); // dont increment amount
      break;
    case BT_OBJ_DOUBLOON:
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x027C, 0, 0); // dont increment amount
      break;
    case BT_OBJ_NESTS:
      // egg nests
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0388, (u32)main_increase_item, 0); // prevent receiving blue eggs if you dont have them
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0CB8, (u32)save_has_egg_type, 0); // fix egg nests hanging the game with no eggs
      break;
    case BT_OBJ_MOVE_SILO:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0440, (u32)save_fake_has_move, 0); // called when close enough for note count to show
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0E0C, (u32)save_fake_has_move, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0EFC, (u32)save_fake_has_move, 0); // called on scene init and when nearby
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1048, (u32)save_fake_has_move, 0); // called on dialog start
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x111C, (u32)save_fake_has_move, 0); // called on dialog start if wrong character
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1B58, (u32)save_fake_has_move, 0);

      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1D98, (u32)save_fake_set_move, 0); // called when taught move
      break;
    case BT_OBJ_SWITCH:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x026C, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x048C, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x06B8, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0754, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x08CC, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0920, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0A28, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0B04, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0B94, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0DC8, (u32)save_fake_get_bit, 0);

      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0338, (u32)save_fake_set_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x059C, (u32)save_fake_set_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0ACC, (u32)save_fake_set_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0CEC, (u32)save_fake_set_bit, 0);
      break;
    case BT_OBJ_ROYSTEN:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x00E0, (u32)save_fake_get_bit, 0);

      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x05FC, (u32)save_fake_give_fast_swimming, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0640, (u32)save_fake_give_bubbles, 0);
      break;
    case BT_OBJ_BOTTLES_FAMILY:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x09BC, (u32)save_fake_give_move, 0);
      break;
    case BT_OBJ_BARGASAURUS:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x02A4, (u32)save_fake_give_move, 0);
      break;
    case BT_OBJ_TRAIN_SIGN:
      util_inject(UTIL_INJECT_JUMP    , (u32)obj + 0x032C, (u32)main_train_summon, 1);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0250, (u32)save_fake_get_bit, 0); // defeated chuffy
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0450, (u32)save_fake_get_bit, 0); // levitated train
      break;
    case BT_OBJ_BK_CART:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x010C, (u32)save_fake_get_bit, 0); // used ice key
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x00FC, (u32)save_fake_count_item, 0); // get opened_mega_glowbo
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0130, (u32)save_fake_get_bit, 0); // collected blue egg
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0140, (u32)save_fake_get_bit, 0); // hatched blue egg
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0164, (u32)save_fake_get_bit, 0); // collected pink egg
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0174, (u32)save_fake_get_bit, 0); // hatched pink egg
      break;
    case BT_OBJ_MYSTERY_EGGS:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0478, (u32)save_fake_set_bit, 0); // collected blue egg
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0488, (u32)save_fake_set_bit, 0); // collected pink egg

      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x04B0, 0, 0); // prevent increasing inventory count
      break;
    case BT_OBJ_ICE_KEY:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x009C, (u32)save_fake_give_item, 0); // set opened_mega_glowbo instead
      break;
    case BT_OBJ_HEGGY:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1624, (u32)save_fake_give_homing_eggs, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x199C, (u32)save_fake_give_homing_eggs, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x165C, (u32)save_fake_give_breegull_bash, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x19BC, (u32)save_fake_give_breegull_bash, 0);
      break;
    case BT_OBJ_JIGGYWIGGY_TEMPLE:
      if (!ap_memory.pc.settings.skip_puzzles) break;
      util_inject(UTIL_INJECT_RETVALUE, (u32)obj + 0x0120, 999, 0); // show 999 jiggies required
      util_inject(UTIL_INJECT_RETVALUE, (u32)obj + 0x01C4, 0xFFFF, 0); // always show 'true disciple' dialog
      break;
    case BT_OBJ_JIGGYWIGGY_INFO:
      if (!ap_memory.pc.settings.skip_puzzles) break;
      util_inject(UTIL_INJECT_JUMP    , (u32)obj + 0x0214, (u32)save_worlds_jiggy_requirment, 0);
      break;
    case BT_OBJ_JIGGYWIGGY_POST:
      if (!ap_memory.pc.settings.skip_puzzles) break;
      util_inject(UTIL_INJECT_RETVALUE, (u32)obj + 0x0254, 0, 0); // only show jiggy requirement dialog
      break;
    case BT_OBJ_PAUSE_MENU:
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x1CFC, 0, 0); // allow totals to show 0, fixes ui getting stuck onscreen
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0FE0, (u32)main_bt_paused_displaced, 1); // run our function while at main pause menu
      break;
    case BT_OBJ_CAPTAIN_BLACKEYE:
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0D74, 0, 0); // prevent giving 2 doubloons
      break;
    case BT_OBJ_FILE_SELECT:
      // allow refusing selection
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0828, 0x001F0821, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x082C, (u32)main_bt_file_select_cursor_displaced, 1);

      // custom banjo text
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x4494, 0x001F0821, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x4498, (u32)main_bt_file_select_bottom_text_displaced, 1);
      break;
  }
}

void post_object_init(bt_object_t *obj) {
  if (!BT_IN_GAME) return;
  switch (obj->objType) {
    case BT_OBJ_CHUFFY_CABIN:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0668, (u32)main_train_change_station, 0);
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x066C, 0x86040000, 0);
      util_inject(UTIL_INJECT_BRANCH  , (u32)obj + 0x0670, 0x6C, 1);
      break;
  }
}

void pre_load_data(u16 *id) {

}

void post_load_data(u16 id, u32 addr) {
  if (!BT_IN_GAME) return;
  switch (id) {
    case 0x0D8C: // jamjar's clockwork tutorial text
      if (ap_memory.n64.misc.show_text != ap_memory.pc.misc.show_text) {
        bt_dialog_data_t* data = (bt_dialog_data_t*)addr;
        strcpy(data->text, ap_memory.pc.misc.text);
      }
      break;
    // train locations
    case 0x0CF5: // GGM
    case 0x0CF6: // WW
    case 0x0CFB: // IoH
    case 0x0CF8: // TDL
    case 0x0CF7: // GI
    case 0x0CF9: // HFP lava
    case 0x0CFA: // HFP lava
      if (main.override_text) {
        main.override_text = 0;
        bt_dialog_data_t* data = (bt_dialog_data_t*)addr;
        (*(u8*)(data->text+data->size)) = 0x05; // prevent waiting for next dialog
      }
      break;
    case 0x1506: { // jiggywiggy disciple - you must collect jiggies
      if (!ap_memory.pc.settings.skip_puzzles) break;
      bt_dialog_data_t* data = (bt_dialog_data_t*)addr;
      strcpy(data->text+ 1, "WHAT'S THAT I SEE IN YOUR YAML? 'SKIP PUZZLES' IS ENABLED?");
      break;
    }
    case 0x1509: { // jiggywiggy disciple - true disciple
      if (!ap_memory.pc.settings.skip_puzzles) break;
      bt_dialog_data_t* data = (bt_dialog_data_t*)addr;
      strcpy(data->text+ 1, "SORRY, BUT THE GREAT JIGGYWIGGY IS IN A DIFFERENT TEMPLE.");
      break;
    }
  }
}
