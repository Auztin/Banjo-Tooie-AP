#include "data_map.hpp"

std::map<uint16_t, std::map<std::string, std::vector<std::string>>> ASSET_MAP_CHECK = {
        {0, { // ALL MAPS
            {"JIGGIES", {"1230685", "1230638"}},
            {"JINJO_FAMILY", {
                "1230676",
                "1230677",
                "1230678",
                "1230679",
                "1230680",
                "1230681",
                "1230682",
                "1230683",
                "1230684"}}
        }},
        {0xAF, { // Spiral Mountain
            {"STOPNSWAP", {"1230956"}},
            {"JINJOS", {"1230595"}},
            {"PAGES", {"1230752"}},
            {"ROYSTEN", {"1230777", "1230778"}}
        }},
        {0xAE, { // SM - Behind the waterfall
            {"STOPNSWAP", {"1230957"}}
        }},
        {0xAD, { //SM - Grunty's Lair
            {"CHEATOR", {"1230992", "1230993", "1230994", "1230995", "1230996"}}
        }},

        //JINJO VILLAGE
        {0x142, { // JV
            {"TREBLE", {"1230789"}},
            {"STOPNSWAP", {"1230958"}}
        }},
        {0x143, { //JV - Bottles' House
            {"AMAZE", {"1231005"}},
        }},

        //ISLE O' HAGS
        {0x155, { //IoH - Cliff Top
            {"JINJOS", {"1230593"}},
            {"GLOWBO", {"1230702"}},
            {"NOTES", {"1230936","1230937","1230938","1230939",}},
            {"SILO", {"1230763"}},
            {"STATIONBTN", {"1230794"}}
        }},
        {0x150, { //IoH - Heggy's Egg Shed
            {"STOPNSWAP", {"1230953", "1230954", "1230955"}}
        }},
        {0x154, { //IoH - Pine Grove
            {"NOTES", {"1230932","1230933","1230934", "1230935"}},
            {"SILO", {"1230759"}}
        }},
        {0x152, { //IoH - Plateau
            {"JINJOS", {"1230594"}},
            {"HONEYCOMB", {"1230727"}},
            {"NOTES", {"1230928", "1230929", "1230930", "1230931"}},
            {"SILO", {"1230756"}}
        }},
        {0x153, { //IoH - Plateau - Honey B's Hive
            {"HONEYB", {
                "1230997",
                "1230998",
                "1230999",
                "1231000",
                "1231001"}}
        }},
        {0x15A, { //IoH - Wasteland
            {"JINJOS", {"1230592"}},
            {"NOTES", {"1230940","1230941","1230942","1230943"}},
            {"SILO", {"1230767"}},
        }},
        {0x14F, { //IoH - Wooded Hollow
            {"JINJOS", {"1230591"}},
            {"STOPNSWAP", {"1230953","1230954","1230955"}}
        }},
        //MAYAHEM TEMPLE
        {0xB8, { //MT
            {"JIGGIES", {"1230599","1230604"}},
            {"JINJOS", {"1230552", "1230554", "1230555"}},
            {"PAGES", {"1230728"}},
            {"HONEYCOMB", {"1230703","1230704"}},
            {"NOTES", {
                "1230800",
                "1230801",
                "1230802",
                "1230803",
                "1230804",
                "1230805",
                "1230806",
                "1230807",
                "1230808",
                "1230809",
                "1230810",
                "1230811",
                "1230812",
                "1230813",
                "1230814",
                "1230815",
            }},
            {"TREBLE", {"1230781"}},
            {"SILO", {"1230753","1230754"}},
        }},
        {0xC4, { //MT - Jade Snake Grove
            {"JIGGIES", {"1230601","1230605"}},
            {"JINJOS", {"1230551"}},
            {"PAGES", {"1230730"}},
            {"GLOWBO", {"1230687"}},
            {"SILO", {"1230755",}},
        }},
        {0xBB, { //MT - Mayan Kickball Stadium (Lobby)
            {"JIGGIES", {"1230598"}}
        }},
        {0xB7, { //MT - Mumbo's Skull
            {"GLOWBO", {"1230686"}}
        }},
        {0xB9, { //MT - Prison Compound
            {"JIGGIES", {"1230602", "1230603"}},
            {"PAGES", {"1230729"}}
        }},
        {0x17A,	{ //MT - Targitzan's Really Sacred Chamber
            {"JIGGIES", {"1230596"}}
        }},
        {0x177,	{ //MT - Targitzan's Slightly Sacred Chamber
            {"JIGGIES", {"1230597"}}
        }},
        {0xC5, { //MT - Treasure Chamber
            {"JIGGIES", {"1230600"}},
            {"HONEYCOMB", {"1230705"}}
        }},
        {0x178, { //MT - Inside Tatgitzan's Temple
            {"JINJOS", {"1230553"}}
        }},
        //GLITTER GULCH MINE

        {0xC7,{ //GGM
            {"JIGGIES", {"1230607","1230612","1230613"}},
            {"JINJOS", {"1230559","1230560"}},
            {"PAGES", {"1230731", "1230732"}},
            {"HONEYCOMB", {"1230707"}},
            {"GLOWBO", {"1230688","1230689"}},
            {"NOTES", {
                "1230816",
                "1230817",
                "1230818",
                "1230819",
                "1230820",
                "1230821",
                "1230822",
                "1230823",
                "1230824",
                "1230825",
                "1230826",
                "1230827",
            }},
            {"SILO", {"1230757"}},
            {"CHUNKS", {"1231002", "1231003", "1231004"}}
        }},
        {0xCC,{ //GGM - Flooded Caves
            {"JIGGIES", {"1230615"}}
        }},
        {0xCA,{ //GGM - Fuel Depot
            {"NOTES", {"1230828","1230829","1230830","1230831"}}
        }},
        {0xD3, { //GGM - Generator Cavern
            {"JIGGIES", {"1230608"}}
        }},
        {0xD2, { //GGM - Gloomy Caverns
            {"JINJOS", {"1230557"}}
        }},
        {0xD1, { //GGM - Inside Chuffy's Boiler
            {"JIGGIES", {"1230606"}},
            {"CHUFFY", {"1230796"}}
        }},
        {0x163,	{ //GGM - Ordnance Storage Entrance
            {"JIGGIES", {"1230610"}},
            {"SILO", {"1230758",}},
        }},
        {0xCF, { //GGM - Power Hut Basement
            {"JIGGIES", {"1230614"}},
        }},
        {0xD8, { //GGM - Prospector's Hut
            {"JIGGIES", {"1230611"}},
        }},
        {0xDA, { //GGM - Toxic Gas Cave
            {"JINJOS", {"1230558"}},
            {"HONEYCOMB", {"1230706"}}
        }},
        {0xD7, { //GGM - Train Station
            {"HONEYCOMB", {"1230708"}}
        }},
        {0xCD, { //GGM - Water Storage
            {"JINJOS", {"1230556"}},
            {"PAGES", {"1230733"}},
            {"TREBLE", {"1230782"}}
        }},
        {0xCE, { //GGM - Waterfall Cavern
            {"JIGGIES", {"1230609"}},
        }},
        //{0xD0, {}}, // GGM - Chuffy Cabin

        //WITCHYWORLD
        {0xD6, { //WW
            {"JIGGIES", {"1230619","1230621","1230622","1230625"}},
            {"JINJOS", {"1230561","1230563","1230564","1230565"}},
            {"PAGES", {"1230736"}},
            {"HONEYCOMB", {"1230709"}},
            {"NOTES", {
                "1230832",
                "1230833",
                "1230834",
                "1230835",
                "1230836",
                "1230837",
                "1230838",
                "1230839",
                "1230840",
                "1230841",
                "1230842",
                "1230843",
                "1230844",
                "1230845",
                "1230846",
                "1230847",
            }},
            {"TREBLE", {"1230783"}},
            {"SILO", {"1230761","1230760"}},
        }},
        {0xEA, { //WW - Cave of Horrors
            {"JINJOS", {"1230562"}}
        }},
        {0xE1, { //WW - Crazy Castle Stockade
            {"JIGGIES", {"1230616","1230620"}},
            {"HONEYCOMB", {"1230711"}},
            {"SILO", {"1230762"}},
        }},
        {0xDD, { //WW - Dodgem Dome Lobby
            {"JIGGIES", {"1230617"}},
        }},
        {0xEB, { //WW - Haunted Cavern
            {"PAGES", {"1230734"}}
        }},
        {0xF9, { //WW - Mr. Patch
            {"JIGGIES", {"1230618"}},
        }},
        {0xE6, { //WW - Star Spinner
            {"JIGGIES", {"1230623"}},
        }},
        {0xE7, { //WW - The Inferno
            {"JIGGIES", {"1230624"}},
            {"PAGES", {"1230735"}},
            {"GLOWBO", {"1230690"}}
        }},
        {0x176, { // WW - Mumbo Skull
            {"HONEYCOMB", {"1230710"}}
        }},
        {0xD5, { //WW - Wumba's Wigwam
            {"GLOWBO", {"1230691"}}
        }},
        {0xEC, { // WW - Train Station
            {"STATIONBTN", {"1230795"}}
        }},

        //JOLLY ROGER'S LAGOON
        {0x1A7, { //JRL
            {"JIGGIES", {"1230627","1230635","1230629"}},
            {"JINJOS", {"1230566"}},
            {"HONEYCOMB", {"1230714"}},
            {"DOUBLOON", {
                "1230521",
                "1230522",
                "1230523",
                "1230524",
                "1230525",
                "1230526",
                "1230527",
                "1230528",
                "1230529",
                "1230530",
                "1230531",
                "1230532",
                "1230533",
                "1230534",
                "1230539",
                "1230540",
                "1230541",
                "1230542",
                "1230543",
                "1230544",
                "1230547",
                "1230548",
                "1230549",
                "1230550",
            }},
            {"NOTES", {
                "1230848",
                "1230849",
                "1230850",
                "1230851",
                "1230852",
            }},
            {"SILO", {"1230764"}}
        }},
        {0xF4, { //JRL - Ancient Swimming Baths
            {"PAGES", {"1230739"}}
        }},
        {0x1A8,	{ //JRL - Atlantis
            {"JIGGIES", {"1230633"}},
            {"JINJOS", {"1230570"}},
            {"PAGES", {"1230738"}},
            {"HONEYCOMB", {"1230713","1230712"}},
            {"GLOWBO", {"1230693"}},
            {"NOTES", {"1230853","1230854"}},
            {"TREBLE", {"1230784"}}
        }},
        {0xFF, { //JRL - Blubber's Wave Race Hire
            {"JINJOS", {"1230567"}},
            {"NOTES", {"1230855","1230856","1230857"}}
        }},
        {0xF6, {  //JRL - Electric Eel's lair
            {"SILO", {"1230765"}},
        }},
        {0xF8, { //JRL - Inside the Big Fish
            {"JINJOS", {"1230568"}}
        }},
        {0xED, { //JRL - Jolly's
            {"JIGGIES", {"1230631"}},
            {"DOUBLOON", {"1230545","1230546"}},
            {"NOTES", {"1230861","1230862","1230863"}},
            {"SILO", {"1230766"}},
        }},
        {0xFC, { //JRL - Lord Woo Fak Fak
            {"JIGGIES", {"1230632"}},
        }},
        {0xEE, { //JRL - Pawno's Emporium
            {"JIGGIES", {"1230634"}},
            {"PAGES", {"1230737"}},
            {"GLOWBO", {"1230692"}},
            {"NOTES", {"1230858","1230859","1230860"}}
        }},
        {0x1A9,	{ //JRL - Sea Bottom
            {"JIGGIES", {"1230633"}},
            {"PAGES", {"1230738"}},
            {"HONEYCOMB", {"1230712"}}
        }},
        {0x181,	{ //JRL - Sea Botom Cavern
            {"JIGGIES", {"1230626"}},
        }},
        {0xF7, { //JRL - Seaweed Sanctum
            {"JINJOS", {"1230569"}}
        }},
        {0x1A6,	{ //JRL - Smuggler's cavern
            {"JIGGIES", {"1230633","1230630"}},
            {"PAGES", {"1230738"}},
            {"HONEYCOMB", {"1230712"}}
        }},
        {0xFA, { //JRL - Temple of the Fishes
            {"JIGGIES", {"1230628"}},
        }},
        {0xEF, { //JRL - Mumbo's Skull
            {"DOUBLOON", {"1230535","1230536","1230537","1230538"}}
        }},

        //TERRYDACTYLAND
        {0x112,	{ //TDL
            {"JIGGIES", {"1230637","1230644","1230645"}},
            {"JINJOS", {"1230571","1230572","1230573","1230574"}},
            {"PAGES", {"1230740","1230742"}},
            {"HONEYCOMB", {"1230715"}},
            {"GLOWBO", {"1230694","1230695"}},
            {"NOTES", {
                "1230864",
                "1230865",
                "1230866",
                "1230867",
                "1230868",
                "1230869",
                "1230870",
                "1230871",
                "1230872",
                "1230873",
                "1230874",
                "1230875",
            }},
            {"TREBLE", {"1230785"}},
            {"SILO", {"1230768"}},
            {"STATIONBTN", {"1230791"}},
            {"ROAR", {"1231009"}}
        }},
        {0x123, { //TDL - Inside Chompa's Belly
            {"JIGGIES", {"1230641"}},
        }},
        {0x116, { //TDL - Inside the Mountain
            {"JIGGIES", {"1230636"}},
            {"PAGES", {"1230741"}}
        }},
        {0x115, { //TDL - Oogle Boogles' Cave
            {"JIGGIES", {"1230640"}},
        }},
        {0x117, { //TDL - River Passage
            {"HONEYCOMB", {"1230717"}},
            {"NOTES", {"1230876","1230877","1230878","1230879"}},
            {"SILO", {"1230769"}},
        }},
        {0x119, { // Unga Bunga Cave
            {"SILO", {"1230770"}}
        }},
        {0x11A, { //TDL - Stomping Plains
            {"JIGGIES", {"1230643"}},
            {"JINJOS", {"1230575"}}
        }},
        {0x118,	{ //TDL - Styracosaurus Family Cave
            {"HONEYCOMB", {"1230716"}}
        }},
        {0x113,	{ //TDL - Terry's Nest
            {"JIGGIES", {"1230639","1230642"}},
        }},
        {0x114,	{ //TDL - Train Station
            {"JIGGIES", {"1230644"}}
        }},

        //GRUNTY'S INDUSTRIES
        {0x100,	{ //GI
            {"JIGGIES", {"1230649"}},
            {"JINJOS", {"1230580"}},
            {"HONEYCOMB", {"1230720"}},
            {"TREBLE", {"1230786"}},
            {"STATIONBTN", {"1230790"}}
        }},
        {0x10F, { //GI - Basement
            {"JIGGIES", {"1230647"}},
            {"NOTES", {"1230892","1230893"}}
        }},
        {0x110,	{ //GI - Basement (Repair Depot)
            {"PAGES", {"1230745"}}
        }},
        {0x111,	{ //GI - Basement (Waste Disposal)
            {"JIGGIES", {"1230646","1230655","1230661","1230629"}},
            {"JINJOS", {"1230578"}},
            {"NOTES", {"1230890","1230891"}},
            {"SILO", {"1230771"}},
        }},
        {0x101,	{ //GI - Floor 1
            {"JIGGIES", {"1230649","1230652"}},
            {"NOTES", {"1230883","1230884"}},
            {"SILO", {"1230773"}},
        }},
        {0x106,	{ //GI - Floor 2
            {"JIGGIES", {"1230649"}},
            {"JINJOS", {"1230577"}},
            {"PAGES", {"1230744"}},
            {"GLOWBO", {"1230696"}},
            {"NOTES", {
                "1230885",
                "1230886",
                "1230887",
                "1230888",
                "1230889"
            }},
            {"SILO", {"1230772"}},
        }},
        {0x108,	{ //GI - Floor 3
            {"HONEYCOMB", {"1230718"}},
            {"GLOWBO", {"1230697"}},
            {"NOTES", {"1230894","1230895"}}
        }},
        {0x109,	{ //GI - Floor 3 (Boiler Plant)
            {"JIGGIES", {"1230649"}},
            {"JINJOS", {"1230579"}}
        }},
        {0x10A,	{ //GI - Floor 3 (Packing Room)
            {"JIGGIES", {"1230654"}},
        }},
        // {0x10B,	{ //GI - Floor 4

        // }},
        {0x10D,	{ //GI - Floor 4 (Quality Control)
            {"JIGGIES", {"1230651"}},
        }},
        {0x10E,	{ //GI - Floor 5
            {"JIGGIES", {"1230649","1230650"}},
            {"JINJOS", {"1230576"}}
        }},
        {0x187,	{ //GI - Sewer Entrance
            {"JIGGIES", {"1230648"}},
        }},
        {0x102,	{ //GI - Train Station
            {"HONEYCOMB", {"1230719"}},
            {"NOTES", {"1230880","1230881","1230882"}}
        }},
        {0x104,	{ //GI - Trash Compactor
            {"JIGGIES", {"1230653"}},
        }},
        {0x103,	{ //GI - Workers' Quarters
            {"JIGGIES", {"1230649"}},
            {"PAGES", {"1230743"}}
        }},

        //HAILFIRE PEAKS
        {0x131,	{ //HFP - Boggy's Igloo
            {"JIGGIES", {"1230659"}}
        }},
        {0x12B,	{ //HFP - Chilli Billi
            {"JIGGIES", {"1230656"}}
        }},
        {0x12C,	{ //HFP - Chilly Willy
            {"JIGGIES", {"1230656"}}
        }},
        {0x132,	{ //HFP - Icicle Grotto
            {"JINJOS", {"1230584"}},
            {"PAGES", {"1230747"}},
            {"TREBLE", {"1230787"}}
        }},
        {0x128,	{ //HFP - Icy Side
            {"JIGGIES", {"1230660","1230662","1230664"}},
            {"JINJOS", {"1230585","1230583"}},
            {"PAGES", {"1230748"}},
            {"GLOWBO", {"1230699","1230046"}},
            {"NOTES", {
                "1230904",
                "1230905",
                "1230906",
                "1230907",
                "1230908",
                "1230909",
                "1230910",
                "1230911",
            }},
            {"SILO", {"1230775",}},
            {"STATIONBTN", {"1230793"}}
        }},
        {0x133,	{ //HFP - Inside the Volcano
            {"JIGGIES", {"1230657"}},
            {"HONEYCOMB", {"1230721"}}
        }},
        {0x12D,	{ //HFP - Kickball Stadium lobby
            {"JIGGIES", {"1230663"}},
        }},
        {0x127,	{ //HFP - Lava Side
            {"JIGGIES", {"1230658","1230665","1230629"}},
            {"JINJOS", {"1230581","1230582"}},
            {"PAGES", {"1230746"}},
            {"HONEYCOMB", {"1230723"}},
            {"GLOWBO", {"1230698"}},
            {"NOTES", {
                "1230896",
                "1230897",
                "1230898",
                "1230899",
                "1230900",
                "1230901",
                "1230902",
                "1230903",
            }},
            {"SILO", {"1230774"}},
            {"STATIONBTN", {"1230792"}}
        }},
        {0x129,	{ //HFP - Lava Train Station
            {"HONEYCOMB", {"1230722"}}
        }},
        // {0x12A, { // HFP - Icy Side Station

        // }},
        //CLOUD CUCKOOLAND
        {0x136,	{ //CCL
            {"JIGGIES", {
                "1230667", // Mr Fit
                "1230669", // Canary Mary 3
                "1230671", // Jiggium Plant
                "1230675", // Jelly Castle
                "1230637", // Dippy
            }},
            {"PAGES", {
                "1230749" // Canary Mary
            }},
            {"HONEYCOMB", {
                "1230724", // Dirt Patch
                "1230726", // Pot O Gold
                "1230725" // Trash
            }},
            {"GLOWBO", {
                "1230700"
            }}
        }},
        {0x13A,	{ //CCL - Central Cavern
            {"JIGGIES", {"1230674"}},
            {"JINJOS", {"1230588"}},
            {"GLOWBO", {"1230701"}},
            {"NOTES", {
                "1230912",
                "1230913",
                "1230914",
                "1230915",
                "1230916",
                "1230917",
                "1230918",
                "1230919",
                "1230920",
                "1230921",
                "1230922",
                "1230923",
                "1230924",
                "1230925",
                "1230926",
                "1230927",
            }},
            {"TREBLE", {"1230788"}},
            {"SILO", {"1230776"}}
        }},
        {0x138,	{ //CCL - Inside the Cheese Wedge
            {"JIGGIES", {"1230672"}},
            {"JINJOS", {"1230587"}}
        }},
        {0x13D,	{ //CCL - Inside the Pot o' Gold
            {"JIGGIES", {"1230668"}},
            {"PAGES", {"1230750"}}
        }},
        {0x137,	{ //CCL - Inside the Trash Can
            {"JIGGIES", {"1230673"}},
            {"JINJOS", {"1230586"}}
        }},
        {0x13F,	{ //CCL - Mingy Jongo's Skull
            {"JIGGIES", {"1230666"}},
            {"JINJOS", {"1230589"}}
        }},
        {0x13E,	{ //CCL - Mumbo's Skull
            {"JIGGIES", {"1230666"}},
            {"JINJOS", {"1230589"}}
        }},
        {0x140,	{ //CCL - Wumba's Wigwam
            {"JINJOS", {"1230590"}}
        }},
        {0x139,	{ //CCL - Zubbas' Nest
            {"JIGGIES", {"1230670"}},
            {"PAGES", {"1230751"}}
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
            case 1230563: return real->ww_jinjo_entrance;
            case 1230564: return real->ww_jinjo_space;
            case 1230565: return real->ww_jinjo_western;

            case 1230566: return real->jrl_jinjo_alcove_across_town;
            case 1230567: return real->jrl_jinjo_blubbers;
            case 1230568: return real->jrl_jinjo_big_fish;
            case 1230569: return real->jrl_jinjo_seaweed_sanctum;
            case 1230570: return real->jrl_jinjo_collected_chest;

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

            case 1230694: return real->tdl_glowbo_humba;
            case 1230695: return real->tdl_glowbo_mumbo;

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
            case 1230796: return real->ggm_defeated_chuffy;
        //Jinjo Family
            case 1230676: return real->jv_jiggy_collected_jinjo_white;
            case 1230677: return real->jv_jiggy_collected_jinjo_orange;
            case 1230678: return real->jv_jiggy_collected_jinjo_yellow;
            case 1230679: return real->jv_jiggy_collected_jinjo_brown;
            case 1230680: return real->jv_jiggy_collected_jinjo_green;
            case 1230681: return real->jv_jiggy_collected_jinjo_red;
            case 1230682: return real->jv_jiggy_collected_jinjo_blue;
            case 1230683: return real->jv_jiggy_collected_jinjo_purple;
            case 1230684: return real->jv_jiggy_collected_jinjo_black;
        //StopNSwap
            case 1230953: return real->wh_yellow_egg_hatched;
            case 1230954: return real->wh_pink_egg_hatched;
            case 1230955: return real->wh_blue_egg_hatched;
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
            case 1230997: return real->trade_honey_b >= 1;
            case 1230998: return real->trade_honey_b >= 2;
            case 1230999: return real->trade_honey_b >= 3;
            case 1231000: return real->trade_honey_b >= 4;
            case 1231001: return real->trade_honey_b == 5;

        //Dino Kids
            case 1231006: return real->tdl_returned_missing_dino;
            case 1231007: return real->tdl_healed_sick_dino && !real->tdl_sick_dino_on_train;
            case 1231008: return real->tdl_enlarged_small_dino;
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
            case 1230777: return real->sm_opened_fish;
            case 1230778: return real->sm_opened_fish;
        //Jamjars + Amaze + roar
            case 1230753: return fake->egg_aim;
            case 1230754: return fake->breegull_blaster;
            case 1230755: return fake->grip_grab;
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

bool check_custom_flag(u8* data, u16 id) {
  u8 byte = id/8;
  u8 bit = 1 << (id % 8);
  return data[byte] & bit;
}

std::map<std::string, world_entrance_t> WORLD_ENTRANCES =
{
    {"Mayahem Temple", {.mapId = 0xB8, .from_map = 0x14F, .entranceId = 10, .exitId = 2}},
    {"Glitter Gulch Mine", {.mapId = 0xC7, .from_map = 0x152, .entranceId = 17, .exitId = 2}},
    {"Witchyworld", {.mapId = 0xD6, .from_map = 0x154, .entranceId = 18, .exitId = 2}},
    {"Jolly Roger's Lagoon - Town Center", {.mapId = 0x1A7, .from_map = 0x155, .entranceId = 3, .exitId = 5}},
    {"Terrydactyland", {.mapId = 0x112, .from_map = 0x15A, .entranceId = 23, .exitId = 2}},
    {"Outside Grunty Industries", {.mapId = 0x100, .from_map = 0x15C, .entranceId = 9, .exitId = 2}},
    {"Hailfire Peaks", {.mapId = 0x127, .from_map = 0x155, .entranceId = 21, .exitId = 6}},
    {"Cloud Cuckooland", {.mapId = 0x136, .from_map = 0x15A, .entranceId = 20, .exitId = 5}},
    {"Cauldron Keep", {.mapId = 0x15D, .from_map = 0x15C, .entranceId = 1, .exitId = 3}}
};

std::map<int, std::map<int, int> > NEST_DATA = {
    {0x00AD, { // Gruntilda's Lair
        {1231010, 0x000},
        {1231011, 0x001},
        {1231012, 0x002},
        {1231013, 0x003},
        {1231014, 0x004},
        {1231015, 0x005},
        {1231016, 0x006},
    }}, {0x00AF, { // Spiral Mountain
        {1231017, 0x007},
        {1231018, 0x008},
        {1231019, 0x009},
        {1231020, 0x00A},
        {1231021, 0x00B},
        {1231022, 0x00C},
        {1231023, 0x00D},
        {1231024, 0x00E},
        {1231025, 0x00F},
        {1231026, 0x010},
        {1231027, 0x011},
        {1231028, 0x012},
        {1231029, 0x013},
        {1231030, 0x014},
        {1231031, 0x015},
        {1231032, 0x016},
        {1231033, 0x017},
        {1231034, 0x018},
    }}, {0x0141, { // Digger Tunnel
        {1231035, 0x019},
    }}, {0x0142, { // Jinjo Village
        {1231036, 0x01A},
        {1231037, 0x01B},
        {1231038, 0x01C},
        {1231039, 0x01D},
        {1231040, 0x01E},
        {1231041, 0x01F},
        {1231042, 0x020},
        {1231043, 0x021},
        {1231044, 0x022},
        {1231045, 0x023},
        {1231046, 0x024},
        {1231047, 0x025},
    }}, {0x0143, { // Bottles' House
        {1231048, 0x026},
        {1231049, 0x027},
        {1231050, 0x028},
        {1231051, 0x029},
    }}, {0x014F, { // Wooded Hollow
        {1231052, 0x02A},
        {1231053, 0x02B},
        {1231054, 0x02C},
        {1231055, 0x02D},
        {1231056, 0x02E},
        {1231057, 0x02F},
        {1231058, 0x030},
        {1231059, 0x031},
        {1231060, 0x032},
    }}, {0x0152, { // Plateau
        {1231061, 0x033},
        {1231062, 0x034},
        {1231063, 0x035},
        {1231064, 0x036},
        {1231065, 0x037},
        {1231066, 0x038},
        {1231067, 0x039},
    }}, {0x0154, { // Pine Grove
        {1231068, 0x03A},
        {1231069, 0x03B},
        {1231070, 0x03C},
        {1231071, 0x03D},
        {1231072, 0x03E},
        {1231073, 0x03F},
    }}, {0x0155, { // Cliff Top
        {1231074, 0x040},
        {1231075, 0x041},
        {1231076, 0x042},
        {1231077, 0x043},
        {1231078, 0x044},
        {1231079, 0x045},
        {1231482, 0x046},
    }}, {0x0157, { // IoH Humba
        {1231080, 0x047},
        {1231081, 0x048},
    }}, {0x015A, { // Wasteland
        {1231082, 0x049},
        {1231083, 0x04A},
        {1231084, 0x04B},
        {1231085, 0x04C},
        {1231086, 0x04D},
        {1231087, 0x04E},
        {1231088, 0x04F},
        {1231089, 0x050},
    }}, {0x015B, { // Another Digger Tunnel
        {1231090, 0x051},
        {1231091, 0x052},
    }}, {0x015C, { // Quagmire
        {1231092, 0x053},
        {1231093, 0x054},
        {1231094, 0x055},
        {1231095, 0x056},
        {1231096, 0x057},
        {1231097, 0x058},
    }}, {0x00B6, { // MT Humba
        {1231098, 0x059},
        {1231099, 0x05A},
    }}, {0x00B7, { // MT Mumbo
        {1231100, 0x05B},
        {1231101, 0x05C},
    }}, {0x00B8, { // MT
        {1231102, 0x05D},
        {1231103, 0x05E},
        {1231104, 0x05F},
        {1231105, 0x060},
        {1231106, 0x061},
        {1231107, 0x062},
        {1231108, 0x063},
        {1231109, 0x064},
        {1231110, 0x065},
        {1231111, 0x066},
    }}, {0x00B9, { // MT Prison Compound
        {1231112, 0x067},
        {1231113, 0x068},
        {1231114, 0x069},
        {1231115, 0x06A},
        {1231116, 0x06B},
        {1231117, 0x06C},
        {1231118, 0x06D},
    }}, {0x00C4, { // MT Jade Snake Grove
        {1231119, 0x06E},
        {1231120, 0x06F},
        {1231121, 0x070},
    }}, {0x0178, { // MT Targitzan's Temple
        {1231122, 0x071},
        {1231123, 0x072},
        {1231124, 0x073},
        {1231125, 0x074},
        {1231126, 0x075},
        {1231127, 0x076},
        {1231128, 0x077},
        {1231129, 0x078},
        {1231130, 0x079},
        {1231131, 0x07A},
        {1231132, 0x07B},
    }}, {0x0179, { // MT Targitzan's Temple Lobby
        {1231133, 0x07C},
        {1231134, 0x07D},
        {1231135, 0x07E},
        {1231136, 0x07F},
        {1231137, 0x080},
        {1231138, 0x081},
    }}, {0x00C7, { // GGM
        {1231139, 0x082},
        {1231140, 0x083},
        {1231141, 0x084},
        {1231142, 0x085},
    }}, {0x00CA, { // GGM Fuel Depot
        {1231143, 0x086},
        {1231144, 0x087},
        {1231145, 0x088},
        {1231146, 0x089},
        {1231147, 0x08A},
        {1231148, 0x08B},
    }}, {0x00CB, { // GGM Crushing Shed
        {1231149, 0x08C},
        {1231150, 0x08D},
    }}, {0x00CC, { // GGM Flooded Caves
        {1231151, 0x08E},
        {1231152, 0x08F},
    }}, {0x00CD, { // GGM Water Storage
        {1231153, 0x090},
    }}, {0x00D2, { // GGM Gloomy Caverns
        {1231154, 0x091},
        {1231155, 0x092},
        {1231156, 0x093},
        {1231157, 0x094},
    }}, {0x00D3, { // GGM Generator Cavern
        {1231158, 0x095},
    }}, {0x00D4, { // GGM Power Hut
        {1231159, 0x096},
    }}, {0x00D7, { // GGM Train Station
        {1231160, 0x097},
        {1231161, 0x098},
        {1231162, 0x099},
        {1231163, 0x09A},
    }}, {0x00D8, { // GGM Prospetor's Hut
        {1231164, 0x09B},
    }}, {0x00D9, { // GGM Mumbo
        {1231165, 0x09C},
        {1231166, 0x09D},
        {1231167, 0x09E},
    }}, {0x00DA, { // GGM Toxic Gas Cave
        {1231168, 0x09F},
        {1231169, 0x0A0},
    }}, {0x00DB, { // GGM Canary Cave
        {1231170, 0x0A1},
        {1231171, 0x0A2},
        {1231172, 0x0A3},
        {1231173, 0x0A4},
    }}, {0x0163, { // GGM Ordnance Storage Entrance
        {1231174, 0x0A5},
        {1231175, 0x0A6},
        {1231176, 0x0A7},
    }}, {0x00D6, { // WW
        {1231177, 0x0A8},
        {1231178, 0x0A9},
        {1231179, 0x0AA},
        {1231180, 0x0AB},
        {1231181, 0x0AC},
        {1231182, 0x0AD},
        {1231183, 0x0AE},
        {1231184, 0x0AF},
        {1231185, 0x0B0},
        {1231186, 0x0B1},
        {1231187, 0x0B2},
        {1231188, 0x0B3},
    }}, {0x00E1, { // WW Crazy Castle Stockade
        {1231189, 0x0B4},
        {1231190, 0x0B5},
    }}, {0x00E3, { // WW Pump Room
        {1231191, 0x0B6},
        {1231192, 0x0B7},
    }}, {0x00E6, { // WW Star Spinner
        {1231193, 0x0B8},
        {1231194, 0x0B9},
        {1231195, 0x0BA},
    }}, {0x00E7, { // WW Inferno
        {1231196, 0x0BB},
        {1231197, 0x0BC},
    }}, {0x00EB, { // WW Haunted Caverns
        {1231198, 0x0BD},
        {1231199, 0x0BE},
        {1231200, 0x0BF},
    }}, {0x00EC, { // WW Train Station
        {1231201, 0x0C0},
        {1231202, 0x0C1},
    }}, {0x00F9, { // WW Big Top
        {1231203, 0x0C2},
        {1231204, 0x0C3},
        {1231205, 0x0C4},
        {1231206, 0x0C5},
        {1231207, 0x0C6},
        {1231208, 0x0C7},
        {1231209, 0x0C8},
        {1231210, 0x0C9},
        {1231211, 0x0CA},
        {1231212, 0x0CB},
        {1231213, 0x0CC},
        {1231214, 0x0CD},
        {1231215, 0x0CE},
        {1231216, 0x0CF},
        {1231217, 0x0D0},
        {1231218, 0x0D1},
    }}, {0x00ED, { // JRL Jolly's
        {1231219, 0x0D2},
        {1231220, 0x0D3},
        {1231221, 0x0D4},
        {1231222, 0x0D5},
        {1231223, 0x0D6},
        {1231224, 0x0D7},
    }}, {0x00EE, { // JRL Pawno's Emporium
        {1231225, 0x0D8},
        {1231226, 0x0D9},
        {1231227, 0x0DA},
    }}, {0x00F7, { // JRL Seaweed Sanctum
        {1231228, 0x0DB},
        {1231229, 0x0DC},
        {1231230, 0x0DD},
        {1231231, 0x0DE},
    }}, {0x00F8, { // JRL Inside the Big Fish
        {1231232, 0x0DF},
        {1231233, 0x0E0},
    }}, {0x00FA, { // JRL Temple of the Fishes
        {1231234, 0x0E1},
        {1231235, 0x0E2},
        {1231236, 0x0E3},
        {1231237, 0x0E4},
    }}, {0x00FC, { // JRL Davy Jones' Locker
        {1231238, 0x0E5},
        {1231239, 0x0E6},
        {1231240, 0x0E7},
        {1231241, 0x0E8},
    }}, {0x0120, { // JRL Humba
        {1231242, 0x0E9},
    }}, {0x01A6, { // JRL Smuggler's Cavern
        {1231243, 0x0EA},
        {1231244, 0x0EB},
    }}, {0x01A7, { // JRL
        {1231245, 0x0EC},
    }}, {0x01A8, { // JRL Atlantis
        {1231246, 0x0ED},
        {1231247, 0x0EE},
        {1231248, 0x0EF},
        {1231249, 0x0F0},
        {1231250, 0x0F1},
        {1231251, 0x0F2},
    }}, {0x01A9, { // JRL Locker Cavern
        {1231252, 0x0F3},
        {1231253, 0x0F4},
        {1231254, 0x0F5},
        {1231255, 0x0F6},
        {1231256, 0x0F7},
        {1231258, 0x0F8},
        {1231257, 0x0F9},
    }}, {0x0112, { // TDL
        {1231259, 0x0FA},
        {1231260, 0x0FB},
        {1231261, 0x0FC},
        {1231262, 0x0FD},
        {1231263, 0x0FE},
        {1231264, 0x0FF},
        {1231265, 0x100},
        {1231266, 0x101},
        {1231267, 0x102},
        {1231268, 0x103},
        {1231269, 0x104},
        {1231270, 0x105},
        {1231271, 0x106},
        {1231272, 0x107},
        {1231273, 0x108},
        {1231274, 0x109},
        {1231275, 0x10A},
        {1231276, 0x10B},
        {1231277, 0x10C},
        {1231278, 0x10D},
    }}, {0x0113, { // TDL Terry's Nest
        {1231279, 0x10E},
        {1231280, 0x10F},
    }}, {0x0114, { // TDL Train Station
        {1231281, 0x110},
        {1231282, 0x111},
        {1231283, 0x112},
        {1231284, 0x113},
    }}, {0x0115, { // TDL Oogle Boogle Cave
        {1231285, 0x114},
        {1231286, 0x115},
        {1231287, 0x116},
        {1231288, 0x117},
    }}, {0x0116, { // TDL Inside the Mountain
        {1231289, 0x118},
        {1231290, 0x119},
        {1231291, 0x11A},
        {1231292, 0x11B},
    }}, {0x0117, { // TDL River Passage
        {1231293, 0x11C},
    }}, {0x0118, { // TDL Scrotty Cave
        {1231294, 0x11D},
        {1231295, 0x11E},
        {1231296, 0x11F},
    }}, {0x0119, { // TDL Unga Bunga Cave
        {1231297, 0x120},
        {1231298, 0x121},
        {1231299, 0x122},
        {1231300, 0x123},
        {1231301, 0x124},
        {1231302, 0x125},
    }}, {0x011A, { // TDL Stomping Plains
        {1231303, 0x126},
        {1231304, 0x127},
        {1231305, 0x128},
        {1231306, 0x129},
        {1231307, 0x12A},
        {1231308, 0x12B},
        {1231309, 0x12C},
    }}, {0x011B, { // TDL Bonfire Cavern
        {1231310, 0x12D},
        {1231311, 0x12E},
    }}, {0x0171, { // TDL Mumbo
        {1231312, 0x12F},
        {1231313, 0x130},
    }}, {0x0100, { // GI Outside
        {1231314, 0x131},
        {1231315, 0x132},
        {1231316, 0x133},
        {1231317, 0x134},
        {1231318, 0x135},
    }}, {0x0101, { // GI Floor 1
        {1231319, 0x136},
        {1231320, 0x137},
        {1231321, 0x138},
        {1231322, 0x139},
        {1231323, 0x13A},
        {1231324, 0x13B},
    }}, {0x0102, { // GI Train Station
        {1231325, 0x13C},
        {1231326, 0x13D},
        {1231327, 0x13E},
    }}, {0x0103, { // GI Worker's Quarters
        {1231328, 0x13F},
        {1231329, 0x140},
    }}, {0x0104, { // GI Trash compactor
        {1231330, 0x141},
        {1231331, 0x142},
    }}, {0x0105, { // GI Elevator Shaft
        {1231332, 0x143},
        {1231333, 0x144},
        {1231334, 0x145},
    }}, {0x0106, { // GI Floor 2
        {1231336, 0x146},
        {1231337, 0x147},
        {1231339, 0x148},
        {1231340, 0x149},
        {1231341, 0x14A},
        {1231342, 0x14B},
        {1231343, 0x14C},
        {1231344, 0x14D},
        {1231335, 0x14E},
        {1231338, 0x14F},
    }}, {0x0107, { // GI Floor 2 Electromagnetic Chamber
        {1231345, 0x150},
        {1231346, 0x151},
        {1231347, 0x152},
    }}, {0x0108, { // GI Floor 3
        {1231348, 0x153},
        {1231349, 0x154},
        {1231350, 0x155},
        {1231351, 0x156},
        {1231352, 0x157},
        {1231353, 0x158},
    }}, {0x0109, { // GI Boiler Plant
        {1231354, 0x159},
        {1231355, 0x15A},
    }}, {0x010B, { // GI Floor 4
        {1231356, 0x15B},
        {1231357, 0x15C},
        {1231358, 0x15D},
        {1231360, 0x15E},
        {1231361, 0x15F},
        {1231362, 0x160},
        {1231359, 0x161},
    }}, {0x010D, { // GI Quality Control
        {1231363, 0x162},
        {1231364, 0x163},
        {1231365, 0x164},
    }}, {0x010E, { // GI Floor 5
        {1231366, 0x165},
        {1231367, 0x166},
        {1231368, 0x167},
    }}, {0x010F, { // GI Air Conditioning Plant
        {1231369, 0x168},
        {1231370, 0x169},
        {1231371, 0x16A},
        {1231372, 0x16B},
        {1231373, 0x16C},
    }}, {0x0110, { // GI Repair Depot
        {1231374, 0x16D},
        {1231375, 0x16E},
    }}, {0x0111, { // GI Waste Disposal
        {1231376, 0x16F},
        {1231377, 0x170},
        {1231378, 0x171},
        {1231379, 0x172},
    }}, {0x0162, { // GI Clinker's Cavern
        {1231380, 0x173},
        {1231381, 0x174},
        {1231382, 0x175},
        {1231383, 0x176},
        {1231384, 0x177},
        {1231385, 0x178},
        {1231386, 0x179},
        {1231387, 0x17A},
    }}, {0x0187, { // GI Sewer Entrance
        {1231388, 0x17B},
        {1231389, 0x17C},
        {1231390, 0x17D},
        {1231391, 0x17E},
    }}, {0x0127, { // HFP Lava
        {1231392, 0x17F},
        {1231393, 0x180},
        {1231394, 0x181},
        {1231395, 0x182},
        {1231396, 0x183},
        {1231397, 0x184},
        {1231398, 0x185},
        {1231399, 0x186},
        {1231400, 0x187},
        {1231401, 0x188},
        {1231402, 0x189},
    }}, {0x0128, { // HFP Icy
        {1231403, 0x18A},
        {1231404, 0x18B},
        {1231405, 0x18C},
        {1231406, 0x18D},
        {1231407, 0x18E},
        {1231408, 0x18F},
        {1231409, 0x190},
    }}, {0x0129, { // HFP Lava Train Station
        {1231410, 0x191},
        {1231411, 0x192},
    }}, {0x012A, { // HFP Icy Train Station
        {1231412, 0x193},
        {1231413, 0x194},
    }}, {0x012B, { // HFP Chilli Billi
        {1231414, 0x195},
    }}, {0x012C, { // HFP Chilly Willy
        {1231415, 0x196},
    }}, {0x012D, { // HFP Kickball Coliseum
        {1231416, 0x197},
        {1231417, 0x198},
        {1231418, 0x199},
        {1231419, 0x19A},
        {1231420, 0x19B},
        {1231421, 0x19C},
    }}, {0x0132, { // HFP Icicle Grotto
        {1231422, 0x19D},
        {1231423, 0x19E},
        {1231424, 0x19F},
        {1231425, 0x1A0},
        {1231426, 0x1A1},
        {1231427, 0x1A2},
    }}, {0x0134, { // HFP Mumbo
        {1231428, 0x1A3},
        {1231429, 0x1A4},
    }}, {0x0135, { // HFP Humba
        {1231430, 0x1A5},
        {1231431, 0x1A6},
    }}, {0x0136, { // CCL
        {1231432, 0x1A7},
        {1231433, 0x1A8},
        {1231434, 0x1A9},
        {1231435, 0x1AA},
        {1231436, 0x1AB},
        {1231437, 0x1AC},
        {1231438, 0x1AD},
        {1231439, 0x1AE},
        {1231440, 0x1AF},
        {1231441, 0x1B0},
        {1231442, 0x1B1},
        {1231443, 0x1B2},
        {1231444, 0x1B3},
        {1231445, 0x1B4},
        {1231446, 0x1B5},
        {1231447, 0x1B6},
        {1231448, 0x1B7},
        {1231449, 0x1B8},
        {1231450, 0x1B9},
        {1231451, 0x1BA},
        {1231452, 0x1BC},
        {1231453, 0x1BB},
        {1231454, 0x1BD},
        {1231455, 0x1BE},
        {1231456, 0x1BF},
        {1231457, 0x1C0},
        {1231458, 0x1C1},
        {1231459, 0x1C2},
        {1231460, 0x1C3},
        {1231461, 0x1C4},
        {1231462, 0x1C5},
        {1231463, 0x1C6},
        {1231464, 0x1C7},
        {1231466, 0x1C8},
        {1231465, 0x1C9},
    }}, {0x0137, { // CCL Trash Can
        {1231467, 0x1CA},
        {1231468, 0x1CB},
    }}, {0x0138, { // CCL Cheese Wedge
        {1231469, 0x1CC},
        {1231470, 0x1CD},
    }}, {0x013A, { // CCL Central Cavern
        {1231471, 0x1CE},
        {1231472, 0x1CF},
        {1231473, 0x1D0},
        {1231474, 0x1D1},
        {1231475, 0x1D2},
        {1231476, 0x1D3},
        {1231477, 0x1D4},
    }}, {0x013D, { // CCL Pot O Gold
        {1231478, 0x1D5},
        {1231479, 0x1D6},
    }}, {0x0140, { // CCL Humba
        {1231480, 0x1D7},
        {1231481, 0x1D8},
    }}
};
