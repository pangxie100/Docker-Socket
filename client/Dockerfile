FROM ubuntu:18.04
COPY . /client_app
WORKDIR /client_app
RUN apt-get update && \ 
    apt-get -y install gcc
RUN gcc -o client client.c
CMD ["./client"]
