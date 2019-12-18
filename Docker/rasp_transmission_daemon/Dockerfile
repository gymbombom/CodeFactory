FROM alpine:3.10.3

MAINTAINER gymbombom <gymbombom@kakao.com>

RUN apk update
RUN apk upgrade
RUN apk add transmission-daemon
RUN apk add transmission-cli

RUN mkdir -p /home/transmission/share
RUN chmod 777 /home/transmission
RUN chmod 777 /home/transmission/share


VOLUME ["/home/transmission/share"]

EXPOSE 9091