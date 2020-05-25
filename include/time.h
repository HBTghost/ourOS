#ifndef _time_h
#define _time_h

typedef struct {
    int tm_sec;         /* seconds */
    int tm_min;         /* minutes */
    int tm_hour;        /* hours */
    int tm_mday;        /* day of the month */
    int tm_mon;         /* month */
    int tm_year;        /* year */
    int tm_wday;        /* day of the week */
    int tm_yday;        /* day in the year */
    int tm_isdst;       /* daylight saving time */
} time_t_clone;



void time(time_t_clone * tp);
char *convert_asc(char *str_time, const time_t_clone* t);
void read_time(time_t_clone * tp);
void print_time_locale();
void print_time_now_struct();
#endif
