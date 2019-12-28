FROM alpine:3.10.3

MAINTAINER gymbombom <gymbombom@kakao.com>

RUN apk update
RUN apk upgrade

RUN apk add subversion

RUN mkdir -p /home/svn/share
RUN chmod 777 /home/svn
RUN chmod 777 /home/svn/share


EXPOSE 3690

VOLUME ["/home/svn/share"]