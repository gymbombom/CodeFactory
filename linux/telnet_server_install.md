# centos telnet server 설치

```shell
	$ sudo yum install telnet-server # telnet 서버모듈 설치
	$ vi /etc/xinetd.d/telnet
	# disable = yes"를 "disable = no" 로 설정

	service xinetd restart $ xinetd 리스타트
```


### root 사용자 telnet 접속 가능하게 설정
```shell
$ vi /etc/securett

pts/0
pts/1
pts/2
pts/3
pts/4
pts/5
pts/6
pts/7
pts/8
pts/9
#위내용 뒷줄에 삽입
```