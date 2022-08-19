#!/bin/bash

count=$(xrandr | grep " connected " | wc -l)

if [[ $count -eq 2 ]]
then
	xrandr --output eDP-1-1 --primary --mode 1920x1080 --output HDMI-0 --mode 1920x1080 --right-of eDP-1-1
	echo "deneme"
else
	xrandr --output HDMI-0 --off
fi
