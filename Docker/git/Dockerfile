FROM centos:7

MAINTAINER Andamiro <dlfrb2002@gmail.com>

# update and upgrade
#RUN yum update -y
#RUN yum upgrade -y

#install
RUN yum install vim -y
RUN yum install git -y
RUN yum install openssh-server openssh-clients openssh-askpass -y
RUN yum install net-tools -y
#RUN apt-get install net-tools -y
#RUN apt-get install --fix-missing git -y

#korean language pack
#RUN apt-get install language-pack-ko -y
#RUN locale-gen ko_KR.UTF-8
#RUN echo "export LC_CTYPE=\"ko_KR.UTF-8\";" >> /etc/profile
#RUN source /etc/profile

#useradd
RUN useradd -ms /bin/bash  git

#create directory
RUN mkdir /home/git/repos
RUN chmod 777 /home/git/repos

USER git
RUN ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
USER root
RUN ssh-keygen -f /etc/ssh/ssh_host_rsa_key -N '' -t rsa
RUN ssh-keygen -f /etc/ssh/ssh_host_ecdsa_key -N '' -t ecdsa
RUN ssh-keygen -f /etc/ssh/ssh_host_ed25519_key -N '' -t ed25519

#cmd

#port 
EXPOSE 22

#volume
#VOLUME /home/git/repos
