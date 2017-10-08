# python 설치방법
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

### python 경로 변경하여 설치
```shell
    curl -O https://www.python.org/ftp/python/3.4.4/Python-3.4.4.tgz #source 파일 다운로드
    tar -xvzf Python-3.4.4.tgz #source 파일 압축해제
    cd Python-3.4.4 # 압축해제한 디렉토리로 이동
    ./configure --prefix=/home/lik/python --enable-shared  # python binary 설치 위치를 /home/lik/python 로 설정
    make  # make
    make install # make install

    echo "/home/lik/python/bin" >> /etc/ld.so.conf.d/python.conf/python.conf #kernel 2.6 부터 사용가능.... 해당 파일에 shared library 위치 설정(시스템 전반에 영향을 미침)
    #또는
    echo "/home/lik/python/bin" >> /etc/ld.so.conf #shared Library 위치 설정 (시스템 전체에 영향을 미침)
    #또는
    echo "export LD_LIBRARY_PATH=/home/lik/python/lib" >> /home/lik/.bashrc # LD_LIBRARY_PATH export

    (옵션)
    echo "export PYTHON_HOME='/home/lik/python'" >> /home/lik/.bashrc # PYTHON_HOME export
    echo "export PATH=$PYTHON_HOME/bin:$PATH" >> /home/lik/.bashrc # PATH 에 추가
    source .//home/lik/.bashrc


```