#!/bin/bash

LOG_DIR="/home/pi/shell/log/"
LOG_FILENAME="log_$(date +%Y%m%d%H).dat"

echo "$(date +%Y-%m-%d_%H:%M)" >> $LOG_DIR$LOG_FILENAME
#vcgencmd measure_temp >>  $LOG_DIR$LOG_FILENAME
#free >> $LOG_DIR$LOG_FILENAME
#/usr/bin/top -n 2 -b | grep Cpu >> $LOG_DIR$LOG_FILENAME
echo "---------------------------------1. uptime-------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
uptime은 현재 대기중인 프로세스가 얼마나 있는지를 나타내는 load average값을 확인하는 가장 쉬운 방법이다.
리눅스 시스템에서 이 값은 대기 중인 프로세스뿐만 아니라 disk I/O와 같은 I/O작업으로 block된 프로세스까지 포함되어 있다.
이를 통해서 얼마나 많은 리소스가 사용되고 있는지 확인할수 있지만, 정확하게 이해할 수는 없다.
위에 있는 3개의 숫자는 각각 1분, 5분, 15분에 load average 값이다.
이를 통해서 시간의 변화를 알 수 있는데, 예를들어서 장애가 발생했다는 소식을 듣고 해당 instance에 로그인 했을때 1분 동안의 값이 15분 값에 비해서 작다면 이는 장애가 발생하고선 내가 너무 뒤늦게 로그인했음을 알 수 있다.
위 예제에서는 1분 값이 약 30이고 15분 값이 19정도 되는것으로 볼때 최근에 상승한것을 알 수 있다. 여기서 숫자가 이 만큼 높은 것은 많은 의미를 갖고 있다.
아마도 CPU 수요에 문제가 있을거라 추측되지만 이 의미를 확인하기 위해선 뒤에 나오는 vmstat이나 mpstat같은 커맨드를 이용해서 확인할 수 있다.
END

   uptime >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------2. dmesg last 10line--------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
dmesg는 시스템 메세지를 확인할 수 있는 커맨드이다.
부팅시부터 시작해서 모든 커널메세지가 출력되기 때문에 tail을 이용해서 마지막 10줄만 출력한것이다.
이 메세지를 통해서 성능에 문제를 줄 수 있는 에러를 찾을 수 있는데 위의 예제에서는 oom-killer(out of memory)와 TCP request가 드랍된것을 알 수 있다.
END

   dmesg | tail >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------3.vmstat--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
virtual memory stat의 약자인 vmstat은 왠만한 환경에서 사용 가능한 툴이다.
1을 인자로 준 vmstat은 1초마다 정보를 보여준다. 첫번째 라인은 부팅된 뒤에 평균적인 값을 나타낸다.

확인해봐야할 항목

r: CPU에서 동작중인 프로세스의 숫자입니다.
      CPU 자원이 포화(saturation)가 발생하는지 확인할때에 좋은 값입니다.
      r 값이 CPU의 값보다 큰 경우에 포화되어 있다고 해석된다.
free: free memory를 kb단위로 나타냅니다.
      free memory가 너무 자리수가 많은 경우 free -m를 이용하면 조금더 편하게 확인할 수 있다.
si, so: swap-in과 swap-out에 대한 값입니다.
      0이 아니라면 현재 시스템에 메모리가 부족한것이다.
us, sy, id, wa, st: 모든 CPU의 평균적인 CPU time을 측정할 수 있다.
      각각 user time, 커널에서 사용되는 system time, idle, wait I/O 그리고 stolen time순이다(stolen time은 hypervisor가 가상 CPU를 서비스 하는 동안 실제 CPU를 차지한 시간을 이야기한다.).
END

   vmstat >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------4.mpstat--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
이 커멘드는 CPU time을 CPU 별로 측정할 수 있다.
이 방법을 통하면 각 CPU별로 불균형한 상태를 확인할 수 있는데, 한 CPU만 일하고 있는것은 application이 single thread로 동작한다는 이야기다.
END
   mpstat -P ALL >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------5.pidstat--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
pidstat은 process당 top명령을 수행하는것과 비슷하다.
다만 차이점은 스크린 전체에 표시하는것이 아니라 지속적으로 변화하는 상황을 띄워주기 떄문에 상황변화를 기록하기 좋다.
위 예제를 보면 두개의 java process의 CPU 사용량이 엄청나다.
%CPU 항목은 모든 CPU의 전체 사용량을 이야기한다.
따라서 1591%를 사용중인 java process들은 16CPU 가까이 사용중임을 나타내는것이다.
END
   pidstat >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------6.iostat--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
