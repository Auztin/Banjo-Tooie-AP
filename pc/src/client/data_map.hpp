#ifndef BT_MAP_HPP
    #define BT_MAP_HPP

    #include <iostream>
    #include <map>
    #include <string>
    #include <vector>
    #include <ap_memory.h>
    #include <bt/save_flags.h>
    #include <usb/usb_com.hpp>

    extern std::map<uint16_t, std::map<std::string, std::vector<std::string>>> ASSET_MAP_CHECK;
    // const std::map<std::string, std::string> ADDRESS_MAP;
    bool check_flag(std::string);

    typedef struct {
        int mapId;
        int from_map;
        int entranceId;
        int exitId;
    } world_entrance_t;

    extern std::map<std::string, world_entrance_t> WORLD_ENTRANCES;
#endif