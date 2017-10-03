import sys
from cx_Freeze import setup, Executable

setup( name="telnet",
    version="1.0",
    description = "실행 파일로 배포",
    author="lik",
    executables = [Executable("../run.py", base="Win32GUI")])
