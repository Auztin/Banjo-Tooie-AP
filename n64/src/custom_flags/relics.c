#include "all.h"

s32 custom_flag_relics(u16 id) {
  switch (id) {
    case 0x1A20: return 0x01; // Right of Exit
    case 0x19A0: return 0x02; // Left of Exit

    case 0x1F20: return 0x03; // Blue Room 1
    case 0x1EA0: return 0x04; // Blue Room 2
    case 0x1E20: return 0x05; // Blue Room 3

    case 0x1D20: return 0x06; // Totem 1
    case 0x1DA0: return 0x07; // Totem 2
    case 0x1CA0: return 0x08; // Totem 3
    case 0x1C20: return 0x09; // Totem 4
    case 0x20A0: return 0x10; // Totem 5
    case 0x2120: return 0x11; // Yellow Room near Jinjo Entrance
    case 0x2220: return 0x12; // Yellow Room 2
    case 0x21A0: return 0x13; // Yellow Room 3
    case 0x22A0: return 0x14; // Yellow Room 4
    case 0x2320: return 0x15; // Yellow Room 5
    case 0x2020: return 0x16; // Front of Targitzan Second Door
    case 0x1FA0: return 0x17; // Front of Targitzan First Door 
    case 0x24A0: return 0x18; // Secret Hallway near First Door 1
    case 0x2420: return 0x19; // Secret Hallway near First Door 2
    case 0x23A0: return 0x20; // Secret Hallway near First Door 3
    case 0x25A0: return 0x21; // Secret Hallway near Front Entrance 1
    case 0x2520: return 0x22; // Secret Hallway near Front Entrance 2
    case 0x1AA0: return 0x23; // Red Room 1
    case 0x1B20: return 0x24; // Red Room 2
    case 0x1BA0: return 0x25; // Red Room 3
  }
  return -1;
}
