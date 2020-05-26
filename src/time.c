#include "../include/time.h"
#include "kernel.h"
#include <string.h>
#include <stdio.h>
#define DEFAULT_REGION  1
//https://wiki.osdev.org/CMOS

bool fmt12 = false;

const char *_days_label[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"};

static int currentLocaleTime = 2;

typedef struct
{
    int id;
    char *city;
    char *code;
    int diff;
} huso;

const huso husos[] =
    {

        {1, "GMT", "GMT", 0},
        {2, "Viet Nam", "HCM", +7},
};

const char *_days_week_label[] = {
    "Sun", "Mon", "Tue", "Wed",
    "Thu", "Fri", "Sat"};

const char *_month_full_label[] = {
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"};

const char *_months_short_label[] = {
    "Jan", "Feb", "Mar",
    "Apr", "May", "Jun",
    "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"};int i = 0

char *convert_asc(char *str_time , const time_t_clone *t)
{
    char _time[9];
    char _day[3];
    char _year[3];
    int wday = -1; int mon =-1;
    

    
    //HH:mm:ss
    int d = ((t->tm_hour & 0xF0) >> 4);
    int u = ((t->tm_hour & 0x0F));
    int h = d * 10 + u;

    //get time by region
    h = (h - husos[DEFAULT_REGION - 1].diff + husos[currentLocaleTime - 1].diff) % 24;

    //h : 12 => _time  = "12" 
    _time[0] = h / 10 + '0'; 
    _time[1] = h %10 + '0';
    _time[2] = ':';
    
    //minute 0 -> 60, not use devide 10 => cast hexa to 2 character
    _time[3] = ((t->tm_min & 0xF0) >> 4) + '0';
    _time[4] = ((t->tm_min & 0x0F)) + '0';

    //same minute
    _time[5] =  ':';
    _time[6] = ((t->tm_sec & 0xF0) >> 4) + '0';
    _time[7] = ((t->tm_sec & 0x0F)) + '0';



    //
    wday = ((t->tm_wday & 0xF0) >> 4) * 10 + (t->tm_wday & 0x0F) - 0x01;
    strcpy(str_time, _days_label[wday]);
    strcat(str_time, " ");
    mon = ((t->tm_mon & 0xF0) >> 4) * 10 + (t->tm_mon & 0x0F) - 0x01;
    strcat(str_time, _months_short_label[mon]);
    strcat(str_time, " ");
    _day[0] = ((t->tm_mday & 0xF0) >> 4) + '0';
    _day[1] = ((t->tm_mday & 0x0F)) + '0';
    _day[2] = 0;
    strcat(str_time, _day);
    strcat(str_time, " ");

    _year[0] = ((t->tm_year & 0xF0) >> 4) + '0';
    _year[1] = ((t->tm_year & 0x0F)) + '0';
    _year[2] = 0;
    strcat(str_time, "20");
    strcat(str_time, _year);

    strcat(str_time, " ");
    strcat(str_time, _time);
    

    return str_time;
}

/*
Register  Contents            Range
 0x00      Seconds             0–59
 0x02      Minutes             0–59
 0x04      Hours               0–23 in 24-hour mode, 
                               1–12 in 12-hour mode, highest bit set if pm
 0x06      Weekday             1–7, Sunday = 1
 0x07      Day of Month        1–31
 0x08      Month               1–12
 0x09      Year                0–99
 0x32      Century (maybe)     19–20?
 0x0A      Status Register A
 0x0B      Status Register B

*/


void read_time(time_t_clone *tp)
{

    //hour
    outb(0x70, 4);
    tp->tm_hour = inb(0x71);
    
    //minute 0x02
    outb(0x70, 2);
    tp->tm_min = inb(0x71);

    //second 0x00
    outb(0x70, 0);
    tp->tm_sec = inb(0x71);
    
    //wday 0x06
    outb(0x70, 6);
    tp->tm_wday = inb(0x71);
    
    //day of month 0x07
    outb(0x70, 7);
    tp->tm_mday = inb(0x71);

    //month 0x08
    outb(0x70, 8);
    tp->tm_mon = inb(0x71);

    //year 0x09
    outb(0x70, 9);
    tp->tm_year = inb(0x71);
    return;
}
//5 19 40 2 37 5 32
void print_time_now_struct(){
    time_t_clone t;
    read_time(&t);
    print_string("- hour"); //5 
    print_int(t.tm_hour);
    print_string("- minutue"); //19
    print_int(t.tm_min);
    print_string("- second"); //40
    print_int(t.tm_sec);



    print_string("- Weeekday");  // 2 => mon
    print_int(t.tm_wday);


    print_string("- dom val "); //37d  => 0x25 
    print_int(t.tm_mday);
    
    
    //get hex to int

    
    char day [3];
    day[0] = ((t.tm_mday & 0xF0) >> 4) + '0';
    day[1] = ((t.tm_mday & 0x0F)) + '0';
    day[2] = 0;
    

    print_string("- dom real"); //37
    print_string(day);
    
    print_string("- Month"); //5
    //print_int(t.tm_moprint_time_localeear"); //32
    print_int(t.tm_year);

}
void print_time_locale()
{
    char timeString[24] = {0};
    time_t_clone t;
    read_time(&t);
    print_string (convert_asc(timeString, &t));
    //print_string(asctime(timeString, &t, 1, 1));
}
char* get_cur_time(char* t) {
    char timeString[24] = {0};
    time_t_clone t_clone;
    read_time(&t_clone);
    print_string (convert_asc(timeString, &t_clone));
    for (int i = 0; i < 24; ++i) {
      t[i] = timeString[i];
    }
    return t;
}