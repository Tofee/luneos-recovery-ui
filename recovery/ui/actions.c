#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>

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

void event_handler_ChangeMassStorage(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        const char * txt = lv_btnm_get_active_btn_text(obj);
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
}

void event_handler_Reboot(lv_obj_t * obj, lv_event_t event)
{
    if(obj && event == LV_EVENT_CLICKED) {
        printf("Reboot !\n");

        sync();
        reboot(RB_AUTOBOOT);
    }
}

void event_handler_Poweroff(lv_obj_t * obj, lv_event_t event)
{
    if(obj && event == LV_EVENT_CLICKED) {
        printf("Power Off !\n");

        sync();
        reboot(RB_POWER_OFF);
    }
}
