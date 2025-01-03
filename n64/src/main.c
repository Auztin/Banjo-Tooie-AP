#include "main.h"
#include "dma.h"
#include "usb.h"
#include "save.h"
#include "ap.h"
#include "ap_menu.h"
#include "custom_flags/all.h"

#include <string.h>
#include <stdlib.h>

main_t main = {0, };

void pre_init() {
  main.is_emulator = io_read(0xA4100010) == 0 ? 1 : 0;
  ap.trap_type = AP_TRAP_MAX;
}

void post_init() {
  // allow immediately pressing start to skip title screen if version matches
  if (AP_VERSION.as_int == save_data.version) BT_TITLE_SCREEN = 0x40;

  util_inject(UTIL_INJECT_RAW , 0x800D0C24, 0, 0); // dont show amount of notes when collected
  util_inject(UTIL_INJECT_RAW , 0x800D0C44, 0, 0); // dont show amount of jiggies when collected
  util_inject(UTIL_INJECT_JUMP, 0x800A1718, (u32)ap_get_health, 1); // always return 2 health while trapping
  util_inject(UTIL_INJECT_JUMP, 0x800A17A8, (u32)ap_increase_health, 1); // prevent decreasing health while trapping
  util_inject(UTIL_INJECT_JUMP, 0x80096628, (u32)ap_ground_info, 1); // allow slipping on any surface
  usb_init();
  main.zb_credits[0] = bt_fn_zoombox_new(50, BT_ZOOMBOX_ICON_BANJO, 0, 1);
  main.zb_credits[1] = bt_fn_zoombox_new(160, BT_ZOOMBOX_ICON_KAZOOIE, 0, 0);
  for (int i = 0; i < 2; i++) {
    bt_zoombox_t* zb = main.zb_credits[i];
    bt_fn_zoombox_init(zb);
    bt_fn_zoombox_text_speed(zb, 30);
    bt_fn_zoombox_background_speed(zb, 0.15);
  }
}

void pre_draw_objects(u8 type, bt_draw_ctx_t* draw_ctx) {

}

void post_draw_objects(u8 type, bt_draw_ctx_t* draw_ctx) {

}

void pre_draw_hud(bt_draw_ctx_t* draw_ctx) {

}

struct main_credit_lines_t {
  s16 icon;
  char name[20];
} main_credit_lines[] = {
  {.icon=BT_ZOOMBOX_ICON_KAZOOIE_HIGH_PITCHED, .name="G0GOTBC..."},
  {.icon=BT_ZOOMBOX_ICON_BOGGY, .name="FHNNHF..."},
  {.icon=BT_ZOOMBOX_ICON_EVIL_BOTTLES, .name="AUSTIN..."},
  {.icon=BT_ZOOMBOX_ICON_CANARY_MARY, .name="UNALIVE..."},
  {.icon=BT_ZOOMBOX_ICON_SAFE, .name="OZONE..."},
  {.icon=BT_ZOOMBOX_ICON_WELDAR, .name="AND JJJJ12212   "},
};

