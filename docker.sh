#!/bin/bash

IMAGE_TAG=tp-final-veiga:latest

# Server
SERVER_NAME=tp-final-server
SERVER_ALIAS=server
SERVER_PORT=8080
SERVER_PORTS_FLAGS="-p $SERVER_PORT:$SERVER_PORT"
COMMAND_SERVER="./build/server $SERVER_PORT"

# Client
CLIENT_NAME=tp-final-client
CLIENT_XSOCK=/tmp/.X11-unix
CLIENT_XAUTH=/tmp/.docker.xauth
CLIENT_PORTS_FLAGS="--link $SERVER_NAME:$SERVER_ALIAS"
CLIENT_DISPLAY_FLAGS="-v $CLIENT_XSOCK:$CLIENT_XSOCK -v $CLIENT_XAUTH:$CLIENT_XAUTH -e XAUTHORITY=$CLIENT_XAUTH"
COMMAND_CLIENT="./build/client $SERVER_ALIAS $SERVER_PORT"

print_green() {
  GREEN='\e[32m'
  NC='\e[0m'  
  PROMT="${GREEN} $1 ${NC}"
  echo -e $PROMT
}

remove_container() {
  CONTAINER_NAME="$1"
  print_green "Deleting server"
  sudo docker rm $CONTAINER_NAME > /dev/null
}

if [[ $1 == "build" ]]; then
  sudo docker build -t $IMAGE_TAG .
elif [[ $1 == "server" ]]; then
  print_green "Running server"
  sudo docker run -it $SERVER_PORTS_FLAGS --name $SERVER_NAME $IMAGE_TAG $COMMAND_SERVER
  remove_container $SERVER_NAME
elif [[ $1 == "client" ]]; then
  print_green "Running client"
  sudo docker run -it $CLIENT_DISPLAY_FLAGS --name $CLIENT_NAME $CLIENT_PORTS_FLAGS $IMAGE_TAG $COMMAND_CLIENT 
  remove_container $CLIENT_NAME
else
  echo "USAGE: ./run.sh (build|client|server)"
fi
