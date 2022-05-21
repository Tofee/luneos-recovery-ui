#ifndef ACTIONS_H
#define ACTIONS_H
/* clang-format off */

void event_handler_ChangeMassStorage(lv_event_t *e);
void event_handler_Reboot(lv_event_t *e);
void event_handler_Poweroff(lv_event_t *e);
void event_handler_refresh_dmesg(lv_timer_t * t);

#endif /* ACTIONS_H */