void post_draw_hud(bt_draw_ctx_t* draw_ctx) {
  ap_draw_hud(draw_ctx);
  ap_menu_draw(draw_ctx);
  if (bt_current_map == BT_MAP_TITLE_SCREEN) {
    if (bt_controllers[0].held.dup && bt_controllers[0].held.r && bt_controllers[0].pressed.start) BT_TITLE_SCREEN = 0x40;
    char version[10] = "V";
    char major[3];
    char minor[3];
    char patch[3];
    itoa(AP_VERSION_MAJOR, major, 10);
    itoa(AP_VERSION_MINOR, minor, 10);
    itoa(AP_VERSION_PATCH, patch, 10);
    strcat(version, major);
    strcat(version, ".");
    strcat(version, minor);
    if (AP_VERSION_PATCH) {
      strcat(version, ".");
      strcat(version, patch);
    }
    bt_fn_text_reset_options();
    bt_text_options.appearance = BT_TEXT_TEXTURE_GOLD;
    bt_text_options.size = 0.70;
    bt_fn_text_big_draw(draw_ctx, 20, 215, version);
    for (int i = 0; i < 2; i++) {
      bt_zoombox_t* zb = main.zb_credits[i];
      if (!zb) continue;
      bt_fn_zoombox_update(zb);
      bt_fn_zoombox_draw(zb, draw_ctx);
      switch (bt_fn_zoombox_state(zb)) {
        case BT_ZOOMBOX_STATE_READY:
          switch (main.credits_state) {
            case 0:
              if (i) {
                bt_fn_zoombox_open(zb);
                bt_fn_zoombox_append_text(zb, "HEY BANJO, CHECK IT OUT! WE'RE ON THE TITLE SCREEN!");
              }
              break;
            case 1:
              if (!i) {
                bt_fn_zoombox_open(zb);
                bt_fn_zoombox_append_text(zb, "OH... I GUESS THAT MEANS SOMEONE ROMHACKED OUR GAME.");
              }
              break;
          }
          break;
        case BT_ZOOMBOX_STATE_TEXT_PRINTED:
          bt_fn_zoombox_close(zb);
          break;
        case BT_ZOOMBOX_STATE_CLOSED:
          switch (main.credits_state) {
            case 0:
              if (i) main.credits_state++;
              break;
            case 1:
              if (!i) {
                main.credits_state++;
                bt_fn_zoombox_leave(zb);
              }
              break;
            case 2:
              if (i) {
                main.credits_state++;
                bt_fn_zoombox_open(zb);
                bt_fn_zoombox_append_text(zb, "YEAH, IT LOOKS LIKE THESE NERDS DID MOST OF THE WORK:");
              }
              break;
            case 3:
              if (i) {
                bool all_done = true;
                for (int i = 0; i < sizeof(main_credit_lines)/sizeof(*main_credit_lines); i++) {
                  struct main_credit_lines_t* line = &main_credit_lines[i];
                  if (line->icon >= 0) {
                    bt_fn_zoombox_queue_icon(zb, line->icon);
                    bt_fn_zoombox_open(zb);
                    bt_fn_zoombox_append_text(zb, line->name);
                    line->icon = -1;
                    all_done = false;
                    break;
                  }
                }
                if (all_done) bt_fn_zoombox_leave(zb);
              }
              break;
            default: bt_fn_zoombox_leave(zb);
          }
          break;
        case BT_ZOOMBOX_STATE_DONE:
          bt_fn_zoombox_free(zb);
          main.zb_credits[i] = 0;
          break;
      }
    }
  }
}

bt_obj_setup_t setup_cache[512];
u32 setup_cache_count;

void pre_spawn_prop(u16* id, bt_s32_xyz_t* pos, u32* yrot, bt_obj_setup_t* setup) {
  if (!BT_IN_GAME) return;
  switch (*id) {
    case 0x01CA: // ice egg nest
    case 0x01CB: // grenade egg nest
    case 0x01CE: // red feather nest
    case 0x01CF: // gold feather nest
    case 0x01E9: // egg nest
    case 0x04A6: // feather nest
      if (!setup->id) {
        switch (bt_current_map) {
          case 0x00DB: // ggm canary cave
            switch (pos->x) {
              case 0xFFFFFD11: // left crate
                setup->id = 0x07FF;
                break;
              case 0x0000027C: // right crate
                setup->id = 0x07FE;
                break;
            }
            break;
          case 0x0106: // gi floor 2
            switch (pos->x) {
              case 0x00000208: // crate near humba
                setup->id = 0x07FF;
                break;
              case 0xFFFFFCB9: // crate near floor 1 stairs
                setup->id = 0x07FE;
                break;
            }
            break;
          case 0x010B: // gi floor 4
            switch (pos->x) {
              case 0xFFFFF39D: // crate near crushers warp pad
                setup->id = 0x07FF;
                break;
            }
            break;
          case 0x01A8: // jrl atlantis
            setup->id = 0x07FF; // ice egg seemee
            break;
          case 0x01A9: // jrl locker/big fish cavern
            switch (*id) {
              case 0x01CB: // grenade egg seemee
                setup->id = 0x07FF;
                break;
              case 0x01CF: // gold feather seemee
                setup->id = 0x07FE;
                break;
            }
            break;
          case 0x0136: // ccl
            switch (*id) { // dirt piles
              case 0x01E9:
                setup->id = 0x07FF;
                break;
              case 0x04A6:
                setup->id = 0x07FE;
                break;
            }
            break;
        }
      }
      if (
           setup->id && ap_memory.pc.settings.randomize_nests
        && !save_custom_get_bit(save_data.custom[bt_save_slot].nests, custom_flag_nest(bt_current_map, setup->id))) {
        *id = 0x01E9;
      }
      break;
  }
}

