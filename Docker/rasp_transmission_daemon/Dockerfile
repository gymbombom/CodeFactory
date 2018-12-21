FROM ubuntu:18.04

MAINTAINER Andamiro <dlfrb2002@gmail.com>

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install transmission-daemon -y
RUN apt-get install vim -y
RUN apt-get install net-tools -y

#RUN apt-get install language-pack-ko -y

# RUN locale-gen ko_KR.UTF-8
#RUN echo "export LC_CTYPE=\"ko_KR.UTF-8\";" >> /etc/profile
# RUN source /etc/profile

#config File Backup
RUN mv /etc/transmission-daemon/settings.json /etc/transmission-daemon/settings.json_bk

#user Add
RUN useradd -ms /bin/bash transmission

#direcoty Add
RUN mkdir /home/transmission/share
RUN chmod -R 777 /home/transmission/share

RUN mkdir /home/transmission/share/downloads
RUN chmod -R 777 /home/transmission/share/downloads

RUN mkdir /home/transmission/share/seeds
RUN chmod -R 777 /home/transmission/share/seeds

RUN mkdir /home/transmission/shell
RUN chmod -R 777 /home/transmission/shell

#confFile CP
ADD AutoDelete.sh /home/transmission/shell/
RUN chmod 755 /home/transmission/shell/AutoDelete.sh

ADD settings.json /etc/transmission-daemon/
RUN chmod 755 /etc/transmission-daemon/settings.json



EXPOSE 9091
#EXPOSE 51413
