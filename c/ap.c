#include "ap.h"
#include "bt.h"
#include "save.h"
#include "usb.h"
#include <string.h>

ap_t ap = {0, };

u8 ap_dialog_icons[] = {
  BT_ZOOMBOX_ICON_GLOWBO,
  BT_ZOOMBOX_ICON_JIGGY,
  BT_ZOOMBOX_ICON_HONEYCOMB,
  BT_ZOOMBOX_ICON_SUB,
  BT_ZOOMBOX_ICON_WASHER,
  BT_ZOOMBOX_ICON_BANJO,
  BT_ZOOMBOX_ICON_KAZOOIE,
  BT_ZOOMBOX_ICON_BOTTLES,
  BT_ZOOMBOX_ICON_MUMBO,
  BT_ZOOMBOX_ICON_JINJO_YELLOW,
  BT_ZOOMBOX_ICON_JINJO_GREEN,
  BT_ZOOMBOX_ICON_JINJO_BLUE,
  BT_ZOOMBOX_ICON_JINJO_PURPLE,
  BT_ZOOMBOX_ICON_JINJO_ORANGE,
  BT_ZOOMBOX_ICON_BEEHIVE,
  BT_ZOOMBOX_ICON_GRUNTY,
  BT_ZOOMBOX_ICON_ZUBBA,
  BT_ZOOMBOX_ICON_JAMJARS,
  BT_ZOOMBOX_ICON_BOVINA,
  BT_ZOOMBOX_ICON_MINGO_WHITE,
  BT_ZOOMBOX_ICON_MINGO_ORANGE,
  BT_ZOOMBOX_ICON_MINGO_YELLOW,
  BT_ZOOMBOX_ICON_MINGO_BROWN,
  BT_ZOOMBOX_ICON_UNOGOPAZ,
  BT_ZOOMBOX_ICON_CHIEF_BLOATAZIN,
  BT_ZOOMBOX_ICON_DILBERTA,
  BT_ZOOMBOX_ICON_STONIES1,
  BT_ZOOMBOX_ICON_CANARY_MARY,
  BT_ZOOMBOX_ICON_CHEATO,
  BT_ZOOMBOX_ICON_GOBI,
  BT_ZOOMBOX_ICON_DINO_KID1,
  BT_ZOOMBOX_ICON_MR_PATCH,
  BT_ZOOMBOX_ICON_MOGGY,
  BT_ZOOMBOX_ICON_SOGGY,
  BT_ZOOMBOX_ICON_GROGGY,
  BT_ZOOMBOX_ICON_MRS_BOGGY,
  BT_ZOOMBOX_ICON_PROSPECTOR,
  BT_ZOOMBOX_ICON_HUMBA,
  BT_ZOOMBOX_ICON_UFO,
  BT_ZOOMBOX_ICON_OLD_KING_COAL,
  BT_ZOOMBOX_ICON_SSSLUMBER,
  BT_ZOOMBOX_ICON_BOGGY,
  BT_ZOOMBOX_ICON_BIG_AL,
  BT_ZOOMBOX_ICON_SALTY_JOE,
  BT_ZOOMBOX_ICON_CONGA,
  BT_ZOOMBOX_ICON_PAWNO,
  BT_ZOOMBOX_ICON_TIPTUP,
  BT_ZOOMBOX_ICON_JOLLY,
  BT_ZOOMBOX_ICON_MERRY_MAGGIE,
  BT_ZOOMBOX_ICON_TERRY,
  BT_ZOOMBOX_ICON_BARGASAURUS,
  BT_ZOOMBOX_ICON_YELLOW_STONY,
  BT_ZOOMBOX_ICON_ALIEN,
  BT_ZOOMBOX_ICON_CHRIS_P_BACON,
  BT_ZOOMBOX_ICON_CAPTAIN_BLUBBER,
  BT_ZOOMBOX_ICON_STYRACOSAURUS_MOM,
  BT_ZOOMBOX_ICON_ROYSTEN,
  BT_ZOOMBOX_ICON_SAFE,
  BT_ZOOMBOX_ICON_GUFFO,
  BT_ZOOMBOX_ICON_MR_FIT,
  BT_ZOOMBOX_ICON_CAPTAIN_BLACKEYE,
  BT_ZOOMBOX_ICON_JINJO_RED,
  BT_ZOOMBOX_ICON_JINJO_WHITE,
  BT_ZOOMBOX_ICON_JINJO_BLACK,
  BT_ZOOMBOX_ICON_JINJO_BROWN,
  BT_ZOOMBOX_ICON_CHILLY_WILLY,
  BT_ZOOMBOX_ICON_CHILLI_BILLI,
  BT_ZOOMBOX_ICON_MINGY_JONGO,
  BT_ZOOMBOX_ICON_YELLOW_DODGEM,
  BT_ZOOMBOX_ICON_MINGELLA,
  BT_ZOOMBOX_ICON_BLOBBELDA,
  BT_ZOOMBOX_ICON_KLUNGO,
  BT_ZOOMBOX_ICON_BOTTLES_DEAD,
  BT_ZOOMBOX_ICON_MINGO_GREEN,
  BT_ZOOMBOX_ICON_MINGO_RED,
  BT_ZOOMBOX_ICON_MINGO_BLUE,
  BT_ZOOMBOX_ICON_MINGO_PURPLE,
  BT_ZOOMBOX_ICON_MINGO_BLACK,
  BT_ZOOMBOX_ICON_RABBIT_WORKER1,
  BT_ZOOMBOX_ICON_UNGA_BUNGA,
  BT_ZOOMBOX_ICON_JIGGYWIGGY,
  BT_ZOOMBOX_ICON_JIGGYWIGGY_DISCIPLE,
  BT_ZOOMBOX_ICON_HONEY_B,
  BT_ZOOMBOX_ICON_BANJO_KAZOOIE,
  BT_ZOOMBOX_ICON_PIG1,
  BT_ZOOMBOX_ICON_OOGLE_BOOGLE,
  BT_ZOOMBOX_ICON_GI_ANNOUNCER,
  BT_ZOOMBOX_ICON_DINGPOT,
  BT_ZOOMBOX_ICON_KING_JINGALING_DEAD,
  BT_ZOOMBOX_ICON_ROCKNUT,
  BT_ZOOMBOX_ICON_MILDRED,
  BT_ZOOMBOX_ICON_BIGGA_FOOT,
  BT_ZOOMBOX_ICON_GEORGE,
  BT_ZOOMBOX_ICON_SABREMAN,
  BT_ZOOMBOX_ICON_DIPPY,
  BT_ZOOMBOX_ICON_LOGGO,
  BT_ZOOMBOX_ICON_KING_JINGALING,
  BT_ZOOMBOX_ICON_MRS_BOTTLES,
  BT_ZOOMBOX_ICON_SPECCY,
  BT_ZOOMBOX_ICON_GOGGLES,
  BT_ZOOMBOX_ICON_TARGITZAN,
  BT_ZOOMBOX_ICON_CHOMPA,
  BT_ZOOMBOX_ICON_LORD_WOO_FAK_FAK,
  BT_ZOOMBOX_ICON_WELDAR,
  BT_ZOOMBOX_ICON_ALIEN_CHILD,
  BT_ZOOMBOX_ICON_EVIL_BOTTLES,
  BT_ZOOMBOX_ICON_DINO_KID2,
  BT_ZOOMBOX_ICON_DINO_SCRIT_SMALL,
  BT_ZOOMBOX_ICON_DINO_SCRIT_BIG,
  BT_ZOOMBOX_ICON_HEGGY,
};

