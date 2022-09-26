#!/bin/bash

if ! command -v g++ &> /dev/null
then
    echo "g++ compiler not found on this machine"
    exit
else
    echo "g++ installed!"
    echo "checking for required packages..."
    if ! dpkg -s libncurses5-dev
    then
        echo "Could not verify presence of ncurses package"
        exit
    else
        echo "ncurses package verified"
    fi
fi

make

./life

