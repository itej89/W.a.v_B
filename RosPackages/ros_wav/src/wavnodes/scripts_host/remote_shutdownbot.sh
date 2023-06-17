#!/bin/bash


printf "%s" "waiting for Wav B ..."
while ! timeout 0.2 ping -c 1 -n 192.168.1.172 &> /dev/null
do
    printf "%c" "."
done
printf "\n%s\n"  "Wav B is online"

ssh -t wav@192.168.1.172 'sudo shutdown now'
