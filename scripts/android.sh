#!/bin/bash

# Do it

echo Android GPS "michael forgot the GPS" tool
echo Choose a command:

echo "[p] push the app to the phone"
echo "[l] list devices connected"
echo "[f] setup the port forwarding"

read -p "[plf]: " c
pushd .
cd rosws/src/rover_android
echo "ensuring I can run ADB"
chmod +x adb/adb

case "${c,,}" in 
 "p")
	echo "Starting ADB"
	echo Pushing file "apk/app_sensors.apk" via ADB
	set -e
	adb/adb install apk/app_sensors.apk
	set +e
	echo "Should be good!"
	echo "Check for a ROS Sensors App on the phone"
        ;;
 "l")
	echo "running adb"
	adb/adb devices
	;;
 "f")
	echo "forwarding local port 11311 to phone"
	adb/adb forward tcp:11311 tcp:11311
	echo "run the app with localhost as its thing, should work"
        ;;

echo "this script was brought to you by matthew at 7 in the morning"
echo "how the hell do you forget a GPS michael..."
