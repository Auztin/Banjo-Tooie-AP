#include "all.h"

s32 custom_flag_signpost(u16 scene, u16 id) {
  u32 uid = (scene << 16) | id;
  switch (uid) {
    // Jinjo Village
    case 0x0142008D: return 0x00; // 1231483 SIGNIH1 = "IoH: Grey Jinjo Family House Signpost"
    // Wooded Hollow
    case 0x014F0027: return 0x01; // 1231488 SIGNIH6 = "IoH: Wooded Hollow Path to Plateau Signpost"
    case 0x014F0076: return 0x02; // 1231486 SIGNIH4 = "IoH: Behind Jiggywiggy's Temple Signpost 2"
    case 0x014F0077: return 0x03; // 1231485 SIGNIH3 = "IoH: Behind Jiggywiggy's Temple Signpost 1"
    case 0x014F0078: return 0x04; // 1231487 SIGNIH5 = "IoH: Behind Jiggywiggy's Temple Signpost 3"
    case 0x014F0081: return 0x05; // 1231484 SIGNIH2 = "IoH: Outside Heggy's Egg Shed Signpost"
    // WH - Jiggywiggy's Temple
    case 0x01510011: return 0x06; // 1231489 SIGNIH7 = "IoH: Jiggywiggy's Temple Signpost 1"
    case 0x01510012: return 0x07; // 1231490 SIGNIH8 = "IoH: Jiggywiggy's Temple Signpost 2"
    case 0x01510013: return 0x08; // 1231491 SIGNIH9 = "IoH: Jiggywiggy's Temple Signpost 3"
    case 0x01510014: return 0x09; // 1231492 SIGNIH10 = "IoH: Jiggywiggy's Temple Signpost 4"
    case 0x01510015: return 0x0A; // 1231493 SIGNIH11 = "IoH: Jiggywiggy's Temple Signpost 5"
    case 0x01510016: return 0x0B; // 1231494 SIGNIH12 = "IoH: Jiggywiggy's Temple Signpost 6"
    case 0x01510017: return 0x0C; // 1231495 SIGNIH13 = "IoH: Jiggywiggy's Temple Signpost 7"
    case 0x01510018: return 0x0D; // 1231496 SIGNIH14 = "IoH: Jiggywiggy's Temple Signpost 8"
    // Pine Grove
    case 0x01540002: return 0x0E; // 1231499 SIGNIH17 = "IoH: Pine Grove Signpost 3"
    case 0x01540024: return 0x0F; // 1231498 SIGNIH16 = "IoH: Pine Grove Signpost 2"
    case 0x01540025: return 0x10; // 1231497 SIGNIH15 = "IoH: Pine Grove Signpost 1"
    // Cliff Top
    case 0x01550054: return 0x11; // 1231500 SIGNIH18 = "IoH: Cliff Top Signpost"
    // Wasteland
    case 0x015A0022: return 0x12; // 1231501 SIGNIH19 = "IoH: Wasteland Signpost"
    // MT - Mumbo's Skull
    case 0x00B70009: return 0x13; // 1231502 SIGNMT1 = "MT: Mumbo's Skull Signpost"
    // MT
    case 0x00B8009D: return 0x14; // 1231503 SIGNMT2 = "MT: Golden Goliath Signpost"
    // MT - Prison Compound
    case 0x00B90074: return 0x15; // 1231504 SIGNMT3 = "MT: Pillars Signpost"
    case 0x00B90094: return 0x16; // 1231505 SIGNMT4 = "MT: Prison Compound Quicksand Signpost"
    // MT - Jade Snake Grove
    case 0x00C40052: return 0x17; // 1231508 SIGNMT7 = "MT: Left of Code Chamber Signpost"
    case 0x00C4005E: return 0x18; // 1231507 SIGNMT6 = "MT: Jade Snake Grove Quicksand Signpost 2"
    case 0x00C4005F: return 0x19; // 1231506 SIGNMT5 = "MT: Jade Snake Grove Quicksand Signpost 1"
    // MT - Inside Targitzan's Temple
    case 0x0178001C: return 0x1A; // 1231509 SIGNMT8 = "MT: Targitzan's Temple Signpost 1"
    case 0x0178006D: return 0x1B; // 1231510 SIGNMT9 = "MT: Targitzan's Temple Signpost 2"
    // GGM - Gloomy Caverns
    case 0x00D20021: return 0x1C; // 1231511 SIGNGM1 = "GGM: Gloomy Cavern Signpost"
    // GGM - Generator Cavern
    case 0x00D3003B: return 0x1D; // 1231512 SIGNGM2 = "GGM: Generator Cavern Signpost"
    // GGM - Toxic Gas Cave
    case 0x00DA0008: return 0x1E; // 1231513 SIGNGM3 = "GGM: Toxic Gas Cave Signpost"
    // GGM - Inside Chuffy's Wagon
    case 0x0121000B: return 0x1F; // 1231514 SIGNGM4 = "GGM: Inside Chuffy's Wagon Signpost"
    // WW
    case 0x00D6003E: return 0x20; // 1231516 SIGNWW2 = "WW: Madame Grunty Signpost"
    case 0x00D60036: return 0x21; // 1231517 SIGNWW3 = "WW: Burger Stand Signpost"
    case 0x00D60050: return 0x22; // 1231519 SIGNWW5 = "WW: Cactus of Strength Signpost"
    case 0x00D600AC: return 0x23; // 1231518 SIGNWW4 = "WW: Fries Stand Signpost"
    case 0x00D601DF: return 0x24; // 1231515 SIGNWW1 = "WW: Dodgem Dome Signpost"
    // WW - Crazy Castle Pump Room
    case 0x00E30012: return 0x25; // 1231520 SIGNWW6 = "WW: Pump Room Signpost"
    // WW - Cave of Horrors
    case 0x00EA0028: return 0x26; // 1231521 SIGNWW7 = "WW: Gobi Cage Signpost"
    // WW - The Haunted Cavern
    case 0x00EB0021: return 0x27; // 1231522 SIGNWW8 = "WW: The Haunted Caverns Signpost"
    // JRL - Seaweed Sanctum
    case 0x00F70078: return 0x28; // 1231523 SIGNJR1 = "JRL: Seeweed Sanctum Signpost"
    // JRL - Blubber's Waveracer Hire
    case 0x00FF0009: return 0x29; // 1231524 SIGNJR2 = "JRL: Blubber's Signpost"
    // JRL - Smugglers' Cavern
    case 0x01A600A3: return 0x2A; // 1231525 SIGNJR3 = "JRL: Smuggler's Cavern Signpost"
    // JRL
    case 0x01A701CE: return 0x2B; // 1231526 SIGNJR4 = "JRL: Waste Pipe Alcove Signpost"
    // GI
    case 0x01000114: return 0x2C; // 1231531 SIGNGI1 = "GI Outside: Signpost"
    // GI F1 - Worker's Quarters
    case 0x01030032: return 0x2D; // 1231532 SIGNGI2 = "GI Floor 1: Workers Quarters Signpost"
    // GI - Elevator Shaft
    case 0x0105001E: return 0x2E; // 1231533 SIGNGI3 = "GI Elevator Shaft: Signpost 1"
    case 0x0105001F: return 0x2F; // 1231534 SIGNGI4 = "GI Elevator Shaft: Signpost 2"
    // TDL
    case 0x0112017E: return 0x30; // 1231527 SIGNTL1 = "TDL: Roar Cage Signpost"
    // TDL - Inside the Mountain
    case 0x01160050: return 0x31; // 1231528 SIGNTL2 = "TDL: Inside The Mountain Near Cheato Page Signpost"
    case 0x0116006B: return 0x32; // 1231529 SIGNTL3 = "TDL: Inside The Mountain Near Top Signpost"
    // TDL - River Passage
    case 0x0117002B: return 0x33; // 1231530 SIGNTL4 = "TDL: River Passage Signpost"
    // HFP - Lava
    case 0x012700FA: return 0x34; // 1231536 SIGNHP2 = "HFP: Top Hot Pool Signpost"
    case 0x01270155: return 0x35; // 1231535 SIGNHP1 = "HFP: Bottom Hot Pool Signpost"
    // HFP - Inside the Volcano
    case 0x01330047: return 0x36; // 1231538 SIGNHP4 = "HFP: Volcano Signpost 2"
    case 0x0133004D: return 0x37; // 1231537 SIGNHP3 = "HFP: Volcano Signpost 1"
    case 0x0133004E: return 0x38; // 1231539 SIGNHP5 = "HFP: Volcano Signpost 3"
    // CCL - Central Cavern
    case 0x013A0149: return 0x39; // 1231540 SIGNCC1 = "CCL: Indoors Pool Underwater Signpost"
    case 0x013A014A: return 0x3A; // 1231542 SIGNCC3 = "CCL: On Rim of Glowbo Pool Signpost"
    case 0x013A014B: return 0x3B; // 1231541 SIGNCC2 = "CCL: Sack Pack Silo Signpost"
    // CCL - Wumba's Wigwam
    case 0x01400004: return 0x3C; // 1231543 SIGNCC4 = "CCL: Wumba's Wigwam Signpost"
  }
  return -1;
}
