# Docker-Socket
This is a socket program which runs in docker container. It builds connection between two containers. 

"server" and "client" run in both MacOS and Linux. 
"server_linux" and "client_linux" only run in Linux. 

"server_linux" and "client_linux" can run in MacOS. However, you cannot find the volume by using command "cd /var/lib/docker/volumes/client_persistent_storage/_data" to check the copied file "mydata.txt". The reason is that the docker in MacOS is a VM. So, this path is not a real path.  

## Compile and run
Install Docker Engine on Ubuntu:
```
$ sudo apt-get remove docker docker-engine docker.io containerd runc
$ sudo apt-get update
$ sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg \
    lsb-release
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
$ echo \
  "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
$ sudo apt-get update
$ sudo apt-get install docker-ce docker-ce-cli containerd.io
```
If in the first time, you fail to install parts like "docker-ce", try the whole process again. 

Test:
```
$ sudo docker run hello-world
```
Reference Website: https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository

You should run server first.
Server part
```
$ sudo -s
$ chmod +x run_server.sh
$ ./run_server.sh
```
Client part
```
$ sudo -s
$ chmod +x run_client.sh
$ ./run_client.sh
```

For more details, please see the report.
