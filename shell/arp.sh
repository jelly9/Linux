#!/bin/bash

head='192.168.43'
i=1
count=0
while [ $i -le 254 ]
do
    if [ $count -gt 10 ];then
        count=0
        sleep 1
    fi

    ping -c1 "$head"".$i" &
    let i++
    let count++
done

#等待后台作业
wait
echo "-------------------------------------"
arp -a | grep -v 'incomplete'
echo "-------------------------------------"
