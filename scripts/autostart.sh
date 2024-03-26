#!/bin/sh

fcitx5 &
# picom make my window very not good.
#picom &

# my wireless mouse
xinput set-button-map 10 3 2 1
#change background
feh --bg-fill /home/lx/Pictures/wallPaper/5.jpeg
wmname LG3D
./dwm-bar.sh
