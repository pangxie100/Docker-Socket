#FROM gcc:4.9
FROM ubuntu:18.04
COPY . /server_storage
WORKDIR /server_storage
RUN md5sum mydata.txt
RUN apt-get update && \ 
    apt-get -y install gcc
RUN gcc -o server server.c
CMD ["./server"]

