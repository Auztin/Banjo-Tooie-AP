#include "ap.h"
#include "bt.h"
#include "save.h"
#include "usb.h"
#include "main.h"
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
  BT_ZOOMBOX_ICON_MINJO_WHITE,
  BT_ZOOMBOX_ICON_MINJO_ORANGE,
  BT_ZOOMBOX_ICON_MINJO_YELLOW,
  BT_ZOOMBOX_ICON_MINJO_BROWN,
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
  BT_ZOOMBOX_ICON_MINJO_GREEN,
  BT_ZOOMBOX_ICON_MINJO_RED,
  BT_ZOOMBOX_ICON_MINJO_BLUE,
  BT_ZOOMBOX_ICON_MINJO_PURPLE,
  BT_ZOOMBOX_ICON_MINJO_BLACK,
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

void ap_open_doors(u16 world) {
  bt_fnt_object_get_data door_func1 = 0;
  bt_fnt_object_get_data door_func2 = 0;
  switch (world) {
    case AP_ITEM_MTA:
      door_func1 = (bt_fnt_object_get_data)0x80087088;
      break;
    case AP_ITEM_GGA:
      door_func1 = (bt_fnt_object_get_data)0x80087098;
      break;
    case AP_ITEM_WWA:
      door_func1 = (bt_fnt_object_get_data)0x800870C8;
      break;
    case AP_ITEM_JRA:
      door_func1 = (bt_fnt_object_get_data)0x80087060;
      break;
    case AP_ITEM_TDA:
      door_func1 = (bt_fnt_object_get_data)0x800870C0;
      break;
    case AP_ITEM_GIA:
      door_func1 = (bt_fnt_object_get_data)0x800870D0;
      door_func2 = (bt_fnt_object_get_data)0x800870D8;
      break;
    case AP_ITEM_HFA:
      door_func1 = (bt_fnt_object_get_data)0x800870A0;
      break;
    case AP_ITEM_CCA:
      door_func1 = (bt_fnt_object_get_data)0x80087648;
      break;
    case AP_ITEM_CKA:
      door_func1 = (bt_fnt_object_get_data)0x800870F0;
      break;
    default: return;
  }
  s32 object_count = 0;
  bt_fn_object_count(&object_count);
  if (object_count) {
    for (object_count++; object_count > 0;) {
      bt_obj_instance_t* object_instance = bt_fn_object_instance(&object_count);
      bt_fnt_object_get_data object_function = object_instance->fn_obj_init;
      bt_obj_world_door_t* object_data;
      if (door_func1 == object_function || (door_func2 && door_func2 == object_function)) {
        object_data = (bt_obj_world_door_t*)object_function();
        object_data->fn_play_anim(object_instance, 7, 3);
      }
    }
  }
}

