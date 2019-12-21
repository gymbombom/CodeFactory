FROM alpine:3.10.3

MAINTAINER gymbombom <gymbombom@kakao.com>

RUN apk update
RUN apk upgrade
RUN apk add vsftpd

RUN mkdir -p /home/vsftpd/share
RUN mkdir -p /home/vsftpd/share_data
RUN chmod 777 /home/vsftpd
RUN chmod 777 /home/vsftpd/share
RUN chmod 777 /home/vsftpd/share_data


VOLUME ["/home/vsftpd/share"]
VOLUME ["/home/vsftpd/share_data"]


EXPOSE 20
EXPOSE 21

EXPOSE 10090
EXPOSE 10091
EXPOSE 10092
EXPOSE 10093
EXPOSE 10094
EXPOSE 10095
EXPOSE 10096
EXPOSE 10097
EXPOSE 10098
EXPOSE 10099
EXPOSE 10100