u8 ap_set_jinjo(save_data_totals_t* totals, u8 color, u16 ui_entry, u8 value) {
  if (value == totals->jinjos[color]) return 0;
  u16 max = color+1;
  bt_fn_ui_show_number(ui_entry, totals->jinjos[color], max);
  bt_fn_ui_show_number(ui_entry, value, max);
  totals->jinjos[color] = value;
  return value == max ? 2 : 1;
}

void ap_sync_items(u16 type, u8 value) {
  save_data_totals_t* totals = &(save_data.custom[bt_save_slot].totals);
  u16 current;
  u16 max;
  switch (type) {
    case AP_ITEM_PAGES:
      if (value != totals->pages) {
        totals->pages = value;
        if (bt_flags.cheats_feathers_received) value -= 5;
        if (bt_flags.cheats_eggs_received) value -= 5;
        if (bt_flags.cheats_fallproof_received) value -= 5;
        if (bt_flags.cheats_honeyback_received) value -= 5;
        if (bt_flags.cheats_jukebox_received) value -= 5;
        current = bt_items[BT_ITEM_PAGES] ^ bt_item_keys[BT_ITEM_PAGES].key;
        bt_fn_increase_item(BT_ITEM_PAGES, value-current);
      }
      break;
    case AP_ITEM_HONEY:
      if (value != totals->honeycombs) {
        totals->honeycombs = value;
        if (bt_flags.trade_honey_b > 0) value -= 1;
        if (bt_flags.trade_honey_b > 1) value -= 3;
        if (bt_flags.trade_honey_b > 2) value -= 5;
        if (bt_flags.trade_honey_b > 3) value -= 7;
        if (bt_flags.trade_honey_b > 4) value -= 9;
        current = bt_items[BT_ITEM_EMPTY_HONEYCOMBS] ^ bt_item_keys[BT_ITEM_EMPTY_HONEYCOMBS].key;
        bt_fn_increase_item(BT_ITEM_EMPTY_HONEYCOMBS, value-current);
      }
      break;
    case AP_ITEM_WJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_WHITE, BT_UI_NUMBERS_WHITE_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_white = value-1;
      }
      break;
    case AP_ITEM_OJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_ORANGE, BT_UI_NUMBERS_ORANGE_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_orange = value-1;
      }
      break;
    case AP_ITEM_YJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_YELLOW, BT_UI_NUMBERS_YELLOW_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_yellow = value-1;
      }
      break;
    case AP_ITEM_BRJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_BROWN, BT_UI_NUMBERS_BROWN_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_brown = value-1;
      }
      break;
    case AP_ITEM_GJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_GREEN, BT_UI_NUMBERS_GREEN_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_green = value-1;
      }
      break;
    case AP_ITEM_RJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_RED, BT_UI_NUMBERS_RED_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_red = value-1;
      }
      break;
    case AP_ITEM_BLJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_BLUE, BT_UI_NUMBERS_BLUE_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_blue = value-1;
      }
      break;
    case AP_ITEM_PJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_PURPLE, BT_UI_NUMBERS_PURPLE_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_purple = value-1;
      }
      break;
    case AP_ITEM_BKJINJO:
      if (value = ap_set_jinjo(totals, BT_JINJO_BLACK, BT_UI_NUMBERS_BLACK_JINJO, value)) {
        bt_flags.jv_jiggy_collected_jinjo_black = value-1;
      }
      break;
    case AP_ITEM_DOUBLOON:
      if (value != totals->doubloons) {
        totals->doubloons = value;
        if (bt_flags.jrl_paid_jolly) value -= 2;
        if (bt_flags.jrl_paid_blubber) value -= 1;
        if (bt_flags.jrl_opened_pawno_jiggy) value -= 20;
        if (bt_flags.jrl_opened_pawno_page) value -= 5;
        current = bt_items[BT_ITEM_DOUBLOONS] ^ bt_item_keys[BT_ITEM_DOUBLOONS].key;
        bt_fn_increase_item(BT_ITEM_DOUBLOONS, value-current);
      }
      break;
    case AP_ITEM_JIGGY:
      if (value != totals->jiggies) {
        bt_fn_ui_show_number(BT_UI_NUMBERS_JIGGIES_BOTTOM_CENTER, totals->jiggies, 0);
        bt_fn_ui_show_number(BT_UI_NUMBERS_JIGGIES_BOTTOM_CENTER, value, 0);
        totals->jiggies = value;
      }
      break;
    case AP_ITEM_TREBLE:
      if (value != totals->treble_clefs) {
        bt_fn_ui_show_number(BT_UI_NUMBERS_NOTES, totals->notes*5+totals->treble_clefs*20, 0);
        bt_fn_ui_show_number(BT_UI_NUMBERS_NOTES, totals->notes*5+value*20, 0);
        totals->treble_clefs = value;
      }
      break;
    case AP_ITEM_NOTE:
      if (value != totals->notes) {
        bt_fn_ui_show_number(BT_UI_NUMBERS_NOTES, totals->notes*5+totals->treble_clefs*20, 0);
        bt_fn_ui_show_number(BT_UI_NUMBERS_NOTES, value*5+totals->treble_clefs*20, 0);
        totals->notes = value;
      }
      break;
    case AP_ITEM_MUMBOTOKEN:
      if (value != totals->mumbo_tokens) {
        bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].position = BT_UI_NUMBER_POSITION_SHARED_BOTTOM_LEFT_LOWER;
        bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].icon = BT_UI_ICONS_MINGY_JONGO;
        bt_fn_ui_show_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER, totals->mumbo_tokens, 0);
        bt_fn_ui_show_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER, value, 0);
        totals->mumbo_tokens = value;
      }
      break;
    case AP_ITEM_IKEY:
      if (bt_flags.opened_mega_glowbo) break;
      current = bt_items[BT_ITEM_ICE_KEYS] ^ bt_item_keys[BT_ITEM_ICE_KEYS].key;
      if (value != current) {
        bt_fn_increase_item(BT_ITEM_ICE_KEYS, value-current);
      }
      break;
    case AP_ITEM_PMEGG:
      if (bt_flags.wh_pink_egg_hatched) break;
      bt_flags.sm_pink_egg_collected = value > 0;
      if (!bt_flags.wh_blue_egg_hatched) value += ap_memory.pc.items[AP_ITEM_BMEGG];
      current = bt_items[BT_ITEM_MYSTERY_EGGS] ^ bt_item_keys[BT_ITEM_MYSTERY_EGGS].key;
      if (value != current) {
        bt_fn_increase_item(BT_ITEM_MYSTERY_EGGS, value-current);
      }
      break;
    case AP_ITEM_BMEGG:
      if (bt_flags.wh_blue_egg_hatched) break;
      bt_flags.sm_blue_egg_collected = value > 0;
      if (!bt_flags.wh_pink_egg_hatched) value += ap_memory.pc.items[AP_ITEM_PMEGG];
      current = bt_items[BT_ITEM_MYSTERY_EGGS] ^ bt_item_keys[BT_ITEM_MYSTERY_EGGS].key;
      if (value != current) {
        bt_fn_increase_item(BT_ITEM_MYSTERY_EGGS, value-current);
      }
      break;
    case AP_ITEM_GGRAB:
      bt_flags.grip_grab = value > 0;
      break;
    case AP_ITEM_BBLASTER:
      bt_flags.breegull_blaster = value > 0;
      break;
    case AP_ITEM_EGGAIM:
      bt_flags.egg_aim = value > 0;
      break;
    case AP_ITEM_BDRILL:
      bt_flags.bill_drill = value > 0;
      break;
    case AP_ITEM_BBAYONET:
      bt_flags.beak_bayonet = value > 0;
      break;
    case AP_ITEM_AIREAIM:
      bt_flags.airborne_egg_aiming = value > 0;
      break;
    case AP_ITEM_SPLITUP:
      bt_flags.split_up = value > 0;
      break;
    case AP_ITEM_WWHACK:
      bt_flags.wing_whack = value > 0;
      break;
    case AP_ITEM_TTORP:
      bt_flags.talon_torpedo = value > 0;
      break;
    case AP_ITEM_AUQAIM:
      bt_flags.sub_aqua_egg_aiming = value > 0;
      break;
    case AP_ITEM_SHPACK:
      bt_flags.shack_pack = value > 0;
      break;
    case AP_ITEM_GLIDE:
      bt_flags.glide = value > 0;
      break;
    case AP_ITEM_SNPACK:
      bt_flags.snooze_pack = value > 0;
      break;
    case AP_ITEM_LSPRING:
      bt_flags.leg_spring = value > 0;
      break;
    case AP_ITEM_CLAWBTS:
      bt_flags.claw_clamber_boots = value > 0;
      break;
    case AP_ITEM_SPRINGB:
      bt_flags.springy_step_shoes = value > 0;
      break;
    case AP_ITEM_TAXPACK:
      bt_flags.taxi_pack = value > 0;
      break;
    case AP_ITEM_HATCH:
      bt_flags.hatch = value > 0;
      break;
    case AP_ITEM_PACKWH:
      bt_flags.pack_whack = value > 0;
      break;
    case AP_ITEM_SAPACK:
      bt_flags.sack_pack = value > 0;
      break;
    case AP_ITEM_FEGGS:
      if (value && !bt_flags.fire_eggs) bt_fn_increase_item(BT_ITEM_FIRE_EGGS, 999);
      bt_flags.fire_eggs = value > 0;
      break;
    case AP_ITEM_GEGGS:
      if (value && !bt_flags.grenade_eggs) bt_fn_increase_item(BT_ITEM_GRENADE_EGGS, 999);
      bt_flags.grenade_eggs = value > 0;
      break;
    case AP_ITEM_CEGGS:
      if (value && !bt_flags.clockwork_kazooie_eggs) bt_fn_increase_item(BT_ITEM_CLOCKWORK_EGGS, 999);
      bt_flags.clockwork_kazooie_eggs = value > 0;
      break;
    case AP_ITEM_IEGGS:
      if (value && !bt_flags.ice_eggs) bt_fn_increase_item(BT_ITEM_ICE_EGGS, 999);
      bt_flags.ice_eggs = value > 0;
      break;
    case AP_ITEM_FSWIM:
      bt_flags.fast_swimming = value > 0;
      break;
    case AP_ITEM_DAIR:
      if (value && !bt_flags.extra_bubbles) bt_fn_refill_air(1, 10);
      bt_flags.extra_bubbles = value > 0;
      break;
    case AP_ITEM_BBASH:
      bt_flags.breegull_bash = value > 0;
      break;
    case AP_ITEM_HOMINGEGGS:
      bt_flags.cheats_homing_eggs_received = value > 0;
      break;
    case AP_ITEM_AMAZEOGAZE:
      bt_flags.amaze_o_gaze = value > 0;
      break;
    case AP_ITEM_ROAR:
      bt_flags.trex_roar = value > 0;
      break;
    case AP_ITEM_DIVE:
      bt_flags.diving = value > 0;
      break;
    case AP_ITEM_FPAD:
      bt_flags.flight = value > 0;
      break;
    case AP_ITEM_GRAT:
      bt_flags.basic_peck_attack = value > 0;
      break;
    case AP_ITEM_ROLL:
      bt_flags.rolling_attack = value > 0;
      break;
    case AP_ITEM_ARAT:
      bt_flags.airborne_peck_attack = value > 0;
      break;
    case AP_ITEM_BBARGE:
      bt_flags.beak_barge_attack = value > 0;
      break;
    case AP_ITEM_TJUMP:
      bt_flags.basic_jumping = value > 0;
      break;
    case AP_ITEM_FLUTTER:
      bt_flags.feathery_flap = value > 0;
      break;
    case AP_ITEM_FFLIP:
      bt_flags.flap_flip = value > 0;
      break;
    case AP_ITEM_CLIMB:
      bt_flags.climbing = value > 0;
      break;
    case AP_ITEM_BEGGS:
      if (value && !bt_flags.blue_eggs) bt_fn_increase_item(BT_ITEM_BLUE_EGGS, 999);
      bt_flags.blue_eggs = value > 0;
      break;
    case AP_ITEM_TTROT:
      bt_flags.talon_trot = value > 0;
      break;
    case AP_ITEM_BBUST:
      bt_flags.beak_buster_attack = value > 0;
      break;
    case AP_ITEM_WWING:
      bt_flags.wonder_wing = value > 0;
      break;
    case AP_ITEM_SSTRIDE:
      bt_flags.wading_boots = value > 0;
      break;
    case AP_ITEM_TTRAIN:
      bt_flags.turbo_trainers = value > 0;
      break;
    case AP_ITEM_BBOMB:
      bt_flags.beak_bomb_attack = value > 0;
      break;
    case AP_ITEM_EGGSHOOT:
      bt_flags.egg_firing = value > 0;
      break;
    case AP_ITEM_MUMBOMT:
      bt_flags.mt_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOGM:
      bt_flags.ggm_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOWW:
      bt_flags.ww_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOJR:
      bt_flags.jrl_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOTD:
      bt_flags.tdl_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOGI:
      bt_flags.gi_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOHP:
      bt_flags.hfp_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOCC:
      bt_flags.ccl_mumbo = value > 0;
      break;
    case AP_ITEM_MUMBOIH:
      bt_flags.ioh_mumbo = value > 0;
      break;
    case AP_ITEM_HUMBAMT:
      bt_flags.mt_humba = value > 0;
      break;
    case AP_ITEM_HUMBAGM:
      bt_flags.ggm_humba = value > 0;
      break;
    case AP_ITEM_HUMBAWW:
      bt_flags.ww_humba = value > 0;
      break;
    case AP_ITEM_HUMBAJR:
      bt_flags.jrl_humba = value > 0;
      break;
    case AP_ITEM_HUMBATD:
      bt_flags.tdl_humba = value > 0;
      break;
    case AP_ITEM_HUMBAGI:
      bt_flags.gi_humba = value > 0;
      break;
    case AP_ITEM_HUMBAHP:
      bt_flags.hfp_humba = value > 0;
      break;
    case AP_ITEM_HUMBACC:
      bt_flags.ccl_humba = value > 0;
      break;
    case AP_ITEM_HUMBAIH:
      bt_flags.humba_dragon_kazooie = value > 0;
      break;
    case AP_ITEM_TRAINSWIH:
      bt_flags.ioh_opened_train = value > 0;
      break;
    case AP_ITEM_TRAINSWTD:
      bt_flags.tdl_opened_train = value > 0;
      break;
    case AP_ITEM_TRAINSWGI:
      bt_flags.gi_outside_opened_train = value > 0;
      break;
    case AP_ITEM_TRAINSWHP1:
      bt_flags.hfp_lava_opened_train = value > 0;
      break;
    case AP_ITEM_TRAINSWHP2:
      bt_flags.hfp_icy_opened_train = value > 0;
      break;
    case AP_ITEM_TRAINSWWW:
      bt_flags.ww_opened_train = value > 0;
      break;
    case AP_ITEM_CHUFFY:
      if (value) {
        if (
             !bt_flags.train_at_ioh
          && !bt_flags.train_at_tdl
          && !bt_flags.train_at_gi
          && !bt_flags.train_at_hfp_lava
          && !bt_flags.train_at_hfp_icy
          && !bt_flags.train_at_ww
        ) bt_flags.train_at_ggm = 1;
        save_data.custom[bt_save_slot].fake_flags.ggm_defeated_chuffy = 1;
        save_data.custom[bt_save_slot].fake_flags.ggm_mumbo_train = 1;
      }
      else {
        bt_flags.train_at_ioh = 0;
        bt_flags.train_at_tdl = 0;
        bt_flags.train_at_gi = 0;
        bt_flags.train_at_hfp_lava = 0;
        bt_flags.train_at_hfp_icy = 0;
        bt_flags.train_at_ww = 0;
        bt_flags.train_at_ggm = 0;
        save_data.custom[bt_save_slot].fake_flags.ggm_defeated_chuffy = 0;
        save_data.custom[bt_save_slot].fake_flags.ggm_mumbo_train = 0;
      }
      break;
    case AP_ITEM_MTA:
      bt_flags.mt_open = value > 0;
      break;
    case AP_ITEM_GGA:
      bt_flags.ggm_open = value > 0;
      break;
    case AP_ITEM_WWA:
      bt_flags.ww_open = value > 0;
      break;
    case AP_ITEM_JRA:
      bt_flags.jrl_open = value > 0;
      break;
    case AP_ITEM_TDA:
      bt_flags.tdl_open = value > 0;
      break;
    case AP_ITEM_GIA:
      bt_flags.gi_open = value > 0;
      break;
    case AP_ITEM_HFA:
      bt_flags.hfp_open = value > 0;
      break;
    case AP_ITEM_CCA:
      bt_flags.ccl_open = value > 0;
      break;
    case AP_ITEM_CKA:
      bt_flags.ck_open = value > 0;
      break;
    case AP_ITEM_H1A:
      bt_flags.hag1_open = value > 0;
      break;
  }
}

