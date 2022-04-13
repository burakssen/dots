#!/bin/bash

getIcon() {
    if [ "$1" -lt 50 ]; then
    	echo "/home/burakssen/.config/scripts/backlight/icons/brightness-low.svg"
    else
	echo "/home/burakssen/.config/scripts/backlight/icons/brightness.svg"	
    fi

}

dunstify "Brightness at $(xbacklight -get)%" -i $(getIcon "$(xbacklight -get)") -a "Backlight" -u low -h "int:value:$(xbacklight -get)" -h string:x-dunst-stack-tag:backlight

