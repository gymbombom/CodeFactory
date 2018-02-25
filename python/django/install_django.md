#Django 설치
>\#django , \#Django, \#장고설치, \#Django설치, \#django 설치 \#virtualenv


### 1.Django 설치
```shell
    pip3 install django==1.11.4 # django 설치(1.11.4 버젼)
    # pip3 install --upgrade django==1.11.4 
    # pip3 install --upgrade django
    python3 -m django --version # django version 확인
```

### 2. virtualenv 설치
> 격리된 python 개발 환경을 만드는 tool
```shell
    $ sudo pip3 install virtualenv #virtualenv 설치
```

### 3. virtualenv 기본 사용법
```shell
     $ virtualenv <env_dir> # 가상환경 생성
     $ virtualenv --python=python3.3 <env_dir> # python 버전을 선택하여 가상환경 생성
	 or
	 $ virtualenv --python=/home/django/python/bin/python3.6 <env_dir>
	 $ source $<env_dir>/bin/activate #가상환경으로 진입
	 (venv) deactivate # 가상환경 빠져나오기
```

```shell
    $ . <env_dir>/bin/activate #가상환경 활성화 가상환경을 활성화 하면 prompt에 (venv)가 뜬다.
```

### 다른 컴퓨터에 동일한 개발환경 구축
```shell
    (venv)$ pip3 freeze > package.txt #가상환경 안에서 해당명령 실행하면 설치된 package와 버전이 텍스트에 기록된다.
    $ pip3 install -r package.txt # 파일을 읽어서 다른 컴퓨터에 동일환경으로 설치
```

### 다운 받은 파이썬 소스코드를  virtualenv에 설치
```shell
    #다운받은 소스코드를 임시 디렉토리에 저장하고 해당 디렉토리에서 아래와 같이 실행
    $ <env_dir>/venv/bin/python setup.py install
```

### 프로젝트 생성
```shell
    $ django-admin startproject <project_name> # project 생성
```

### APP 생성
```shell
    $ ./manage.py startapp comunity #app 생성
```

### miftate 활성화
> 마이그레이션은 Django가 데이터베이스 스키마에 모델 변경 (필드 추가, 모델 삭제 등)을 전파하는 방식입니다.
```shell
    $ ./managy.py migrate # 마이그레이션 스키마 생성
```

### super user 생성
```shell
    $ ./managy.py createsuperuser #super user 생성
```

### runserver
```shell
    ./manage.py runserver # 127.0.0.1:8000 포트로 runserver
    ./manage.py runserver 1.2.3.4:8000 #1.2.3.4:8000 포트로 runserver
    ./manage.py runserver 7000 #127.0.0.1 7000 포트로 runserver
    ./manage.py runserver -6 # ipv6로 runserver
```


