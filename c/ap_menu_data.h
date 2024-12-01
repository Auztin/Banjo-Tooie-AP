#ifndef AP_MENU_DATA_H
#define AP_MENU_DATA_H

typedef struct {
  u8 lines;
  u8 icon;
  char** text;
} ap_menu_zb_data_t;

typedef struct {
  u16 item;
  u8  state;
  struct {
    u16 on_map;
    u16 og_map;
    u8  og_exit;
  } exit_map;
  ap_menu_zb_data_t zb;
} ap_menu_data_t;

ap_menu_zb_data_t ap_menu_main_data[] = {
  {.lines=1, .icon=BT_ZOOMBOX_ICON_JIGGYWIGGY, .text=(char*[]){"CHOOSE AN OPTION WITH \x87 AND GO BACK WITH \x86"}},
  {.lines=1, .icon=BT_ZOOMBOX_ICON_BANJO, .text=(char*[]){"RECEIVED ITEMS"}},
  {.lines=1, .icon=BT_ZOOMBOX_ICON_KAZOOIE, .text=(char*[]){"VIEW TOTALS"}},
  {.lines=1, .icon=BT_ZOOMBOX_ICON_GRUNTY, .text=(char*[]){"WORLD ENTRANCES"}},
  {.lines=1, .icon=BT_ZOOMBOX_ICON_GI_ANNOUNCER, .text=(char*[]){"OPTIONS"}},
};

ap_menu_zb_data_t ap_menu_received_data[] = {
  {.lines=1, .icon=BT_ZOOMBOX_ICON_JIGGYWIGGY, .text=(char*[]){"WHICH TYPE OF ITEM WOULD YOU LIKE TO CHECK?"}},
  {.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"MOVES FROM","BANJO-KAZOOIE"}},
  {.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"MOVES FROM","BANJO-TOOIE"}},
  {.lines=1, .icon=BT_ZOOMBOX_ICON_GLOWBO, .text=(char*[]){"MUMBO AND HUMBA"}},
  {.lines=1, .icon=BT_ZOOMBOX_ICON_OLD_KING_COAL, .text=(char*[]){"TRAIN STATIONS AND CHUFFY"}},
};

ap_menu_data_t ap_menu_received_moves_bk_data[] = {
  {.item=AP_ITEM_BBARGE, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"BEAK","BARGE"}}},
  {.item=AP_ITEM_BBOMB, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"BEAK","BOMB"}}},
  {.item=AP_ITEM_BBUST, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"BEAK","BUSTER"}}},
  {.item=AP_ITEM_GRAT, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"GROUND","RATATAT"}}},
  {.item=AP_ITEM_CLIMB, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"CLIMB"}}},
  {.item=AP_ITEM_EGGSHOOT, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"EGG","SHOOT"}}},
  {.item=AP_ITEM_FLUTTER, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"FLUTTER"}}},
  {.item=AP_ITEM_FFLIP, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"FLAP","FLIP"}}},
  {.item=AP_ITEM_FPAD, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"FLIGHT"}}},
  {.item=AP_ITEM_TJUMP, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"TALL","JUMP"}}},
  {.item=AP_ITEM_ARAT, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"AIR","RATATAT"}}},
  {.item=AP_ITEM_ROLL, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"ROLL"}}},
  {.item=AP_ITEM_SSTRIDE, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"STILT","STRIDE"}}},
  {.item=AP_ITEM_DIVE, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"DIVE"}}},
  {.item=AP_ITEM_TTROT, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"TALON","TROT"}}},
  {.item=AP_ITEM_TTRAIN, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"TURBO","TRAINERS"}}},
  {.item=AP_ITEM_WWING, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"WONDER","WING"}}},
  {.item=AP_ITEM_BEGGS, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BOTTLES, .text=(char*[]){"BLUE","EGGS"}}},
};

