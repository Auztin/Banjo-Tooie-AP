#include "all.h"

s32 custom_flag_signpost(u16 scene, u16 id) {
  u32 uid = (scene << 16) | id;
  switch (uid) {
    // Jinjo Village
    case 0x0142008D: return 0x00;
    // Wooded Hollow
    case 0x014F0027: return 0x01;
    case 0x014F0076: return 0x02;
    case 0x014F0077: return 0x03;
    case 0x014F0078: return 0x04;
    case 0x014F0081: return 0x05;
    // WH - Jiggywiggy's Temple
    case 0x01510011: return 0x06;
    case 0x01510012: return 0x07;
    case 0x01510013: return 0x08;
    case 0x01510014: return 0x09;
    case 0x01510015: return 0x0A;
    case 0x01510016: return 0x0B;
    case 0x01510017: return 0x0C;
    case 0x01510018: return 0x0D;
    // Pine Grove
    case 0x01540002: return 0x0E;
    case 0x01540024: return 0x0F;
    case 0x01540025: return 0x10;
    // Cliff Top
    case 0x01550054: return 0x11;
    // Wasteland
    case 0x015A0022: return 0x12;
    // MT - Mumbo's Skull
    case 0x00B70009: return 0x13;
    // MT
    case 0x00B8009D: return 0x14;
    // MT - Prison Compound
    case 0x00B90074: return 0x15;
    case 0x00B90094: return 0x16;
    // MT - Jade Snake Grove
    case 0x00C40052: return 0x17;
    case 0x00C4005E: return 0x18;
    case 0x00C4005F: return 0x19;
    // MT - Inside Targitzan's Temple
    case 0x0178001C: return 0x1A;
    case 0x0178006D: return 0x1B;
    // GGM - Gloomy Caverns
    case 0x00D20021: return 0x1C;
    // GGM - Generator Cavern
    case 0x00D3003B: return 0x1D;
    // GGM - Toxic Gas Cave
    case 0x00DA0008: return 0x1E;
    // GGM - Inside Chuffy's Wagon
    case 0x0121000B: return 0x1F;
    // WW
    case 0x00D6003E: return 0x20;
    case 0x00D60036: return 0x21;
    case 0x00D60050: return 0x22;
    case 0x00D600AC: return 0x23;
    case 0x00D601DF: return 0x24;
    // WW - Crazy Castle Pump Room
    case 0x00E30012: return 0x25;
    // WW - Cave of Horrors
    case 0x00EA0028: return 0x26;
    // WW - The Haunted Cavern
    case 0x00EB0021: return 0x27;
    // JRL - Seaweed Sanctum
    case 0x00F70078: return 0x28;
    // JRL - Blubber's Waveracer Hire
    case 0x00FF0009: return 0x29;
    // JRL - Smugglers' Cavern
    case 0x01A600A3: return 0x2A;
    // JRL
    case 0x01A701CE: return 0x2B;
    // GI
    case 0x01000114: return 0x2C;
    // GI F1 - Worker's Quarters
    case 0x01030032: return 0x2D;
    // GI - Elevator Shaft
    case 0x0105001E: return 0x2E;
    case 0x0105001F: return 0x2F;
    // TDL
    case 0x0112017E: return 0x30;
    // TDL - Inside the Mountain
    case 0x01160050: return 0x31;
    case 0x0116006B: return 0x32;
    // TDL - River Passage
    case 0x0117002B: return 0x33;
    // HFP - Lava
    case 0x012700FA: return 0x34;
    case 0x01270155: return 0x35;
    // HFP - Inside the Volcano
    case 0x01330047: return 0x36;
    case 0x0133004D: return 0x37;
    case 0x0133004E: return 0x38;
    // CCL - Central Cavern
    case 0x013A0149: return 0x39;
    case 0x013A014A: return 0x3A;
    case 0x013A014B: return 0x3B;
    // CCL - Wumba's Wigwam
    case 0x01400004: return 0x3C;
  }
  return -1;
}
