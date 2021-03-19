docker container rm -f server_container_and_dns_name
docker build -t server_image .
docker volume rm server_persistent_storage
docker volume create server_persistent_storage
docker volume inspect server_persistent_storage
docker run --rm --name server_container_and_dns_name -v server_persistent_storage:/server_storage -it server_image
