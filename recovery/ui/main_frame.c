#include <stdio.h>
#include <stdlib.h>
#include <sys/klog.h>
#include "lvgl/lvgl.h"

#include "actions.h"

LV_FONT_DECLARE(Prelude_20);
LV_FONT_DECLARE(Prelude_40);

void create_main_frame()
{
    lv_theme_t * th = lv_theme_night_init(210, &Prelude_40);     //Set a HUE value and a Font for the Night Theme
    lv_theme_set_current(th);                                           //Apply the theme

    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_disp_load_scr(scr);

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_transp_fit);
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
    lv_label_set_text(label, "Current USB Mass Storage");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t h_style_btnm_pressed;
    lv_style_copy(&h_style_btnm_pressed, th->style.btnm.btn.pr);
    h_style_btnm_pressed.body.grad_color = lv_color_make(10, 30, 120);
    h_style_btnm_pressed.body.main_color = LV_COLOR_BLUE;

    static lv_style_t h_style_btnm_rel;
    lv_style_copy(&h_style_btnm_rel, th->style.btnm.btn.rel);
    h_style_btnm_rel.body.main_color = lv_color_make(10, 30, 120);
    h_style_btnm_rel.body.grad_color = LV_COLOR_BLUE;

    static lv_style_t h_style_btnm_bg;
    lv_style_copy(&h_style_btnm_bg, th->style.btnm.bg);
    h_style_btnm_bg.body.padding.bottom = LV_DPI*2;

    static const char * btnm_str[] = {"SDCard", "\n", "eMMC", ""};
    lv_obj_t * btnm = lv_btnm_create(h, NULL);
    lv_obj_set_size(btnm, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL)/4);
    lv_btnm_set_map(btnm, btnm_str);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_TGL_REL, &h_style_btnm_rel);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, &h_style_btnm_pressed);
    lv_btnm_set_btn_ctrl_all(btnm, LV_BTNM_CTRL_TGL_ENABLE);
    lv_btnm_set_one_toggle(btnm, true);
    lv_btnm_set_btn_ctrl(btnm, 0, LV_BTNM_CTRL_TGL_STATE);
    lv_obj_set_event_cb(btnm, event_handler_ChangeMassStorage);

    static lv_style_t spacer_style;
    lv_style_copy(&spacer_style, &lv_style_transp_fit);
    h_style.body.padding.inner = LV_DPI / 10;
    h_style.body.padding.top = LV_DPI / 10;
    h_style.body.padding.bottom = LV_DPI / 10;

    lv_obj_t * spacer_cont = lv_cont_create(h, NULL);
    lv_obj_set_style(spacer_cont, &h_style);
    lv_obj_set_click(spacer_cont, false);

    /*label for actions*/
    lv_obj_t * label2 = lv_label_create(h, NULL);
    lv_label_set_text(label2, "Actions");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 0);

    /* Reboot */
    static lv_style_t h_style_btn_reboot_rel;
    lv_style_copy(&h_style_btn_reboot_rel, th->style.btn.rel);
    h_style_btn_reboot_rel.body.main_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 200);
    h_style_btn_reboot_rel.body.grad_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 80);
    static lv_style_t h_style_btn_reboot_pr;
    lv_style_copy(&h_style_btn_reboot_pr, th->style.btn.pr);
    h_style_btn_reboot_pr.body.main_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 80);
    h_style_btn_reboot_pr.body.grad_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 120);

    lv_obj_t * btnReboot = lv_btn_create(h, NULL);
    lv_obj_set_size(btnReboot, lv_disp_get_hor_res(NULL)/2, lv_disp_get_ver_res(NULL)/6);
    lv_obj_set_event_cb(btnReboot, event_handler_Reboot);
    lv_obj_align(btnReboot, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_btn_set_style(btnReboot, LV_BTN_STYLE_REL, &h_style_btn_reboot_rel);
    lv_btn_set_style(btnReboot, LV_BTN_STYLE_PR, &h_style_btn_reboot_pr);

    lv_obj_t * labelButtonReboot = lv_label_create(btnReboot, NULL);
    lv_label_set_text(labelButtonReboot, "Reboot");

    /* Power Off */
    static lv_style_t h_style_btn_poweroff_rel;
    lv_style_copy(&h_style_btn_poweroff_rel, th->style.btn.rel);
    h_style_btn_poweroff_rel.body.main_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 200);
    h_style_btn_poweroff_rel.body.grad_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 80);
    static lv_style_t h_style_btn_poweroff_pr;
    lv_style_copy(&h_style_btn_poweroff_pr, th->style.btn.pr);
    h_style_btn_poweroff_pr.body.main_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 80);
    h_style_btn_poweroff_pr.body.grad_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 120);

    lv_obj_t * btnPowerOff = lv_btn_create(h, NULL);
    lv_obj_set_size(btnPowerOff, lv_disp_get_hor_res(NULL)/2, lv_disp_get_ver_res(NULL)/6);
    lv_obj_set_event_cb(btnPowerOff, event_handler_Poweroff);
    lv_obj_align(btnPowerOff, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_btn_set_style(btnPowerOff, LV_BTN_STYLE_REL, &h_style_btn_poweroff_rel);
    lv_btn_set_style(btnPowerOff, LV_BTN_STYLE_PR, &h_style_btn_poweroff_pr);

    lv_obj_t * labelButtonPowerOff = lv_label_create(btnPowerOff, NULL);
    lv_label_set_text(labelButtonPowerOff, "Power Off");

    /* Dmesg log */
    int len = klogctl(10, NULL, 0); /* read ring buffer size */
    if (len < 16*1024)
        len = 16*1024;
    if (len > 16*1024*1024)
        len = 16*1024*1024;
    char *dmesg_buf = malloc(len);
    len = klogctl(3, dmesg_buf, len); /* read ring buffer */
    if (len<0) sprintf(dmesg_buf, "Kernel message empty or access forbidden.");

    lv_obj_t * dmesgTextArea = lv_ta_create(h, NULL);
    lv_obj_set_size(dmesgTextArea, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL)/6);
    lv_obj_align(dmesgTextArea, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_ta_set_text(dmesgTextArea, dmesg_buf);    /*Set an initial text*/

    free(dmesg_buf);
}

