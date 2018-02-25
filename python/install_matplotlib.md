# matplotlib 설치

### pip로 설치
```shell
    (virtualenv)$ pip install matplotlib
```

### 아래의 에러 발생시  
```python
RuntimeError: Python is not installed as a framework. The Mac OS X backend will not be able to function correctly if Python is not installed as a framework. See the Python documentation for more information on installing Python as a framework on Mac OS X. Please either reinstall Python as a framework, or try one of the other backends. If you are using (Ana)Conda please install python.app and replace the use of 'python' with 'pythonw'. See 'Working with Matplotlib on OSX' in the Matplotlib FAQ for more information.
```

### script 에서 
```python
    import matplotlib
    matplotlib.use('TkAgg')
    import matplotlib.pyplot as plt
```

### virtualenv bash 에서
```shell
    (virtualenv)$ echo "backend: TkAgg" >> ~/.matplotlib/matplotlibrc
```

### 다른 backend 확인
<https://matplotlib.org/faq/usage_faq.html>
