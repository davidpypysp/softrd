IMAGE_NAME='davidpy1992/softrd-dev'
CID=$(docker ps -q -f ancestor=davidpy1992/softrd-dev)

if [ ! "${CID}" ]; then
    echo "Start container"
    docker-compose run --service-ports softrd-dev bash
else
    echo "Running container id is " $CID
    docker exec -it ${CID} bash
fi