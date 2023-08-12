#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
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
    fbdev_init();

    evdev_init();
    evdev_set_file(EVDEV_TOUCH_DEVICE);

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize the display buffer.*/
    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    fbdev_get_sizes(&disp_drv.hor_res, &disp_drv.ver_res);
    disp_drv.flush_cb = fbdev_flush;
    lv_disp_drv_register(&disp_drv);

	/* Initialize and register evdev input device interface */
    static lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = evdev_read;
	lv_indev_drv_register(&indev_drv);

    /*Create the UI*/
    create_main_frame();

    /*Handle LitlevGL tasks (5ms ticks)*/
    while(1) {
        lv_task_handler();
        usleep(5000);    // wait 5ms
        lv_tick_inc(5);  // inform lvgl that 5ms have passed
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