ap_menu_data_t ap_menu_received_moves_bt1_data[] = {
  {.item=AP_ITEM_GGRAB, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"GRIP","GRAB"}}},
  {.item=AP_ITEM_BBLASTER, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"BREEGULL","BLASTER"}}},
  {.item=AP_ITEM_EGGAIM, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"EGG AIM"}}},
  {.item=AP_ITEM_BDRILL, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"BILL DRILL"}}},
  {.item=AP_ITEM_BBAYONET, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"BEAK","BAYONET"}}},
  {.item=AP_ITEM_AIREAIM, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"AIR","EGG AIM"}}},
  {.item=AP_ITEM_SPLITUP, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"SPLIT UP"}}},
  {.item=AP_ITEM_TTORP, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"TALON","TORPEDO"}}},
  {.item=AP_ITEM_AUQAIM, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"AQUA","EGG AIM"}}},
  {.item=AP_ITEM_CLAWBTS, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"CLAW","CLAMBERS"}}},
  {.item=AP_ITEM_SPRINGB, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"SPRINGY","STEP"}}},
  {.item=AP_ITEM_FEGGS, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"FIRE","EGGS"}}},
  {.item=AP_ITEM_GEGGS, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"GRENADE","EGGS"}}},
  {.item=AP_ITEM_CEGGS, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"CLOCK","WORKS"}}},
  {.item=AP_ITEM_IEGGS, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"ICE EGGS"}}},
};

ap_menu_data_t ap_menu_received_moves_bt2_data[] = {
  {.item=AP_ITEM_SHPACK, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"SHACK","PACK"}}},
  {.item=AP_ITEM_SNPACK, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"SNOOZE","PACK"}}},
  {.item=AP_ITEM_TAXPACK, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"TAXI PACK"}}},
  {.item=AP_ITEM_PACKWH, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"PACK","WHACK"}}},
  {.item=AP_ITEM_SAPACK, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"SACK","PACK"}}},
  {.item=AP_ITEM_WWHACK, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"WING","WHACK"}}},
  {.item=AP_ITEM_GLIDE, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"GLIDE"}}},
  {.item=AP_ITEM_LSPRING, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"LEG","SPRING"}}},
  {.item=AP_ITEM_HATCH, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_JAMJARS, .text=(char*[]){"HATCH"}}},
  {.item=AP_ITEM_DAIR, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_ROYSTEN, .text=(char*[]){"EXTRA","BUBBLES"}}},
  {.item=AP_ITEM_FSWIM, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_ROYSTEN, .text=(char*[]){"FAST","SWIM"}}},
  {.item=AP_ITEM_BBASH, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_HEGGY, .text=(char*[]){"BREEGULL","BASH"}}},
  {.item=AP_ITEM_HOMINGEGGS, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_HEGGY, .text=(char*[]){"HOMING","EGGS"}}},
  {.item=AP_ITEM_AMAZEOGAZE, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_GOGGLES, .text=(char*[]){"AMAZE","O GAZE"}}},
  {.item=AP_ITEM_ROAR, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_BARGASAURUS, .text=(char*[]){"TREX","ROAR"}}},
};

ap_menu_data_t ap_menu_received_mumbo_humba_data[] = {
  {.item=AP_ITEM_MUMBOMT, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"GOLDEN","GOLIATH"}}},
  {.item=AP_ITEM_MUMBOGM, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"LEVITATE"}}},
  {.item=AP_ITEM_MUMBOWW, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"POWER"}}},
  {.item=AP_ITEM_MUMBOJR, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"OXY-","GENATE"}}},
  {.item=AP_ITEM_MUMBOTD, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"ENLARGE"}}},
  {.item=AP_ITEM_MUMBOGI, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"EMP"}}},
  {.item=AP_ITEM_MUMBOHP, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"LIFE","FORCE"}}},
  {.item=AP_ITEM_MUMBOCC, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"RAIN","DANCE"}}},
  {.item=AP_ITEM_MUMBOIH, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"HEAL"}}},
  {.item=AP_ITEM_HUMBAMT, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"STONY"}}},
  {.item=AP_ITEM_HUMBAGM, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"DETO-","NATOR"}}},
  {.item=AP_ITEM_HUMBAWW, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"VAN"}}},
  {.item=AP_ITEM_HUMBAJR, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"SUB"}}},
  {.item=AP_ITEM_HUMBATD, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"T-REX"}}},
  {.item=AP_ITEM_HUMBAGI, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"WASHER"}}},
  {.item=AP_ITEM_HUMBAHP, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"SNOWBALL"}}},
  {.item=AP_ITEM_HUMBACC, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"BEE"}}},
  {.item=AP_ITEM_HUMBAIH, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_HUMBA, .text=(char*[]){"DRAGON","KAZOOIE"}}},
};

