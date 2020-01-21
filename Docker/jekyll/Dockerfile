FROM ubuntu:19.10
MAINTAINER gymbombom <gymbombom@kakao.com>


RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install ruby -y
RUN apt-get install ruby-dev -y
RUN apt-get install -y bundler

RUN gem install jekyll

RUN apt-get install git -y
RUN apt-get install vim -y

RUN mkdir -p /home/jekyll/share
RUN chmod 777 /home/jekyll
RUN chmod 777 /home/jekyll/share