void ap_draw_hud(bt_draw_ctx_t* draw_ctx) {
  if (ap.zoombox) bt_fn_zoombox_draw(ap.zoombox, draw_ctx);
}

bool ap_get_next_message() {
  if (ap_memory.n64.misc.show_message != ap_memory.pc.misc.show_message) {
    ap_memory.n64.misc.show_message = ap_memory.pc.misc.show_message;
    usb.send.misc = 1;
    ap.message_lines = 0;
    char* start = ap.message;
    for (int i = 0; i < sizeof(ap.message); i++) {
      switch (ap_memory.pc.message[i]) {
        case '\0':
          ap.message[i] = '\0';
          ap.messages[ap.message_lines] = start;
          return true;
        case '\n':
          if (ap.message_lines < sizeof(ap.messages)) {
            ap.message[i] = '\0';
            ap.messages[ap.message_lines] = start;
            start = ap.message+i+1;
            ap.message_lines++;
          }
          else ap.message[i] = ' ';
          break;
        default:
          ap.message[i] = ap_memory.pc.message[i];
      }
    }
  }
  return false;
}

void ap_update() {
  if (ap.zoombox) {
    bt_fn_zoombox_update(ap.zoombox);
    bool show = !bt_temp_flags.in_cutscene && !bt_dialog.textObjectPtr && !bt_loading_map.loading;
    if (!show) {
      if (ap.zoombox_ready) bt_fn_zoombox_close(ap.zoombox);
      bt_fn_zoombox_selected(ap.zoombox, false);
    }
    switch (bt_fn_zoombox_state(ap.zoombox)) {
      case BT_ZOOMBOX_STATE_READY:
        ap.zoombox_ready = 1;
        if (show) {
          bt_fn_zoombox_open(ap.zoombox);
          bt_fn_zoombox_append_lines(ap.zoombox, ap.message_lines+1, ap.messages);
        }
        break;
      case BT_ZOOMBOX_STATE_TEXT_PRINTED:
        if (ap_get_next_message()) bt_fn_zoombox_append_lines(ap.zoombox, ap.message_lines+1, ap.messages);
        else {
          bt_fn_zoombox_close(ap.zoombox);
          ap.message[0] = '\0';
        }
        break;
      case BT_ZOOMBOX_STATE_CLOSED:
        if (ap.message[0] == '\0') bt_fn_zoombox_leave(ap.zoombox);
        else if (show) {
          bt_fn_zoombox_selected(ap.zoombox, true);
          bt_fn_zoombox_open(ap.zoombox);
          bt_fn_zoombox_append_lines(ap.zoombox, ap.message_lines+1, ap.messages);
        }
        break;
      case BT_ZOOMBOX_STATE_DONE:
        bt_fn_zoombox_free(ap.zoombox);
        ap.zoombox = 0;
        ap.zoombox_ready = 0;
        break;
    }
  }
}

