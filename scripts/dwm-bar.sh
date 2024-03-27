#!/bin/sh
battery(){
    battery=`acpi|awk '{gsub(" ","")};{gsub(",|:"," ");print $3}'`;
    statue=`acpi|awk '{gsub(",","")};{print $3}'`;

    if [[ $statue == "Discharging" ]]; then
        statue="disc"
    elif [[ $statue == "Charging" ]]; then
        statue="chr"
    elif [[ $statue == "Full" ]]; then
        statue="F"
    elif [[ $statue == 'Not' ]];then
        statue='notc'
    else
        statue="unknown"
    fi
    echo $battery"("$statue")"
    # echo `acpi|awk '{gsub(",|%","");print $4"("$3")"}'`
}
brightness(){
    echo `brightnessctl | grep -o "(.*" | tr -d "(%)"`
}
getDate(){
    echo `date +"%a %m/%d %H:%M"`
}
volume(){
    if [ $(pamixer --get-mute) == "true" ];then
        echo 'mute'
    else
        echo $(pamixer --get-volume)
    fi
}

main(){
    bat=`battery`
    bri=`brightness`
    dat=`getDate`
    vol=`volume`
    xsetroot -name  "bl $bri | vol $vol |bat $bat | $dat"
}
while true; do
    main
	sleep 20
done
