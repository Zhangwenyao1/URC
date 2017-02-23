#!/bin/bash

export PATH=/usr/local/cuda-8.0/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
export __GL_PERFMON_MODE=1
. /opt/ros/kinetic/setup.bash
. /home/ubuntu/URC/rosws/devel/setup.bash

exec "$@"
