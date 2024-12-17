# Banjo-Tooie (US Only) ROM Hack for Archipelago
This repository is designed to work with [jjjj12212](https://github.com/jjjj12212)'s [Archipelago-BanjoTooie](https://github.com/jjjj12212/Archipelago-BanjoTooie/) project. It contains the source code for the ROM hack, which is compatible with the `banjo_tooie_connector.lua` in that project. This project also contains source code for a PC program designed to interface with an EverDrive 64 over USB, allowing the randomizer to be played on a real N64 console.

# How to use
The official Banjo-Tooie apworld will contain everything you need to use this ROM Hack, for both emulator and console. Please see that project (linked above) for setup and usage instructions.

# How to build
## Dependencies
In the n64/tools folder, you will need to place:
* [libdragon/](https://github.com/DragonMinded/libdragon)
* [mips64/](https://github.com/DragonMinded/libdragon/releases/tag/toolchain-continuous-prerelease)
* [armips](https://github.com/Kingcom/armips/releases)

In the n64/rom folder, you will need to place a file called `Banjo-Tooie.n64`. This file cannot be byte-swapped. If you open the file in a hex editor, you should see near the top: `42 41 4E 4A   4F 20 54 4F   4F 49 45 20   20 20 20 20` `BANJO TOOIE`

Run `make`.
