#!/bin/bash
#
# Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
# 
# for testing only
#/opt/usr/scripts/telnetd &

# if keyscan is already on, do nothing
if [ -x /tmp/keyscan.pid ]; then
  exit
else
  st pmu show | grep -q 'hevc.*ON'
  while [ $? = "0" ]; do
    echo HEVC still on;
    /opt/usr/scripts/popup_timeout "Waiting for video mode stop..." 1
  done
    # copy saved or initial values to /tmp for runtime
  cp /opt/usr/scripts/initial_patches.sh /tmp
    # patch with initial or saved values and build menus
  . /opt/usr/scripts/apply.sh
    # launch keyscan to enable UI
  export EVAS_FONT_DPI=72
  export EINA_LOG_LEVELS=ecore_x:0,evas_main:0
  export ECORE_IMF_MODULE=isf
  export ECORE_INPUT_TIMEOUT_FIX=0
  export EINA_LOG_DLOG_ENABLE=0
  export EINA_LOG_LEVEL=0
  export ECORE_INPUT_FIX=1
  export XDG_CACHE_HOME=/tmp/.cache
  export EVAS_GL_NO_BLACKLIST=1
  export EINA_LOG_SYSLOG_ENABLE=0
  export ELM_PROFILE=mobile
  nice /opt/usr/scripts/keyscan /dev/event0 /dev/event1 /opt/usr/scripts/
fi
