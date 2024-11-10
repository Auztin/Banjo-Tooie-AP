#include "data_map.hpp"

    std::map<uint16_t, std::map<std::string, std::vector<std::string>>> ASSET_MAP_CHECK = {
        {0, {
            {"JIGGIES", {"1230685, 1230638"}}
        }},
        {0xAF, {
            {"STOPNSWAP", {"1230956"}},
            {"JINJOS", {"1230595"}},
            {"PAGES", {"1230752"}}
        }}
    };

bool check_flag(std::string locationId) {
    // int loc_id = std::stoi(locationId);
    // switch(loc_id) {
    //     case 1230685: return ap_memory
    // }
    return false;
}

// const std::map<std::string, std::string> ADDRESS_MAP = {
//     {"1230685", "JV: King Jingaling Jiggy"},
//     {"1230596", "MT: Targitzan Jiggy"},
//     {"1230597", "MT: Slightly Sacred Chamber Jiggy"},
//     {"1230598", "MT: Kickball Jiggy"},
//     {"1230599", "MT: Bovina Jiggy"},
//     {"1230600", "MT: Treasure Chamber Jiggy"},
//     {"1230601", "MT: Golden Goliath Jiggy"},
//     {"1230602", "MT: Prison Compound Quicksand Jiggy"},
//     {"1230603", "MT: Pillars Jiggy"},
//     {"1230604", "MT: Top of Temple Jiggy"},
//     {"1230605", "MT: Ssslumber Jiggy"}
// };