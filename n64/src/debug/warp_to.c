#ifndef NDEBUG

#include "warp_to.h"
#include <stdlib.h>

bt_obj_setup_t debug_warp_to_setup_cache[512];
u32 debug_warp_to_setup_count;

int debug_warp_to_map = 0;
int debug_warp_to_iter = 0;
u16 debug_warp_to_maps[] = {
  BT_MAP_0x0AD, // SM - Grunty's Lair
  BT_MAP_0x0AE, // SM - Behind the waterfall
  BT_MAP_SM, // SM - Spiral Mountain
  BT_MAP_MT_HUMBA, // MT - Wumba's Wigwam
  BT_MAP_MT_MUMBO, // MT - Mumbo's Skull
  BT_MAP_MT, // MT
  BT_MAP_0x0B9, // MT - Prison Compound
  BT_MAP_0x0BA, // MT - Columns Vault
  BT_MAP_MT_KICKBALL_LOBBY, // MT - Mayan Kickball Stadium (Lobby)
  BT_MAP_0x0BC, // MT - Code Chamber
  BT_MAP_0x0C4, // MT - Jade Snake Grove
  BT_MAP_0x0C5, // MT - Treasure Chamber
  BT_MAP_0x0C7, // GGM
  BT_MAP_0x0CA, // GGM - Fuel Depot
  BT_MAP_0x0CB, // GGM - Crushing Shed
  BT_MAP_0x0CC, // GGM - Flooded Caves
  BT_MAP_0x0CD, // GGM - Water Storage
  BT_MAP_0x0CE, // GGM - Waterfall Cavern
  BT_MAP_0x0CF, // GGM - Power Hut Basement
  BT_MAP_CHUFFYS_CAB, // GGM - Chuffy's Cab
  BT_MAP_0x0D1, // GGM - Inside Chuffy's Boiler
  BT_MAP_0x0D2, // GGM - Gloomy Caverns
  BT_MAP_0x0D3, // GGM - Generator Cavern
  BT_MAP_0x0D4, // GGM - Power Hut
  BT_MAP_WW_HUMBA, // WW - Wumba's Wigwam
  BT_MAP_0x0D6, // WW
  BT_MAP_TRAIN_STATION_GGM, // GGM - Train Station
  BT_MAP_0x0D8, // GGM - Prospector's Hut
  BT_MAP_GGM_MUMBO, // GGM - Mumbo's Skull
  BT_MAP_0x0DA, // GGM - Toxic Gas Cave
  BT_MAP_0x0DB, // GGM - Canary Cave
  BT_MAP_0x0DC, // GGM - Ordnance Storage
  BT_MAP_0x0DD, // WW - Dodgem Dome Lobby
  BT_MAP_0x0E1, // WW - Crazy Castle Stockade
  BT_MAP_0x0E2, // WW - Crazy Castle Lobby
  BT_MAP_0x0E3, // WW - Crazy Castle Pump Room
  BT_MAP_0x0E6, // WW - Star Spinner
  BT_MAP_0x0E7, // WW - The Inferno
  BT_MAP_GGM_HUMBA, // GGM - Wumba's Wigwam
  BT_MAP_0x0EA, // WW - Cave of Horrors
  BT_MAP_0x0EB, // WW - Haunted Cavern
  BT_MAP_TRAIN_STATION_WW, // WW - Train Station
  BT_MAP_0x0ED, // JRL - Jolly's
  BT_MAP_0x0EE, // JRL - Pawno's Emporium
  BT_MAP_JRL_MUMBO, // JRL - Mumbo's Skull
  BT_MAP_0x0F1, // JRL - Inside the UFO
  BT_MAP_0x0F4, // JRL - Ancient Swimming Baths
  BT_MAP_0x0F6, // JRL - Electric Eel's lair
  BT_MAP_0x0F7, // JRL - Seaweed Sanctum
  BT_MAP_0x0F8, // JRL - Inside the Big Fish
  BT_MAP_0x0F9, // WW - Mr. Patch
  BT_MAP_0x0FA, // JRL - Temple of the Fishes
  BT_MAP_0x0FC, // JRL - Lord Woo Fak Fak
  BT_MAP_0x0FF, // JRL - Blubber's Wave Race Hire
  BT_MAP_0x100, // GI
  BT_MAP_GI_FLOOR1, // GI - Floor 1
  BT_MAP_TRAIN_STATION_GI, // GI - Train Station
  BT_MAP_0x103, // GI - Workers' Quarters
  BT_MAP_0x104, // GI - Trash Compactor
  BT_MAP_0x105, // GI - Elevator shaft
  BT_MAP_GI_FLOOR2, // GI - Floor 2
  BT_MAP_0x107, // GI - Floor 2 (Electromagnet Chamber)
  BT_MAP_GI_FLOOR3, // GI - Floor 3
  BT_MAP_0x109, // GI - Floor 3 (Boiler Plant)
  BT_MAP_GI_FLOOR4, // GI - Floor 4
  BT_MAP_0x10C, // GI - Floor 4 (Cable Room)
  BT_MAP_0x10D, // GI - Floor 4 (Quality Control)
  BT_MAP_GI_FLOOR5, // GI - Floor 5
  BT_MAP_0x10F, // GI - Basement
  BT_MAP_0x110, // GI - Basement (Repair Depot)
  BT_MAP_0x111, // GI - Basement (Waste Disposal)
  BT_MAP_0x112, // TDL
  BT_MAP_0x113, // TDL - Terry's Nest
  BT_MAP_TRAIN_STATION_TDL, // TDL - Train Station
  BT_MAP_TDL_OOGLE_BOOGLE_CAVE, // TDL - Oogle Boogles' Cave
  BT_MAP_0x116, // TDL - Inside the Mountain
  BT_MAP_0x117, // TDL - River Passage
  BT_MAP_0x118, // TDL - Styracosaurus Family Cave
  BT_MAP_0x119, // TDL - Unga Bunga's Cave
  BT_MAP_STOMPING_PLAINS, // TDL - Stomping Plains
  BT_MAP_0x11B, // TDL - Bonfire Cavern
  BT_MAP_TDL_HUMBA, // TDL - Wumba's Wigwam (Small)
  BT_MAP_GI_HUMBA, // GI - Wumba's Wigwam
  BT_MAP_JRL_HUMBA, // JRL - Wumba's Wigwam
  BT_MAP_0x121, // GGM - Inside Chuffy's Wagon
  BT_MAP_TDL_HUMBA_ENLARGED, // TDL - Wumba's Wigwam (Big)
  BT_MAP_TDL_MINIGAME_CHOMPA, // TDL - Inside Chompa's Belly
  BT_MAP_WW_MINIGAME_UFO_WW, // WW - Saucer of Peril
  BT_MAP_0x125, // GI - Water Supply Pipe
  BT_MAP_0x126, // GGM - Water Supply Pipe
  BT_MAP_0x127, // HFP - Lava Side
  BT_MAP_0x128, // HFP - Icy Side
  BT_MAP_TRAIN_STATION_HFP_LAVA, // HFP - Lava Train Station
  BT_MAP_TRAIN_STATION_HFP_ICY, // HFP - Ice Train Station
  BT_MAP_0x12B, // HFP - Chilli Billi
  BT_MAP_0x12C, // HFP - Chilly Willy
  BT_MAP_0x12D, // HFP - Kickball Stadium lobby
  BT_MAP_0x131, // HFP - Boggy's Igloo
  BT_MAP_0x132, // HFP - Icicle Grotto
  BT_MAP_0x133, // HFP - Inside the Volcano
  BT_MAP_HFP_MUMBO, // HFP - Mumbo's Skull
  BT_MAP_HFP_HUMBA, // HFP - Wumba's Wigwam
  BT_MAP_CCL, // CCL
  BT_MAP_CCL_MINIGAME_TRASH_CAN, // CCL - Inside the Trash Can
  BT_MAP_0x138, // CCL - Inside the Cheese Wedge
  BT_MAP_CCL_MINIGAME_ZUBBAS_NEST, // CCL - Zubbas' Nest
  BT_MAP_0x13A, // CCL - Central Cavern
  BT_MAP_WW_MINIGAME_UFO_CRAZY_CASTLE, // WW - Crazy Castle Stockade (Saucer)
  BT_MAP_WW_MINIGAME_UFO_STAR_SPINNER, // WW - Star Spinner (Saucer)
  BT_MAP_CCL_MINIGAME_POT_O_GOLD, // CCL - Inside the Pot o' Gold
  BT_MAP_CCL_MUMBO, // CCL - Mumbo's Skull
  BT_MAP_CCL_MINGY_JONGO, // CCL - Mingy Jongo's Skull
  BT_MAP_CCL_HUMBA, // CCL - Wumba's Wigwam
  BT_MAP_DIGGER_TUNNEL, // SM - Inside the Digger Tunnel
  BT_MAP_JV, // JV
  BT_MAP_BOTTLES_HOUSE, // JV - Bottles' House
  BT_MAP_0x144, // JV - King Jingaling's Throne Room
  BT_MAP_0x14F, // IoH - Wooded Hollow
  BT_MAP_0x150, // IoH - Heggy's Egg Shed
  BT_MAP_0x151, // IoH - Jiggywiggy's Temple
  BT_MAP_0x152, // IoH - Plateau
  BT_MAP_0x153, // IoH - Plateau - Honey B's Hive
  BT_MAP_IOH_PINE_GROVE, // IoH - Pine Grove
  BT_MAP_IOH_CLIFF_TOP, // IoH - Cliff Top
  BT_MAP_IOH_MUMBO, // IoH - Cliff Top - Mumbo's Skull
  BT_MAP_IOH_HUMBA, // IoH - Pine Grove - Wumba's Wigwam
  BT_MAP_IOH_WASTELAND, // IoH - Wasteland
  BT_MAP_ANOTHER_DIGGER_TUNNEL, // IoH - Inside another digger tunnel
  BT_MAP_0x15C, // IoH - Quagmire
  BT_MAP_CK, // CK
  BT_MAP_0x15E, // CK - The Gatehouse
  BT_MAP_CK_TOT_QUIZ_ROOM, // CK - Tower of Tragedy
  BT_MAP_CK_GUN_CHAMBER, // CK - Gun Chamber
  BT_MAP_0x162, // GI - Floor 4 (Clinker's Cavern)
  BT_MAP_0x163, // GGM - Ordnance Storage Entrance
  BT_MAP_TDL_MUMBO, // TDL - Mumbo's Skull
  BT_MAP_GI_MUMBO, // GI - Mumbo's Skull
  BT_MAP_0x173, // SM - Banjo's House
  BT_MAP_WW_MUMBO, // WW - Mumbo's Skull
  BT_MAP_0x177, // MT - Targitzan's Slightly Sacred Chamber
  BT_MAP_0x178, // MT - Inside Targitzan's Temple
  BT_MAP_0x179, // MT - Targitzan's Temple Lobby
  BT_MAP_0x17A, // MT - Targitzan's Really Sacred Chamber
  BT_MAP_0x187, // GI - Sewer Entrance
  BT_MAP_0x19A, // CK - HAG 1
  BT_MAP_0x19B, // JV - Jingaling's Zombified Palace
  BT_MAP_0x1A6, // JRL - Smuggler's cavern
  BT_MAP_0x1A7, // JRL
  BT_MAP_0x1A8, // JRL - Atlantis
  BT_MAP_0x1A9, // JRL - Sea Bottom
};