void ap_check() {
  if (!bt_temp_flags.in_cutscene) {
    if (ap_memory.n64.misc.death_link_ap != ap_memory.pc.misc.death_link_ap && !bt_player_chars.died) {
      switch (bt_player_chars.control_type) {
        case BT_PLAYER_CHAR_CLOCKWORK:
          bt_fn_hurt_player(bt_player_chars.control_index);
          break;
        default:
          u8 health = bt_fn_get_health(bt_current_player_char);
          if (health) {
            bt_fn_increase_health(bt_current_player_char, -100);
            if (bt_fn_hurt_player(bt_player_chars.control_index)) {
              ap_memory.n64.misc.death_link_ap++;
              usb.send.misc = 1;
              ap.death_link = 1;
              bt_fn_increase_health(bt_current_player_char, 100);
            }
            else bt_fn_increase_health(bt_current_player_char, health);
          }
      }
    }
    if (!ap.zoombox && ap_get_next_message()) {
      u8 dialog_character = ap_memory.pc.settings.dialog_character;
      if (dialog_character >= sizeof(ap_dialog_icons)) dialog_character = ap_dialog_icons[BT_RANDOM % sizeof(ap_dialog_icons)];
      else dialog_character = ap_dialog_icons[dialog_character];
      ap.zoombox = bt_fn_zoombox_new(200, dialog_character, 0, 1);
      bt_fn_zoombox_init(ap.zoombox);
    }
    for (int i = 0; i < AP_ITEM_MAX; i++) {
      if (ap.items[i] != ap_memory.pc.items[i]) {
        ap.items[i] = ap_memory.pc.items[i];
        ap_sync_items(i, ap_memory.pc.items[i]);
      }
    }
  }
  if (bt_player_chars.died) {
    if (!ap.death_link && !ap.death_link_queued) {
      ap_memory.n64.misc.death_link_us++;
      usb.send.misc = 1;
    }
    ap.death_link_queued = 1;
  }
  else if (ap.death_link_queued) {
    ap.death_link = 0;
    ap.death_link_queued = 0;
  }
  if (bt_current_map != ap_memory.n64.misc.current_map) {
    ap_memory.n64.misc.current_map = bt_current_map;
    usb.send.misc = 1;
  }
  if (bt_controllers[0].held.l) {
    if (bt_controllers[0].pressed.dup) { // REFILL
      bt_fn_increase_item(BT_ITEM_RED_FEATHERS, 999);
      bt_fn_increase_item(BT_ITEM_GOLD_FEATHERS, 999);
      if (bt_flags.blue_eggs) bt_fn_increase_item(BT_ITEM_BLUE_EGGS, 999);
      if (bt_flags.fire_eggs) bt_fn_increase_item(BT_ITEM_FIRE_EGGS, 999);
      if (bt_flags.grenade_eggs) bt_fn_increase_item(BT_ITEM_GRENADE_EGGS, 999);
      if (bt_flags.ice_eggs) bt_fn_increase_item(BT_ITEM_ICE_EGGS, 999);
      if (bt_flags.clockwork_kazooie_eggs) bt_fn_increase_item(BT_ITEM_CLOCKWORK_EGGS, 999);
    }
    if (bt_controllers[0].pressed.dright) { // SUPER BANJO
      bt_flags.cheats_superbanjo_enabled = !bt_flags.cheats_superbanjo_enabled;
    }
    if (bt_controllers[0].pressed.dleft && bt_flags.cheats_homing_eggs_received) { // HOMING EGGS
      bt_flags.cheats_homing_eggs_enabled = !bt_flags.cheats_homing_eggs_enabled;
    }
    if (bt_controllers[0].pressed.ddown && bt_flags.cheats_honeyback_received) { // HONEYBACK
      bt_flags.cheats_honeyback_enabled = !bt_flags.cheats_honeyback_enabled;
    }
    if (bt_controllers[0].released.start) { // SMOOTH BANJO
      ap.smooth_banjo = !ap.smooth_banjo;
      BT_FPS = ap.smooth_banjo ? 1 : 2;
    }
  }
  else {
    // if (bt_controllers[0].held.dup); // SNEAK
    // if (bt_controllers[0].pressed.dright); // CHECK MOVES AND WORLDS
    // if (bt_controllers[0].pressed.dleft); // CHECK MAGIC
    // if (bt_controllers[0].pressed.ddown); // CHECK COLLECTED TREBLE, STATIONS AND VICTORY CONDITION
  }

  u8* real_in = (u8*)&bt_flags;
  u8* real_out = (u8*)&(ap_memory.n64.saves.real);
  u8* fake_in = (u8*)&(save_data.custom[bt_save_slot].fake_flags);
  u8* fake_out = (u8*)&(ap_memory.n64.saves.fake);
  for (int i = 0; i < sizeof(bt_save_flags_t); i++) {
    if (real_out[i] != real_in[i]) {
      real_out[i] = real_in[i];
      usb.send.saves_real = 1;
    }
    if (fake_out[i] != fake_in[i]) {
      fake_out[i] = fake_in[i];
      usb.send.saves_fake = 1;
    }
  }
}