ap_menu_data_t ap_menu_received_train_stations_data[] = {
  {.item=AP_ITEM_CHUFFY, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_OLD_KING_COAL, .text=(char*[]){"CHUFFY"}}},
  {.item=AP_ITEM_TRAINSWIH, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MUMBO, .text=(char*[]){"ISLE O HAGS"}}},
  {.item=AP_ITEM_TRAINSWTD, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_TERRY, .text=(char*[]){"TERRY-","DACTYLAND"}}},
  {.item=AP_ITEM_TRAINSWGI, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_WELDAR, .text=(char*[]){"GRUNTY","INDUSTRIES"}}},
  {.item=AP_ITEM_TRAINSWHP1, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_CHILLI_BILLI, .text=(char*[]){"HAILFIRE PEAKS","LAVA SIDE"}}},
  {.item=AP_ITEM_TRAINSWHP2, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_CHILLY_WILLY, .text=(char*[]){"HAILFIRE PEAKS","ICY SIDE"}}},
  {.item=AP_ITEM_TRAINSWWW, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MR_PATCH, .text=(char*[]){"WITCHYWORLD"}}},
};


ap_menu_data_t ap_menu_world_entrances_data[] = {
  {
    .item=AP_ITEM_MTA,
    .exit_map={.on_map=0x14F, .og_map=0x0B8, .og_exit=10},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_TARGITZAN, .text=(char*[]){" MT -  MT"}}
  },
  {
    .item=AP_ITEM_GGA,
    .exit_map={.on_map=0x152, .og_map=0x0C7, .og_exit=17},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_OLD_KING_COAL, .text=(char*[]){"GGM - GGM"}}
  },
  {
    .item=AP_ITEM_WWA,
    .exit_map={.on_map=0x154, .og_map=0x0D6, .og_exit=18},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_MR_PATCH, .text=(char*[]){" WW -  WW"}}
  },
  {
    .item=AP_ITEM_JRA,
    .exit_map={.on_map=0x155, .og_map=0x1A7, .og_exit= 3},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_LORD_WOO_FAK_FAK, .text=(char*[]){"JRL - JRL"}}
  },
  {
    .item=AP_ITEM_TDA,
    .exit_map={.on_map=0x15A, .og_map=0x112, .og_exit=23},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_TERRY, .text=(char*[]){"TDL - TDL"}}
  },
  {
    .item=AP_ITEM_GIA,
    .exit_map={.on_map=0x15C, .og_map=0x100, .og_exit= 9},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_WELDAR, .text=(char*[]){" GI -  GI"}}
  },
  {
    .item=AP_ITEM_HFA,
    .exit_map={.on_map=0x155, .og_map=0x127, .og_exit=21},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_CHILLY_WILLY, .text=(char*[]){"HFP - HFP"}}
  },
  {
    .item=AP_ITEM_CCA,
    .exit_map={.on_map=0x15A, .og_map=0x136, .og_exit=20},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_CANARY_MARY, .text=(char*[]){"CCL - CCL"}}
  },
  {
    .item=AP_ITEM_CKA,
    .exit_map={.on_map=0x15C, .og_map=0x15D, .og_exit= 1},
    .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_KLUNGO, .text=(char*[]){" CK -  CK"}}
  },
};

enum {
  AP_MENU_OPTION_DRAGON_KAZOOIE,
  AP_MENU_OPTION_SUPER_BANJO,
  AP_MENU_OPTION_HOMING_EGGS,
  AP_MENU_OPTION_HONEYBACK,
  AP_MENU_OPTION_SMOOTH_BANJO,
  AP_MENU_OPTION_RESPAWN,
  AP_MENU_OPTION_RESET,
};

ap_menu_data_t ap_menu_options_data[] = {
  {.item=AP_MENU_OPTION_RESPAWN, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BOTTLES_DEAD, .text=(char*[]){"RESPAWN"}}},
  {.item=AP_MENU_OPTION_RESET, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_EVIL_BOTTLES, .text=(char*[]){"RESET"}}},
  {.item=AP_MENU_OPTION_DRAGON_KAZOOIE, .zb={.lines=2, .icon=BT_ZOOMBOX_ICON_KAZOOIE, .text=(char*[]){"DRAGON","KAZOOIE"}}},
  {.item=AP_MENU_OPTION_SMOOTH_BANJO, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BANJO_KAZOOIE, .text=(char*[]){"SMOOTH BANJO"}}},
  {.item=AP_MENU_OPTION_SUPER_BANJO, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_BANJO, .text=(char*[]){"SUPER BANJO"}}},
  {.item=AP_MENU_OPTION_HOMING_EGGS, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HEGGY, .text=(char*[]){"HOMING EGGS"}}},
  {.item=AP_MENU_OPTION_HONEYBACK, .zb={.lines=1, .icon=BT_ZOOMBOX_ICON_HONEYCOMB, .text=(char*[]){"HONEYBACK"}}},
};

#endif // AP_MENU_DATA_H
