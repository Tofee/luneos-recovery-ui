#include <stdio.h>
#include <stdlib.h>
#include <sys/klog.h>

#include "lvgl/lvgl.h"

#include "actions.h"

LV_FONT_DECLARE(Prelude_40);

void create_main_frame()
{
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_obj_set_size(scr, LV_PCT(100), LV_PCT(100));
    lv_disp_load_scr(scr);

    static lv_style_t h_style;
    lv_style_init(&h_style);
    lv_style_set_pad_all(&h_style, 10);

    lv_obj_t * h = lv_obj_create(scr);
    lv_obj_add_style(h, &h_style, 0);
    lv_obj_set_size(h, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(h, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(h, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    static lv_style_t text_prelude40_style;
    lv_style_init(&text_prelude40_style);
    lv_style_set_text_font(&text_prelude40_style, &Prelude_40);

    /*Label for selecting which storage is exposed as usb mass storage*/
    lv_obj_t * label = lv_label_create(h);
    lv_obj_add_style(label, &text_prelude40_style, 0);
    lv_label_set_text(label, "Current USB Mass Storage");
/*
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
*/
    static const char * btnm_str[] = {"SDCard", "\n", "eMMC", ""};
    lv_obj_t * btnm = lv_btnmatrix_create(h);
    lv_obj_set_size(btnm, LV_PCT(100), lv_disp_get_ver_res(NULL)/4);
    lv_btnmatrix_set_map(btnm, btnm_str);
    /*Allow selecting on one number at time*/
    lv_btnmatrix_set_btn_ctrl_all(btnm, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_one_checked(btnm, true);
    lv_btnmatrix_set_btn_ctrl(btnm, 0, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_add_event_cb(btnm, event_handler_ChangeMassStorage, LV_EVENT_VALUE_CHANGED, NULL);

/*
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_TGL_REL, &h_style_btnm_rel);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, &h_style_btnm_pressed);
*/

    /*label for actions*/
    lv_obj_t * label2 = lv_label_create(h);
    lv_obj_add_style(label2, &text_prelude40_style, 0);
    lv_label_set_text(label2, "Actions");

    /* Reboot */
/*
    static lv_style_t h_style_btn_reboot_rel;
    lv_style_copy(&h_style_btn_reboot_rel, th->style.btn.rel);
    h_style_btn_reboot_rel.body.main_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 200);
    h_style_btn_reboot_rel.body.grad_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 80);
    static lv_style_t h_style_btn_reboot_pr;
    lv_style_copy(&h_style_btn_reboot_pr, th->style.btn.pr);
    h_style_btn_reboot_pr.body.main_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 80);
    h_style_btn_reboot_pr.body.grad_color = lv_color_mix(LV_COLOR_YELLOW, LV_COLOR_BLACK, 120);
*/
    lv_obj_t * btnReboot = lv_btn_create(h);
    lv_obj_set_size(btnReboot, LV_PCT(50), LV_PCT(15));
    lv_obj_add_event_cb(btnReboot, event_handler_Reboot, LV_EVENT_CLICKED, NULL);
/*
    lv_btn_set_style(btnReboot, LV_BTN_STYLE_REL, &h_style_btn_reboot_rel);
    lv_btn_set_style(btnReboot, LV_BTN_STYLE_PR, &h_style_btn_reboot_pr);
*/
    lv_obj_t * labelButtonReboot = lv_label_create(btnReboot);
    lv_label_set_text(labelButtonReboot, "Reboot");
    lv_obj_center(labelButtonReboot);

    /* Power Off */
/*
    static lv_style_t h_style_btn_poweroff_rel;
    lv_style_copy(&h_style_btn_poweroff_rel, th->style.btn.rel);
    h_style_btn_poweroff_rel.body.main_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 200);
    h_style_btn_poweroff_rel.body.grad_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 80);
    static lv_style_t h_style_btn_poweroff_pr;
    lv_style_copy(&h_style_btn_poweroff_pr, th->style.btn.pr);
    h_style_btn_poweroff_pr.body.main_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 80);
    h_style_btn_poweroff_pr.body.grad_color = lv_color_mix(LV_COLOR_RED, LV_COLOR_BLACK, 120);
*/
    lv_obj_t * btnPowerOff = lv_btn_create(h);
    lv_obj_set_size(btnPowerOff, LV_PCT(50), LV_PCT(15));
    lv_obj_add_event_cb(btnPowerOff, event_handler_Poweroff, LV_EVENT_CLICKED, NULL);
/*
    lv_btn_set_style(btnPowerOff, LV_BTN_STYLE_REL, &h_style_btn_poweroff_rel);
    lv_btn_set_style(btnPowerOff, LV_BTN_STYLE_PR, &h_style_btn_poweroff_pr);
*/
    lv_obj_t * labelButtonPowerOff = lv_label_create(btnPowerOff);
    lv_label_set_text(labelButtonPowerOff, "Power Off");
    lv_obj_center(labelButtonPowerOff);

    /* Dmesg log */
    int len = klogctl(10, NULL, 0); /* read ring buffer size */
    if (len < 16*1024)
        len = 16*1024;
    if (len > 16*1024*1024)
        len = 16*1024*1024;
    char *dmesg_buf = malloc(len);
    len = klogctl(3, dmesg_buf, len); /* read ring buffer */
    if (len<0) sprintf(dmesg_buf, "Kernel message empty or access forbidden.");

    lv_obj_t * dmesgTextArea = lv_textarea_create(h);
    lv_obj_set_size(dmesgTextArea, LV_PCT(100), lv_disp_get_ver_res(NULL)/6);
    lv_textarea_set_text(dmesgTextArea, dmesg_buf);    /*Set an initial text*/
    lv_obj_set_flex_grow(dmesgTextArea, 1);

    free(dmesg_buf);
}

