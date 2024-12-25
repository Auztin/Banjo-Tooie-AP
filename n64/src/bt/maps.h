#ifndef BT_MAPS_H
#define BT_MAPS_H

#define bt_current_map (*(u16*)0x8012B402)

typedef struct {
  u16 map;
  u8 loading;
  u8 exit;
} bt_loading_map_t;
#define bt_loading_map (*(bt_loading_map_t*)0x80127640)

typedef struct {
  u16 map;
  u16 exit;
} bt_respawn_point_t;
#define bt_respawn_point ((bt_respawn_point_t*)0x80127050)

typedef u32 (*bt_fnt_load_scene)(u16, u16, u8);
#define bt_fn_load_scene ((bt_fnt_load_scene)0x800A7990)

// Taken from ScriptHawk: https://github.com/Isotarge/ScriptHawk/blob/master/games/bt.lua
enum {
  BT_MAP_CUTSCENE_OPENING = 0x0A1, // Cutscene - Two Years have passed..
  BT_MAP_0x0A2, // Cutscene - Hag 1 Arrives
  BT_MAP_0x0A3, // Cutscene - Arrival of Mingella & Blobbelda
  BT_MAP_0x0A4, // Cutscene - Revival of Gruntilda
  BT_MAP_0x0A5, // Cutscene - Gruntilda casts the spell
  BT_MAP_0x0A6, // Cutscene - Hag 1 leaves
  BT_MAP_0x0A7, // Cutscene - Banjo vows to defeat Grunty
  BT_MAP_0x0A8, // Cutscene - Playing Poker
  BT_MAP_0x0A9, // Cutscene - Earthquake
  BT_MAP_0x0AA, // Cutscene - Mumbo takes a look outside
  BT_MAP_0x0AB, // Cutscene - Mumbo warns Banjo & Bottles
  BT_MAP_0x0AC, // Cutscene - Banjo's house is destroyed
  BT_MAP_0x0AD, // SM - Grunty's Lair
  BT_MAP_0x0AE, // SM - Behind the waterfall
  BT_MAP_SM, // SM - Spiral Mountain
  BT_MAP_MT_HUMBA = 0x0B6, // MT - Wumba's Wigwam
  BT_MAP_MT_MUMBO, // MT - Mumbo's Skull
  BT_MAP_0x0B8, // MT
  BT_MAP_0x0B9, // MT - Prison Compound
  BT_MAP_0x0BA, // MT - Columns Vault
  BT_MAP_MT_KICKBALL_LOBBY, // MT - Mayan Kickball Stadium (Lobby)
  BT_MAP_0x0BC, // MT - Code Chamber
  BT_MAP_0x0C4 = 0x0C4, // MT - Jade Snake Grove
  BT_MAP_0x0C5, // MT - Treasure Chamber
  BT_MAP_0x0C6, // MT - Kickball Arena 1
  BT_MAP_0x0C7, // GGM
  BT_MAP_0x0C8, // MT - Kickball Arena 2
  BT_MAP_0x0C9, // MT - Kickball Arena 3
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
  BT_MAP_0x0DE, // WW - Dodgem Challenge 1 vs 1
  BT_MAP_0x0DF, // WW - Dodgem Challenge 2 vs 1
  BT_MAP_0x0E0, // WW - Dodgem Challenge 3 vs 1
  BT_MAP_0x0E1, // WW - Crazy Castle Stockade
  BT_MAP_0x0E2, // WW - Crazy Castle Lobby
  BT_MAP_0x0E3, // WW - Crazy Castle Pump Room
  BT_MAP_0x0E4, // WW - Balloon Burst Game
  BT_MAP_0x0E5, // WW - Hoop Hurry
  BT_MAP_0x0E6, // WW - Star Spinner
  BT_MAP_0x0E7, // WW - The Inferno
  BT_MAP_GGM_HUMBA = 0x0E9, // GGM - Wumba's Wigwam
  BT_MAP_0x0EA, // WW - Cave of Horrors
  BT_MAP_0x0EB, // WW - Haunted Cavern
  BT_MAP_TRAIN_STATION_WW, // WW - Train Station
  BT_MAP_0x0ED, // JRL - Jolly's
  BT_MAP_0x0EE, // JRL - Pawno's Emporium
  BT_MAP_JRL_MUMBO, // JRL - Mumbo's Skull
  BT_MAP_0x0F1 = 0x0F1, // JRL - Inside the UFO
  BT_MAP_0x0F4 = 0x0F4, // JRL - Ancient Swimming Baths
  BT_MAP_0x0F6 = 0x0F6, // JRL - Electric Eel's lair
  BT_MAP_0x0F7, // JRL - Seaweed Sanctum
  BT_MAP_0x0F8, // JRL - Inside the Big Fish
  BT_MAP_0x0F9, // WW - Mr. Patch
  BT_MAP_0x0FA, // JRL - Temple of the Fishes
  BT_MAP_0x0FC = 0x0FC, // JRL - Lord Woo Fak Fak
  BT_MAP_0x0FF = 0x0FF, // JRL - Blubber's Wave Race Hire
  BT_MAP_0x100, // GI
  BT_MAP_0x101, // GI - Floor 1
  BT_MAP_TRAIN_STATION_GI, // GI - Train Station
  BT_MAP_0x103, // GI - Workers' Quarters
  BT_MAP_0x104, // GI - Trash Compactor
  BT_MAP_0x105, // GI - Elevator shaft
  BT_MAP_0x106, // GI - Floor 2
  BT_MAP_0x107, // GI - Floor 2 (Electromagnet Chamber)
  BT_MAP_0x108, // GI - Floor 3
  BT_MAP_0x109, // GI - Floor 3 (Boiler Plant)
  BT_MAP_0x10A, // GI - Floor 3 (Packing Room)
  BT_MAP_0x10B, // GI - Floor 4
  BT_MAP_0x10C, // GI - Floor 4 (Cable Room)
  BT_MAP_0x10D, // GI - Floor 4 (Quality Control)
  BT_MAP_0x10E, // GI - Floor 5
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
  BT_MAP_TDL_HUMBA = 0x11E, // TDL - Wumba's Wigwam (Small)
  BT_MAP_GI_HUMBA, // GI - Wumba's Wigwam
  BT_MAP_JRL_HUMBA, // JRL - Wumba's Wigwam
  BT_MAP_0x121, // GGM - Inside Chuffy's Wagon
  BT_MAP_TDL_HUMBA_ENLARGED, // TDL - Wumba's Wigwam (Big)
  BT_MAP_0x123, // TDL - Inside Chompa's Belly
  BT_MAP_0x124, // WW - Saucer of Peril
  BT_MAP_0x125, // GI - Water Supply Pipe
  BT_MAP_0x126, // GGM - Water Supply Pipe
  BT_MAP_0x127, // HFP - Lava Side
  BT_MAP_0x128, // HFP - Icy Side
  BT_MAP_TRAIN_STATION_HFP_LAVA, // HFP - Lava Train Station
  BT_MAP_TRAIN_STATION_HFP_ICY, // HFP - Ice Train Station
  BT_MAP_0x12B, // HFP - Chilli Billi
  BT_MAP_0x12C, // HFP - Chilly Willy
  BT_MAP_0x12D, // HFP - Kickball Stadium lobby
  BT_MAP_0x12E, // HFP - Kickball Stadium 1
  BT_MAP_0x12F, // HFP - Kickball Stadium 2
  BT_MAP_0x130, // HFP - Kickball Stadium 3
  BT_MAP_0x131, // HFP - Boggy's Igloo
  BT_MAP_0x132, // HFP - Icicle Grotto
  BT_MAP_0x133, // HFP - Inside the Volcano
  BT_MAP_HFP_MUMBO, // HFP - Mumbo's Skull
  BT_MAP_HFP_HUMBA, // HFP - Wumba's Wigwam
  BT_MAP_CCL, // CCL
  BT_MAP_0x137, // CCL - Inside the Trash Can
  BT_MAP_0x138, // CCL - Inside the Cheese Wedge
  BT_MAP_0x139, // CCL - Zubbas' Nest
  BT_MAP_0x13A, // CCL - Central Cavern
  BT_MAP_0x13B, // WW - Crazy Castle Stockade (Saucer)
  BT_MAP_0x13C, // WW - Star Spinner (Saucer)
  BT_MAP_0x13D, // CCL - Inside the Pot o' Gold
  BT_MAP_CCL_MUMBO, // CCL - Mumbo's Skull
  BT_MAP_CCL_MINGY_JONGO, // CCL - Mingy Jongo's Skull
  BT_MAP_CCL_HUMBA, // CCL - Wumba's Wigwam
  BT_MAP_DIGGER_TUNNEL, // SM - Inside the Digger Tunnel
  BT_MAP_JV, // JV
  BT_MAP_BOTTLES_HOUSE, // JV - Bottles' House
  BT_MAP_0x144, // JV - King Jingaling's Throne Room
  BT_MAP_0x145, // JV - Green Jinjo's house
  BT_MAP_0x146, // JV - Black Jinjo's house
  BT_MAP_0x147, // JV - Yellow Jinjo's house
  BT_MAP_0x148, // JV - Blue Jinjo's house
  BT_MAP_0x14A = 0x14A, // JV - Brown Jinjo's house
  BT_MAP_0x14B, // JV - Orange Jinjo's house
  BT_MAP_0x14C, // JV - Purple Jinjo's house
  BT_MAP_0x14D, // JV - Red Jinjo's house
  BT_MAP_0x14E, // JV - White Jinjo's house
  BT_MAP_0x14F, // IoH - Wooded Hollow
  BT_MAP_0x150, // IoH - Heggy's Egg Shed
  BT_MAP_0x151, // IoH - Jiggywiggy's Temple
  BT_MAP_0x152, // IoH - Plateau
  BT_MAP_0x153, // IoH - Plateau - Honey B's Hive
  BT_MAP_IOH_PINE_GROVE, // IoH - Pine Grove
  BT_MAP_IOH_CLIFF_TOP, // IoH - Cliff Top
  BT_MAP_IOH_MUMBO, // IoH - Cliff Top - Mumbo's Skull
  BT_MAP_IOH_HUMBA, // IoH - Pine Grove - Wumba's Wigwam
  BT_MAP_FILE_SELECT, // Game Select Screen
  BT_MAP_0x159, // Cutscene - Opening cutscene
  BT_MAP_IOH_WASTELAND, // IoH - Wasteland
  BT_MAP_ANOTHER_DIGGER_TUNNEL, // IoH - Inside another digger tunnel
  BT_MAP_0x15C, // IoH - Quagmire
  BT_MAP_0x15D, // CK
  BT_MAP_0x15E, // CK - The Gatehouse
  BT_MAP_CK_TOT_QUIZ_ROOM, // CK - Tower of Tragedy
  BT_MAP_CK_GUN_CHAMBER, // CK - Gun Chamber
  BT_MAP_0x161, // CCL - Canary Mary Race
  BT_MAP_0x162, // GI - Floor 4 (Clinker's Cavern)
  BT_MAP_0x163, // GGM - Ordnance Storage Entrance
  BT_MAP_0x164, // GI - Clinker's Cavern (multiplayer)
  BT_MAP_0x165, // GGM - Ordnance Storage (multiplayer)
  BT_MAP_0x166, // MT - Targitzan's Temple (multiplayer)
  BT_MAP_0x167, // MT - (character parade)
  BT_MAP_0x168, // HFP - Icy Side (character parade)
  BT_MAP_0x169, // JV - Bottles' House (character parade)
  BT_MAP_0x16A, // CK - Gun Chamber (character parade)
  BT_MAP_0x16F = 0x16F, // GGM - Canary Mary Race (1)
  BT_MAP_0x170, // GGM - Canary Mary Race (2)
  BT_MAP_TDL_MUMBO, // TDL - Mumbo's Skull
  BT_MAP_GI_MUMBO, // GI - Mumbo's Skull
  BT_MAP_0x173, // SM - Banjo's House
  BT_MAP_WW_MUMBO = 0x176, // WW - Mumbo's Skull
  BT_MAP_0x177, // MT - Targitzan's Slightly Sacred Chamber
  BT_MAP_0x178, // MT - Inside Targitzan's Temple
  BT_MAP_0x179, // MT - Targitzan's Temple Lobby
  BT_MAP_0x17A, // MT - Targitzan's Really Sacred Chamber
  BT_MAP_0x17B, // WW - Balloon Burst (multiplayer)
  BT_MAP_0x17C, // WW - Hoop Hurry (multiplayer)
  BT_MAP_0x17D, // GI - Packing Game
  BT_MAP_0x17E, // Cutscene - Zombified Throne Room
  BT_MAP_0x17F, // MT - Kickball Arena 4
  BT_MAP_0x180, // HFP - Kickball Arena
  BT_MAP_0x181, // JRL - Sea Bottom Cavern
  BT_MAP_0x182, // JRL - Sub Shootout (multiplayer)
  BT_MAP_0x183, // TDL - Chompa's Belly Shootout (multiplayer)
  BT_MAP_0x185 = 0x185, // CCL - Trash Can Mini
  BT_MAP_0x186, // WW - Dodgems
  BT_MAP_0x187, // GI - Sewer Entrance
  BT_MAP_0x188, // CCL - Zubbas' Nest (multiplayer)
  BT_MAP_0x189, // CK - Tower of Tragedy Quiz (Multiplayer)
  BT_MAP_0x18A, // CK - Inside HAG 1
  BT_MAP_TITLE_SCREEN, // Intro Screen
  BT_MAP_0x18C, // Cutscene - Introduction to B.O.B.
  BT_MAP_0x18D, // Cutscene - Jingaling Zapped
  BT_MAP_0x18E, // Cutscene - Meanwhile.... Jingaling Zapping
  BT_MAP_0x18F, // Cutscene - B.O.B preparing to fire
  BT_MAP_0x190, // Cutscene - Jingaling Getting Zapped
  BT_MAP_CUTSCENE_SAD_PARTY_AT_BOTTLES, // Cutscene - Sad Party at Bottles'
  BT_MAP_0x192, // Cutscene - Bottles Eating Burnt Food
  BT_MAP_0x193, // Cutscene - Bottles' energy restoring
  BT_MAP_CUTSCENE_REVIVAL, // Cutscene - Banjo and Kazooie Running Into Gun Chamber
  BT_MAP_0x195, // Cutscene - Banjo and Kazooie at B.O.B's controls
  BT_MAP_0x196, // Cutscene - Kick About
  BT_MAP_0x197, // Cutscene - `I wonder what we'll hit...` Kazooie
  BT_MAP_0x198, // Cutscene - Jingaling Restoring
  BT_MAP_0x199, // Cutscene - All Jinjos Happy Again
  BT_MAP_0x19A, // CK - HAG 1
  BT_MAP_0x19B, // JV - Jingaling's Zombified Palace
  BT_MAP_0x19C, // Cutscene - Roll the credits
  BT_MAP_0x19D, // Cutscene - Character Parade
  BT_MAP_0x1A6 = 0x1A6, // JRL - Smuggler's cavern
  BT_MAP_0x1A7, // JRL
  BT_MAP_0x1A8, // JRL - Atlantis
  BT_MAP_0x1A9, // JRL - Sea Bottom
};

#endif // BT_MAPS_H
