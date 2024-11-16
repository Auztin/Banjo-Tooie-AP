#include "main.h"
#include "dma.h"
#include "usb.h"
#include "save.h"
#include "ap.h"

#include <string.h>

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
  bt_temp_flags.bubble_cutscene = 0;
  if (ap_memory.pc.settings.skip_tower_of_tragedy) bt_flags.tower_of_tragedy_completed = 0;
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
      if (ap_memory.pc.settings.skip_tower_of_tragedy) { // should only be possible if you save & quit in the ToT quiz room
        *scene = BT_MAP_JINJO_VILLAGE;
        *exit = 0x0003;
      }
      break;
    case BT_MAP_TOT_QUIZ_ROOM:
      if (ap_memory.pc.settings.skip_tower_of_tragedy) bt_flags.tower_of_tragedy_completed = 1;
      break;
    case BT_MAP_TRAIN_STATION_GGM:
      if (ap_memory.pc.settings.randomize_chuffy && !save_data.custom[bt_save_slot].fake_flags.ggm_defeated_chuffy) {
        bt_flags.train_at_ggm = 0;
        bt_flags.train_at_ioh = 1;
      }
      break;
  }
}

void post_load_scene(u16 scene, u16 exit) {
  BT_FPS = ap.smooth_banjo ? 1 : 2;
}

void pre_load_save() {
}