void ap_item_nest(bool feather_nest) {
  struct nest_t {
    u8 type;
    u8 obtained;
  } eggs[] = {
    {.type=BT_ITEM_BLUE_EGGS, .obtained=bt_flags.blue_eggs},
    {.type=BT_ITEM_FIRE_EGGS, .obtained=bt_flags.fire_eggs},
    {.type=BT_ITEM_GRENADE_EGGS, .obtained=bt_flags.grenade_eggs},
    {.type=BT_ITEM_ICE_EGGS, .obtained=bt_flags.ice_eggs},
    {.type=BT_ITEM_CLOCKWORK_EGGS, .obtained=bt_flags.clockwork_kazooie_eggs},
  }, feathers[] = {
    {.type=BT_ITEM_RED_FEATHERS, .obtained=bt_flags.flight | bt_flags.talon_torpedo},
    {.type=BT_ITEM_GOLD_FEATHERS, .obtained=bt_flags.wonder_wing},
  };
  struct nest_t* nests = eggs;
  u8 elements = sizeof(eggs)/sizeof(*eggs);
  if (feather_nest) {
    nests = feathers;
    elements = sizeof(feathers)/sizeof(*feathers);
  }
  s8 lowest = -1;
  float current_percent = 2;
  for (int i = 0; i < elements; i++) {
    struct nest_t* nest = &nests[i];
    if (!nest->obtained) continue;
    u16 key = bt_item_keys[nest->type].key;
    float amount = bt_items[nest->type] ^ key;
    float max = bt_items_max[nest->type].value;
    float percent = amount/max;
    if (percent < current_percent) {
      lowest = nest->type;
      current_percent = percent;
    }
  }
  u8 amount = 0;
  switch (lowest) {
    case BT_ITEM_BLUE_EGGS:
      amount = 20;
      break;
    case BT_ITEM_FIRE_EGGS:
      amount = 10;
      break;
    case BT_ITEM_GRENADE_EGGS:
      amount = 10;
      break;
    case BT_ITEM_ICE_EGGS:
      amount = 10;
      break;
    case BT_ITEM_CLOCKWORK_EGGS:
      amount = 1;
      break;
    case BT_ITEM_RED_FEATHERS:
      amount = 20;
      break;
    case BT_ITEM_GOLD_FEATHERS:
      amount = 2;
      break;
    default: return;
  }
  bt_fn_increase_item(lowest, amount);
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
        bt_ui_numbers[BT_UI_NUMBERS_GRUNTY_TIMER_CENTER].format = BT_UI_NUMBER_FORMAT_MAX;
        bt_fn_ui_show_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER, totals->mumbo_tokens, ap_memory.pc.settings.max_mumbo_tokens);
        bt_fn_ui_show_number(BT_UI_NUMBERS_GRUNTY_TIMER_CENTER, value, ap_memory.pc.settings.max_mumbo_tokens);
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
      if (value && !bt_flags.flight && !bt_flags.talon_torpedo) bt_fn_increase_item(BT_ITEM_RED_FEATHERS, 999);
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
      if (value && !bt_flags.extra_bubbles) {
        bt_fn_ui_hide_number(BT_UI_NUMBERS_BUBBLES);
        bt_fn_refill_air(1, 10);
      }
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
      if (value && !bt_flags.flight && !bt_flags.talon_torpedo) bt_fn_increase_item(BT_ITEM_RED_FEATHERS, 999);
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
      if (value && !bt_flags.wonder_wing) bt_fn_increase_item(BT_ITEM_GOLD_FEATHERS, 999);
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
        bt_fake_flags.ggm_defeated_chuffy = 1;
        bt_fake_flags.ggm_mumbo_train = 1;
      }
      else {
        bt_flags.train_at_ioh = 0;
        bt_flags.train_at_tdl = 0;
        bt_flags.train_at_gi = 0;
        bt_flags.train_at_hfp_lava = 0;
        bt_flags.train_at_hfp_icy = 0;
        bt_flags.train_at_ww = 0;
        bt_flags.train_at_ggm = 0;
        bt_fake_flags.ggm_defeated_chuffy = 0;
        bt_fake_flags.ggm_mumbo_train = 0;
      }
      break;
    case AP_ITEM_GNEST:
      if (bt_custom_save.golden_egg_nests < value) bt_fn_give_golden_eggs();
      bt_custom_save.golden_egg_nests = value;
      break;
    case AP_ITEM_ENEST:
      for (; bt_custom_save.egg_nests != value; bt_custom_save.egg_nests++) ap_item_nest(false);
      break;
    case AP_ITEM_FNEST:
      for (; bt_custom_save.feather_nests != value; bt_custom_save.feather_nests++) ap_item_nest(true);
      break;
    case AP_ITEM_MTA:
      bt_flags.mt_open = value > 0;
      if (bt_flags.mt_open) ap_open_doors(type);
      break;
    case AP_ITEM_GGA:
      bt_flags.ggm_open = value > 0;
      if (bt_flags.ggm_open) ap_open_doors(type);
      break;
    case AP_ITEM_WWA:
      bt_flags.ww_open = value > 0;
      if (bt_flags.ww_open) ap_open_doors(type);
      break;
    case AP_ITEM_JRA:
      bt_flags.jrl_open = value > 0;
      if (bt_flags.jrl_open) ap_open_doors(type);
      break;
    case AP_ITEM_TDA:
      bt_flags.tdl_open = value > 0;
      if (bt_flags.tdl_open) ap_open_doors(type);
      break;
    case AP_ITEM_GIA:
      bt_flags.gi_open = value > 0;
      if (bt_flags.gi_open) ap_open_doors(type);
      break;
    case AP_ITEM_HFA:
      bt_flags.hfp_open = value > 0;
      if (bt_flags.hfp_open) ap_open_doors(type);
      break;
    case AP_ITEM_CCA:
      bt_flags.ccl_open = value > 0;
      if (bt_flags.ccl_open) ap_open_doors(type);
      break;
    case AP_ITEM_CKA:
      bt_flags.ck_open = value > 0;
      if (bt_flags.ck_open) ap_open_doors(type);
      break;
    case AP_ITEM_H1A:
      bt_flags.hag1_open = value > 0;
      if (bt_flags.hag1_open) ap_open_doors(type);
      break;
  }
}

void ap_increment_trap() {
  bt_custom_save.traps[ap.trap_type]++;
  if (bt_custom_save.traps[ap.trap_type] > ap_memory.pc.traps[ap.trap_type]) {
    bt_custom_save.traps[ap.trap_type] = ap_memory.pc.traps[ap.trap_type];
  }
}

bool ap_trap_trip(bool checking) {
  if (checking && bt_fn_character_in_water(bt_current_player_char)) return false;
  switch (bt_fn_get_character_animation(bt_current_player_char)) {
    case 0x58:
    case 0x20:
      break;
    default:
      if (!checking && bt_fn_get_character_last_animation(bt_current_player_char) == 0x20) {
        bt_fn_set_character_animation(bt_current_player_char, bt_fn_get_default_animation(bt_current_player_char));
        ap.fn_trap = 0;
        ap_increment_trap();
      }
      else {
        switch (bt_player_chars.control_type) {
          case BT_PLAYER_CHAR_BREEGULL_BLASTER:
            break;
          default:
            bt_fn_set_character_animation(bt_current_player_char, 0x58);
            return true;
        }
      }
  }
  return false;
}

