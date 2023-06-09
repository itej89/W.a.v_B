#!/bin/bash


printf "%s" "waiting for Wav B ..."
while ! timeout 0.2 ping -c 1 -n 10.42.0.1 &> /dev/null
do
    printf "%c" "."
done
printf "\n%s\n"  "Wav B is online"

ssh -t wav@10.42.0.1 'sudo shutdown now'
