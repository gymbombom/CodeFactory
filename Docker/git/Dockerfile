FROM alpine:3.10.3
MAINTAINER gymbombom <gymbombom@kakao.com>

RUN apk update
RUN apk upgrade

RUN apk add git
RUN apk add openssh-server

RUN mkdir -p /home/git/share
RUN chmod 777 /home/git
RUN chmod 777 /home/git/share

RUN ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa

RUN ssh-keygen -f /etc/ssh/ssh_host_rsa_key -N '' -t rsa
RUN ssh-keygen -f /etc/ssh/ssh_host_ecdsa_key -N '' -t ecdsa
RUN ssh-keygen -f /etc/ssh/ssh_host_ed25519_key -N '' -t ed25519


VOLUME ["/home/git/share"]

EXPOSE 22