void post_spawn_prop(u16 id, bt_s32_xyz_t* pos, u32 yrot, bt_obj_setup_t* setup, bt_obj_instance_t* obj) {
  if (!obj || !BT_IN_GAME) return;
  if (setup && setup_cache_count < sizeof(setup_cache)/sizeof(*setup_cache)) setup_cache[setup_cache_count++] = *setup;
}

void pre_loop() {
  usb_check();
  ap_update();
  ap_menu_update();

  u32 c0_count = C0_COUNT();
  main.delta = (c0_count-main.last_c0_count)/TICKS_PER_MILLISECOND;
  main.milliseconds_on_map += main.delta;
  main.last_c0_count = c0_count;
}

void post_loop() {
  if (BT_IN_GAME) ap_check();
  if (bt_current_map != ap_memory.n64.misc.current_map) {
    ap_memory.n64.misc.current_map = bt_current_map;
    usb.send.misc = 1;
  }
}

void main_visited_world(u16 scene) {
  switch (scene) {
    case 0x0B8:
      bt_fake_flags.mt_visited = 1;
      break;
    case 0x0C7:
      bt_fake_flags.ggm_visited = 1;
      break;
    case 0x0D6:
      bt_fake_flags.ww_visited = 1;
      break;
    case 0x1A7:
      bt_fake_flags.jrl_visited = 1;
      break;
    case 0x112:
      bt_fake_flags.tdl_visited = 1;
      break;
    case 0x100:
      bt_fake_flags.gi_visited = 1;
      break;
    case 0x127:
      bt_fake_flags.hfp_visited = 1;
      break;
    case 0x136:
      bt_fake_flags.ccl_visited = 1;
      break;
    case 0x15D:
      bt_fake_flags.ck_visited = 1;
      break;
  }
}

