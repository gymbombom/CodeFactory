#docker 사용법

###설치
```shell
sudo wget -qO- https://get.docker.com/ | sh 
# Docker는 리눅스 배포판 종류를 자동으로 인식하여 Docker 패키지를 설치해주는 스크립트를 제공
# 스크립트로 Docker를 설치하면  hello-world 이미지도 자동으로 설치됨.
# hello-world 이미지가 필요없다면 삭제해야함.
#$ sudo docker rm `sudo docker ps -aq`
#$ sudo docker rmi hello-world 
```

```shell
brew cask install docker #맥북은 이렇게 설치
```