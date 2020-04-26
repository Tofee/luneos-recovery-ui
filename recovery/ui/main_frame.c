#include "lvgl/lvgl.h"

void create_main_frame()
{
    /*Create a "Hello world!" label*/
    lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Hello world!");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}
