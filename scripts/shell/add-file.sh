#!/bin/bash

function add() {
    local flag=$1
    local name=$2
    if [ "$flag" = "-f" ]; then
        touch $name
    elif [ "$flag" = "-d" ]; then
        mkdir $name
    else
        echo "Usage: $0 [-f filename] or [-d dirname]"
    fi
}
