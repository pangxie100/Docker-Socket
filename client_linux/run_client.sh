#!/bin/bash

docker volume rm client_persistent_storage
docker volume create client_persistent_storage
docker volume inspect client_persistent_storage
ip_addr=$(docker inspect --format='{{.NetworkSettings.IPAddress}}' server_container_and_dns_name)
echo -e "FROM ubuntu:18.04\nCOPY . /client_storage\nWORKDIR /client_storage\nRUN apt-get update && \ \n    apt-get -y install gcc\nRUN gcc -o client client.c\nEXPOSE 8000\nCMD [\"./client\",\"$ip_addr\"]" > Dockerfile
docker build -t client_image .
docker run --rm --name client_container -v client_persistent_storage:/client_storage -it client_image
