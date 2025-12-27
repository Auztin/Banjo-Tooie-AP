#include "saves.h"
#include <save.h>

void saves_load(u32 _unk_A0) {
	bt_saves_load(_unk_A0);
}

u16 saves_totals(bt_saves_totals_type_t type) {
	if (bt_save_slot > 2) return 0;
	u16 total = 0;
	switch (type) {
	case BT_SAVES_TOTALS_JINJOS:
		for (int i = 0; i < 9; i++) total += saves_jinjo_family_count(i);
		return total;
	case BT_SAVES_TOTALS_JIGGIES:
		return ap_save.items[API_JIGGY];
	case BT_SAVES_TOTALS_HONEYCOMBS:
		return ap_save.items[API_EMPTY_HONEYCOMB];
	case BT_SAVES_TOTALS_GLOWBOS:
		if (bt_flags.mt_mumbo) total++;
		if (bt_flags.gi_mumbo) total++;
		if (bt_flags.ioh_mumbo) total++;
		if (bt_flags.ccl_mumbo) total++;
		if (bt_flags.hfp_mumbo) total++;
		if (bt_flags.tdl_mumbo) total++;
		if (bt_flags.jrl_mumbo) total++;
		if (bt_flags.ww_mumbo) total++;
		if (bt_flags.ggm_mumbo) total++;
		if (bt_flags.mt_humba) total++;
		if (bt_flags.gi_humba) total++;
		if (bt_flags.ccl_humba) total++;
		if (bt_flags.hfp_humba) total++;
		if (bt_flags.tdl_humba) total++;
		if (bt_flags.jrl_humba) total++;
		if (bt_flags.ww_humba) total++;
		if (bt_flags.ggm_humba) total++;
		return total;
	case BT_SAVES_TOTALS_PAGES:
		return ap_save.items[API_CHEATO_PAGE];
	case BT_SAVES_TOTALS_SACRED_STATUES:
		if (ap_save.options.shuffle_green_relics) return ap_save.items[API_GREEN_RELIC];
		if (bt_flags.mt_sacred_statue_adjacent_big_pillars_room1) total++;
		if (bt_flags.mt_sacred_statue_adjacent_big_pillars_room2) total++;
		if (bt_flags.mt_sacred_statue_near_entrance1) total++;
		if (bt_flags.mt_sacred_statue_near_entrance2) total++;
		if (bt_flags.mt_sacred_statue_small_pillars1) total++;
		if (bt_flags.mt_sacred_statue_small_pillars2) total++;
		if (bt_flags.mt_sacred_statue_small_pillars3) total++;
		if (bt_flags.mt_sacred_statue_sput_sput2) total++;
		if (bt_flags.mt_sacred_statue_sput_sput1) total++;
		if (bt_flags.mt_sacred_statue_sput_sput3) total++;
		if (bt_flags.mt_sacred_statue_sput_sput4) total++;
		if (bt_flags.mt_sacred_statue_adjacent_big_pillars_room3) total++;
		if (bt_flags.mt_sacred_statue_big_pillars4) total++;
		if (bt_flags.mt_sacred_statue_big_pillars3) total++;
		if (bt_flags.mt_sacred_statue_big_pillars1) total++;
		if (bt_flags.mt_sacred_statue_big_pillars2) total++;
		if (bt_flags.mt_sacred_statue_big_pillars5) total++;
		if (bt_flags.mt_sacred_statue_sput_sput5) total++;
		if (bt_flags.mt_sacred_statue_near_sacred_chambers1) total++;
		if (bt_flags.mt_sacred_statue_near_sacred_chambers2) total++;
		if (bt_flags.mt_sacred_statue_passage_near_entrance1) total++;
		if (bt_flags.mt_sacred_statue_passage_near_entrance2) total++;
		if (bt_flags.mt_sacred_statue_passage_near_sacred_chambers1) total++;
		if (bt_flags.mt_sacred_statue_passage_near_sacred_chambers2) total++;
		if (bt_flags.mt_sacred_statue_passage_near_sacred_chambers3) total++;
		return total;
	case BT_SAVES_TOTALS_NOTES:
		total += ap_save.items[API_NOTE_NEST] * 5;
		total += ap_save.items[API_BASS_CLEF] * 10;
		total += ap_save.items[API_TREBLE_CLEF] * 20;
		return total;
	case BT_SAVES_TOTALS_DOUBLOONS:
		return ap_save.items[API_DOUBLOON];
	case BT_SAVES_TOTALS_BIG_TOP_TICKETS:
		if (ap_save.options.shuffle_big_top_tickets) return ap_save.items[API_BIG_TOP_TICKET];
		if (bt_flags.ww_ticket_collected_entrance) total++;
		if (bt_flags.ww_ticket_collected_space) total++;
		if (bt_flags.ww_ticket_collected_spooky) total++;
		if (bt_flags.ww_ticket_collected_western) total++;
		return total;
	default: return 0;
	}
}

u8 saves_jinjo_family_count(bt_jinjo_t color) {
	if (bt_save_slot > 2) return 0;
	switch (color) {
	case BT_JINJO_WHITE: return ap_save.items[API_WHITE_JINJO];
	case BT_JINJO_ORANGE: return ap_save.items[API_ORANGE_JINJO];
	case BT_JINJO_YELLOW: return ap_save.items[API_YELLOW_JINJO];
	case BT_JINJO_BROWN: return ap_save.items[API_BROWN_JINJO];
	case BT_JINJO_GREEN: return ap_save.items[API_GREEN_JINJO];
	case BT_JINJO_RED: return ap_save.items[API_RED_JINJO];
	case BT_JINJO_BLUE: return ap_save.items[API_BLUE_JINJO];
	case BT_JINJO_PURPLE: return ap_save.items[API_PURPLE_JINJO];
	case BT_JINJO_BLACK: return ap_save.items[API_BLACK_JINJO];
	default: return 0;
	}
}
