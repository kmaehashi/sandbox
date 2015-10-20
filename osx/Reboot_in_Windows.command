#!/bin/sh -e

clear
echo Rebooting into Windows...
sudo bless --folder /Volumes/BOOTCAMP --setBoot --legacy
sudo shutdown -r now
