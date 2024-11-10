#include "data_map.hpp"
#include <usb/usb_com.hpp>

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
    int loc_id = std::stoi(locationId);
    auto* real = &ap_memory.n64.saves.real;
    auto* fake = &ap_memory.n64.saves.fake;
    switch(loc_id) {
        //Jiggies
            case 1230685: return real->ioh_jiggy_collected_jingaling;

            case 1230596: return real->mt_jiggy_collected_targitzan;
            case 1230597: return real->mt_jiggy_collected_slightly_sacred_chamber;
            case 1230598: return real->mt_jiggy_collected_kickball;
            case 1230599: return real->mt_jiggy_collected_bovina;
            case 1230600: return real->mt_jiggy_collected_treasure_chamber;
            case 1230601: return real->mt_jiggy_collected_goliath;
            case 1230602: return real->mt_jiggy_collected_wading_boots;
            case 1230603: return real->mt_jiggy_collected_columns;
            case 1230604: return real->mt_jiggy_collected_temple_top;
            case 1230605: return real->mt_jiggy_collected_ssslumber;

            case 1230606: return real->ggm_jiggy_collected_chuffy;
            case 1230607: return real->ggm_jiggy_collected_canary_mary;
            case 1230608: return real->ggm_jiggy_collected_generator_cavern;
            case 1230609: return real->ggm_jiggy_collected_waterfall_cavern;
            case 1230610: return real->ggm_jiggy_collected_ordnance_storage;
            case 1230611: return real->ggm_jiggy_collected_dilberta;
            case 1230612: return real->ggm_jiggy_collected_crushing_shed;
            case 1230613: return real->ggm_jiggy_collected_behind_waterfall;
            case 1230614: return real->ggm_jiggy_collected_power_hut_basement;
            case 1230615: return real->ggm_jiggy_collected_flooded_caves;

            case 1230616: return real->ww_jiggy_collected_hoop_hurry;
            case 1230617: return real->ww_jiggy_collected_dodgem;
            case 1230618: return real->ww_jiggy_collected_mr_patch;
            case 1230619: return real->ww_jiggy_collected_saucer_of_peril;
            case 1230620: return real->ww_jiggy_collected_balloon_burst;
            case 1230621: return real->ww_jiggy_collected_high_dive;
            case 1230622: return real->ww_jiggy_collected_mrs_boggy;
            case 1230623: return real->ww_jiggy_collected_star_spinner;
            case 1230624: return real->ww_jiggy_collected_inferno;
            case 1230625: return real->ww_jiggy_collected_test_of_strength;
    
            case 1230626: return real->jrl_jiggy_collected_sea_bottom_cavern;
            case 1230627: return real->jrl_jiggy_collected_tiptup;
            case 1230628: return real->jrl_jiggy_collected_chris_p_bacon;
            case 1230629: return real->jrl_jiggy_collected_pig_pool;
            case 1230630: return real->jrl_jiggy_collected_smugglers_cavern;
            case 1230631: return real->jrl_jiggy_collected_jolly;
            case 1230632: return real->jrl_jiggy_collected_lord_woo_fak_fak;
            case 1230633: return real->jrl_jiggy_collected_seemee;
            case 1230634: return real->jrl_jiggy_collected_pawno;
            case 1230635: return real->jrl_jiggy_collected_aliens;

            case 1230636: return real->tdl_jiggy_collected_below_terry_nest;
            case 1230637: return real->tdl_jiggy_collected_dippy;
            case 1230638: return real->tdl_jiggy_collected_scrotty;
            case 1230639: return real->tdl_jiggy_collected_terry_fight;
            case 1230640: return real->tdl_jiggy_collected_oogle_boogle;
            case 1230641: return real->tdl_jiggy_collected_chompasaurus;
            case 1230642: return real->tdl_jiggy_collected_terry_eggs;
            case 1230643: return real->tdl_jiggy_collected_stomponadon;
            case 1230644: return real->tdl_jiggy_collected_rocknuts;
            case 1230645: return real->tdl_jiggy_collected_roar_cage;

            case 1230646: return real->gi_floor1_jiggy_collected_toxic_waste_disposal_side_room;
            case 1230647: return real->gi_floor1_jiggy_collected_weldar;
            case 1230648: return real->gi_floor4_jiggy_collected_clinkers_cavern;
            case 1230649: return real->gi_jiggy_collected_workers;
            case 1230650: return real->gi_roof_jiggy_collected_window_edge;
            case 1230651: return real->gi_floor4_jiggy_collected_quality_control;
            case 1230652: return real->gi_floor1_jiggy_collected_guarded_by_tintops;
            case 1230653: return real->gi_floor1_jiggy_collected_trash_compactor;
            case 1230654: return real->gi_floor3_jiggy_collected_packing_room;
            case 1230655: return real->gi_floor1_jiggy_collected_toxic_waste_disposal;

            case 1230656: return real->hfp_jiggy_collected_dragon_brothers;
            case 1230657: return real->hfp_lava_jiggy_collected_inside_volcano;
            case 1230658: return real->hfp_lava_jiggy_collected_sabreman;
            case 1230659: return real->hfp_icy_jiggy_collected_boggy;
            case 1230660: return real->hfp_icy_jiggy_collected_train_station;
            case 1230661: return real->hfp_icy_jiggy_collected_oil_rig;
            case 1230662: return real->hfp_jiggy_collected_tdl;
            case 1230663: return real->hfp_lava_jiggy_collected_kickball;
            case 1230664: return real->hfp_icy_jiggy_collected_aliens;
            case 1230665: return real->hfp_lava_jiggy_collected_near_stadium_splitup_buttons;

            case 1230666: return real->ccl_jiggy_collected_mingy_jongo;
            case 1230667: return real->ccl_jiggy_collected_mr_fit;
            case 1230668: return real->ccl_jiggy_collected_pot_o_gold;
            case 1230669: return real->ccl_jiggy_collected_canary_mary;
            case 1230670: return real->ccl_jiggy_collected_zzzubas;
            case 1230671: return real->ccl_jiggy_collected_eyeballus_jiggium_plants;
            case 1230672: return real->ccl_jiggy_collected_cheese;
            case 1230673: return real->ccl_jiggy_collected_guffo;
            case 1230674: return real->ccl_jiggy_collected_superstash;
            case 1230675: return real->ccl_jiggy_collected_jelly_castle;


        case 1230777: return fake->extra_bubbles;
        case 1230778: return fake->fast_swimming;
    }
    return false;
}

