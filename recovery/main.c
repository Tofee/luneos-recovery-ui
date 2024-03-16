#include "lvgl/lvgl.h"

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "ui/main_frame.h"

#define DISP_BUF_SIZE (1440*720/10) /* about 10% of screen size should be enough*/

#ifndef EVDEV_TOUCH_DEVICE
#define EVDEV_TOUCH_DEVICE "/dev/input/touchscreen0"
#endif /*EVDEV_TOUCH_DEVICE*/

int main(void)
{
    /*LittlevGL init*/
    lv_init();


    /*Linux frame buffer device init*/
    lv_display_t *disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");

    lv_evdev_create(LV_INDEV_TYPE_POINTER, EVDEV_TOUCH_DEVICE);

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize the display buffer.*/
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /*Create the UI*/
    create_main_frame();

    /*Handle LitlevGL tasks (5ms ticks)*/
    while(1) {
        lv_task_handler();
        usleep(5000);    // wait 5ms
    }

    return 0;
}


/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