void debug_warp_to_draw(bt_draw_ctx_t* draw_ctx) {
  bt_fn_text_reset_options();
  bt_text_options.appearance = BT_TEXT_TEXTURE_GOLD;
  bt_text_options.size = 0.70;
  int y = 0;
  char current_map[5];
  itoa(bt_current_map, current_map, 16);
  bt_fn_text_big_draw(draw_ctx, 20, y+=20, current_map);
  char _map[5];
  itoa(debug_warp_to_maps[debug_warp_to_map], _map, 16);
  bt_fn_text_big_draw(draw_ctx, 20, y+=20, _map);
  if (bt_current_map == debug_warp_to_maps[debug_warp_to_map] && debug_warp_to_setup_count) {
    char _setup_count[5];
    itoa(debug_warp_to_setup_count-1, _setup_count, 16);
    bt_fn_text_big_draw(draw_ctx, 20, y+=20, _setup_count);
    char _iter[5];
    itoa(debug_warp_to_iter, _iter, 16);
    bt_fn_text_big_draw(draw_ctx, 20, y+=20, _iter);
    char id[5];
    itoa(debug_warp_to_setup_cache[debug_warp_to_iter].id, id, 16);
    bt_fn_text_big_draw(draw_ctx, 20, y+=20, id);
    // char type[5];
    // itoa(debug_warp_to_setup_cache[iter].type, type, 16);
    // bt_fn_text_big_draw(draw_ctx, 20, y+=20, type);
  }
}

