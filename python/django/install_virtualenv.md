# virtualenv 설치

### virtualenv 설치
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
    # 다운받은 소스코드를 임시 디렉토리에 저장하고 해당 디렉토리에서 아래와 같이 실행
    $ <env_dir>/venv/bin/python setup.py install
```