#include "time.h"
#include "kernel.h"
#include <string.h> 
#include <stdio.h>
#define DEFAULT_HUSO 1

bool fmt12 = 0 ;
const char *_days[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday",
  "Thursday", "Friday", "Saturday"
};

static int currentHuso = 1;


typedef struct
{
    int id;
    char * city;
    char * code;
    int diff;
} huso;

const huso husos[] =
{
    { 1, "Buenos Aires  ", "ART",  -3 },
    { 2, "Rio de Janeiro", "BRT", -3 },
    { 3, "Mexico DF     ", "CDT",-6 },
    { 4, "San Francisco ", "PDT",-8 },
    { 5, "Washington DC ", "EDT",-5 },
    { 6, "Londres       ", "BST",0 },
    { 7, "Sidney        ", "MDT",+10 },
    { 8, "Tokio         ", "JST",+9 },
    { 9, "Moscu         ", "MSK",+4 }
};

const char *_days_abbrev[] = {
  "Sun", "Mon", "Tue", "Wed", 
  "Thu", "Fri", "Sat"
};

const char *_months[] = {
  "January", "February", "March",
  "April", "May", "June",
  "July", "August", "September",
  "October", "November", "December"
};

const char *_months_abbrev[] = {
  "Jan", "Feb", "Mar",
  "Apr", "May", "Jun",
  "Jul", "Aug", "Sep",
  "Oct", "Nov", "Dec"
};

char * asctime(char * str_time, const time_t_clone * tp, int fmt, int showday) {
    // Thu May 29 11:35:33 ART 2014
    char time[9];
    int wday, mon;
    char day[3];
    char year[3];
    if(fmt) {
        wday = ((tp->tm_wday & 0xF0) >> 4) * 10 + (tp->tm_wday & 0x0F);
        strcpy(str_time, _days_abbrev[wday]);
        strcat(str_time, " ");
        mon = ((tp->tm_mon & 0xF0) >> 4) * 10 + (tp->tm_mon & 0x0F);
        strcat(str_time, _months_abbrev[mon]);
        strcat(str_time, " ");
    }
	if(showday) {
    	day[0] = ((tp->tm_mday & 0xF0) >> 4) + '0';
   		day[1] = ((tp->tm_mday & 0x0F)) + '0';
    	day[2] = 0;
		strcat(str_time, day);
		strcat(str_time, " ");  
	}
    int d = ((tp->tm_hour & 0xF0) >> 4);
    int u = ((tp->tm_hour & 0x0F));
    int h = d * 10 + u;
    h = (h - husos[DEFAULT_HUSO - 1].diff + husos[currentHuso - 1].diff) % 24;
    if(fmt12 && h > 12)
        h = h - 12;
    time[0] = h/10 + '0';
    time[1] = h%10 + '0';
    time[2] = ':';
    time[3] = ((tp->tm_min & 0xF0) >> 4) + '0';
    time[4] = ((tp->tm_min & 0x0F)) + '0';
    time[5] = ':';
    time[6] = ((tp->tm_sec & 0xF0) >> 4) + '0';
    time[7] = ((tp->tm_sec & 0x0F)) + '0';
    time[8] = 0;
    strcat(str_time, time);
    strcat(str_time, " ");
    strcat(str_time, husos[currentHuso - 1].code);
    strcat(str_time, " ");
    if(fmt) {
        year[0] = ((tp->tm_year & 0xF0) >> 4) + '0';
        year[1] = ((tp->tm_year & 0x0F)) + '0';
        year[2] = 0;
        strcat(str_time, "20");
        strcat(str_time, year);
    }
    return str_time;
}

void read_time(time_t_clone * tp) {
    outb(0x70, 4);
    tp->tm_hour = inb(0x71);
    outb(0x70, 2);
    tp->tm_min = inb(0x71);
    outb(0x70, 0);
    tp->tm_sec = inb(0x71);
    outb(0x70, 6);
    tp->tm_wday = inb(0x71);
    outb(0x70, 7);
    tp->tm_mday = inb(0x71);
    outb(0x70, 8);
    tp->tm_mon = inb(0x71);
    outb(0x70, 9);
    tp->tm_year = inb(0x71);
    return;
}
void test_time() {
    char timeString[24] = {0};
    time_t_clone t;
    read_time(&t);
    print_string(asctime(timeString, &t, 1, 1));
}