block device(HDD, SSD, …)가 어떻게 동작하는지 이해하기 좋은 툴이다.
확인해봐야할 항목
r/s, w/s rkB/s, wkB/s: read 요청과 write 요청, read kB/s, write kB/s를 나타낸다.
      어떤 요청이 가장 많이 들어오는지 확인해볼 수 있는 중요한 지표다. 성능 문제는 생각보다 과도한 요청때문에 발생하는 경우도 있기 때문이다.
await: I/O처리 평균 시간을 밀리초로 표현한 값이다.
      application한테는 I/O요청을 queue하고 서비스를 받는데 걸리는 시간이기 때문에 application이 이 시간동안 대기하게 된다.
      일반적인 장치의 요청 처리 시간보다 긴 경우에는 블럭장치 자체의 문제가 있거나 장치가 포화된 상태임을 알 수 있다.
END
   iostat -xz >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------7.free -m--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
확인해봐야할 항목
buffers: Block 장치 I/O의 buffer 캐시, 사용량
cached: 파일 시스템에서 사용되는 page cache의 양
      위 값들이 0에 가까워 지면 안된다.
      이는 곧 높은 Disk I/O가 발생하고 있음을 의미한다(iostat으로 확인 가능).
       위 예제는 각각 59MB, 541MB로 괜찮은 정도에 속한다.
““-/+ buffers/cache”는 사용중인 메모리와 여유 메모리의 양을 나타낸다.
      리눅스는 빠르게 다시 애플리케이션에 메모리가 할당될 수 있도록 캐시메모리를 사용한다.
      따라서 캐시 메모리도 여유 메모리에 포함되어 보여야한다. 캐시메모리 또한 여유메모리로 계산하지 않는 착각으로 인해서 linuxatemyram란 사이트까지 있다.
END
   free -m >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------8.sar -n DEV 1--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
이 툴을 사용하면 network throughput(Rx, Tx KB/s)을 측정할수 있다.
위 예제에서는 eth0의 수신량이 약 22Mbytes/s(21999.10rxkB/s)이다.
이는 176Mbits/s인데 한계인 1Gbit/s에 아직 많이 못 미치는 값이다.

위 값중 %ifutil은 nicstat로도 측정 가능한 네트워크 장치 사용률이다.
하지만 nicstat에서도 그렇듯 정확한 값을 가져오는게 어려워서 위 예제에서도 잘 작동하지 않는다.
END
   sar -n DEV 1 5 >> $LOG_DIR$LOG_FILENAME


echo "---------------------------------9.sar -n TCP,ETCP 1 5--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
이 값은 TCP 통신량을 요약해서 보여준다.
active/s: 로컬에서부터 요청한 초당 TCP 커넥션 수를 보여준다 (예를들어, connect()를 통한 연결).
passive/s: 원격으로부터 요청된 초당 TCP 커넥션 수를 보여준다 (예를들어, accept()를 통한 연결).
retrans/s: 초당 TCP 재연결 수를 보여준다.
      active와 passive 수를 보는것은 서버의 부하를 대략적으로 측정하는데에 편리하다.
      위 설명을 보면 active를 outbound passive를 inbound 연결로 판단할 수 있는데, 꼭 그렇지만은 않다. (예를들면 localhost에서 localhost로 연결같은 connection)
      retransmits은 네트워크나 서버의 이슈가 있음을 이야기한다.
      신뢰성이 떨어지는 네트워크 환경이나(공용인터넷), 서버가 처리할 수 있는 용량 이상의 커넥션이 붙어서 패킷이 드랍되는것을 이야기한다.
      위 예제에서는 초당 하나의 TCP 서버가 들어오는것을 알 수 있다.
END
   sar -n TCP,ETCP 1 5 >> $LOG_DIR$LOG_FILENAME

echo "---------------------------------10.top -n 1 -b--------------------------------------------- " >> $LOG_DIR$LOG_FILENAME
:<< 'END'
top 명령어는 위에서 체크해본 다양한 측정치를 쉽게 체크할 수 있다.
시스템 전반적으로 값을 확인하기 쉽다는 장점이 있다.
화면이 지속적으로 바뀌는 점 떄문에 패턴을 찾는것이 어렵다.
일시적으로 멈추는 현상을 잡기 위해서도 화면을 주기적으로 빠르게 멈춰주지 않으면 찾기 힘들다(Ctrl+S는 업데이트를 중지시키고, Ctrl+Q는 다시 시작시킨다), 그리고 화면이 지워져버린다.
END
   top -n 1 -b >> $LOG_DIR$LOG_FILENAME
echo "=======================================================================================" >> $LOG_DIR$LOG_FILENAME
echo "=======================================================================================" >> $LOG_DIR$LOG_FILENAME