void debug_warp_to_spawn_prop(u16 id, bt_s32_xyz_t* pos, u32 yrot, bt_obj_setup_t* setup, bt_obj_instance_t* obj) {
  if (
       setup
    // && setup->type == 0x198
    && debug_warp_to_setup_count < sizeof(debug_warp_to_setup_cache)/sizeof(*debug_warp_to_setup_cache)
  ) debug_warp_to_setup_cache[debug_warp_to_setup_count++] = *setup;
}

void debug_warp_to_loop() {
  if (bt_controllers[0].pressed.dleft) {
    if (debug_warp_to_maps[debug_warp_to_map] == bt_current_map) {
      debug_warp_to_iter--;
      if (debug_warp_to_iter < 0) {
        debug_warp_to_iter++;
        debug_warp_to_map--;
      }
    }
    else {
      debug_warp_to_map--;
      debug_warp_to_iter = 0;
    }
    if (debug_warp_to_map < 0) debug_warp_to_map = (sizeof(debug_warp_to_maps)/sizeof(*debug_warp_to_maps))-1;
  }
  if (bt_controllers[0].pressed.dright) {
    if (debug_warp_to_maps[debug_warp_to_map] == bt_current_map) {
      debug_warp_to_iter++;
      if (debug_warp_to_iter >= debug_warp_to_setup_count) {
        debug_warp_to_iter--;
        debug_warp_to_map++;
      }
    }
    else {
      debug_warp_to_map++;
      debug_warp_to_iter = debug_warp_to_setup_count-1;
    }
    if (debug_warp_to_map >= sizeof(debug_warp_to_maps)) debug_warp_to_map = 0;
  }
  if (bt_controllers[0].pressed.ddown) {
    bt_fn_change_character(bt_current_player_char, BT_PLAYER_CHAR_BANJO_KAZOOIE);
    if (debug_warp_to_maps[debug_warp_to_map] == bt_current_map) {
      bt_s16_xyz_t item = debug_warp_to_setup_cache[debug_warp_to_iter].pos;
      bt_xyz_t pos = {.x=item.x, .y = item.y, .z=item.z};
      bt_fn_character_move_to(&pos, 0.1, 0);
    }
    else {
      debug_warp_to_iter = 0;
      bt_fn_load_scene(debug_warp_to_maps[debug_warp_to_map], 1, 0);
    }
  }
  if (bt_controllers[0].pressed.dup) {
    bt_s16_xyz_t item = debug_warp_to_setup_cache[debug_warp_to_iter].pos;
    bt_xyz_t pos = {.x=item.x, .y = item.y, .z=item.z};
    bt_fn_set_camera_position(bt_cameras[0].pos_rot, &pos);
  }
}

void debug_warp_to_load_scene(u16* scene, u16* exit) {
  debug_warp_to_setup_count = 0;
}

#endif // NDEBUG
