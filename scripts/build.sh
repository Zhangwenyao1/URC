#!/bin/bash

# Build ros and pio projects

success_count=4
fail_count=0
echo Building ROS workspace...
cd rosws
catkin_make
if [ $? -ne 0 ]; then
  echo -e "ROS \e[101m\e[93mFAILED\e[0m to build!"
  read -p "Do you want to continue building? (y/n) " yn
  if [ "${yn,,}" = "n" ]; then
    exit 1
  fi
  success_count=$((success_count - 1))
  fail_count=$((fail_count + 1))
fi
cd ..
true
for duino in ./microcontroller/*
do
    echo -e "Building platformio project in \e[95m\e[1m$duino\e[0m"
    cd $duino
    pio run
    if [ $? -ne 0 ]; then
       echo -e "Platformio project \e[95m\e[1m$duino\e[0m \e[101m\e[93mFAILED\e[0m to build!"
       read -p "Do you want to continue building? (y/n) " yn
       if [ "${yn,,}" = "n" ]; then
          exit 1
       fi
       true
       success_count=$((success_count - 1))
       fail_count=$((fail_count + 1))
    fi
    cd ../..
done

echo Done building!
echo -e "\e[95m\e[1m$success_count\e[0m successes, \e[95m\e[1m$fail_count\e[0m fails."