void pre_load_scene(u16 *scene, u16 *exit) {
  setup_cache_count = 0;
  if (!BT_IN_GAME && bt_current_map != BT_MAP_FILE_SELECT) {
    if (*scene == BT_MAP_FILE_SELECT) {
      save_data.version = AP_VERSION.as_int;
      save_dirty = 1;
      for (int i = 0; i < 2; i++) {
        bt_zoombox_t* zb = main.zb_credits[i];
        if (!zb) continue;
        bt_fn_zoombox_free(zb);
        main.zb_credits[i] = 0;
      }
    }
    return;
  }
  bt_temp_flags.bubble_cutscene = 0;
  bt_flags.ccl_open = ap_memory.pc.items[AP_ITEM_CCA] > 0;
  if (bt_flags.ck_opened_gun_chamber) bt_flags.tower_of_tragedy_completed = 0;
  if (ap_memory.pc.settings.randomize_chuffy && !bt_fake_flags.ggm_defeated_chuffy) {
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
      main_visited_world(mapping->on_map);
      main_visited_world(mapping->to_map);
      break;
    }
  }
  switch (*scene) {
    case BT_MAP_CUTSCENE_OPENING:
      main.new_file = 1;
      *scene = BT_MAP_SM;
      *exit = 0x0004;
      break;
    case BT_MAP_CUTSCENE_REVIVAL:
      if (bt_current_map == BT_MAP_FILE_SELECT) {
        *scene = BT_MAP_JV;
        *exit = 0x0003;
      }
      else {
        *scene = BT_MAP_CK_GUN_CHAMBER;
        *exit = 0x0001;
      }
      break;
    case BT_MAP_CK_TOT_QUIZ_ROOM:
      if (bt_flags.ck_opened_gun_chamber) bt_flags.tower_of_tragedy_completed = 1;
      break;
    case BT_MAP_TRAIN_STATION_GGM:
      if (ap_memory.pc.settings.randomize_chuffy && !bt_fake_flags.ggm_defeated_chuffy) {
        bt_flags.train_at_ggm = 0;
        bt_flags.train_at_ioh = 1;
      }
      break;
    case BT_MAP_CCL:
      bt_flags.ccl_open = 1; // needed for bubble to spawn
      break;
    case BT_MAP_MT_KICKBALL_LOBBY:
      if (ap_memory.pc.settings.backdoors) bt_flags.hfp_lava_stadium_opened_mt = 1;
      break;
    case BT_MAP_TDL_OOGLE_BOOGLE_CAVE:
      if (ap_memory.pc.settings.backdoors && *exit) bt_flags.tdl_opened_oogle_boogle_cave = 1;
      break;
    case BT_MAP_JV:
      if (
           ap_memory.pc.settings.randomize_nests
        && bt_current_map == BT_MAP_SM
        && *exit == 3
        && !save_custom_get_bit(bt_custom_save.nests, 0x019)
      ) {
        *scene = BT_MAP_DIGGER_TUNNEL;
        *exit = 1;
      }
      break;
    case BT_MAP_SM:
      if (
           ap_memory.pc.settings.randomize_nests
        && bt_current_map == BT_MAP_JV
        && *exit == 3
        && !save_custom_get_bit(bt_custom_save.nests, 0x019)
      ) {
        *scene = BT_MAP_DIGGER_TUNNEL;
        *exit = 2;
      }
      break;
    case BT_MAP_IOH_WASTELAND:
      if (
           ap_memory.pc.settings.randomize_nests
        && bt_current_map == BT_MAP_IOH_PINE_GROVE
        && *exit == 1
        && (!save_custom_get_bit(bt_custom_save.nests, 0x051) || !save_custom_get_bit(bt_custom_save.nests, 0x052))
      ) {
        *scene = BT_MAP_ANOTHER_DIGGER_TUNNEL;
        *exit = 1;
      }
      break;
    case BT_MAP_IOH_PINE_GROVE:
      if (
           ap_memory.pc.settings.randomize_nests
        && bt_current_map == BT_MAP_IOH_WASTELAND
        && *exit == 3
        && (!save_custom_get_bit(bt_custom_save.nests, 0x051) || !save_custom_get_bit(bt_custom_save.nests, 0x052))
      ) {
        *scene = BT_MAP_ANOTHER_DIGGER_TUNNEL;
        *exit = 2;
      }
      break;
    case BT_MAP_BOTTLES_HOUSE:
      if (bt_fake_flags.jukebox_bottles_house_party) break;
      switch (ap_memory.pc.settings.victory_condition) {
        case 3:
        case 5:
          if (bt_custom_save.totals.mumbo_tokens < ap_memory.pc.settings.max_mumbo_tokens) break;
          bt_fake_flags.jukebox_bottles_house_party = 1;
          *scene = BT_MAP_CUTSCENE_SAD_PARTY_AT_BOTTLES;
          *exit = 0;
          break;
      }
      break;
    case BT_MAP_CK:
      if (ap_memory.pc.settings.victory_condition == 4) {
        bt_flags.hag1_open = ap_memory.pc.items[AP_ITEM_H1A] > 0;
        if (!bt_flags.hag1_open && bt_flags.jiggywiggy_completed_challenges > 9) bt_flags.jiggywiggy_completed_challenges = 9;
      }
      break;
    case BT_MAP_IOH_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ioh_mumbo = 1;
      break;
    case BT_MAP_MT_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.mt_mumbo = 1;
      break;
    case BT_MAP_GGM_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ggm_mumbo = 1;
      break;
    case BT_MAP_WW_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ww_mumbo = 1;
      break;
    case BT_MAP_JRL_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.jrl_mumbo = 1;
      break;
    case BT_MAP_TDL_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.tdl_mumbo = 1;
      break;
    case BT_MAP_GI_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.gi_mumbo = 1;
      break;
    case BT_MAP_HFP_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.hfp_mumbo = 1;
      break;
    case BT_MAP_CCL_MUMBO:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ccl_mumbo = 1;
      break;
    case BT_MAP_IOH_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.humba_dragon_kazooie = 1;
      break;
    case BT_MAP_MT_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.mt_humba = 1;
      break;
    case BT_MAP_GGM_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ggm_humba = 1;
      break;
    case BT_MAP_WW_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ww_humba = 1;
      break;
    case BT_MAP_JRL_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.jrl_humba = 1;
      break;
    case BT_MAP_TDL_HUMBA:
    case BT_MAP_TDL_HUMBA_ENLARGED:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.tdl_humba = 1;
      break;
    case BT_MAP_GI_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.gi_humba = 1;
      break;
    case BT_MAP_HFP_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.hfp_humba = 1;
      break;
    case BT_MAP_CCL_HUMBA:
      if (bt_player_chars.control_type == BT_PLAYER_CHAR_BANJO_KAZOOIE) bt_fake_flags.ccl_humba = 1;
      break;
  }
}

