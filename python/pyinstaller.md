# python 파일을 실행파일로 만들기 (exe)

### 설치
```shell
	pip install pyinstaller # pyinstaller 설치
```

### 사용법
```shell
	pyinstaller --version # pyinstaller 버전 확인(이걸 실행하지 않으면 build 다 안된다.. 왜일까????)
	pyinstaller <python_file_name> # 실행파일로 build
```

### 옵션
```shell
	-F 최종출력으로 exe파일 하나만 생성
	-w 실행시 콘솔창이 출력되지 않게한다.
	-i exe파일 아이콘을 지정한다.
```

> this application failed to start because it could not find or load the qt platform plugin windows 에러 해결방법
```shell
	# exe 파일이 있는 디렉토리에 platforms 디렉토리 생성 후 , QT 가 설치된 디렉토리에서 qwindows.dll을 복사하면 된다.
````