void ap_new_file() {
  bt_flags.jinjo_pattern = 1;
  bt_flags.tutorial_honeycombs = 1;
  bt_flags.tutorial_treble_clefs = 1;
  bt_flags.tutorial_gold_feathers = 1;
  bt_flags.tutorial_red_feathers = 1;
  bt_flags.tutorial_eggs = 1;
  bt_flags.tutorial_glowbos = 1;
  bt_flags.tutorial_notes = 1;
  bt_flags.tutorial_jinjos = 1;
  bt_flags.tutorial_honeycomb_pieces = 1;
  bt_flags.tutorial_signposts = 1;
  bt_flags.tutorial_claw_clamber_boots = 1;
  bt_flags.tutorial_springy_step_shoes = 1;
  bt_flags.tutorial_mt_goliath_timeout = 1;
  bt_flags.tutorial_mt_goliath = 1;
  bt_flags.tutorial_pages = 1;
  bt_flags.tutorial_code_chamber_typing = 1;
  bt_flags.tutorial_code_chamber_podium = 1;
  bt_flags.tutorial_cheat_codes = 1;
  bt_flags.tutorial_mumbo_pad_as_mumbo = 1;
  bt_flags.tutorial_mumbo_pad = 1;
  bt_flags.tutorial_humba_first_transform = 1;
  bt_flags.tutorial_clockwork_kazooie_eggs = 1;
  bt_flags.tutorial_change_egg_type = 1;
  bt_flags.tutorial_doubloons = 1;
  bt_flags.tutorial_ww_big_top_ticket = 1;
  bt_flags.tutorial_humba_first_untransform = 1;
  bt_flags.tutorial_silos = 1;
  bt_flags.tutorial_stony = 1;
  bt_flags.tutorial_daddy_trex = 1;
  bt_flags.tutorial_jukebox_broken = 1;
  bt_flags.tutorial_gi_battery_required = 1;
  bt_flags.tutorial_mystery_eggs = 1;
  bt_flags.tutorial_floatus_floatium_creature = 1;
  bt_flags.tutorial_dragon_kazooie = 1;
  bt_flags.tutorial_bee = 1;
  bt_flags.tutorial_snowball = 1;
  bt_flags.tutorial_washer = 1;
  bt_flags.tutorial_baby_trex = 1;
  bt_flags.tutorial_submarine = 1;
  bt_flags.tutorial_van = 1;
  bt_flags.tutorial_detonator = 1;
  bt_flags.tutorial_gi_intruder_alert = 1;
  bt_flags.tutorial_warp_pads = 1;
  bt_flags.tutorial_first_jiggywiggy_challenge_completed = 1;
  bt_flags.tutorial_skill_stop_honeycomb = 1;
  bt_flags.encountered_first_skill_stop_honeycomb = 1;
  bt_flags.tutorial_random_stop_honeycomb = 1;
  bt_flags.encountered_first_random_stop_honeycomb = 1;
  bt_flags.tutorial_ww_saucer_of_peril = 1;
  bt_flags.tutorial_mumbo = 1;
  bt_flags.tutorial_kickball = 1;
  bt_flags.tutorial_jiggywiggy_alter_of_knowledge = 1;
  bt_flags.tutorial_splitup = 1;
  bt_flags.tutorial_splitup_pads = 1;
  bt_flags.tutorial_ggm_canary_mary = 1;
  bt_flags.tutorial_jiggywiggy_monolith = 1;
  bt_flags.tutorial_ww_no_food_outside_entrance = 1;
  bt_flags.tutorial_ww_no_food_outside_train = 1;
  bt_flags.sm_klungo_cutscene = 1;
  bt_flags.ww_cutscene_cable_car_ride = 1;
  bt_flags.gi_outside_cutscene_jinjo_close = 1;
  bt_flags.gi_outside_cutscene_jinjo_open = 1;
  bt_flags.gi_floor4_cutscene_quality_control_toxic = 1;
  bt_flags.gi_floor4_cutscene_quality_control_cleaned = 1;
  bt_flags.tdl_cutscene_chompasaurus = 1;
  bt_flags.hfp_lava_cutscene_gobi = 1;
  bt_flags.wh_cutscene = 1;
  bt_flags.ccl_cutscene_opened_zzzubas = 1;
  bt_flags.hfp_lava_cutscene_chilli_billi_weakness = 1;
  bt_flags.hfp_icy_cutscene_chilly_willy_weakness = 1;
  bt_flags.hfp_lava_cutscene_chilli_billi_lick = 1;
  bt_flags.hfp_icy_cutscene_chilly_willy_lick = 1;
  bt_flags.ccl_cutscene_mingy_jongo_first_hit = 1;
  bt_flags.jv_cutscene_completed_first_family = 1;
  bt_flags.jv_cutscene_saved_first_jinjo = 1;
  bt_flags.mt_cutscene_jamjars = 1;
  bt_flags.humba_cutscene_mumbo_not_welcome = 1;
  bt_flags.ggm_cutscene_timed_gate = 1;
  bt_flags.tdl_cutscene_enlarge_wigwam = 1;
  bt_flags.mt_cutscene_goliath = 1;
  bt_flags.jiggywiggy_laser_cutscene = 1;
  bt_flags.ccl_plants_entrance_to_buried_items = 1;
  bt_flags.ccl_plants_pot_o_gold_to_pot_o_gold_button = 1;
  bt_flags.ccl_plants_jelly_castle_to_blue_skull = 1;
  bt_flags.ccl_plants_blue_skull_to_jelly_castle = 1;
  bt_flags.ccl_plants_trash_can_to_red_skull = 1;
  bt_flags.ccl_plants_red_skull_to_trash_can = 1;
  bt_flags.ccl_plants_sack_race_end_to_red_skull_upper = 1;
  bt_flags.ccl_plants_humba_to_near_buried_items = 1;
  bt_flags.ccl_plants_buried_items_to_entrance = 1;
  bt_flags.ccl_plants_near_buried_items_to_humba = 1;
  bt_flags.ccl_plants_sack_race_start_to_red_skull_upper = 1;
  bt_flags.ccl_plants_cheese_to_blue_skull_upper = 1;
  bt_flags.jingaling_cutscene = 1;
  bt_flags.jingaling_zombified = 1;
  bt_flags.ioh_jiggy_spawned_jingaling = 1;
  bt_flags.ioh_jiggy_collected_jingaling = 1;
  bt_flags.intro_terry_no_hatch = 1;
  bt_flags.intro_hag1 = 1;
  bt_flags.intro_bovina = 1;
  bt_flags.intro_minjos = 1;
  bt_flags.intro_humba_pine_grove = 1;
  bt_flags.intro_dilberta = 1;
  bt_flags.intro_unogopaz_as_stony = 1;
  bt_flags.intro_unogopaz = 1;
  bt_flags.intro_mt_kickball_welcome = 1;
  bt_flags.intro_cheato = 1;
  bt_flags.intro_mumbo = 1;
  bt_flags.intro_gobi = 1;
  bt_flags.intro_bullion_bill = 1;
  bt_flags.intro_humba = 1;
  bt_flags.intro_mrs_boggy = 1;
  bt_flags.intro_ww_dino = 1;
  bt_flags.intro_targitzan = 1;
  bt_flags.intro_ufo2 = 1;
  bt_flags.intro_ufo = 1;
  bt_flags.intro_ww_fries = 1;
  bt_flags.intro_ww_burgers = 1;
  bt_flags.intro_conga = 1;
  bt_flags.intro_klungo3 = 1;
  bt_flags.intro_tiptup = 1;
  bt_flags.intro_groggy = 1;
  bt_flags.intro_soggy = 1;
  bt_flags.intro_moggy = 1;
  bt_flags.intro_stomponadon = 1;
  bt_flags.intro_merry_maggie = 1;
  bt_flags.intro_jolly = 1;
  bt_flags.intro_klungo1 = 1;
  bt_flags.intro_code_chamber_plaque = 1;
  bt_flags.intro_blubber = 1;
  bt_flags.intro_captain_blackeye = 1;
  bt_flags.intro_scrotty = 1;
  bt_flags.intro_oogle_boogle = 1;
  bt_flags.intro_loggo = 1;
  bt_flags.intro_piggles = 1;
  bt_flags.intro_weldar = 1;
  bt_flags.intro_terry = 1;
  bt_flags.intro_terry_path_to_nest = 1;
  bt_flags.intro_chuffy = 1;
  bt_flags.intro_mrs_bottles = 1;
  bt_flags.intro_terry_past_path_to_nest = 1;
  bt_flags.intro_lord_woo_fak_fak = 1;
  bt_flags.intro_ww_baloon_burst = 1;
  bt_flags.intro_ww_hoop_hurry = 1;
  bt_flags.intro_dingpot = 1;
  bt_flags.intro_speccy = 1;
  bt_flags.intro_klungo2 = 1;
  bt_flags.intro_hfp_icy_big_foot = 1;
  bt_flags.intro_mildred = 1;
  bt_flags.intro_trotty = 1;
  bt_flags.intro_george = 1;
  bt_flags.intro_gi_floor3_packing_room = 1;
  bt_flags.intro_chilli_billi = 1;
  bt_flags.intro_chilly_willy = 1;
  bt_flags.ccl_played_pot_o_gold = 1;
  bt_flags.intro_oogle_boogle_blocker = 1;
  bt_flags.intro_dippy = 1;
  bt_flags.intro_sm_fish = 1;
  bt_flags.intro_jiggywiggy = 1;
  bt_flags.intro_hfp_kickball_welcome = 1;
  bt_flags.intro_hfp_icy_alien_child_cold = 1;
  bt_flags.intro_chompasaurus = 1;
  bt_flags.intro_guffo = 1;
  bt_flags.intro_superstash = 1;
  bt_flags.intro_mr_fit_sprint = 1;
  bt_flags.intro_mr_fit_sack_race = 1;
  bt_flags.intro_mr_fit_high_jump = 1;
  bt_flags.intro_jiggywiggy_disciple = 1;
  bt_flags.intro_heggy = 1;
  bt_flags.intro_jamjars_first_meeting = 1;
  bt_flags.intro_mingy_jongo = 1;
  bt_flags.intro_ww_saucer_of_peril = 1;
  bt_flags.intro_ww_saucer_of_peril_offline = 1;
  bt_flags.intro_hfp_kickball1 = 1;
  bt_flags.intro_mt_kickball3 = 1;
  bt_flags.intro_mt_kickball2 = 1;
  bt_flags.intro_mt_kickball1 = 1;
  bt_flags.intro_ww_dodgem3 = 1;
  bt_flags.intro_ww_dodgem2 = 1;
  bt_flags.intro_ww_dodgem1 = 1;
  bt_flags.intro_jamjars_first_lesson = 1;
  bt_flags.intro_jamjars_first_rations = 1;
  bt_flags.intro_hfp_kickball3 = 1;
  bt_flags.intro_hfp_kickball2 = 1;
  bt_flags.intro_gi_worker_rabbits = 1;
  bt_flags.intro_ccl_canary_mary = 1;
  bt_flags.intro_ggm_canary_mary = 1;
  bt_flags.intro_boggy = 1;
  bt_flags.hfp_icy_boggy_wants_fish = 1;
  bt_flags.intro_ssslumber = 1;
  bt_flags.intro_ssslumber_left = 1;
  bt_flags.intro_hfp_lava_not_welcome = 1;
  bt_flags.intro_hfp_icy_not_welcome = 1;
  bt_flags.intro_chris_p_bacon = 1;
  bt_flags.intro_mr_fit_sprint_with_turbo_trainers = 1;
  bt_flags.intro_honey_b = 1;
  bt_flags.tdl_visited = 1;
  bt_flags.jrl_visited = 1;
  bt_flags.ww_visited = 1;
  bt_flags.ggm_visited = 1;
  bt_flags.mt_visited = 1;
  bt_flags.ioh_visited = 1;
  bt_flags.ck_visited = 1;
  bt_flags.ccl_visited = 1;
  bt_flags.hfp_visited = 1;
  bt_flags.gi_visited = 1;
  bt_flags.mt_opened_prison_door = 1;
}