void post_load_scene(u16 scene, u16 exit) {
  main.milliseconds_on_map = 0;
  main.last_c0_count = C0_COUNT();
  BT_FPS = (ap.smooth_banjo && bt_player_chars.control_type != BT_PLAYER_CHAR_WASHER) ? 1 : 2;

  s32 object_count = 0;
  bt_fn_object_count(&object_count);
  if (object_count) {
    for (object_count++; object_count > 0;) {
      bt_obj_instance_t* object_instance = bt_fn_object_instance(&object_count);
      switch (scene) {
        case 0x00F4: // Ancient Swimming Baths
          switch (object_instance->data->type) {
            case 0x07E1: // Kazooie split up pad
            case 0x07E2: // Banjo split up pad
              object_instance->pos.y -= 75;
              object_instance->pos.z += 450;
              object_instance->rot.x = 0;
              object_instance->rot.z = 0;
              break;
          }
          break;
        case 0x00D6: // Witchyworld
          switch (object_instance->data->type) {
            case 0x07E1: // Kazooie split up pad
              object_instance->pos.x = -300;
              object_instance->pos.y = -163;
              object_instance->pos.z = -1855;
              break;
            case 0x07E2: // Banjo split up pad
              object_instance->pos.x = 304;
              object_instance->pos.y = -163;
              object_instance->pos.z = -1855;
              break;
          }
      }
    }
  }
}

void pre_load_save() {
}

void post_load_save() {
  if (!BT_IN_GAME && bt_current_map != BT_MAP_FILE_SELECT) return;
  if (main.new_file) {
    main.new_file = 0;
    ap_new_file();
  }
  ap.load_file = 1;
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
  bt_temp_flags.ccl_eyeballus_jiggium_plant_dialog = 1;
  bt_temp_flags.ccl_eyeballus_jiggium_plant_cutscene = 1;
  bt_temp_flags.intro_pawno = 1;
  bt_temp_flags.intro_ssslumber = 1;
}

void main_increase_item(u32 _unknown_A0, u16 type, s32 amount) {
  if (type == BT_ITEM_BLUE_EGGS+0x40 && !bt_flags.blue_eggs) return;
  _bt_fn_increase_item(type, amount);
}

extern void main_train_change_station_displaced(u16 station);
void main_train_change_station(u16 station) {
  bt_respawn_point[0].map = station;
  bt_respawn_point[0].exit = 2;
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
    case BT_MAP_IOH_CLIFF_TOP:
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
    case BT_MAP_IOH_CLIFF_TOP:
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
    if (ap_memory.pc.settings.max_mumbo_tokens) {
      bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].position = BT_UI_NUMBER_POSITION_SHARED_BOTTOM_LEFT_LOWER;
      bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].icon = BT_UI_ICONS_MINGY_JONGO;
      bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].format = BT_UI_NUMBER_FORMAT_MAX;
      bt_fn_ui_show_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER, save_data.custom[bt_save_slot].totals.mumbo_tokens, ap_memory.pc.settings.max_mumbo_tokens);
    }
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
                if (!(bt_controllers[0].held.l && bt_controllers[0].held.r)) {
                  bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
                  return 0;
                }
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
      if (!ap_memory.pc.settings.seed) strcpy(text, ", BTCLIENT: D/C");
      else if (ap_memory.pc.settings.seed != save_data.custom[slot].seed) strcpy(text, ", SEED: WRONG");
      else strcpy(text, ", SEED: MATCH");
      return 0;
    }
  }
  return 1;
}

