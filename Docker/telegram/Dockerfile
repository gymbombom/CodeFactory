FROM centos:7
MAINTAINER gymbombom <gymbombom@kakao.com>

RUN yum update -y
RUN yum upgrade -y
RUN yum install gcc -y
RUN yum install glibc-devel -y
RUN yum install openssl-devel -y
RUN yum install sqlite-devel -y
RUN yum install make -y
RUN yum install libffi-devel -y

RUN mkdir -p /home/telegram/share
RUN chmod 777 /home/telegram
RUN chmod 777 /home/telegram/share


WORKDIR /home/telegram
RUN curl -O https://www.python.org/ftp/python/3.8.2/Python-3.8.2.tgz
RUN tar -xvzf ./Python-3.8.2.tgz

WORKDIR /home/telegram/Python-3.8.2
RUN ./configure
RUN make
RUN make install



VOLUME ["/home/telegram/share"]

EXPOSE 22
