/* Batteryd - A simple battery daemon for Archlinux
 * 
 * Copyright (c) 2013 by Christian Rebischke <Chris.Rebischke@gmail.com>
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
 * Email : Chris.Rebischke@gmail.com
 * Github: www.github.com/Shibumi
 * GPG: E2C0DC2A
 *
 * How to compile:
 * g++ batteryd.cpp -o batteryd $(pkg-config --cflags --libs libnotify)
 *
 */


#include <libnotify/notify.h>
#include <cstdlib> 
#include <fstream> 
#include <unistd.h>
#include <sstream> 

using namespace std;



//Begin config section feel free to change these values :)
const int repeater = 60;
const int high = 15;
const int low = 10;
//End config section



int main(void)
{
	string scapacity;
	int icapacity;
	string status;
	ifstream infile1;
	ifstream infile2;
	
	while(true)
    {
        sleep(repeater);
        infile1.open("/sys/class/power_supply/BAT0/status");
        getline(infile1,status);
        infile1.close();
        if(status.compare("Discharging") == 0)
        {
            infile2.open("/sys/class/power_supply/BAT0/capacity");
            getline(infile2,scapacity);
            infile2.close();
            stringstream convert(scapacity);
            convert >> icapacity;
            if(icapacity < high && icapacity > low)
            {
              if(notify_init("batteryd"))
              {
                NotifyNotification *notification = notify_notification_new("Caution!!","Battery is low", NULL);
                notify_notification_show(notification, NULL);
                g_object_unref(notification);
                notify_uninit();
                }
                continue;
            }
            else if(icapacity < low)
            {
              if(notify_init("batteryd"))
              {
                NotifyNotification *notification = notify_notification_new("Caution!!","Battery is very low",NULL);
                notify_notification_show(notification, NULL);
                g_object_unref(notification);
                notify_uninit();
                }
                system("echo -e \a");
                continue;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
    return 0;
}
