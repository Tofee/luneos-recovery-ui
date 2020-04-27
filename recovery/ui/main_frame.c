#include <stdio.h>
#include "lvgl/lvgl.h"

#include "actions.h"

void create_main_frame()
{
    lv_theme_t * th = lv_theme_night_init(210, NULL);     //Set a HUE value and a Font for the Night Theme
    lv_theme_set_current(th);                                           //Apply the theme

    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_disp_load_scr(scr);

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_pretty);
    h_style.body.padding.inner = LV_DPI / 10;
    h_style.body.padding.left = LV_DPI / 4;
    h_style.body.padding.right = LV_DPI / 4;
    h_style.body.padding.top = LV_DPI / 10;
    h_style.body.padding.bottom = LV_DPI / 10;

    lv_obj_t * h = lv_cont_create(scr, NULL);
    lv_obj_set_style(h, &h_style);
    lv_obj_set_click(h, false);
    lv_cont_set_fit(h, LV_FIT_FILL);
    lv_cont_set_layout(h, LV_LAYOUT_COL_M);

    /*Label for selecting which storage is exposed as usb mass storage*/
    lv_obj_t * label = lv_label_create(h, NULL);
    lv_label_set_text(label, "Current USB Mass Storage :");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t h_style_btnm;
    lv_style_copy(&h_style_btnm, &lv_style_pretty);
    h_style_btnm.body.radius = 10;

    static const char * btnm_str[] = {"SDCard", "\n", "eMMC", ""};
    lv_obj_t * btnm = lv_btnm_create(h, NULL);
    lv_obj_set_size(btnm, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL)/4);
    lv_btnm_set_map(btnm, btnm_str);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, &h_style);
    //lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_TGL_REL, &h_style_btnm);
    lv_btnm_set_btn_ctrl_all(btnm, LV_BTNM_CTRL_TGL_ENABLE);
    lv_btnm_set_one_toggle(btnm, true);
    lv_obj_set_event_cb(btnm, event_handler_ChangeMassStorage);

    /*label for actions*/
    lv_obj_t * label2 = lv_label_create(h, NULL);
    lv_label_set_text(label2, "Actions");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 0);

    /* Reboot */
    lv_obj_t * btnReboot = lv_btn_create(h, NULL);
    lv_obj_set_size(btnReboot, lv_disp_get_hor_res(NULL)/2, lv_disp_get_ver_res(NULL)/6);
    lv_obj_set_event_cb(btnReboot, event_handler_Reboot);
    lv_obj_align(btnReboot, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * labelButtonReboot = lv_label_create(btnReboot, NULL);
    lv_label_set_text(labelButtonReboot, "Reboot");

    /* Power Off */
    lv_obj_t * btnPowerOff = lv_btn_create(h, NULL);
    lv_obj_set_size(btnPowerOff, lv_disp_get_hor_res(NULL)/2, lv_disp_get_ver_res(NULL)/6);
    lv_obj_set_event_cb(btnPowerOff, event_handler_Poweroff);
    lv_obj_align(btnPowerOff, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * labelButtonPowerOff = lv_label_create(btnPowerOff, NULL);
    lv_label_set_text(labelButtonPowerOff, "Power Off");
}

