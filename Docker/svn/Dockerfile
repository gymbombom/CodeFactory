FROM ubuntu:18.04

MAINTAINER Andamiro <dlfrb2002@gmail.com>

RUN apt-get update -y
RUN apt-get upgrade -y


RUN apt-get install vim -y
RUN apt-get install net-tools -y
RUN apt-get install language-pack-ko -y
RUN apt-get install subversion -y


RUN useradd -ms /bin/bash svn

EXPOSE 3690
