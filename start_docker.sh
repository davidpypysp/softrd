sudo docker run -it \
    --network='host' \
    -v $(pwd):/softrd \
    davidpy1992/softrd-ubuntu \
    bash