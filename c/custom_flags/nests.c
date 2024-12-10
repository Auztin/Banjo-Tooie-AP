s32 custom_flag_nest(u16 scene, u16 id) {
  u32 uid = (scene << 16) | id;
  switch (uid) {
    // Gruntilda's Lair
    case 0x00AD0009: return 0x000;
    case 0x00AD000A: return 0x001;
    case 0x00AD000B: return 0x002;
    case 0x00AD000C: return 0x003;
    case 0x00AD000D: return 0x004;
    case 0x00AD000E: return 0x005;
    case 0x00AD000F: return 0x006;
    // Spiral Mountain
    case 0x00AF002F: return 0x007;
    case 0x00AF007E: return 0x008;
    case 0x00AF007F: return 0x009;
    case 0x00AF0080: return 0x00A;
    case 0x00AF0081: return 0x00B;
    case 0x00AF0082: return 0x00C;
    case 0x00AF0083: return 0x00D;
    case 0x00AF0084: return 0x00E;
    case 0x00AF0085: return 0x00F;
    case 0x00AF008A: return 0x010;
    case 0x00AF008B: return 0x011;
    case 0x00AF008C: return 0x012;
    case 0x00AF008D: return 0x013;
    case 0x00AF008E: return 0x014;
    case 0x00AF0097: return 0x015;
    case 0x00AF0098: return 0x016;
    case 0x00AF0099: return 0x017;
    case 0x00AF009B: return 0x018;
    // Digger Tunnel
    case 0x0141002E: return 0x019;
    // Jinjo Village
    case 0x01420071: return 0x01A;
    case 0x01420072: return 0x01B;
    case 0x01420073: return 0x01C;
    case 0x01420074: return 0x01D;
    case 0x0142007A: return 0x01E;
    case 0x0142007B: return 0x01F;
    case 0x01420081: return 0x020;
    case 0x01420082: return 0x021;
    case 0x01420083: return 0x022;
    case 0x01420084: return 0x023;
    case 0x0142008B: return 0x024;
    case 0x0142008C: return 0x025;
    // Bottles' House
    case 0x01430014: return 0x026;
    case 0x01430015: return 0x027;
    case 0x01430016: return 0x028;
    case 0x01430017: return 0x029;
    // Wooded Hollow
    case 0x014F006E: return 0x02A;
    case 0x014F006F: return 0x02B;
    case 0x014F0070: return 0x02C;
    case 0x014F0071: return 0x02D;
    case 0x014F0072: return 0x02E;
    case 0x014F0073: return 0x02F;
    case 0x014F0074: return 0x030;
    case 0x014F0083: return 0x031;
    case 0x014F0084: return 0x032;
    // Plateau
    case 0x0152002F: return 0x033;
    case 0x01520030: return 0x034;
    case 0x01520032: return 0x035;
    case 0x01520033: return 0x036;
    case 0x01520034: return 0x037;
    case 0x01520035: return 0x038;
    case 0x01520062: return 0x039;
    // Pine Grove
    case 0x0154001E: return 0x03A;
    case 0x0154001F: return 0x03B;
    case 0x01540020: return 0x03C;
    case 0x01540021: return 0x03D;
    case 0x01540022: return 0x03E;
    case 0x01540023: return 0x03F;
    // Cliff Top
    case 0x01550034: return 0x040;
    case 0x0155004A: return 0x041;
    case 0x01550068: return 0x042;
    case 0x01550069: return 0x043;
    case 0x0155006A: return 0x044;
    case 0x0155006B: return 0x045;
    case 0x0155006C: return 0x046;
    // IoH Humba
    case 0x01570010: return 0x047;
    case 0x01570011: return 0x048;
    // Wasteland
    case 0x015A001C: return 0x049;
    case 0x015A0025: return 0x04A;
    case 0x015A0026: return 0x04B;
    case 0x015A0059: return 0x04C;
    case 0x015A005A: return 0x04D;
    case 0x015A005D: return 0x04E;
    case 0x015A005E: return 0x04F;
    case 0x015A005F: return 0x050;
    // Another Digger Tunnel
    case 0x015B0020: return 0x051;
    case 0x015B0021: return 0x052;
    // Quagmire
    case 0x015C00B8: return 0x053;
    case 0x015C00B9: return 0x054;
    case 0x015C00BA: return 0x055;
    case 0x015C00BB: return 0x056;
    case 0x015C00BC: return 0x057;
    case 0x015C00BD: return 0x058;
    // MT Humba
    case 0x00B60011: return 0x059;
    case 0x00B60012: return 0x05A;
    // MT Mumbo
    case 0x00B7001E: return 0x05B;
    case 0x00B7001F: return 0x05C;
    // MT
    case 0x00B80055: return 0x05D;
    case 0x00B80066: return 0x05E;
    case 0x00B80076: return 0x05F;
    case 0x00B80090: return 0x060;
    case 0x00B80091: return 0x061;
    case 0x00B80095: return 0x062;
    case 0x00B8009B: return 0x063;
    case 0x00B8009C: return 0x064;
    case 0x00B8009F: return 0x065;
    case 0x00B800A0: return 0x066;
    // MT Prison Compound
    case 0x00B90010: return 0x067;
    case 0x00B90015: return 0x068;
    case 0x00B90034: return 0x069;
    case 0x00B9004D: return 0x06A;
    case 0x00B9004E: return 0x06B;
    case 0x00B90066: return 0x06C;
    case 0x00B90097: return 0x06D;
    // MT Jade Snake Grove
    case 0x00C40058: return 0x06E;
    case 0x00C4005B: return 0x06F;
    case 0x00C4005C: return 0x070;
    // MT Targitzan's Temple
    case 0x01780009: return 0x071;
    case 0x01780021: return 0x072;
    case 0x01780043: return 0x073;
    case 0x01780044: return 0x074;
    case 0x01780045: return 0x075;
    case 0x01780046: return 0x076;
    case 0x01780051: return 0x077;
    case 0x01780052: return 0x078;
    case 0x01780053: return 0x079;
    case 0x01780055: return 0x07A;
    case 0x01780064: return 0x07B; // still gives golden eggs
    // MT Targitzan's Temple Lobby
    case 0x0179000C: return 0x07C;
    case 0x0179000D: return 0x07D;
    case 0x0179000E: return 0x07E;
    case 0x0179000F: return 0x07F;
    case 0x01790010: return 0x080;
    case 0x01790011: return 0x081;
    // GGM
    case 0x00C70155: return 0x082;
    case 0x00C70158: return 0x083;
    case 0x00C7016D: return 0x084;
    case 0x00C7016E: return 0x085;
    // GGM Fuel Depot
    case 0x00CA0022: return 0x086;
    case 0x00CA0023: return 0x087;
    case 0x00CA0024: return 0x088;
    case 0x00CA0025: return 0x089;
    case 0x00CA002B: return 0x08A;
    case 0x00CA002C: return 0x08B;
    // GGM Crushing Shed
    case 0x00CB0010: return 0x08C;
    case 0x00CB0011: return 0x08D;
    // GGM Flooded Caves
    case 0x00CC0041: return 0x08E;
    case 0x00CC0042: return 0x08F;
    // GGM Water Storage
    case 0x00CD0010: return 0x090;
    // GGM Gloomy Caverns
    case 0x00D2001C: return 0x091;
    case 0x00D20022: return 0x092;
    case 0x00D2004F: return 0x093;
    case 0x00D20051: return 0x094;
    // GGM Generator Cavern
    case 0x00D30034: return 0x095;
    // GGM Power Hut
    case 0x00D40010: return 0x096;
    // GGM Train Station
    case 0x00D7000B: return 0x097;
    case 0x00D7000D: return 0x098;
    case 0x00D70010: return 0x099;
    case 0x00D70019: return 0x09A;
    // GGM Prospetor's Hut
    case 0x00D80017: return 0x09B;
    // GGM Mumbo
    case 0x00D9000D: return 0x09C;
    case 0x00D9000E: return 0x09D;
    case 0x00D9000F: return 0x09E;
    // GGM Toxic Gas Cave
    case 0x00DA0013: return 0x09F;
    case 0x00DA0014: return 0x0A0;
    // GGM Canary Cave
    case 0x00DB0010: return 0x0A1;
    case 0x00DB0013: return 0x0A2;
    case 0x00DB07FF: return 0x0A3;
    case 0x00DB07FE: return 0x0A4;
    // GGM Ordnance Storage Entrance
    case 0x01630009: return 0x0A5;
    case 0x0163000D: return 0x0A6;
    case 0x0163000E: return 0x0A7;
    // WW
    case 0x00D600AA: return 0x0A8;
    case 0x00D600AB: return 0x0A9;
    case 0x00D601A7: return 0x0AA;
    case 0x00D601A8: return 0x0AB;
    case 0x00D601B5: return 0x0AC;
    case 0x00D601B6: return 0x0AD;
    case 0x00D601B7: return 0x0AE;
    case 0x00D601B8: return 0x0AF;
    case 0x00D601B9: return 0x0B0;
    case 0x00D601BA: return 0x0B1;
    case 0x00D601BB: return 0x0B2;
    case 0x00D601BC: return 0x0B3;
    // WW Crazy Castle Stockade
    case 0x00E10035: return 0x0B4;
    case 0x00E10043: return 0x0B5;
    // WW Pump Room
    case 0x00E30016: return 0x0B6;
    case 0x00E30017: return 0x0B7;
    // WW Star Spinner
    case 0x00E60011: return 0x0B8;
    case 0x00E60013: return 0x0B9;
    case 0x00E60092: return 0x0BA;
    // WW Inferno
    case 0x00E70079: return 0x0BB;
    case 0x00E70088: return 0x0BC;
    // WW Haunted Caverns
    case 0x00EB001D: return 0x0BD;
    case 0x00EB0024: return 0x0BE;
    case 0x00EB0025: return 0x0BF;
    // WW Train Station
    case 0x00EC0038: return 0x0C0;
    case 0x00EC0039: return 0x0C1;
    // WW Big Top
    case 0x00F9001F: return 0x0C2;
    case 0x00F90020: return 0x0C3;
    case 0x00F90025: return 0x0C4;
    case 0x00F90026: return 0x0C5;
    case 0x00F9002B: return 0x0C6;
    case 0x00F9002E: return 0x0C7;
    case 0x00F9002F: return 0x0C8;
    case 0x00F90036: return 0x0C9;
    case 0x00F90038: return 0x0CA;
    case 0x00F90039: return 0x0CB;
    case 0x00F9003A: return 0x0CC;
    case 0x00F9003B: return 0x0CD;
    case 0x00F9003E: return 0x0CE;
    case 0x00F9003F: return 0x0CF;
    case 0x00F90040: return 0x0D0;
    case 0x00F90041: return 0x0D1;
    // JRL Jolly's
    case 0x00ED0015: return 0x0D2;
    case 0x00ED0016: return 0x0D3;
    case 0x00ED001B: return 0x0D4;
    case 0x00ED001C: return 0x0D5;
    case 0x00ED0027: return 0x0D6;
    case 0x00ED003A: return 0x0D7;
    // JRL Pawno's Emporium
    case 0x00EE0016: return 0x0D8;
    case 0x00EE0017: return 0x0D9;
    case 0x00EE0018: return 0x0DA;
    // JRL Seaweed Sanctum
    case 0x00F70004: return 0x0DB;
    case 0x00F7003B: return 0x0DC;
    case 0x00F7003C: return 0x0DD;
    case 0x00F70041: return 0x0DE;
    // JRL Inside the Big Fish
    case 0x00F8001D: return 0x0DF;
    case 0x00F8001E: return 0x0E0;
    // JRL Temple of the Fishes
    case 0x00FA0018: return 0x0E1;
    case 0x00FA0019: return 0x0E2;
    case 0x00FA001A: return 0x0E3;
    case 0x00FA001B: return 0x0E4;
    // JRL Davy Jones' Locker
    case 0x00FC0007: return 0x0E5;
    case 0x00FC0008: return 0x0E6;
    case 0x00FC0009: return 0x0E7;
    case 0x00FC000A: return 0x0E8;
    // JRL Humba
    case 0x01200011: return 0x0E9;
    // JRL Smuggler's Cavern
    case 0x01A601C2: return 0x0EA;
    case 0x01A601C3: return 0x0EB;
    // JRL
    case 0x01A70152: return 0x0EC;
    // JRL Atlantis
    case 0x01A80171: return 0x0ED;
    case 0x01A80172: return 0x0EE;
    case 0x01A80173: return 0x0EF;
    case 0x01A801C5: return 0x0F0;
    case 0x01A801C6: return 0x0F1;
    case 0x01A807FF: return 0x0F2;
    // JRL Locker Cavern
    case 0x01A90190: return 0x0F3;
    case 0x01A90191: return 0x0F4;
    case 0x01A90193: return 0x0F5;
    case 0x01A90194: return 0x0F6;
    case 0x01A90195: return 0x0F7;
    case 0x01A907FF: return 0x0F8;
    case 0x01A907FE: return 0x0F9;
    // TDL
    case 0x0112001B: return 0x0FA;
    case 0x0112001D: return 0x0FB;
    case 0x01120021: return 0x0FC;
    case 0x01120066: return 0x0FD;
    case 0x01120067: return 0x0FE;
    case 0x011200FB: return 0x0FF;
    case 0x01120113: return 0x100;
    case 0x01120139: return 0x101;
    case 0x0112014D: return 0x102;
    case 0x0112014E: return 0x103;
    case 0x01120151: return 0x104;
    case 0x011201BB: return 0x105;
    case 0x011201BC: return 0x106;
    case 0x011201BD: return 0x107;
    case 0x011201BE: return 0x108;
    case 0x0112020C: return 0x109;
    case 0x0112020D: return 0x10A;
    case 0x0112020E: return 0x10B;
    case 0x01120213: return 0x10C;
    case 0x01120214: return 0x10D;
    // TDL Terry's Nest
    case 0x0113002C: return 0x10E;
    case 0x0113002D: return 0x10F;
    // TDL Train Station
    case 0x0114002E: return 0x110;
    case 0x0114002F: return 0x111;
    case 0x01140032: return 0x112;
    case 0x01140043: return 0x113;
    // TDL Oogle Boogle Cave
    case 0x01150023: return 0x114;
    case 0x01150031: return 0x115;
    case 0x01150034: return 0x116;
    case 0x01150035: return 0x117;
    // TDL Inside the Mountain
    case 0x0116004E: return 0x118;
    case 0x0116004F: return 0x119;
    case 0x01160068: return 0x11A;
    case 0x01160069: return 0x11B;
    // TDL River Passage
    case 0x01170024: return 0x11C;
    // TDL Scrotty Cave
    case 0x01180030: return 0x11D;
    case 0x01180032: return 0x11E;
    case 0x01180034: return 0x11F;
    // TDL Unga Bunga Cave
    case 0x01190011: return 0x120;
    case 0x01190012: return 0x121;
    case 0x01190014: return 0x122;
    case 0x01190015: return 0x123;
    case 0x01190016: return 0x124;
    case 0x01190017: return 0x125;
    // TDL Stomping Plains
    case 0x011A0027: return 0x126;
    case 0x011A0028: return 0x127;
    case 0x011A0029: return 0x128;
    case 0x011A002A: return 0x129;
    case 0x011A002C: return 0x12A;
    case 0x011A002D: return 0x12B;
    case 0x011A003A: return 0x12C;
    // TDL Bonfire Cavern
    case 0x011B0012: return 0x12D;
    case 0x011B0013: return 0x12E;
    // TDL Mumbo
    case 0x01710009: return 0x12F;
    case 0x0171000E: return 0x130;
    // GI Outside
    case 0x010000F6: return 0x131;
    case 0x010000F7: return 0x132;
    case 0x010000FD: return 0x133;
    case 0x010000FF: return 0x134;
    case 0x01000194: return 0x135;
    // GI Floor 1
    case 0x01010064: return 0x136;
    case 0x01010077: return 0x137;
    case 0x0101008C: return 0x138;
    case 0x0101008D: return 0x139;
    case 0x0101009F: return 0x13A;
    case 0x010100A1: return 0x13B;
    // GI Train Station
    case 0x0102001E: return 0x13C;
    case 0x01020028: return 0x13D;
    case 0x0102002C: return 0x13E;
    // GI Worker's Quarters
    case 0x01030023: return 0x13F;
    case 0x01030024: return 0x140;
    // GI Trash compactor
    case 0x01040014: return 0x141;
    case 0x01040015: return 0x142;
    // GI Elevator Shaft
    case 0x01050024: return 0x143;
    case 0x01050025: return 0x144;
    case 0x01050026: return 0x145;
    // GI Floor 2
    case 0x010600A5: return 0x146;
    case 0x010600AF: return 0x147;
    case 0x010600E1: return 0x148;
    case 0x010600F0: return 0x149;
    case 0x010600F1: return 0x14A;
    case 0x010600F2: return 0x14B;
    case 0x010600F3: return 0x14C;
    case 0x010600FF: return 0x14D;
    case 0x010607FF: return 0x14E;
    case 0x010607FE: return 0x14F;
    // GI Floor 2 Electromagnetic Chamber
    case 0x01070017: return 0x150;
    case 0x01070026: return 0x151;
    case 0x01070027: return 0x152;
    // GI Floor 3
    case 0x0108000D: return 0x153;
    case 0x01080010: return 0x154;
    case 0x0108004D: return 0x155;
    case 0x010800FB: return 0x156;
    case 0x01080101: return 0x157;
    case 0x01080102: return 0x158;
    // GI Boiler Plant
    case 0x01090047: return 0x159;
    case 0x0109004E: return 0x15A;
    // GI Floor 4
    case 0x010B006D: return 0x15B;
    case 0x010B006E: return 0x15C;
    case 0x010B006F: return 0x15D;
    case 0x010B0086: return 0x15E;
    case 0x010B0087: return 0x15F;
    case 0x010B00AB: return 0x160;
    case 0x010B07FF: return 0x161;
    // GI Quality Control
    case 0x010D0013: return 0x162;
    case 0x010D0017: return 0x163;
    case 0x010D0018: return 0x164;
    // GI Floor 5
    case 0x010E000D: return 0x165;
    case 0x010E0045: return 0x166;
    case 0x010E0052: return 0x167;
    // GI Air Conditioning Plant
    case 0x010F0002: return 0x168;
    case 0x010F002E: return 0x169;
    case 0x010F002F: return 0x16A;
    case 0x010F0035: return 0x16B;
    case 0x010F0041: return 0x16C;
    // GI Repair Depot
    case 0x01100036: return 0x16D;
    case 0x01100038: return 0x16E;
    // GI Waste Disposal
    case 0x0111006B: return 0x16F;
    case 0x0111007C: return 0x170;
    case 0x0111007D: return 0x171;
    case 0x0111008E: return 0x172;
    // GI Clinker's Cavern
    case 0x0162008A: return 0x173;
    case 0x0162008B: return 0x174;
    case 0x01620090: return 0x175;
    case 0x01620091: return 0x176;
    case 0x016200D6: return 0x177;
    case 0x016200D9: return 0x178;
    case 0x016200DA: return 0x179;
    case 0x016200DC: return 0x17A;
    // GI Sewer Entrance
    case 0x0187000C: return 0x17B;
    case 0x0187000D: return 0x17C;
    case 0x0187000E: return 0x17D;
    case 0x0187000F: return 0x17E;
    // HFP Lava
    case 0x012700B7: return 0x17F;
    case 0x012700E4: return 0x180;
    case 0x012700EE: return 0x181;
    case 0x012700EF: return 0x182;
    case 0x012700F0: return 0x183;
    case 0x012700F1: return 0x184;
    case 0x01270102: return 0x185;
    case 0x01270103: return 0x186;
    case 0x01270104: return 0x187;
    case 0x01270125: return 0x188;
    case 0x01270126: return 0x189;
    // HFP Icy
    case 0x01280139: return 0x18A;
    case 0x01280147: return 0x18B;
    case 0x0128014B: return 0x18C;
    case 0x0128014C: return 0x18D;
    case 0x0128014D: return 0x18E;
    case 0x0128014E: return 0x18F;
    case 0x0128014F: return 0x190;
    // HFP Lava Train Station
    case 0x0129004B: return 0x191;
    case 0x0129005D: return 0x192;
    // HFP Icy Train Station
    case 0x012A0003: return 0x193;
    case 0x012A0004: return 0x194;
    // HFP Chilli Billi
    case 0x012B0001: return 0x195;
    // HFP Chilly Willy
    case 0x012C0001: return 0x196;
    // HFP Kickball Coliseum
    case 0x012D0034: return 0x197;
    case 0x012D0035: return 0x198;
    case 0x012D0056: return 0x199;
    case 0x012D0057: return 0x19A;
    case 0x012D006B: return 0x19B;
    case 0x012D006C: return 0x19C;
    // HFP Icicle Grotto
    case 0x01320077: return 0x19D;
    case 0x01320078: return 0x19E;
    case 0x01320079: return 0x19F;
    case 0x0132007A: return 0x1A0;
    case 0x0132007B: return 0x1A1;
    case 0x0132007C: return 0x1A2;
    // HFP Mumbo
    case 0x0134000F: return 0x1A3;
    case 0x01340012: return 0x1A4;
    // HFP Humba
    case 0x01350004: return 0x1A5;
    case 0x0135000A: return 0x1A6;
    // CCL
    case 0x0136005D: return 0x1A7;
    case 0x0136005E: return 0x1A8;
    case 0x0136005F: return 0x1A9;
    case 0x0136006E: return 0x1AA;
    case 0x013600D0: return 0x1AB;
    case 0x013600D8: return 0x1AC;
    case 0x013600D9: return 0x1AD;
    case 0x01360107: return 0x1AE;
    case 0x01360108: return 0x1AF;
    case 0x01360109: return 0x1B0;
    case 0x0136010A: return 0x1B1;
    case 0x0136011D: return 0x1B2;
    case 0x0136011E: return 0x1B3;
    case 0x0136011F: return 0x1B4;
    case 0x01360120: return 0x1B5;
    case 0x01360124: return 0x1B6;
    case 0x01360125: return 0x1B7;
    case 0x01360126: return 0x1B8;
    case 0x01360127: return 0x1B9;
    case 0x01360143: return 0x1BA;
    case 0x01360144: return 0x1BC;
    case 0x01360145: return 0x1BB;
    case 0x01360146: return 0x1BD;
    case 0x01360152: return 0x1BE;
    case 0x0136017F: return 0x1BF;
    case 0x01360180: return 0x1C0;
    case 0x01360181: return 0x1C1;
    case 0x01360182: return 0x1C2;
    case 0x013601A3: return 0x1C3;
    case 0x013601C9: return 0x1C4;
    case 0x013601CA: return 0x1C5;
    case 0x013601CB: return 0x1C6;
    case 0x013601CC: return 0x1C7;
    case 0x013607FF: return 0x1C8;
    case 0x013607FE: return 0x1C9;
    // CCL Trash Can
    case 0x0137002E: return 0x1CA;
    case 0x0137002F: return 0x1CB;
    // CCL Cheese Wedge
    case 0x0138001A: return 0x1CC;
    case 0x0138001F: return 0x1CD;
    // CCL Central Cavern
    case 0x013A005D: return 0x1CE;
    case 0x013A005E: return 0x1CF;
    case 0x013A0103: return 0x1D0;
    case 0x013A0107: return 0x1D1;
    case 0x013A011E: return 0x1D2;
    case 0x013A011F: return 0x1D3;
    case 0x013A0134: return 0x1D4;
    // CCL Pot O Gold
    case 0x013D000F: return 0x1D5;
    case 0x013D0010: return 0x1D6;
    // CCL Humba
    case 0x01400010: return 0x1D7;
    case 0x01400011: return 0x1D8;
  }
  return -1;
}
