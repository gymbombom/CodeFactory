FROM alpine:3.10.3
MAINTAINER gymbombom <gymbombom@kakao.com>

RUN apk update
RUN apk upgrade

RUN apk add postgresql


RUN adduser -D psql

RUN mkdir -p /run/postgresql
RUN chmod 777 /run/postgresql

RUN mkdir -p /home/psql/share
RUN chmod 777 /home/psql/share


VOLUME ["/home/psql/share"]

EXPOSE 5432