bool ap_trap_slip(bool checking) {
  if (checking) {
    if (
         !bt_fn_character_touching_ground(bt_current_player_char)
      || bt_fn_character_in_water(bt_current_player_char)
    ) return false;
    switch (bt_player_chars.control_type) {
      case BT_PLAYER_CHAR_KAZOOIE:
        if (bt_player_chars.character_state == 3) return false;
        break;
      case BT_PLAYER_CHAR_SNOWBALL:
      case BT_PLAYER_CHAR_BEE:
      case BT_PLAYER_CHAR_BREEGULL_BLASTER:
      case BT_PLAYER_CHAR_GOLDEN_GOLIATH:
      case BT_PLAYER_CHAR_SUB:
      case BT_PLAYER_CHAR_DETONATOR:
      case BT_PLAYER_CHAR_TREX:
      case BT_PLAYER_CHAR_DADDY_TREX:
        return false;
    }
    ap.trap_timer = 5000;
    return true;
  }
  ap.trap_timer -= main.delta;
  if (ap.trap_timer <= 0) {
    ap.fn_trap = 0;
    ap.trap_timer = 0;
    ap_increment_trap();
  }
  return false;
}

bool ap_trap_misfire(bool checking) {
  if (checking) {
    switch (bt_player_chars.control_type) {
      case BT_PLAYER_CHAR_BREEGULL_BLASTER:
        return false;
    }
    return bt_fn_character_transform(bt_player_chars.control_index, bt_player_chars.control_type);
  }
  if (bt_fn_get_character_animation(bt_current_player_char) != bt_fn_get_drone_animation(bt_current_player_char)) {
    ap.fn_trap = 0;
    ap_increment_trap();
  }
  return false;
}

bool ap_trap_squish(bool checking) {
  if (checking) {
    switch (bt_current_map) {
      case BT_MAP_STOMPING_PLAINS:
        return false;
    }
    switch (bt_player_chars.control_type) {
      case BT_PLAYER_CHAR_KAZOOIE:
        if (bt_player_chars.character_state == 3) return false;
        break;
      case BT_PLAYER_CHAR_CLOCKWORK:
      case BT_PLAYER_CHAR_GOLDEN_GOLIATH:
      case BT_PLAYER_CHAR_DADDY_TREX:
        return false;
    }
    bt_xyz_t* pos = bt_current_player_char->pos;
    bt_s32_xyz_t coords = {.x=pos->x, .y=pos->y+9000, .z=pos->z};
    bt_fn_spawn_prop(0x362, &coords, 0x0, 0);
    ap.trap_timer = 5000;
    return true;
  }
  ap.trap_timer -= main.delta;
  if (ap.trap_timer <= 0) {
    ap.fn_trap = 0;
    ap.trap_timer = 0;
  }
  return false;
}

void ap_sync_traps() {
  if (
       bt_loading_map.loading
    || bt_player_chars.died
    || !bt_fn_character_enemy_can_target(bt_player_chars.control_index)
  ) return;
  if (ap.fn_trap) ap.fn_trap(false);
  else {
    ap.trap_type = AP_TRAP_MAX;
    for (int i = 0; i < AP_TRAP_MAX; i++) {
      if (bt_custom_save.traps[i] != ap_memory.pc.traps[i]) {
        switch (i) {
          case AP_TRAP_TRIP:
            ap.fn_trap = ap_trap_trip;
            break;
          case AP_TRAP_SLIP:
            ap.fn_trap = ap_trap_slip;
            break;
          case AP_TRAP_MISFIRE:
            ap.fn_trap = ap_trap_misfire;
            break;
          case AP_TRAP_SQUISH:
            ap.fn_trap = ap_trap_squish;
            break;
          default:
            continue;
        }
        ap.trap_type = i;
        if (ap.fn_trap(true)) break;
        else {
          ap.fn_trap = 0;
          ap.trap_type = AP_TRAP_MAX;
        }
      }
    }
  }
}

extern u32 ap_get_health_displaced(bt_player_t* character);
u32 ap_get_health(bt_player_t* character) {
  if (character == bt_current_player_char) {
    if (bt_player_chars.control_type == BT_PLAYER_CHAR_KAZOOIE && bt_player_chars.character_state == 3) return 2;
    switch (ap.trap_type) {
      case AP_TRAP_TRIP:
        return 2;
    }
  }
  return ap_get_health_displaced(character);
}

extern void ap_increase_health_displaced(bt_player_t* character, s32 amount);
void ap_increase_health(bt_player_t* character, s32 amount) {
  if (character == bt_current_player_char) {
    switch (ap.trap_type) {
      case AP_TRAP_TRIP:
        if (amount < 0) return;
        break;
    }
  }
  ap_increase_health_displaced(character, amount);
}

extern u32 ap_ground_info_displaced(bt_player_t* character);
u32 ap_ground_info(bt_player_t* character) {
  if (character == bt_current_player_char && bt_fn_transition_done()) {
    switch (ap.trap_type) {
      case AP_TRAP_SLIP:
        character->slope->timer = 1;
        return 0x40;
    }
  }
  return ap_ground_info_displaced(character);
}

