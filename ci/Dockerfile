FROM ubuntu:22.04

RUN apt update && apt install -y doxygen make

ADD cache/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 /usr/share/

ENV PATH=/usr/share/gcc-arm-none-eabi-9-2020-q2-update/bin/:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
