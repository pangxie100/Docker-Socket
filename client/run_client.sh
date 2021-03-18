#!/bin/bash

docker build -t client_image .
docker volume rm client_persistent_storage
#docker volume create client_persistent_storage --driver local --opt type=btrfs --opt device=/Users/pangzeyu/Desktop/CS208/assignment/assignment2/client2
docker volume create client_persistent_storage
docker volume inspect client_persistent_storage
#ip_addr=$(docker inspect --format='{{.NetworkSettings.IPAddress}}' server_container)
#echo -e "FROM ubuntu:18.04\nCOPY . /client_storage\nWORKDIR /client_storage\nRUN apt-get update && \ \n    apt-get -y install gcc\nRUN gcc -o client client.c\nCMD [\"./client\",\"$ip_addr\"]" > Dockerfile

#docker run --rm --network=server_network --name client_container -p 8001:8000 -v client_persistent_storage:/client_storage -it client_image
#docker run --rm --network=server_network --name client_container -p 8001:8000 -it client_image

#docker run --rm --network=server_network --name client_container -p 8001:8000 -v /Users/pangzeyu/Desktop/CS208/assignment/assignment2/client2:/client_storage -it client_image
docker run --rm --network=server_network --name client_container -p 8001:8000 -v `pwd`:/client_storage -it client_image