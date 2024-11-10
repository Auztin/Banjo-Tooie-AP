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

        //Jinjos
            case 1230551: return real->mt_jinjo_grip_grab;
            case 1230552: return real->mt_jinjo_kickball;
            case 1230553: return real->mt_jinjo_temple;
            case 1230554: return real->mt_jinjo_underwater;
            case 1230555: return real->mt_jinjo_bridge;

            case 1230556: return real->ggm_jinjo_water_storage;
            case 1230557: return real->ggm_jinjo_gloomy_caverns;
            case 1230558: return real->ggm_jinjo_toxic_gas_cave;
            case 1230559: return real->ggm_jinjo_near_train_station;
            case 1230560: return real->ggm_jinjo_tracks;

            case 1230561: return real->ww_jinjo_big_top;
            case 1230562: return real->ww_jinjo_cave_of_horrors;
            case 1230563: return real->ww_jinjo_space;
            case 1230564: return real->ww_jinjo_western;
            case 1230565: return real->ww_jinjo_entrance;

            case 1230566: return real->jrl_jinjo_alcove_across_town;
            case 1230567: return real->jrl_jinjo_blubbers;
            case 1230568: return real->jrl_jinjo_big_fish;
            case 1230569: return real->jrl_jinjo_seaweed_sanctum;
            case 1230570: return real->jrl_jinjo_spawned_chest;

            case 1230571: return real->tdl_jinjo_lower_lake;
            case 1230572: return real->tdl_jinjo_caged_entrance;
            case 1230573: return real->tdl_jinjo_caged_near_rocknut;
            case 1230574: return real->tdl_jinjo_caged_near_humba;
            case 1230575: return real->tdl_jinjo_stomponadon;

            case 1230576: return real->gi_roof_jinjo_center_window;
            case 1230577: return real->gi_floor2_jinjo_toxic_room;
            case 1230578: return real->gi_jinjo_waste_disposal_plant_jrl;
            case 1230579: return real->gi_floor3_jinjo_boiler_plant;
            case 1230580: return real->gi_outside_jinjo;

            case 1230581: return real->hfp_lava_jinjo_waterfall;
            case 1230582: return real->hfp_lava_jinjo_hot_water;
            case 1230583: return real->hfp_icy_jinjo_wind_tunnel;
            case 1230584: return real->hfp_icy_jinjo_icicle_grotto;
            case 1230585: return real->hfp_icy_jinjo_mildred;

            case 1230586: return real->ccl_jinjo_trashcan;
            case 1230587: return real->ccl_jinjo_cheese;
            case 1230588: return real->ccl_jinjo_near_jamjars;
            case 1230589: return real->ccl_jinjo_mingy_jongo;
            case 1230590: return real->ccl_jinjo_humba;

            case 1230591: return real->ioh_jinjo_wooded_hollow;
            case 1230592: return real->ioh_jinjo_wasteland;
            case 1230593: return real->ioh_jinjo_cliff_top;
            case 1230594: return real->ioh_jinjo_plateau;
            case 1230595: return real->sm_jinjo_underwater;

        //Pages
            case 1230728: return real->mt_page_treasure_chamber;
            case 1230729: return real->mt_page_prison_combound;
            case 1230730: return real->mt_page_jade_snake;

            case 1230731: return real->ggm_page_canary_mary;
            case 1230732: return real->ggm_page_entrance;
            case 1230733: return real->ggm_page_water_storage;

            case 1230734: return real->ww_page_haunted_cavern;
            case 1230735: return real->ww_page_inferno;
            case 1230736: return real->ww_page_saucer_of_peril;

            case 1230737: return real->jrl_page_pawno;
            case 1230738: return real->jrl_page_seemee;
            case 1230739: return real->jrl_page_ancient_swimming_baths;

            case 1230740: return real->tdl_page_dippy;
            case 1230741: return real->tdl_page_inside_the_mountain;
            case 1230742: return real->tdl_page_near_mumbo;

            case 1230743: return real->gi_floor1_page_collected_loggo;
            case 1230744: return real->gi_floor2_page;
            case 1230745: return real->gi_floor1_page_weldar;

            case 1230746: return real->hfp_lava_page_from_stadium;
            case 1230747: return real->hfp_icy_page_icicle_grotto;
            case 1230748: return real->hfp_icy_page_tall_tower;

            case 1230749: return real->ccl_page_collected_canary_mary;
            case 1230750: return real->ccl_page_collected_pot_o_gold;
            case 1230751: return real->ccl_page_collected_zzzubas;

            case 1230752: return real->sm_page_nook;
        //Honeycombs
            case 1230703: return real->mt_honeycomb_piece_entrance;
            case 1230704: return real->mt_honeycomb_piece_bovina;
            case 1230705: return real->mt_honeycomb_piece_treasure_chamber;

            case 1230706: return real->ggm_honeycomb_piece_toxic_gas_cave;
            case 1230707: return real->ggm_honeycomb_piece_prospectors_hut;
            case 1230708: return real->ggm_honeycomb_piece_train_station;

            case 1230709: return real->ww_honeycomb_piece_space;
            case 1230710: return real->ww_honeycomb_piece_mumbo;
            case 1230711: return real->ww_honeycomb_piece_western;

            case 1230712: return real->jrl_honeycomb_piece_seemee;
            case 1230713: return real->jrl_honeycomb_piece_atlantis;
            case 1230714: return real->jrl_honeycomb_piece_above_pig_pool;

            case 1230715: return real->tdl_honeycomb_piece_lower_lake;
            case 1230716: return real->tdl_honeycomb_piece_scrotty;
            case 1230717: return real->tdl_honeycomb_piece_river_passage;

            case 1230718: return real->gi_floor2_honeycomb_piece_corner_box;
            case 1230719: return real->gi_floor1_honeycomb_piece_train_station;
            case 1230720: return real->gi_roof_honeycomb_piece_chimney;

            case 1230721: return real->hfp_lava_honeycomb_piece_inside_volcano;
            case 1230722: return real->hfp_lava_honeycomb_piece_train_station;
            case 1230723: return real->hfp_lava_honeycomb_piece_hot_water;

            case 1230724: return real->ccl_honeycomb_piece_collected_buried_item;
            case 1230725: return real->ccl_honeycomb_piece_trash_can;
            case 1230726: return real->ccl_honeycomb_piece_pot_o_gold;

            case 1230727: return real->ioh_honeycomb_piece_plateau;
        // GLOWBOS
            case 1230046: return real->collected_mega_glowbo;

            case 1230686: return real->mt_glowbo_mumbo;
            case 1230687: return real->mt_glowbo_humba;

            case 1230688: return real->ggm_glowbo_humba;
            case 1230689: return real->ggm_glowbo_mumbo;

            case 1230690: return real->ww_glowbo_mumbo;
            case 1230691: return real->ww_glowbo_humba;

            case 1230692: return real->jrl_glowbo_mumbo;
            case 1230693: return real->jrl_glowbo_humba;

            case 1230694: return real->jrl_glowbo_humba;
            case 1230695: return real->jrl_glowbo_mumbo;

            case 1230696: return real->gi_floor2_glowbo_humba;
            case 1230697: return real->gi_floor3_glowbo_mumbo;

            case 1230698: return real->hfp_lava_glowbo_mumbo;
            case 1230699: return real->hfp_icy_glowbo_humba;

            case 1230700: return real->ccl_glowbo_humba;
            case 1230701: return real->ccl_glowbo_mumbo;

            case 1230702: return real->ioh_glowbo;
        //Treble Clef
            case 1230781: return real->mt_notes_tc_behind_temple;
            case 1230782: return real->ggm_notes_tc_water_storage;
            case 1230783: return real->ww_notes_tc_space;
            case 1230784: return real->jrl_notes_tc_blubbul_atlantis;
            case 1230785: return real->tdl_notes_tc_near_humba;
            case 1230786: return real->gi_outside_notes_tc_above_building_entrance;
            case 1230787: return real->hfp_icy_notes_tc_icicle_grotto;
            case 1230788: return real->ccl_notes_tc_high_bridge;
            case 1230789: return real->ioh_notes_tc_atop_jinjo_house;
        //Doubloons
            case 1230521: return real->jrl_doubloon_collected_bollards1;
            case 1230522: return real->jrl_doubloon_collected_bollards2;
            case 1230523: return real->jrl_doubloon_collected_bollards3;
            case 1230524: return real->jrl_doubloon_collected_bollards4;
            case 1230525: return real->jrl_doubloon_collected_bollards5;
            case 1230526: return real->jrl_doubloon_collected_bollards6;
            case 1230527: return real->jrl_doubloon_collected_wing_whack1;
            case 1230528: return real->jrl_doubloon_collected_wing_whack2;
            case 1230529: return real->jrl_doubloon_collected_wing_whack3;
            case 1230530: return real->jrl_doubloon_collected_wing_whack4;
            case 1230531: return real->jrl_doubloon_collected_pig_pool4;
            case 1230532: return real->jrl_doubloon_collected_pig_pool3;
            case 1230533: return real->jrl_doubloon_collected_pig_pool2;
            case 1230534: return real->jrl_doubloon_collected_pig_pool1;
            case 1230535: return real->jrl_doubloon_collected_mumbo1;
            case 1230536: return real->jrl_doubloon_collected_mumbo2;
            case 1230537: return real->jrl_doubloon_collected_mumbo3;
            case 1230538: return real->jrl_doubloon_collected_mumbo4;


            case 1230539: return real->jrl_doubloon_collected_buried_spot_entrance;
            case 1230540: return real->jrl_doubloon_collected_buried_spot_pawnos;
            case 1230541: return real->jrl_doubloon_collected_buried_spot_jollys;

            case 1230542: return real->jrl_doubloon_collected_shock_jump_alcove3;
            case 1230543: return real->jrl_doubloon_collected_shock_jump_alcove2;
            case 1230544: return real->jrl_doubloon_collected_shock_jump_alcove1;

            case 1230545: return real->jrl_doubloon_collected_captain_blackeye1;
            case 1230546: return real->jrl_doubloon_collected_captain_blackeye2;

            case 1230547: return real->jrl_doubloon_collected_underwater4;
            case 1230548: return real->jrl_doubloon_collected_underwater3;
            case 1230549: return real->jrl_doubloon_collected_underwater2;
            case 1230550: return real->jrl_doubloon_collected_underwater1;
        //Jiggy Chunks
            case 1231002: return real->ggm_jiggy_collected_crushing_shed_pieces3;
            case 1231003: return real->ggm_jiggy_collected_crushing_shed_pieces2;
            case 1231004: return real->ggm_jiggy_collected_crushing_shed_pieces1;
        // Train Stations
            case 1230790: return fake->gi_outside_opened_train;
            case 1230791: return fake->tdl_opened_train;
            case 1230792: return fake->hfp_lava_opened_train;
            case 1230793: return fake->hfp_icy_opened_train;
            case 1230794: return fake->ioh_opened_train;
            case 1230795: return fake->ww_opened_train;
        //Chuffy
            case 1230796: return fake->ggm_defeated_chuffy;
        //Jinjo Family
            case 1230676: return fake->jv_jiggy_collected_jinjo_white;
            case 1230677: return fake->jv_jiggy_collected_jinjo_orange;
            case 1230678: return fake->jv_jiggy_collected_jinjo_yellow;
            case 1230679: return fake->jv_jiggy_collected_jinjo_brown;
            case 1230680: return fake->jv_jiggy_collected_jinjo_green;
            case 1230681: return fake->jv_jiggy_collected_jinjo_red;
            case 1230682: return fake->jv_jiggy_collected_jinjo_blue;
            case 1230683: return fake->jv_jiggy_collected_jinjo_purple;
            case 1230684: return fake->jv_jiggy_collected_jinjo_black;
        //StopNSwap
            case 1230953: return fake->wh_yellow_egg_hatched;
            case 1230954: return fake->wh_pink_egg_hatched;
            case 1230955: return fake->wh_blue_egg_hatched;
            case 1230956: return fake->sm_pink_egg_collected;
            case 1230957: return fake->sm_blue_egg_collected;
            case 1230958: return fake->opened_mega_glowbo;
        //Cheato Rewards
            case 1230992: return real->cheats_feathers_received;
            case 1230993: return real->cheats_eggs_received;
            case 1230994: return real->cheats_fallproof_received;
            case 1230995: return real->cheats_honeyback_received;
            case 1230996: return real->cheats_jukebox_received;
        //HoneyB
        /*
            HoneyB has to be properly calcluated and process by the middleman
        */
        //Notes
            case 1230800: return real->mt_notes_before_goliath1;
            case 1230801: return real->mt_notes_before_goliath2;
            case 1230802: return real->mt_notes_before_goliath3;
            case 1230803: return real->mt_notes_before_goliath4;
            case 1230804: return real->mt_notes_after_goliath1;
            case 1230805: return real->mt_notes_after_goliath2;
            case 1230806: return real->mt_notes_after_goliath3;
            case 1230807: return real->mt_notes_after_goliath4;
            case 1230808: return real->mt_notes_before_mumbo1;
            case 1230809: return real->mt_notes_before_mumbo2;
            case 1230810: return real->mt_notes_before_mumbo3;
            case 1230811: return real->mt_notes_before_mumbo4;
            case 1230812: return real->mt_notes_after_mumbo1;
            case 1230813: return real->mt_notes_after_mumbo2;
            case 1230814: return real->mt_notes_after_mumbo3;
            case 1230815: return real->mt_notes_mumbo;

            case 1230816: return real->ggm_notes_near_crushing_shed4;
            case 1230817: return real->ggm_notes_near_crushing_shed3;
            case 1230818: return real->ggm_notes_near_crushing_shed2;
            case 1230819: return real->ggm_notes_near_crushing_shed1;
            case 1230820: return real->ggm_notes_near_prospectors_hut4;
            case 1230821: return real->ggm_notes_near_prospectors_hut3;
            case 1230822: return real->ggm_notes_near_prospectors_hut2;
            case 1230823: return real->ggm_notes_near_prospectors_hut1;
            case 1230824: return real->ggm_notes_near_prospectors_hut5;
            case 1230825: return real->ggm_notes_near_mumbo3;
            case 1230826: return real->ggm_notes_near_mumbo2;
            case 1230827: return real->ggm_notes_near_mumbo1;
            case 1230828: return real->ggm_notes_fuel_depot4;
            case 1230829: return real->ggm_notes_fuel_depot3;
            case 1230830: return real->ggm_notes_fuel_depot2;
            case 1230831: return real->ggm_notes_fuel_depot1;

            case 1230832: return real->ww_notes_big_top_entrance;
            case 1230833: return real->ww_notes_big_top_space_entrance;
            case 1230834: return real->ww_notes_big_top_space;
            case 1230835: return real->ww_notes_big_top_spooky_space;
            case 1230836: return real->ww_notes_big_top_spooky;
            case 1230837: return real->ww_notes_big_top_western_spooky;
            case 1230838: return real->ww_notes_big_top_western;
            case 1230839: return real->ww_notes_big_top_entrance_western;
            case 1230840: return real->ww_notes_electric_fence2;
            case 1230841: return real->ww_notes_electric_fence1;
            case 1230842: return real->ww_notes_space2;
            case 1230843: return real->ww_notes_space1;
            case 1230844: return real->ww_notes_spooky2;
            case 1230845: return real->ww_notes_spooky1;
            case 1230846: return real->ww_notes_western1;
            case 1230847: return real->ww_notes_western2;

            case 1230848: return real->jrl_notes_outside_jollys;
            case 1230849: return real->jrl_notes_outside_pawnos;
            case 1230850: return real->jrl_notes_outside_blubbers;
            case 1230851: return real->jrl_notes_blubbul2;
            case 1230852: return real->jrl_notes_blubbul1;
            case 1230853: return real->jrl_notes_atlantis1;
            case 1230854: return real->jrl_notes_atlantis2;
            case 1230855: return real->jrl_notes_blubbers3;
            case 1230856: return real->jrl_notes_blubbers2;
            case 1230857: return real->jrl_notes_blubbers1;
            case 1230858: return real->jrl_notes_pawnos3;
            case 1230859: return real->jrl_notes_pawnos2;
            case 1230860: return real->jrl_notes_pawnos1;
            case 1230861: return real->jrl_notes_jollys1;
            case 1230862: return real->jrl_notes_jollys3;
            case 1230863: return real->jrl_notes_jollys2;

            case 1230864: return real->tdl_notes_near_train_station3;
            case 1230865: return real->tdl_notes_near_train_station2;
            case 1230866: return real->tdl_notes_near_train_station1;
            case 1230867: return real->tdl_notes_lower_lake2;
            case 1230868: return real->tdl_notes_lower_lake1;
            case 1230869: return real->tdl_notes_lower_lake3;
            case 1230870: return real->tdl_notes_path_to_nest3;
            case 1230871: return real->tdl_notes_path_to_nest2;
            case 1230872: return real->tdl_notes_path_to_nest1;
            case 1230873: return real->tdl_notes_roar_cage3;
            case 1230874: return real->tdl_notes_roar_cage2;
            case 1230875: return real->tdl_notes_roar_cage1;
            case 1230876: return real->tdl_notes_river_passage1;
            case 1230877: return real->tdl_notes_river_passage4;
            case 1230878: return real->tdl_notes_river_passage3;
            case 1230879: return real->tdl_notes_river_passage2;

            case 1230880: return real->gi_floor1_notes_train_station3;
            case 1230881: return real->gi_floor1_notes_train_station2;
            case 1230882: return real->gi_floor1_notes_train_station1;
            case 1230883: return real->gi_floor1_notes_ac1;
            case 1230884: return real->gi_floor1_notes_ac2;
            case 1230885: return real->gi_floor2_notes_toxic_room3;
            case 1230886: return real->gi_floor2_notes_toxic_room2;
            case 1230887: return real->gi_floor2_notes_toxic_room1;
            case 1230888: return real->gi_floor2_notes_near_humba2;
            case 1230889: return real->gi_floor2_notes_near_humba1;
            case 1230890: return real->gi_floor1_notes_toxic_waste_disposal2;
            case 1230891: return real->gi_floor1_notes_toxic_waste_disposal1;
            case 1230892: return real->gi_floor1_notes_air_con_plant2;
            case 1230893: return real->gi_floor1_notes_air_con_plant1;
            case 1230894: return real->gi_floor3_notes_upper_platforms2;
            case 1230895: return real->gi_floor3_notes_upper_platforms1;

            case 1230896: return real->hfp_lava_notes_near_shack_pack2;
            case 1230897: return real->hfp_lava_notes_near_shack_pack1;
            case 1230898: return real->hfp_lava_notes_near_mumbo1;
            case 1230899: return real->hfp_lava_notes_near_mumbo2;
            case 1230900: return real->hfp_lava_notes_near_warp_pad2;
            case 1230901: return real->hfp_lava_notes_near_warp_pad1;
            case 1230902: return real->hfp_lava_notes_ladder2;
            case 1230903: return real->hfp_lava_notes_ladder1;
            case 1230904: return real->hfp_icy_notes_near_oil_rig2;
            case 1230905: return real->hfp_icy_notes_near_oil_rig1;
            case 1230906: return real->hfp_icy_notes_near_claw_clamber_boots1;
            case 1230907: return real->hfp_icy_notes_near_claw_clamber_boots2;
            case 1230908: return real->hfp_icy_notes_near_boggy2;
            case 1230909: return real->hfp_icy_notes_near_boggy1;
            case 1230910: return real->hfp_icy_notes_near_humba2;
            case 1230911: return real->hfp_icy_notes_near_humba1;

            case 1230912: return real->ccl_notes_above_jamjars;
            case 1230913: return real->ccl_notes_blue_skull_exit;
            case 1230914: return real->ccl_notes_with_jamjars2;
            case 1230915: return real->ccl_notes_with_jamjars1;
            case 1230916: return real->ccl_notes_cheese_exit;
            case 1230917: return real->ccl_notes_pot_o_gold_exit;
            case 1230918: return real->ccl_notes_dippy_exit;
            case 1230919: return real->ccl_notes_mr_fit_sprint_exit;
            case 1230920: return real->ccl_notes_red_skull;
            case 1230921: return real->ccl_notes_claw_clamber_boots_exit;
            case 1230922: return real->ccl_notes_high_bridge_exit;
            case 1230923: return real->ccl_notes_high_bridge_code_button_exit;
            case 1230924: return real->ccl_notes_glowbo_exit;
            case 1230925: return real->ccl_notes_warp_pad;
            case 1230926: return real->ccl_notes_splitup_kazooie;
            case 1230927: return real->ccl_notes_splitup_banjo;

            case 1230928: return real->ioh_notes_plateau_sign1;;
            case 1230929: return real->ioh_notes_plateau_sign2;
            case 1230930: return real->ioh_notes_plateau_hive2;
            case 1230931: return real->ioh_notes_plateau_hive1;
            case 1230932: return real->ioh_notes_pine_grove_land2;
            case 1230933: return real->ioh_notes_pine_grove_land1;
            case 1230934: return real->ioh_notes_pine_grove_underwater2;
            case 1230935: return real->ioh_notes_pine_grove_underwater1;
            case 1230936: return real->ioh_notes_cliff_top_hfp1;
            case 1230937: return real->ioh_notes_cliff_top_hfp4;
            case 1230938: return real->ioh_notes_cliff_top_hfp3;
            case 1230939: return real->ioh_notes_cliff_top_hfp2;
            case 1230940: return real->ioh_notes_wasteland_jinjo2;
            case 1230941: return real->ioh_notes_wasteland_jinjo1;
            case 1230942: return real->ioh_notes_wasteland_ccl2;
            case 1230943: return real->ioh_notes_wasteland_ccl1;
        //Roysten
            case 1230777: return fake->extra_bubbles;
            case 1230778: return fake->fast_swimming;
        //Jamjars + Amaze + roar
            case 1230753: return fake->grip_grab;
            case 1230754: return fake->breegull_blaster;
            case 1230755: return fake->egg_aim;
            case 1230756: return fake->fire_eggs;
            case 1230757: return fake->bill_drill;
            case 1230758: return fake->beak_bayonet;
            case 1230759: return fake->grenade_eggs;
            case 1230760: return fake->airborne_egg_aiming;
            case 1230761: return fake->split_up;
            case 1230762: return fake->pack_whack;
            case 1230763: return fake->ice_eggs;
            case 1230764: return fake->wing_whack;
            case 1230765: return fake->talon_torpedo;
            case 1230766: return fake->sub_aqua_egg_aiming;
            case 1230767: return fake->clockwork_kazooie_eggs;
            case 1230768: return fake->springy_step_shoes;
            case 1230769: return fake->taxi_pack;
            case 1230770: return fake->hatch;
            case 1230771: return fake->snooze_pack;
            case 1230772: return fake->leg_spring;
            case 1230773: return fake->claw_clamber_boots;
            case 1230774: return fake->shack_pack;
            case 1230775: return fake->glide;
            case 1230776: return fake->sack_pack;
            case 1231005: return fake->amaze_o_gaze;
            case 1231009: return fake->trex_roar;
    }
    return false;
}