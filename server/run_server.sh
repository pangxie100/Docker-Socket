docker build -t server_image .
docker volume create server_persistent_storage
docker volume inspect server_persistent_storage
docker network rm server_network
docker network create server_network
docker run --rm --network=server_network --name server_container_and_dns_name -p 8000:8000 -v server_persistent_storage:/server_storage -it server_image
