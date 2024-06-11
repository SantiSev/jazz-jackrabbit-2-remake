#!/bin/bash

BUILD_DIR="./build"

if [ $# -lt 1 ]; then
    echo "Error: This script requires at least one parameter."
    exit 1
fi

# If -b then build the project
if [ $# -eq 2 ]; then
    if [ $2 == "-b" ]; then
        ./build.sh -debug log
    fi
fi

if [ $1 == "server" ]; then
    echo "Running server"

    {
        echo ""
        echo "NEW RUN - Time: $(date)"
        ./$BUILD_DIR/server 8080
    } >> server.log 2>&1
elif [ $1 == "client" ]; then
    echo "Running client"

    {
        echo ""
        echo "NEW RUN - Time: $(date)"
        ./$BUILD_DIR/client localhost 8080
    } >> client.log 2>&1
fi
