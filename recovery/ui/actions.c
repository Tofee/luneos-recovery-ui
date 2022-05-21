#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/reboot.h>
#include <sys/klog.h>

#include "lvgl/lvgl.h"

#ifndef CONFIGFS_USB_MASS_STORAGE_FILE
#define CONFIGFS_USB_MASS_STORAGE_FILE "/config/usb_gadget/g1/functions/mass_storage.usb0/lun.0/file"
#endif /*CONFIGFS_USB_MASS_STORAGE_FILE*/
#ifndef SDCARD_PATH
#define SDCARD_PATH "/dev/mmcblk0"
#endif /*SDCARD_PATH*/
#ifndef EMMC_PATH
#define EMMC_PATH "/dev/mmcblk2"
#endif /*EMMC_PATH*/

void event_handler_ChangeMassStorage(lv_event_t *e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    uint16_t btnId = lv_btnmatrix_get_selected_btn(obj);
    const char * txt = lv_btnmatrix_get_btn_text(obj, btnId);
    printf("Change USB Mass Storage to: %s\n", txt);

    FILE *f = fopen(CONFIGFS_USB_MASS_STORAGE_FILE, "w");
    if(f) {
        if(0 == strcmp(txt, "SDCard")) {
            fprintf(f, "%s\n", SDCARD_PATH);
        }
        else if(0 == strcmp(txt, "eMMC")) {
            fprintf(f, "%s\n", EMMC_PATH);
        }
        fclose(f); f = NULL;
    }
}

void event_handler_Reboot(lv_event_t *e)
{
    printf("Reboot !\n");

    sync();
    reboot(RB_AUTOBOOT);
}

void event_handler_Poweroff(lv_event_t *e)
{
    printf("Power Off !\n");

    sync();
    reboot(RB_POWER_OFF);
}

void event_handler_refresh_dmesg(lv_timer_t * t)
{
    lv_obj_t *dmesgTextArea = t->user_data;
    if (!dmesgTextArea) return;

    /* Dmesg log */
    int len = klogctl(10, NULL, 0); /* read ring buffer size */
    if (len < 16*1024)
        len = 16*1024;
    if (len > 16*1024*1024)
        len = 16*1024*1024;
    char *dmesg_buf = malloc(len);
    len = klogctl(3, dmesg_buf, len); /* read ring buffer */
    if (len<0) sprintf(dmesg_buf, "Kernel message empty or access forbidden.");

    lv_textarea_set_text(dmesgTextArea, dmesg_buf);    /*Set an initial text*/

    free(dmesg_buf);

}