void post_load_save() {
  if (main.new_file) {
    main.new_file = 0;
    ap_new_file();

    // clear custom save data
    u8* data = (u8*)&(save_data.custom[bt_save_slot]);
    for (int i = 0; i < sizeof(save_data.custom[bt_save_slot]); i++) data[i] = 0;
  }
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

void pre_object_init(bt_object_t *obj) {

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

void post_object_init(bt_object_t *obj) {
  if (!BT_IN_GAME) return;
  switch (obj->objType) {
    case BT_OBJ_PAGE:
      util_inject(UTIL_INJECT_RAW     , obj->objPointers[ 0] + 0x01C4, 0, 0); // dont increment amount
      break;
    case BT_OBJ_GLOWBO:
      util_inject(UTIL_INJECT_RAW     , obj->objPointer      + 0x0968, 0, 0); // dont increment amount
      break;
    case BT_OBJ_JINJO:
      // prevent collecting jinjos from giving a jiggy by convincing them that they always have 0 in their family
      util_inject(UTIL_INJECT_RETVALUE, obj->objPointer      + 0x0084, 0, 0);
      util_inject(UTIL_INJECT_RETVALUE, obj->objPointers[ 4] + 0x01CC, 0, 0);
      util_inject(UTIL_INJECT_RETVALUE, obj->objPointers[ 4] + 0x0500, 0, 0);

      util_inject(UTIL_INJECT_RAW     , obj->objPointers[ 4] + 0x01EC, 0, 0); // dont show amount collected
      break;
    case BT_OBJ_HONEYCOMB_PIECE:
      util_inject(UTIL_INJECT_RAW     , obj->objPointer      + 0x0090, 0, 0); // dont increment amount
      break;
    case BT_OBJ_DOUBLOON:
      util_inject(UTIL_INJECT_RAW     , obj->objPointers[ 1] + 0x0198, 0, 0); // dont increment amount
      break;
    case BT_OBJ_NESTS:
      // egg nests
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x01D8, (u32)main_increase_item, 0); // prevent receiving blue eggs if you dont have them
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0B08, (u32)save_has_egg_type, 0); // fix egg nests hanging the game with no eggs
      break;
    case BT_OBJ_MOVE_SILO:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 1] + 0x0058, (u32)save_fake_has_move, 0); // called when close enough for note count to show
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 3] + 0x03FC, (u32)save_fake_has_move, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 4] + 0x007C, (u32)save_fake_has_move, 0); // called on scene init and when nearby
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 4] + 0x01C8, (u32)save_fake_has_move, 0); // called on dialog start
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 4] + 0x029C, (u32)save_fake_has_move, 0); // called on dialog start if wrong character
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[16] + 0x0094, (u32)save_fake_has_move, 0);

      // called when taught move
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[16] + 0x02D4, (u32)save_fake_set_move, 0);
      break;
    case BT_OBJ_SWITCH:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 3] + 0x0010, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 5] + 0x00A4, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 7] + 0x0014, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 9] + 0x001C, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[10] + 0x00C0, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[10] + 0x0114, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[10] + 0x021C, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[11] + 0x008C, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[12] + 0x0014, (u32)save_fake_get_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[14] + 0x0014, (u32)save_fake_get_bit, 0);

      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 4] + 0x0084, (u32)save_fake_set_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 6] + 0x00A8, (u32)save_fake_set_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[11] + 0x0054, (u32)save_fake_set_bit, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[13] + 0x00EC, (u32)save_fake_set_bit, 0);
      break;
    case BT_OBJ_ROYSTEN:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0010, (u32)save_fake_get_bit, 0);

      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x052C, (u32)save_fake_give_fast_swimming, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0570, (u32)save_fake_give_bubbles, 0);
      break;
    case BT_OBJ_BOTTLES_FAMILY:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointers[ 2] + 0x08A4, (u32)save_fake_give_move, 0);
      break;
    case BT_OBJ_BARGASAURUS:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0234, (u32)save_fake_give_move, 0);
      break;
    case BT_OBJ_CHUFFY_CABIN:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0598, (u32)main_train_change_station, 0);
      util_inject(UTIL_INJECT_RAW     , obj->objPointer      + 0x059C, 0x86040000, 0);
      util_inject(UTIL_INJECT_BRANCH  , obj->objPointer      + 0x05A0, 0x6C, 1);
      break;
    case BT_OBJ_TRAIN_SIGN:
      util_inject(UTIL_INJECT_JUMP    , obj->objPointer      + 0x025C, (u32)main_train_summon, 1);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0180, (u32)save_fake_get_bit, 0); // defeated chuffy
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0380, (u32)save_fake_get_bit, 0); // levitated train
      break;
    case BT_OBJ_BK_CART:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x003C, (u32)save_fake_count_item, 0); // get opened_mega_glowbo
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x004C, (u32)save_fake_get_bit, 0); // used ice key
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0070, (u32)save_fake_get_bit, 0); // collected blue egg
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0080, (u32)save_fake_get_bit, 0); // hatched blue egg
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x00A4, (u32)save_fake_get_bit, 0); // collected pink egg
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x00B4, (u32)save_fake_get_bit, 0); // hatched pink egg
      break;
    case BT_OBJ_MYSTERY_EGGS:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0408, (u32)save_fake_set_bit, 0); // collected blue egg
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x0418, (u32)save_fake_set_bit, 0); // collected pink egg

      util_inject(UTIL_INJECT_RAW     , obj->objPointer      + 0x0440, 0, 0); // prevent increasing inventory count
      break;
    case BT_OBJ_ICE_KEY:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x003C, (u32)save_fake_give_item, 0); // set opened_mega_glowbo instead
      break;
    case BT_OBJ_HEGGY:
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x1444, (u32)save_fake_give_homing_eggs, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x17BC, (u32)save_fake_give_homing_eggs, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x147C, (u32)save_fake_give_breegull_bash, 0);
      util_inject(UTIL_INJECT_FUNCTION, obj->objPointer      + 0x17DC, (u32)save_fake_give_breegull_bash, 0);
      break;
    case BT_OBJ_JIGGYWIGGY_TEMPLE:
      if (!ap_memory.pc.settings.skip_puzzles) break;
      util_inject(UTIL_INJECT_RETVALUE, obj->objPointer      + 0x0080, 999, 0); // show 999 jiggies required
      util_inject(UTIL_INJECT_RETVALUE, obj->objPointer      + 0x0124, 0xFFFF, 0); // always show 'true disciple' dialog
      break;
    case BT_OBJ_JIGGYWIGGY_INFO:
      if (!ap_memory.pc.settings.skip_puzzles) break;
      util_inject(UTIL_INJECT_JUMP    , obj->objPointers[ 2]         , (u32)save_worlds_jiggy_requirment, 0);
      break;
    case BT_OBJ_JIGGYWIGGY_POST:
      if (!ap_memory.pc.settings.skip_puzzles) break;
      util_inject(UTIL_INJECT_RETVALUE, obj->objPointer      + 0x01F4, 0, 0); // only show jiggy requirement dialog
      break;
    case BT_OBJ_PAUSE_MENU:
      util_inject(UTIL_INJECT_RAW     , obj->objPointers[ 4] + 0x1364, 0, 0); // allow totals to show 0, fixes ui getting stuck onscreen
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
      strcpy(data->text+ 1, "WHAT'S THAT I SEE IN YOUR YAML? 'SKIP PUZLES' IS ENABLED?");
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
