#!/bin/sh
# res=$(ps ax|grep -v grep|grep stalonetray)
# if [ $res == ""]; then
#     stalonetray
# else 
#     killall stalonetray
# fi
if pgrep "stalonetray" > /dev/null; then
    killall stalonetray
else
    stalonetray
fi