bool ap_stomponadon_stomp(bt_obj_instance_t* dinofoot) {
  if (ap.trap_type == AP_TRAP_SQUISH && ap.trap_timer > 4500) {
    dinofoot->pos.y = bt_current_player_char->pos->y+25;
    ap_increment_trap();
    return true;
  }
  ap.trap_timer = 0;
  dinofoot->state = 7;
  return false;
}

void ap_draw_hud(bt_draw_ctx_t* draw_ctx) {
  if (ap.zoombox && bt_fn_transition_done()) bt_fn_zoombox_draw(ap.zoombox, draw_ctx);
}

bool ap_prepare_message(char* message) {
  ap.message_lines = 0;
  char* start = ap.message;
  for (int i = 0; i < sizeof(ap.message); i++) {
    switch (message[i]) {
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
        ap.message[i] = message[i];
    }
  }
  return false;
}

bool ap_get_next_message() {
  if (ap_memory.n64.misc.show_message != ap_memory.pc.misc.show_message) {
    ap_memory.n64.misc.show_message = ap_memory.pc.misc.show_message;
    usb.send.misc = 1;
    return ap_prepare_message(ap_memory.pc.message);
  }
  else if (ap.internal_message[0]) {
    bool ret = ap_prepare_message(ap.internal_message);
    ap.internal_message[0] = '\0';
    ap.is_internal_message = 1;
    return ret;
  }
  return false;
}

u8 ap_get_zb_icon() {
  u8 icon = ap_memory.pc.settings.dialog_character;
  if (icon == 110 && ap.is_internal_message) {
    ap.is_internal_message = 0;
    return ap.internal_icon;
  }
  if (icon >= sizeof(ap_dialog_icons)) icon = BT_RANDOM % sizeof(ap_dialog_icons);
  ap.zb_icon = icon;
  icon = ap_dialog_icons[icon];
  ap.last_icon = icon;
  return icon;
}

