#!/bin/bash


if [ -z "$@" ]; then
    echo -en "Hibernate\0icon\x1f/home/burakssen/.config/scripts/rofi/icons/hibernate.png\n"
    echo -en "Reboot\0icon\x1f/home/burakssen/.config/scripts/rofi/icons/restart.svg\n"
    echo -en "Shutdown\0icon\x1f/home/burakssen/.config/scripts/rofi/icons/power.svg\n"    
    echo -en "Suspend\0icon\x1f/home/burakssen/.config/scripts/rofi/icons/suspend.svg\n"   
    echo -en "Lock\0icon\x1f/home/burakssen/.config/scripts/rofi/icons/lock.svg\n"
    echo -en "Logout\0icon\x1f/home/burakssen/.config/scripts/rofi/icons/logout.svg\n"
else
    if [ "$1" = "Shutdown" ]; then
        shutdown now
    elif [ "$1" = "Logout" ]; then
        i3-msg exit
    elif [ "$1" = "Reboot" ]; then
        reboot
    elif [ "$1" = "Suspend" ]; then
        systemctl suspend
    elif [ "$1" = "Lock" ]; then
        #i3lock --nofork
   	betterlockscreen -l 
    elif [ "$1" = "Hibernate" ]; then
        systemctl hibernate
    fi
fi
