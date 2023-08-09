FROM gcc

RUN apt -y update && apt -y install git

RUN apt -y install gcc make git doxygen

WORKDIR /mnt