void ap_update() {
  if (ap.zoombox) {
    if (!main.milliseconds_on_map) {
      bt_fn_zoombox_free(ap.zoombox);
      ap.zoombox = bt_fn_zoombox_new(200, ap.last_icon, 0, 1);
      bt_fn_zoombox_init(ap.zoombox);
    }
    else if (bt_fn_transition_done()) {
      bt_fn_zoombox_update(ap.zoombox);
      bool show = !bt_temp_flags.in_cutscene && !bt_dialog.textObjectPtr && !bt_loading_map.loading && !bt_player_chars.died;
      if (!show) {
        if (ap.zoombox_ready) {
          bt_fn_zoombox_clear_text(ap.zoombox);
          bt_fn_zoombox_close(ap.zoombox);
        }
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
          if (ap_get_next_message()) {
            if (ap.zb_icon != ap_memory.pc.settings.dialog_character) {
              bt_fn_zoombox_queue_icon(ap.zoombox, ap_get_zb_icon());
              bt_fn_zoombox_close(ap.zoombox);
              bt_fn_zoombox_open(ap.zoombox);
            }
            bt_fn_zoombox_append_lines(ap.zoombox, ap.message_lines+1, ap.messages);
          }
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
  if (bt_loading_map.loading) {
    switch (bt_player_chars.control_type) {
      case BT_PLAYER_CHAR_MUMBO:
        if (ap.fake_transform) {
          switch (bt_loading_map.map) {
            case BT_MAP_IOH_MUMBO:
            case BT_MAP_MT_MUMBO:
            case BT_MAP_GGM_MUMBO:
            case BT_MAP_WW_MUMBO:
            case BT_MAP_JRL_MUMBO:
            case BT_MAP_TDL_MUMBO:
            case BT_MAP_GI_MUMBO:
            case BT_MAP_HFP_MUMBO:
            case BT_MAP_CCL_MUMBO:
            case BT_MAP_CCL_MINGY_JONGO:
              bt_fn_change_character(bt_current_player_char, BT_PLAYER_CHAR_BANJO_KAZOOIE);
              ap.fake_transform = 0;
              bt_respawn_point[0] = bt_respawn_point[1];
              bt_respawn_point[1] = (bt_respawn_point_t){0, };
              break;
          }
        }
        break;
      case BT_PLAYER_CHAR_BANJO_KAZOOIE: {
        u32 map_exit = (bt_loading_map.map << 8) | bt_loading_map.exit;
        switch (map_exit) {
          case 0x01010F:
          case 0x01060F:
          case 0x010809:
          case 0x010B09:
          case 0x010E09:
            bt_fn_change_character(bt_current_player_char, BT_PLAYER_CHAR_WASHER);
            ap.fake_transform = 1;
            bt_respawn_point[1] = bt_respawn_point[0];
            bt_respawn_point[0] = (bt_respawn_point_t){.map=0x0106, .exit=0x0A};
            break;
        }
        break;
      }
    }
  }
}

void ap_check_enough_notes(u16 start, u16 end) {
  if (start == end || start > end) return;
  for (int i = 0; i < sizeof(ap_memory.pc.settings.silo_requirements)/sizeof(*ap_memory.pc.settings.silo_requirements); i++) {
    u16 amount = ap_memory.pc.settings.silo_requirements[i];
    if (start < amount && end >= amount) {
      ap.internal_icon = BT_ZOOMBOX_ICON_JAMJARS;
      strcpy(ap.internal_message, "YOU HAVE ENOUGH NOTES FOR A NEW MOVE!");
      break;
    }
  }
}

bool ap_can_transform_humba(u16 map, bt_respawn_point_t* respawn, u16* form) {
  switch (map) {
    // MAYAHEM TEMPLE
    case 0x00B8: // MT
    case 0x00C4: // MT - Jade Snake Grove
    case 0x00BB: // MT - Mayan Kickball Stadium (Lobby)
    case 0x00B7: // MT - Mumbo's Skull
    case 0x00B9: // MT - Prison Compound
    case 0x00B6: // MT - Wumba's Wigwam
    case 0x00BC: // MT - Code Chamber
      if (bt_flags.mt_humba && bt_fake_flags.mt_humba) {
        *respawn = (bt_respawn_point_t){.map=0x00C4, .exit=0x04};
        *form = BT_PLAYER_CHAR_STONY;
        return true;
      }
      break;
    // GLITTER GULCH MINE
    case 0x00C7: // GGM
    case 0x00CC: // GGM - Flooded Caves
    case 0x00CA: // GGM - Fuel Depot
    case 0x00D3: // GGM - Generator Cavern
    case 0x00D2: // GGM - Gloomy Caverns
    case 0x00CF: // GGM - Power Hut Basement
    case 0x00D4: // GGM - Power Hut
    case 0x00D8: // GGM - Prospector's Hut
    case 0x00DA: // GGM - Toxic Gas Cave
    case 0x00D7: // GGM - Train Station
    case 0x00CD: // GGM - Water Storage
    case 0x00CE: // GGM - Waterfall Cavern
    case 0x00E9: // GGM - Wumba's Wigwam
    case 0x00CB: // GGM - Crushing Shed
      if (bt_flags.ggm_humba && bt_fake_flags.ggm_humba) {
        *respawn = (bt_respawn_point_t){.map=0x00C7, .exit=0x0E};
        *form = BT_PLAYER_CHAR_DETONATOR;
        return true;
      }
      break;
    // WITCHYWORLD
    case 0x00D6: // WW
    case 0x00EA: // WW - Cave of Horrors
    case 0x00E1: // WW - Crazy Castle Stockade
    case 0x00E2: // WW - Crazy Castle Lobby
    case 0x00E3: // WW - Crazy Castle Pump Room
    case 0x00DD: // WW - Dodgem Dome Lobby
    case 0x00EB: // WW - Haunted Cavern
    case 0x00E6: // WW - Star Spinner
    case 0x00E7: // WW - The Inferno
    case 0x0176: // WW - Mumbo Skull
    case 0x00D5: // WW - Wumba's Wigwam
    case 0x00EC: // WW - Train Station
      if (bt_flags.ww_humba && bt_fake_flags.ww_humba) {
        *respawn = (bt_respawn_point_t){.map=0x00D6, .exit=0x0A};
        *form = BT_PLAYER_CHAR_VAN;
        return true;
      }
      break;
    // JOLLY ROGER'S LAGOON
    case 0x01A7: // JRL
    case 0x00F4: // JRL - Ancient Swimming Baths
    case 0x01A8: // JRL - Atlantis
    case 0x00F6: // JRL - Electric Eel's lair
    case 0x00F8: // JRL - Inside the Big Fish
    case 0x00FC: // JRL - Lord Woo Fak Fak
    case 0x01A9: // JRL - Sea Bottom
    case 0x00FA: // JRL - Temple of the Fishes
    case 0x0120: // JRL - Wumba's Wigwam
      if (bt_flags.jrl_humba && bt_fake_flags.jrl_humba) {
        *respawn = (bt_respawn_point_t){.map=0x01A8, .exit=0x12};
        *form = BT_PLAYER_CHAR_SUB;
        return true;
      }
      break;
    // TERRYDACTYLAND
    case 0x0112: // TDL
    case 0x0115: // TDL - Oogle Boogles' Cave
    case 0x0117: // TDL - River Passage
    case 0x011A: // TDL - Stomping Plains
    case 0x0118: // TDL - Styracosaurus Family Cave
    case 0x011B: // TDL - Bonfire Cavern
    case 0x0114: // TDL - Train Station
    case 0x011E: // TDL - Wumba's Wigwam, Small
    case 0x0122: // TDL - Wumba's Wigwam, Big
      if (bt_flags.tdl_humba && bt_fake_flags.tdl_humba) {
        if (bt_flags.tdl_enlarged_wigwam) {
          *respawn = (bt_respawn_point_t){.map=0x0112, .exit=0x16};
          *form = BT_PLAYER_CHAR_DADDY_TREX;
        }
        else {
          *respawn = (bt_respawn_point_t){.map=0x0112, .exit=0x06};
          *form = BT_PLAYER_CHAR_TREX;
        }
        return true;
      }
      break;
    // GRUNTY'S INDUSTRIES
    case 0x0106: // GI - Floor 2
    case 0x011F: // GI - Wumba's Wigwam
      if (bt_flags.gi_humba && bt_fake_flags.gi_humba) {
        *respawn = (bt_respawn_point_t){.map=0x0106, .exit=0x0A};
        *form = BT_PLAYER_CHAR_WASHER;
        return true;
      }
      break;
    // HAILFIRE PEAKS
    case 0x0132: // HFP - Icicle Grotto
    case 0x0128: // HFP - Icy Side
    case 0x0135: // HFP - Wumba's Wigwam
      if (bt_flags.hfp_humba && bt_fake_flags.hfp_humba) {
        *respawn = (bt_respawn_point_t){.map=0x0128, .exit=0x08};
        *form = BT_PLAYER_CHAR_SNOWBALL;
        return true;
      }
      break;
    // CLOUD CUCKOOLAND
    case 0x0136: // CCL
    case 0x013A: // CCL - Central Cavern
    case 0x013F: // CCL - Mingy Jongo's Skull
    case 0x013E: // CCL - Mumbo's Skull
    case 0x0140: // CCL - Wumba's Wigwam
      if (bt_flags.ccl_humba && bt_fake_flags.ccl_humba) {
        *respawn = (bt_respawn_point_t){.map=0x0136, .exit=0x19};
        *form = BT_PLAYER_CHAR_BEE;
        return true;
      }
      break;
  }
  return false;
}

bool ap_can_transform_mumbo(u16 map, bt_respawn_point_t* respawn) {
  switch (map) {
    // ISLE O' HAGS
    case 0x0155: // IoH - Cliff Top
      if (bt_flags.ioh_mumbo && bt_fake_flags.ioh_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x0155, .exit=0x08};
        return true;
      }
      break;
    // MAYAHEM TEMPLE
    case 0x00B8: // MT
    case 0x00C4: // MT - Jade Snake Grove
    case 0x00BB: // MT - Mayan Kickball Stadium (Lobby)
    case 0x00B9: // MT - Prison Compound
    case 0x00B6: // MT - Wumba's Wigwam
    case 0x00BC: // MT - Code Chamber
      if (bt_flags.mt_mumbo && bt_fake_flags.mt_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x00B8, .exit=0x05};
        return true;
      }
      break;
    // GLITTER GULCH MINE
    case 0x00C7: // GM
    case 0x00CC: // GGM - Flooded Caves
    case 0x00CA: // GGM - Fuel Depot
    case 0x00D3: // GGM - Generator Cavern
    case 0x00D2: // GGM - Gloomy Caverns
    case 0x00CF: // GGM - Power Hut Basement
    case 0x00D4: // GGM - Poer Hut
    case 0x00D8: // GGM - Prospector's Hut
    case 0x00DA: // GGM - Toxic Gas Cave
    case 0x00D7: // GGM - Train Station
    case 0x00CD: // GGM - Water Storage
    case 0x00CE: // GGM - Waterfall Cavern
    case 0x00E9: // GGM - Wumba's Wigwam
    case 0x00CB: // GGM - Crushing Shed
      if (bt_flags.ggm_mumbo && bt_fake_flags.ggm_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x00C7, .exit=0x08};
        return true;
      }
      break;
    // WITCHYWORLD
    case 0x00D6: // WW
    case 0x00EA: // WW - Cave of Horrors
    case 0x00E1: // WW - Crazy Castle Stockade
    case 0x00E2: // WW - Crazy Castle Lobby
    case 0x00E3: // WW - Crazy Castle Pump Room
    case 0x00DD: // WW - Dodgem Dome Lobby
    case 0x00EB: // WW - Haunted Cavern
    case 0x00E6: // WW - Star Spinner
    case 0x00E7: // WW - The Inferno
    case 0x00D5: // WW - Wumba's Wigwam
    case 0x00EC: // WW - Train Station
      if (bt_flags.ww_mumbo && bt_fake_flags.ww_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x00E7, .exit=0x02};
        return true;
      }
      break;
    // JOLLY ROGER'S LAGOON
    case 0x01A7: // JRL
    case 0x00FF: // JRL - Blubber's Wave Race Hire
    case 0x00ED: // JRL - Jolly's
    case 0x00EE: // JRL - Pawno's Emporium
      if (bt_flags.jrl_mumbo && bt_fake_flags.jrl_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x01A7, .exit=0x0E};
        return true;
      }
      break;
    // TERRYDACTYLAND
    case 0x0112: // TDL
    case 0x0115: // TDL - Oogle Boogles' Cave
    case 0x0117: // TDL - River Passage
    case 0x011A: // TDL - Stomping Plains
    case 0x0118: // TDL - Styracosaurus Family Cave
    case 0x011B: // TDL - Bonfire Cavern
    case 0x0114: // TDL - Train Station
    case 0x011E: // TDL - Wumba's Wigwam, Small
    case 0x0122: // TDL - Wumba's Wigwam, Big
      if (bt_flags.tdl_mumbo && bt_fake_flags.tdl_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x0112, .exit=0x04};
        return true;
      }
      break;
    // GRUNTY INDUSTRIES
    case 0x0108: // GI - Floor 3
    case 0x010B: // GI - Floor 4
      if (bt_flags.gi_mumbo && bt_fake_flags.gi_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x0108, .exit=0x0A};
        return true;
      }
      break;
    // HAILFIRE PEAKS
    case 0x0131: // HFP - Boggy's Igloo
    case 0x0132: // HFP - Icicle Grotto
    case 0x0128: // HFP - Icy Side
    case 0x012D: // HFP - Kickball Stadium lobby
    case 0x0127: // HFP - Lava Side
    case 0x0135: // HFP - Wumba's Wigwam
      if (bt_flags.hfp_mumbo && bt_fake_flags.hfp_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x0127, .exit=0x03};
        return true;
      }
      break;
    // CLOUD CUCKOOLAND
    case 0x0136: // CCL
    case 0x013A: // CCL - Central Cavern
    case 0x0140: // CCL - Wumba's Wigwam
      if (bt_flags.ccl_mumbo && bt_fake_flags.ccl_mumbo) {
        *respawn = (bt_respawn_point_t){.map=0x0136, .exit=0x16};
        if (bt_flags.ccl_mumbo_location == 1) respawn->exit = 0x09;
        return true;
      }
      break;
  }
  return false;
}