void ap_load_file() {
  for (int i = 0; i < AP_ITEM_MAX; i++) ap_sync_items(i, ap_memory.pc.items[i]);
  if (ap_memory.pc.settings.randomize_chuffy) {
    bt_flags.ggm_mumbo_train = 1;
  }
  if (ap_memory.pc.settings.skip_klungo) {
    bt_flags.ioh_defeated_klungo1 = 1;
    bt_flags.ioh_defeated_klungo2 = 1;
    // bt_flags.ck_defeated_klungo3 = 1;
  }
  if (ap_memory.pc.settings.skip_tower_of_tragedy && !bt_flags.ck_opened_gun_chamber) {
    bt_flags.played_tower_of_tragedy_round1 = 1;
    bt_flags.played_tower_of_tragedy_round2 = 1;
    bt_flags.played_tower_of_tragedy_round3 = 1;
    bt_flags.ck_tower_of_tragedy_mingella_lost = 1;
    bt_flags.ck_tower_of_tragedy_blobbelda_lost = 1;
    if (ap_memory.pc.settings.skip_tower_of_tragedy == 2) {
      bt_flags.tower_of_tragedy_round = 3;
    }
    else {
      bt_flags.tower_of_tragedy_round = 4;
      bt_flags.ck_opened_gun_chamber = 1;
    }
  }
  if (ap_memory.pc.settings.speed_up_minigames) {
    bt_flags.mt_opened_kickball_door1 = 1;
    bt_flags.mt_opened_kickball_door2 = 1;
    bt_flags.mt_opened_kickball_door3 = 1;

    bt_flags.ww_paid_dodgem = 1;
    bt_flags.ww_opened_dodgem1 = 1;
    bt_flags.ww_opened_dodgem2 = 1;
    bt_flags.ww_opened_dodgem3 = 1;
    bt_flags.ww_won_dodgem1 = 1;
    bt_flags.ww_won_dodgem2 = 1;

    bt_flags.hfp_lava_opened_kickball_door1 = 1;
    bt_flags.hfp_lava_opened_kickball_door2 = 1;
    bt_flags.hfp_lava_opened_kickball_door3 = 1;
  }
  if (ap_memory.pc.settings.open_silos[AP_SILO_JINJO_VILLAGE]) bt_flags.silo_jinjo_village = 1;
  if (ap_memory.pc.settings.open_silos[AP_SILO_WOODED_HOLLOW]) bt_flags.silo_wooded_hollow = 1;
  if (ap_memory.pc.settings.open_silos[AP_SILO_PLATEAU]) bt_flags.silo_plateau = 1;
  if (ap_memory.pc.settings.open_silos[AP_SILO_PINE_GROVE]) bt_flags.silo_pine_grove = 1;
  if (ap_memory.pc.settings.open_silos[AP_SILO_CLIFF_TOP]) bt_flags.silo_cliff_top = 1;
  if (ap_memory.pc.settings.open_silos[AP_SILO_WASTELAND]) bt_flags.silo_wasteland = 1;
  if (ap_memory.pc.settings.open_silos[AP_SILO_QUAGMIRE]) bt_flags.silo_quagmire = 1;
}
