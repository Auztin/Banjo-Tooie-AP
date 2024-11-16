#ifndef AP_H
#define AP_H

#include "util.h"

typedef struct {
  u8 death_link : 1;
  u8 death_link_queued : 1;
  u8 smooth_banjo : 1;
  u8 items[AP_ITEM_MAX];
} ap_t;
extern ap_t ap;

void ap_check();
void ap_new_file();
void ap_load_file();

#endif // AP_H