bool ap_cycle_character() {
  u16 to_form = 0;
  u16 from_form = bt_player_chars.control_type;
  bt_respawn_point_t respawn = {0, };
  bool in_water = bt_fn_character_in_water(bt_current_player_char);
  if (
       ap.fn_trap
    || (from_form != BT_PLAYER_CHAR_BANJO_KAZOOIE && !ap.fake_transform)
    || (!bt_fn_character_touching_ground(bt_current_player_char) && !in_water)
    || !bt_fn_character_enemy_can_target(bt_player_chars.control_index)
  ) return false;
  switch (bt_player_chars.control_type) {
    case BT_PLAYER_CHAR_BANJO_KAZOOIE:
      if (
        ap_can_transform_humba(bt_current_map, &respawn, &to_form)
        && to_form == BT_PLAYER_CHAR_SUB && !in_water
      ) to_form = 0;
      if (!to_form && ap_can_transform_mumbo(bt_current_map, &respawn)) to_form = BT_PLAYER_CHAR_MUMBO;
      break;
    case BT_PLAYER_CHAR_SNOWBALL:
    case BT_PLAYER_CHAR_BEE:
    case BT_PLAYER_CHAR_WASHER:
    case BT_PLAYER_CHAR_STONY:
    case BT_PLAYER_CHAR_SUB:
    case BT_PLAYER_CHAR_DETONATOR:
    case BT_PLAYER_CHAR_VAN:
    case BT_PLAYER_CHAR_TREX:
    case BT_PLAYER_CHAR_DADDY_TREX:
      if (!ap_can_transform_humba(bt_current_map, &respawn, &to_form)) return false;
      if (!ap_can_transform_mumbo(bt_current_map, &respawn)) to_form = BT_PLAYER_CHAR_BANJO_KAZOOIE;
      else to_form = BT_PLAYER_CHAR_MUMBO;
      break;
    case BT_PLAYER_CHAR_MUMBO:
      if (!ap_can_transform_mumbo(bt_current_map, &respawn)) return false;
      to_form = BT_PLAYER_CHAR_BANJO_KAZOOIE;
      break;
  }
  if (!to_form) return false;
  if (to_form == BT_PLAYER_CHAR_BANJO_KAZOOIE) ap.fake_transform = 0;
  else ap.fake_transform = 1;
  if (from_form != to_form) {
    if (from_form == BT_PLAYER_CHAR_BANJO_KAZOOIE) {
      bt_respawn_point[1] = bt_respawn_point[0];
      bt_respawn_point[0] = respawn;
    }
    else if (to_form == BT_PLAYER_CHAR_BANJO_KAZOOIE) {
      bt_respawn_point[0] = bt_respawn_point[1];
      bt_respawn_point[1] = (bt_respawn_point_t){0, };
    }
    else bt_respawn_point[0] = respawn;
    bt_fn_change_character(bt_current_player_char, to_form);
    BT_FPS = (ap.smooth_banjo && bt_player_chars.control_type != BT_PLAYER_CHAR_WASHER) ? 1 : 2;
    return true;
  }
  return false;
}

