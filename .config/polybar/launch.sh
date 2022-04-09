#!/bin/bash
# Source: this github issue recommended on polybar github page itself
# URL: https://github.com/polybar/polybar/issues/763

primary_monitor=eDP-1-1
secondary_monitor=HDMI-0

# Terminate already running bar instances
killall -q polybar

# Wait until the processes have been shut down
while pgrep -u $UID -x polybar > /dev/null; do sleep 0.5; done

# get a list of all currently connected monitors
outputs=$(xrandr --query | grep " connected" | cut -d" " -f1)
#tray_output=eDP1

for monitor in $outputs; do

    export MONITOR=$monitor
    export TRAY_POSITION=none
    
    tray_output=$monitor
    TRAY_POSITION=right
 

    # render different bars for different monitors
    if [ $monitor == $primary_monitor ]
    	then
        # if home primary or work secondary (the big monitors) are connected, load the main bars on them
        MONITOR=$monitor polybar --reload eDP-1-1 --quiet &
    elif [ $monitor == $secondary_monitor]
    	then
        # if second monitors are connected, load different bars for them
        MONITOR=$monitor polybar --reload HDMI-0 --quiet &
    else
        # for any other case, just load the main top and bottom bars
        MONITOR=$monitor polybar --reload HDMI-0 --quiet &
    fi
done
