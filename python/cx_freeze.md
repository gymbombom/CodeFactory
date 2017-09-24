# cx freeze 설치 및 사용법

```shell
	$ pip install cx_Freeze #설치
```

### 소스작성
> setup.py
```python
import sys
from cx_Freeze import setup, Executable

setup( name="Demo",
    version="1.0",
    description = "실행 파일로 배포",
    author="jdkim",
    executables = [Executable("hello.py", base="Win32GUI")])
```

### 빌드
```shell
	$ Python setup.py build # exe 파일로 Build
```
