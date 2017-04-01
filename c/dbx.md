# dbx 사용법
> C, C++ 환경에서 디버그하기 위한 환경제공
>> dbx로 디버그를 하기 위해서는 -g 옵션으로 컴파일되어 있어야한다.

###참고사이트
[https://kldp.org/node/71806](https://kldp.org/node/71806)


###디버그할 프로세스 지정하기
``` shell
dbx - <pid>  #해당 프로세스 디버그 모드로 진입
```

###브레이크 포인트 설정
```shell
(dbx) stop at <filename>:<line> 
ex)b test.c:90 #해당파일의 해당 라인에 브레이크 포인트 설정

(dbx) stop in <function>
ex) stop in GetNum 혹은 stop in Equip::GetNum  #해당 function에 브레이크 포인트 설정
ex) (dbx) stop at iter.c:6  -if i == 5  #특정조건일 경우 브레이크포인트 걸기
ex) (dbx) delete all  #모든 브레이크 포인트 제거
```

###브레이크 포인트까지 실행후 기다리기
```shell
(dbx) cont 
또는
(dbx)continue. #다음 브레이크포인트까지 기다린다.
```

###대략적인 사용법
```shell
(dbx) n #다음라인으로 이동
(dbx) n <count>  #count 횟수만큼 다음라인으로 이동
(dbx) s  #함수안으로 진입
(dbx) where  #현재위치 표시
(dbx) p <variable name>  #프린트
(dbx) until  #반복문 빠져나옴
(dbx) return  #진입한 함수에서 바로 리턴으로 빠져나옴
```
