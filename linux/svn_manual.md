# 1.설치과정
### 공유기 포트포워딩 설정(공유기를 사용하지 않을경우 skip)
##### svn 기본 포트는 3690포트
![](./포트포워딩.png)	

### iptables 방화벽 정책 추가

##### iptables파일을 열고,
```shell
   [root@barosvr01 ~]# vi /etc/sysconfig/iptables
```
##### 3360포트에 대한 방화벽 정책을 추가

```
-A INPUT -m state --state NEW -m tcp -p tcp --dport 3690 -j ACCEPT
```

##### iptables 서비스 리스타트
```shell
 [root@barosvr01 ~]# service iptables restart
```

### 패키지 매니저를 통해 svn 설치	
```shell
 [root@barosvr01 ~]# yum install subversion
 ... (생략)
=============================================================================================
 Package               Arch              Version                       Repository       Size
=============================================================================================
Installing:
 subversion            x86_64            1.6.11-10.el6_5               base            2.3 M
Installing for dependencies:
 neon                  x86_64            0.29.3-3.el6_4                base            119 k
 pakchois              x86_64            0.4-3.2.el6                   base             21 k

Transaction Summary
=============================================================================================
Install       3 Package(s)

Total download size: 2.4 M
Installed size: 12 M
Is this ok [y/N]: y
... (생략)
Installed:
  subversion.x86_64 0:1.6.11-10.el6_5                                                        

Dependency Installed:
  neon.x86_64 0:0.29.3-3.el6_4                 pakchois.x86_64 0:0.4-3.2.el6                

Complete!
```

### 설치확인
```shell
[root@barosvr01 ~]# svn
Type 'svn help' for usage.
```

```shell
[root@barosvr01 ~]# svnserve
svnserve is stopped
```

### repository 생성
##### 저장소 최상위로 사용할 디렉토리를 만든다.
```shell
[root@barosvr01 ~]# mkdir /home/svn/repos
```

##### 저장소 최상위 디렉토리로 이동후, 저장소를 생성한다.
>[root@barosvr01 ~]# cd /home/svn/repos
>[root@barosvr01 repos]#  svnadmin create --fs-type fsfs 저장소명


ex)
```shell
	[root@barosvr01 ~]# cd /home/svn/repos
	[root@barosvr01 repos]#  svnadmin create --fs-type fsfs test

```


### 저장소 설정 변경
#####기존 저장소 설정파일 백업
```shell
[root@barosvr01 ~]# mv /home/svn/repos/test/conf/svnserve.conf /home/svn/repos/test/conf/svnserve.conf_bk
```
##### 새 설정파일 생성
```shell
[root@barosvr01 ~]# vi /home/svn/repos/test/conf/svnserve.conf
```

##### svnserve.conf에 아래내용 추가
>[general]  
>anon-access = none  
>auth-access = write  
>password-db = passwd   
>authz-db = authz


###계정설정
##### svn은 os계정을 사용하지 않고 svn자체계정을 사용한다.
##### 기본 계정설정파일 백업
```shell
	[root@barosvr01 ~]# mv /home/svn/repos/test/conf/passwd /home/svn/repos/test/conf/passwd_bk
```

##### 신규 passwd파일 생성
```shell
	[root@barosvr01 ~]# vi /home/svn/repos/test/conf/passwd
```
#####passwd 파일에 아래내용 추가
>[users]  
>test = test

###svn 서버 기동
#####repository 최상위 디렉토리로 설정하여 기동한다.
```shell
svnserve -d -r /home/svn/repos
```   
### service 명령어로 서버 기동하기 [옵션]
```shell
[root@barosvr01 ~]# vi /etc/sysconfig/svnserve
```
##### 아래내용 추가(경로는 repository 최상위 경로를 적음)
>OPTIONS="--threads --root /home/svn/repos"
#####service svnserve start/stop 명령으로 svn서버를 기동/중지 할수 있다.


# 2.환경구성내용

# 3. 기동 및 종료

# 4.repository 구성내용

# 5. user

