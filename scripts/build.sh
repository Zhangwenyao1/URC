#!/bin/bash

# Build ros and pio projects

success_count=0
fail_count=0

skip=0
case "$1" in 
 "y")
   skip=1 ;;
 "n")
   skip=2 ;;
esac

function contbuild() {
 local yn="u"
 if [ $skip -eq 0 ]; then
   read -p "Do you want to continue building? (y/n) " yn
 else
   case "$skip" in
    1) yn="y" ;;
    2) yn="n" ;;
   esac
 fi
 echo $yn
}

echo Building ROS workspace...
cd rosws
catkin_make
if [ $? -ne 0 ]; then
  echo -e "ROS \e[101m\e[93mFAILED\e[0m to build!"
  yn=$(contbuild)
  if [ "${yn,,}" = "n" ]; then
    exit 1
  fi
  fail_count=$((fail_count + 1))
else
  success_count=$((success_count + 1))
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
       yn=$(contbuild)
       if [ "${yn,,}" = "n" ]; then
          exit 1
       fi
       true
       fail_count=$((fail_count + 1))
    else
       success_count=$((success_count + 1))
    fi
    cd ../..
done

echo Done building!
echo -e "\e[95m\e[1m$success_count\e[0m successes, \e[95m\e[1m$fail_count\e[0m fails."

