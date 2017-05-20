#!/bin/bash

# this is to log disk usage so that after a crash I can see what program and file was being consumed the most

collect_io_stats() {
  sudo iotop -n 1 -b -o > out
  sed '4!d' out
  PID=`sed '4!d' out | awk '{print $1}'`
  sudo lsof -p $PID
  echo -e "\n"
  sed '5!d' out
  PID=`sed '5!d' out | awk '{print $1}'`
  sudo lsof -p $PID
  echo -e "\n"
  sed '6!d' out
  PID=`sed '6!d' out | awk '{print $1}'`
  sudo lsof -p $PID
  echo -e "\n"
  sed '7!d' out
  PID=`sed '7!d' out | awk '{print $1}'`
  sudo lsof -p $PID
  echo -e "\n"
}
while :
do
  date >> ~/collect_io_stats.log
  collect_io_stats >> ~/collect_io_stats.log
  sleep 1
done
