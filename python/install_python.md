#python 설치방법
> centos 6.9 에서 python 설치
> 파이썬 설치 , python 설치, python 컴파일

### 1. gcc, glibc-devel, openssl-devel 설치
```shell
sudo yum install gcc -y #gcc 설치
sudo yum install glibc-devel.x86_64 -y #glibc-devel 설치
sudo yum install openssl-devel.x86_64 -y #openssl-devel 설치
sudo yum install sqlite-devel.x86_64 -y # sqlite-devel 설치
``` 


### 2.python source code 다운로드
```shell
#stable version 확인은 python 공식사이트 documentation 에서 확인
curl -O https://www.python.org/ftp/python/3.6.2/Python-3.6.2.tgz
tar -xvzf  Python-3.6.2.tgz # 압축해제
```

### 3.python 컴파일
```shell
cd Python-3.6.2
#./configure --enable-optimizations
./configure
make
sudo make install
```

### 4.python 설치확인
```shell
python --version #python 버전확인(python3일경우  python3 --version)
```

### 5. 기타
```shell
#sudo 로 pyython 을 사용할 경우 /usr/bin/python3 로 symbolic link 를 걸어줘야 한다.
sudo ln -s /usr/local/bin/python3 /usr/bin/python3 # python3 symbolic link 
sudo ln -s /usr/local/bin/pip3 /usr/bin/pip3 # pip3 symbolic link 생성
```
