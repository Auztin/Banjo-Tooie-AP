#include "main.h"
#include "dma.h"
#include "usb.h"

#include "bt.h"

#include "save.h"

main_t main = {0, };

void pre_init() {
  main.is_emulator = io_read(0xA4100010) == 0 ? 1 : 0;
}

void post_init() {
  usb_init();
}

void pre_loop() {
  if (main.frame_count++ >= 60) main.frame_count = 0;
  usb_check();
}

void post_loop() {
}

void pre_load_scene(u16 *scene, u16 *entry) {
}

void post_load_scene(u16 scene, u16 entry) {

}

void pre_load_save() {
}

void post_load_save() {
  if (main.new_file) {
    main.new_file = 0;
  }
}

void pre_object_init() {

}
void post_object_init() {
  
}
