# GDB 사용법
>보통은 GDB라고 부르는 GNU 디버거는 GNU 소프트웨어 시스템을 위한 기본 디버거이다. GDB는 다양한 유닉스 기반의 시스템에서 동작하는 이식성있는 디버거로, 에이다, C, C++, 포트란 등의 여러 프로그래밍 언어를 지원한다.

### 디버그할 프로세스 지정하기
```shell
    gdb - <pid> #해당 프로세스아이디로 디버그 모드 진입
    gdb attach <pid>  #해당 프로세스아이디로 디버그 모드 진입
    gdb <program name>
    gdb <program name><pid>
```

### 브레이크 포인트 설정
```shell
    (gdb)b <filename>:<line> 혹은 break <filename>:<line>
    ex)b test.c:90 #해당파일의 해당 라인에 브레이크 포인트 설정
    
    (gdb) b <function>
    ex) b GetNum 혹은 b Equip::GetNum #해당 function에 브레이크 포인트 설정
    ex) (gdb) break iter.c:6  -if i == 5 #특정조건일 경우 브레이크포인트 걸기 
    (GDB) break 10 if var == 0  #var 변수의 값이 0일때 10번 행에 설
    (gdb) delete all  #모든 브레이크 포인트 제거
    (GDB) info break #Break Point 출력
```

### 대략적인 사용법
```shell
    (gdb) r(run) #프로그램 재실행(segmentation fault 발생시 오류지점 확인가능)
    (gdb) cont(continue)  #프로그램 계속실행 (다음 Break Point가 나올때까지 실행)
    (gdb) return # 함수리턴하고 빠져나오기
    (gdb) return <value> #임의값으로 리턴하고 함수빠져나오기
    (gdb) finish #함수 마지막 지점으로 이동
    (gdb) u(until) #루프 빠져나오기
    (gdb) l(list) #현재 위치 기준으로 소스 10줄 출력
    (gdb)set listsize <size> #소스출력시 라인사이즈 지정
    (gdb)step(s) #소스 한줄씩 실행 함수를 포함하면 함수 안으로 진입
    (gdb) bt # Back Trace 프로그램 스택을 역으로 탐색
    
    (gdb) display <variables name> # 단계가 진행될때마다 변수 자동 디스플레이
    (gdb) undisplay <variables name> # display 취소
    (gdb)info locals #local 변수들 값 모두 출력
    (gdb)info variables #프로그램 내 모든변수 값 출력
    
    (gdb) q(quit) #종료

```

### DEFINE 된 MACRO print
> 사전에 -g3 옵션으로 컴파일 되어있어야한다.
```shell
    (gdb)info macro <MACRO NAME> 
    또는
    (gdb)macro expend <MACRO NAME> # DEFINE MACRO print
```

### Core 파일 분석 
```shell
    gdb  <program_filename> <core_filename>
    ex) gdb a.out ./core  
```


### gdb로 메모리 dump 뜨기
> ps -ef | grep <program_name\> #프로그램 이름으로 process id 확인
```shell
    $ ps -ef | grep a.out
    centos    2987  2357  0 17:12 pts/0    00:00:00 ./a.out
```
  
>pmap <pid\>  
> pmap 명령으로 비정상적으로 메모리가 늘어나는 메모리 영역을 확인
```shell
    $ pmap 2987
    0000000000400000      4K r-x-- a.out
	0000000000600000      4K r---- a.out
	0000000000601000      4K rw--- a.out
    00007f8be0e00000 150088K rw---   [ anon ]  # 이 영역이 비정상적으로 메모리가 늘어남.
    00007f8bea092000   1756K r-x-- libc-2.17.so
    00007f8bea249000   2044K ----- libc-2.17.so
    00007f8bea448000     16K r---- libc-2.17.so
    00007f8bea44c000      8K rw--- libc-2.17.so
    00007f8bea44e000     20K rw---   [ anon ]
    00007f8bea453000    128K r-x-- ld-2.17.so
    00007f8bea568000   1040K rw---   [ anon ]
    00007f8bea671000      8K rw---   [ anon ]
    00007f8bea673000      4K r---- ld-2.17.so
    00007f8bea674000      4K rw--- ld-2.17.so
    00007f8bea675000      4K rw---   [ anon ]
    00007ffe83edc000    132K rw---   [ stack ]
    00007ffe83f40000      8K r-x--   [ anon ]
    ffffffffff600000      4K r-x--   [ anon ]
    total           155276K
```
```shell
    $ pmap 2987
    2987:   ./a.out
    0000000000400000      4K r-x-- a.out
    0000000000600000      4K r---- a.out
    0000000000601000      4K rw--- a.out
    00007f8bc3c30000 627080K rw---   [ anon ] # 이 영역이 비정상적으로 메모리가 늘어남.
    00007f8bea092000   1756K r-x-- libc-2.17.so
    00007f8bea249000   2044K ----- libc-2.17.so
    00007f8bea448000     16K r---- libc-2.17.so
    00007f8bea44c000      8K rw--- libc-2.17.so
    00007f8bea44e000     20K rw---   [ anon ]
    00007f8bea453000    128K r-x-- ld-2.17.so
    00007f8bea568000   1040K rw---   [ anon ]
    00007f8bea671000      8K rw---   [ anon ]
    00007f8bea673000      4K r---- ld-2.17.so
    00007f8bea674000      4K rw--- ld-2.17.so
    00007f8bea675000      4K rw---   [ anon ]
    00007ffe83edc000    132K rw---   [ stack ]
    00007ffe83f40000      8K r-x--   [ anon ]
    fffffffff600000      4K r-x--   [ anon ]
    total           632268K
```
> cat /proc/<pid\>/smaps  
>비 정상적으로 늘어난  Heap 영역확인

```shell
    $ cat /proc/2987//smaps
    7f8bb1207000-7f8bea092000 rw-p 00000000 00:00 0
    Size:             932396 kB
    Rss:              603396 kB
    Pss:              603396 kB
    Shared_Clean:          0 kB
    Shared_Dirty:          0 kB
    Private_Clean:         0 kB
    Private_Dirty:    603396 kB
    Referenced:       603372 kB
    Anonymous:        603396 kB
    AnonHugePages:    602112 kB
    Swap:                  0 kB
    KernelPageSize:        4 kB
    MMUPageSize:           4 kB
    Locked:                0 kB
    VmFlags: rd wr mr mw me ac sd
```
>gdb -p <pid\> 로 해당 프로세스 진입 후,  
>dump memory <dump_file_path> <memory_address> 명령으로 덤프파일 생성

```shell
    $ gdb -p 2987
    GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-94.el7
    Copyright (C) 2013 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "x86_64-redhat-linux-gnu".
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>.
    Attaching to process 2987
    Reading symbols from /home/centos/gdb_dump/a.out...(no debugging symbols found)...done.
    Reading symbols from /lib64/libc.so.6...(no debugging symbols found)...done.
    Loaded symbols for /lib64/libc.so.6
    Reading symbols from /lib64/ld-linux-x86-64.so.2...(no debugging symbols found)...done.
    Loaded symbols for /lib64/ld-linux-x86-64.so.2
    0x00007f8bea150650 in __nanosleep_nocancel () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install glibc-2.17-157.el7_3.5.x86_64
    (gdb)
```

```shell
    (gdb) dump memory /home/centos/dump 0x7f8bb1207000 0x7f8bea092000
```

>strings <dump_file_name\>  
>해당 메모리 영역에 기록된 내용을 확인

```shell
    $ strings ./dump
    962085
    961909
    961734
    961535
    961355
    961189
    961000
    960810
    960654
    960474
    960286
    960115
    959947
```