extern void main_bt_pause_state_change_displaced(u32, u32, u64, u64);
u8 main_bt_pause_state_change(u32 _unknown_A0, u32 pause_ctx, u64 selected, u64 state) {
  switch (state & 0xFF) {
    case 0x0A:
      pause_ctx += 0x23C;
      pause_ctx = *((u32*)pause_ctx);
      pause_ctx += 0x033;
      strcpy((char*)pause_ctx, "ARCHIPELAGO");
      break;
  }
  return 1;
}

extern void main_bt_pause_load_menu_displaced(bt_pause_ctx_t*);
u8 main_bt_pause_load_menu(bt_pause_ctx_t* pause_ctx) {
  switch (pause_ctx->pause_state) {
    case 2:
      if (pause_ctx->current_menu >= 2 && ap_menu.id == AP_MENU_NONE) {
        ap_menu.id = AP_MENU_MAIN;
        ap_menu.state = AP_MENU_STATE_INIT;
        return 0;
      }
      break;
    case 3:
      if (ap_menu.id == AP_MENU_WAITTOTALS) {
        if (pause_ctx->unpause) {
          ap_menu.id = AP_MENU_NONE;
          ap_menu.state = AP_MENU_STATE_NONE;
        }
      }
      break;
  }
  return 1;
}

extern void main_collected_nest_displaced();
bool main_collected_nest(bt_obj_instance_t* obj) {
  if (ap_memory.pc.settings.randomize_nests) {
    s32 flag = custom_flag_nest(bt_current_map, obj->id);
    if (flag >= 0) {
      bool collected = save_custom_set_bit(save_data.custom[bt_save_slot].nests, flag);
      if (!collected) {
        bt_fn_play_sound(BT_SOUND_COLLECTED_ITEM1, -1, 1, -1);
        bt_fn_sparkle(&obj->pos, 5);
        obj->state = 7;
        if (obj->data && obj->nests.respawn) {
          for (int i = 0; i < setup_cache_count; i++) {
            bt_obj_setup_t* setup = &setup_cache[i];
            if (setup->id != obj->id) continue;
            bt_s32_xyz_t pos = {.x=setup->pos.x, .y=setup->pos.y, .z=setup->pos.z};
            bt_obj_instance_t* new_obj = bt_fn_spawn_prop(setup->type, &pos, 0, setup);
            new_obj->obj_data = setup->obj_data;
            new_obj->_unknown0x7B |= 0x20;
            new_obj->state = 4;
            new_obj->data->collectable = 0;
            break;
          }
        }
      }
      return collected;
    }
  }
  return true;
}

void main_init_ap_nest(bt_obj_instance_t* obj) {
  s32 flag = custom_flag_nest(bt_current_map, obj->id);
  if (
    obj->id && obj->data->type == 0x6EA && ap_memory.pc.settings.randomize_nests && flag >= 0
    && !save_custom_get_bit(save_data.custom[bt_save_slot].nests, flag)
  ) {
    obj->sprite_index = 0xB;
    obj->timer = 0;
    obj->data->state = 0x738;
  }
}

extern void main_init_nest_displaced(bt_obj_instance_t* obj);
void main_init_nest(bt_obj_instance_t* obj) {
  if (!obj) return;
  if (obj->state == 4) {
    obj->timer = 5;
    obj->obj_state = 0x10;
    obj->_unknown0x7C = 0;
    obj->display_state = 0xF0;
  }
  main_init_ap_nest(obj);
}

