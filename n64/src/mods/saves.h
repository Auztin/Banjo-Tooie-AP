#pragma once

#include <bt/_unsorted.h>
#include <bt/saves.h>
#include <n64/types.h>

void saves_load(u32 _unk_A0);
u16 saves_totals(bt_saves_totals_type_t type);
u8 saves_jinjo_family_count(bt_jinjo_t color);
