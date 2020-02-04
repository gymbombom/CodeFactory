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

#exec 옵션은 외부에서 container 내부로 명령을 실행할때 사용하는 옵션이나, 아래와 같이 사용하게 되면 docker 내부 container에 접속하여 command하는 것과 같이 실행됨.
$ docker exec -it git /bin/bash;
```

### docker network 구성
```shell
$ docker network create --subnet 10.0.3.0/24 simple-network #network 생성
$ docker run -dit --privileged  --name con1 --network hes-network  --ip 10.0.3.2 --add-host=con1:10.0.3.2 --add-host=con2:10.0.3.3  --add-host=con3:10.0.3.4  --add-host=con4:10.0.3.5 --add-host=con5:10.0.3.6 hes2:3 /bin/bash; 
```

```shell
brew cask install docker #맥북은 이렇게 설치
```

```shell
#Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Get http://%2Fvar%2Frun%2Fdocker.sock/v1.40/images/json: dial unix /var/run/docker.sock: connect: permission denied 에러 발생시 

$ sudo usermod -a -G docker $USER
$ sudo service docker restart
```

### dockerhub 에 이미지 업로드
```shell
$ docker login;
$ docker push snowdeer/hello-nodejs:v1;

```