void main_init_egg_nest(bt_obj_instance_t* obj) {
  if (!obj) return;
  if (obj->state == 4) {
    obj->sprite_mode = 2;
    obj->timer = 5;
  }
  main_init_ap_nest(obj);
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

      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x02F4, 0x001F0821, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x02F8, (u32)main_collected_nest_displaced, 1);
      util_inject(UTIL_INJECT_JUMP    , (u32)obj + 0x023C, (u32)main_init_nest_displaced, 1);
      util_inject(UTIL_INJECT_JUMP    , (u32)obj + 0x0DE4, (u32)main_init_egg_nest, 0);
      break;
    case BT_OBJ_MOVE_SILO:
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0440, (u32)save_fake_has_move, 0); // called when close enough for note count to show
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0E0C, (u32)save_fake_has_move, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0EFC, (u32)save_fake_has_move, 0); // called on scene init and when nearby
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1048, (u32)save_fake_has_move, 0); // called on dialog start
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x111C, (u32)save_fake_has_move, 0); // called on dialog start if wrong character
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1B58, (u32)save_fake_has_move, 0);

      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x1D98, (u32)save_fake_set_move, 0); // called when taught move

      util_inject(UTIL_INJECT_JUMP    , (u32)obj + 0x0300, (u32)save_jamjar_silo_requirements, 1);
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
      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x0998, 0x001F0821, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x099C, (u32)main_bt_pause_state_change_displaced, 1);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x0FE0, (u32)main_bt_paused_displaced, 1); // run our function while at main pause menu

      util_inject(UTIL_INJECT_RAW     , (u32)obj + 0x06F4, 0x001F0821, 0);
      util_inject(UTIL_INJECT_FUNCTION, (u32)obj + 0x06F8, (u32)main_bt_pause_load_menu_displaced, 1);

      // objects+jinjos shown
      bt_pause_main_entry_t* order = (bt_pause_main_entry_t*)((u32)obj + 0x21A0);
      bt_pause_main_entry_t totals = order[3];
      order[3] = order[2];
      order[2] = order[1];
      order[1] = totals;
      // objects shown
      order = (bt_pause_main_entry_t*)((u32)obj + 0x21C0);
      totals = order[2];
      order[2] = order[1];
      order[1] = totals;
      // jinjos shown
      order = (bt_pause_main_entry_t*)((u32)obj + 0x21D8);
      totals = order[2];
      order[2] = order[1];
      order[1] = totals;
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
    case BT_OBJ_CHUFFY_CABIN:
      util_inject(UTIL_INJECT_JUMP    , (u32)obj + 0x0668, (u32)main_train_change_station_displaced, 1);
      break;
    case BT_OBJ_STOMPONADON:
      if (bt_current_map == BT_MAP_STOMPING_PLAINS) break;
      util_inject(UTIL_INJECT_JUMP, (u32)obj + 0x04B8, (u32)ap_stomponadon_stomp, 1);
      break;
  }
}

void post_object_init(bt_object_t *obj) {
  if (!BT_IN_GAME) return;
}

void pre_load_data(u16 *id) {

}

void post_load_data(u16 id, u32 addr) {
  if (!BT_IN_GAME) return;
  const u32 draw_instructions[] = {
    0x00000002, 0x00000000, 0x10000003, 0x00000000, 0x00000002, 0x00000000, 0x1004002E, 0x00000000,
    0x00000000, 0x00000000, 0x00180001, 0x00000000, 0x41700000, 0x00000000, 0x00000003, 0x00000000,
    0x01290002
  };
  switch (id) {
    case 0x06EA: // egg nests
      bt_nest_egg_sprites_t* data = (bt_nest_egg_sprites_t*)addr;
      for (int w = 0; w < 32; w++) {
        for (int h = 0; h < 32; h++) {
          data->sprites[1].pixels[w][h] = AP_ICON[w][h];
        }
      }
      memcpy(data->draw_instructions.mine_eggs, draw_instructions, sizeof(draw_instructions));
      data->sprite_properties.mine_eggs.loc_size = 0x03C0;
      break;
  }
}

void pre_get_data(u16 *id) {

}

void post_get_data(u16 id, u32 addr) {
  if (!BT_IN_GAME) return;
  switch (id) {
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