void ap_check() {
  if (
    !bt_temp_flags.in_cutscene
    && bt_fn_transition_done() && main.milliseconds_on_map > 1000
    && !bt_player_chars.died && !bt_loading_map.loading
  ) {
    if (ap.load_file) ap_load_file();
    if (ap_memory.n64.misc.death_link_ap != ap_memory.pc.misc.death_link_ap) {
      switch (bt_player_chars.control_type) {
        case BT_PLAYER_CHAR_CLOCKWORK:
          bt_fn_hurt_player(bt_player_chars.control_index);
          break;
        case BT_PLAYER_CHAR_KAZOOIE:
          if (bt_player_chars.character_state == 3) break;
        default:
          bt_fn_set_character_animation(bt_current_player_char, 0x54);
          ap_memory.n64.misc.death_link_ap++;
          usb.send.misc = 1;
          ap.death_link = 1;
      }
    }
    if (!ap.zoombox && ap_get_next_message()) {
      ap.zoombox = bt_fn_zoombox_new(200, ap_get_zb_icon(), 0, 1);
      bt_fn_zoombox_init(ap.zoombox);
    }
    u16 total_notes = save_totals(6);
    for (int i = 0; i < AP_ITEM_MAX; i++) {
      if (ap.items[i] != ap_memory.pc.items[i]) {
        ap.items[i] = ap_memory.pc.items[i];
        ap_sync_items(i, ap_memory.pc.items[i]);
      }
    }
    ap_check_enough_notes(total_notes, save_totals(6));
    ap_sync_traps();
    if (!bt_controllers[0].held.l && bt_controllers[0].pressed.dleft) {
      if (!ap_cycle_character()) bt_fn_play_sound(BT_SOUND_WRONG, -1, 1, -1);
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
  if (bt_controllers[0].held.l) {
    char message[25] = {0};
    if (bt_controllers[0].pressed.dright) { // SUPER BANJO
      bt_flags.cheats_superbanjo_enabled = !bt_flags.cheats_superbanjo_enabled;
      ap.internal_icon = BT_ZOOMBOX_ICON_BANJO;
      strcpy(message, "SUPER BANJO ");
      strcat(message, bt_flags.cheats_superbanjo_enabled ? "ENABLED" : "DISABLED");
    }
    if (bt_controllers[0].pressed.dleft && bt_flags.cheats_homing_eggs_received) { // HOMING EGGS
      bt_flags.cheats_homing_eggs_enabled = !bt_flags.cheats_homing_eggs_enabled;
      ap.internal_icon = BT_ZOOMBOX_ICON_HEGGY;
      strcpy(message, "HOMING EGGS ");
      strcat(message, bt_flags.cheats_homing_eggs_enabled ? "ENABLED" : "DISABLED");
    }
    if (bt_controllers[0].pressed.ddown && bt_flags.cheats_honeyback_received) { // HONEYBACK
      bt_flags.cheats_honeyback_enabled = !bt_flags.cheats_honeyback_enabled;
      ap.internal_icon = BT_ZOOMBOX_ICON_HONEYCOMB;
      strcpy(message, "HONEYBACK ");
      strcat(message, bt_flags.cheats_honeyback_enabled ? "ENABLED" : "DISABLED");
    }
    if (bt_controllers[0].released.start) { // SMOOTH BANJO
      ap.smooth_banjo = !ap.smooth_banjo;
      BT_FPS = (ap.smooth_banjo && bt_player_chars.control_type != BT_PLAYER_CHAR_WASHER) ? 1 : 2;
      ap.internal_icon = BT_ZOOMBOX_ICON_BANJO_KAZOOIE;
      strcpy(message, "SMOOTH BANJO ");
      strcat(message, ap.smooth_banjo ? "ENABLED" : "DISABLED");
    }
    if (message[0]) strcpy(ap.internal_message, message);
  }

  u8* real_in = (u8*)&bt_flags;
  u8* real_out = (u8*)&(ap_memory.n64.saves.real);
  u8* fake_in = (u8*)&(bt_fake_flags);
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
  u8* nests_in = bt_custom_save.nests;
  u8* nests_out = ap_memory.n64.saves.nests;
  for (int i = 0; i < sizeof(bt_custom_save.nests); i++) {
    if (nests_out[i] != nests_in[i]) {
      nests_out[i] = nests_in[i];
      usb.send.saves_nests = 1;
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
  bt_flags.diving = 0;
  bt_flags.flight = 0;
  bt_flags.basic_peck_attack = 0;
  bt_flags.rolling_attack = 0;
  bt_flags.airborne_peck_attack = 0;
  bt_flags.beak_barge_attack = 0;
  bt_flags.basic_jumping = 0;
  bt_flags.feathery_flap = 0;
  bt_flags.flap_flip = 0;
  bt_flags.climbing = 0;
  bt_flags.blue_eggs = 0;
  bt_flags.talon_trot = 0;
  bt_flags.beak_buster_attack = 0;
  bt_flags.wonder_wing = 0;
  bt_flags.wading_boots = 0;
  bt_flags.turbo_trainers = 0;
  bt_flags.beak_bomb_attack = 0;
  bt_flags.egg_firing = 0;
}

void ap_load_file() {
  ap.load_file = 0;
  for (int i = 0; i < AP_ITEM_MAX; i++) ap_sync_items(i, ap_memory.pc.items[i]);
  if (ap_memory.pc.settings.randomize_chuffy) {
    bt_flags.ggm_mumbo_train = 1;
  }
  if (ap_memory.pc.settings.backdoors) {
    bt_flags.mt_opened_kickball_hfp = 1;
    bt_flags.ww_opened_space_ggm = 1;
    bt_flags.tdl_opened_unga_bunga_entrance = 1;
    bt_flags.tdl_opened_oogle_boogle_ww = 1;
    bt_flags.ccl_murdered_george = 1;
    bt_flags.ioh_opened_bridge_hfp = 1;
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
