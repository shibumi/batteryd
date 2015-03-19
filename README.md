# batteryd

A simple and fast battery daemon Linux

**Dependencies:**

* libnotify

**Changelog:**

* Version 1.0.1 : removed exists function
* Version 1.0.0 : First Release

**How to config:**

The config section looks like this:

```
static const int REPEATER = 60;  
static const int HIGH = 15;  
static const int LOW = 10;  
static const char *STATUSPATH = "/sys/class/power_supply/BAT1/status";  
static const char *CAPACITYPATH = "/sys/class/power_supply/BAT1/capacity";  
static const int FILE_LIMIT = 12;  
static const char *DISCHARGING = "Discharging";  
static const int TIMEOUT = 30000;  
```

You config the daemon with setting the variables in the sourcecode directly. 
When done, you just recompile it.  

* *REPEATER* : The *REPEATER* sets the intervall (in seconds) how often the battery has to be checked.  
* *HIGH* : The *HIGH* value marks the reaction zone for example 15%. When the battery reaches 15% the batteryd  
  will notify the user.  
* *LOW*  : The *LOW* value marks the danger-zone for example 10% of battery.  
* *STATUSPATH* : The *STATUSPATH* is the filepath to the battery status file normally in:  
  "/sys/class/power_supply/BAT1/status" or  
  "/sys/class/power_supply/BAT0/status"  
* *CAPACITYPATH* : The *CAPACITYPATH* is the filepath to the battery capacity file normally in:  
  "/sys/class/power_supply/BAT1/capacity" or  
  "/sys/class/power_supply/BAT0/capacity"  
* *FILE_LIMIT* : The *FILE_LIMIT* is the limit-size of the two files above. You shouldn't change this value.
* *DISCHARCHING* : *DISCHARGING* is the buzz-word. When 'Discharging' is in  
  "/sys/class/power_supply/BAT1/status" the daemon will start checking for battery capacity.  
* *TIMEOUT* : *TIMEOUT* sets the timeout for the notify-message on screen ( in milliseconds ).
