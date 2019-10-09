# docker 사용법

### 설치
```shell
sudo wget -qO- https://get.docker.com/ | sh 
# Docker는 리눅스 배포판 종류를 자동으로 인식하여 Docker 패키지를 설치해주는 스크립트를 제공
# 스크립트로 Docker를 설치하면  hello-world 이미지도 자동으로 설치됨.
# hello-world 이미지가 필요없다면 삭제해야함.
#$ sudo docker rm `sudo docker ps -aq`
#$ sudo docker rmi hello-world 
```
### 사용법
```shell
$ docker run -it -p 8822:22 -v /home/pi/git:/home/git/repos --name git rasp_git:1 #run

#docker container를 image로 만들어줌.
$ docker commit <CONTAINER NAME> <REPOSITORY:TAG> 
  ex) docker commit setting hadoop2:4 
$ docker cp <local_path> <container_path> #docker container로 파일 복사
```

### docker network 구성
```shell
$ docker network create --subnet 10.0.3.0/24 simple-network #network 생성
$ docker run -dit --privileged  --name con1 --network hes-network  --ip 10.0.3.2 --add-host=con1:10.0.3.2 --add-host=con2:10.0.3.3  --add-host=con3:10.0.3.4  --add-host=con4:10.0.3.5 --add-host=con5:10.0.3.6 hes2:3 /bin/bash; 
```

```shell
brew cask install docker #맥북은 이렇게 설치
```
