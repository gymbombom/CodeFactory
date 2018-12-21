FROM ubuntu:18.04

MAINTAINER Andamiro <dlfrb2002@gmail.com>

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install vsftpd -y
RUN apt-get install vim -y
RUN apt-get install net-tools -y
#RUN apt-get install language-pack-ko -y

# RUN locale-gen ko_KR.UTF-8
#RUN echo "export LC_CTYPE=\"ko_KR.UTF-8\";" >> /etc/profile
# RUN source /etc/profile

RUN cp /etc/vsftpd.conf /etc/vsftpd.conf_bk

#RUN echo "pasv_enable=YES" >> /etc/vsftpd.conf
#RUN echo "pasv_min_port=10091" >> /etc/vsftpd.conf
#RUN echo "pasv_max_port=10100" >> /etc/vsftpd.conf
#RUN echo "write_enable=YES" >> /etc/vsftpd.conf


RUN useradd -ms /bin/bash vsftpd

#CMD chmod  -R 777 /home/share/share; service vsftpd restart;
EXPOSE 21
EXPOSE 22
