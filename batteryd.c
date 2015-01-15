/* Batteryd - A simple battery daemon for Archlinux
 * 
 * Copyright (c) 2014 by Christian Rebischke <echo Q2hyaXMuUmViaXNjaGtlQGdtYWlsLmNvbQo= | base64 -d>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 *
 *====================================================================== 
 * Author: Christian Rebischke
 * Email : echo Q2hyaXMuUmViaXNjaGtlQGdtYWlsLmNvbQo= | base64 -d
 * Github: www.github.com/Shibumi
 *
 * How to compile:
 * gcc batteryd.c -o batteryd $(pkg-config --cflags --libs libnotify)
 *
 * vim: set ts=2 sts=2 sw=2 et
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libnotify/notify.h>
#define ERROR_NO_STATUS 2
#define ERROR_NO_CAPACITY 3


//Begin config section
static const int REPEATER = 60;
static const int HIGH = 15;
static const int LOW = 10;
static const char *STATUSPATH = "/sys/class/power_supply/BAT1/status";
static const char *CAPACITYPATH = "/sys/class/power_supply/BAT1/capacity";
static const int FILE_LIMIT = 12;
static const char *DISCHARGING = "Discharging";
static const int TIMEOUT = 30000;
//End config section


//Function that checks if file exists or not

int 
exists(const char *fname)
{
    FILE *file;
    if (file = fopen(fname, "r"))
    {
        fclose(file);
        return TRUE;
    }
    return FALSE;
}


int 
main()
{
  char scapacity[FILE_LIMIT];
  int icapacity = 0;
  char status[FILE_LIMIT];
  FILE *statusfile = NULL;
  FILE *capacityfile = NULL;

  while(TRUE)
  {
    //This is the sleep intervall for the daemon
    sleep(REPEATER);
    
    //Filechecks
    if(!exists(STATUSPATH))
    {
      fputs("[-] status file does not exist", stderr);
      return ERROR_NO_STATUS;
    } 
    if(!exists(CAPACITYPATH))
    {
      fputs("[-] capacity file does not exist", stderr);
      return ERROR_NO_CAPACITY;
    } 

    statusfile = fopen(STATUSPATH, "r");
    fgets(status, FILE_LIMIT, statusfile );
    fflush(statusfile);
    fclose(statusfile);
    if(strcmp(status, DISCHARGING ) == 0)
    {
      capacityfile = fopen(CAPACITYPATH, "r");
      fgets(scapacity, FILE_LIMIT, capacityfile);
      fflush(capacityfile);
      fclose(capacityfile);
      icapacity = atoi(scapacity);
      if(icapacity < HIGH && icapacity > LOW)
      {
        if(notify_init("batteryd"))
        {
          NotifyNotification *notification = notify_notification_new("Caution!!","Battery is LOW", NULL);
          notify_notification_set_urgency(notification, NOTIFY_URGENCY_NORMAL);
          notify_notification_set_timeout(notification, TIMEOUT);
          notify_notification_show(notification, NULL);
          g_object_unref(notification);
          notify_uninit();
        }
      }
      else if(icapacity < LOW)
      {
        if(notify_init("batteryd"))
        {
          NotifyNotification *notification = notify_notification_new("Caution!!","Battery is very LOW",NULL);
          notify_notification_set_urgency(notification, NOTIFY_URGENCY_CRITICAL);
          notify_notification_set_timeout(notification, TIMEOUT);
          notify_notification_show(notification, NULL);
          g_object_unref(notification);
          notify_uninit();
        }
      }
    }
  }
}
