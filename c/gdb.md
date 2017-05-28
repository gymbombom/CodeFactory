#GDB 사용법
>보통은 GDB라고 부르는 GNU 디버거는 GNU 소프트웨어 시스템을 위한 기본 디버거이다. GDB는 다양한 유닉스 기반의 시스템에서 동작하는 이식성있는 디버거로, 에이다, C, C++, 포트란 등의 여러 프로그래밍 언어를 지원한다.

###디버그할 프로세스 지정하기
```shell
gdb - <pid> #해당 프로세스아이디로 디버그 모드 진입
gdb attach <pid>  #해당 프로세스아이디로 디버그 모드 진입
gdb <program name>
```

###브레이크 포인트 설정
```shell
(gdb)b <filename>:<line> 혹은 break <filename>:<line>
ex)b test.c:90 #해당파일의 해당 라인에 브레이크 포인트 설정

(gdb) b <function>
ex) b GetNum 혹은 b Equip::GetNum #해당 function에 브레이크 포인트 설정
ex) (gdb) break iter.c:6  -if i == 5 #특정조건일 경우 브레이크포인트 걸기 
ex) (gdb) delete all  #모든 브레이크 포인트 제거
```

###대략적인 사용법
```shell
(gdb) continue  #프로그램 계속실행
(gdb) return # 함수리턴하고 빠져나오기
(gdb) return <value> #임의값으로 리턴하고 함수빠져나오기
(gdb) finish #함수 마지막 지점으로 이동
(gdb) u(until) #루프 빠져나오기
```

###DEFINE 된 MACRO print
> 사전에 -g3 옵션으로 컴파일 되어있어야한다.
```shell
(gdb)info macro <MACRO NAME> 
또는
(gdb)macro expend <MACRO NAME> # DEFINE MACRO print
```

###Core 파일 분석 
```shell
    gdb  program_filename core_filename 
    ex) gdb a.out ./core  
```