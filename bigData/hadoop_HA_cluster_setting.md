# hadoop HA(HighAvailability) setting

### hadoop HA 구성예(clustering 까지 완료상태에서 진행해야함.)
> hadoop1 : namenode(active), datanode  
> hadoop2 : namenode(standby, datanode  
> hadoop3 : datanode

### Zookeeper 설치
> zookeeper 3.4.9 버전 설치

```shell
cp $ZOOKEEPER_HOME/conf/zoo_sample.cfg $ZOOKEEPER_HOME/conf/zoo.cfg
```

```shell
# vi zoo.cfg 설정

dataDir=dataDir=/home/hes/data/zookeeper #myid 파일이 위치한 data Dir 설정
maxClientCnxns=0 #0으로 설정하면 client 제한이 없어짐.
maxSessionTimeout=180000 #session Timeout 설정
server.1=hadoop1:2888:3888
server.2=hadoop2:2888:3888
server.3=hadoop3:2888:3888
```

### data Directory 생성 , myid 생성
```shell
mkdir $ZOOKEEPER_HOME/data # directory 생성
echo 1 > $ZOOKEEPER_HOME/data/myid # myid 파일추가
```

> 현재 zookeeper 설정 압축하고 2,3번 서버에도 scp 로 보냄.  
> hadoop2, hadoop3번 myid 파일 수정

```shell
[hadoop2]# echo 2 > $ZOOKEEPER_HOME/data/myid
[hadoop3]# echo 3 > $ZOOKEEPER_HOME/data/myid
```

### 1 ~ 3번에서 zookeeper 실행
```shell
[hadoop1]# $ZOOKEEPER_HOME/bin/zkServer.sh start
[hadoop2]# $ZOOKEEPER_HOME/bin/zkServer.sh start
[hadoop3]# $ZOOKEEPER_HOME/bin/zkServer.sh start
```

### 1~3 번 서버 모두에서 QuorumPeerMain 프로세스가 떠있으면 정상
```shell
[hadoop1]# jps
        1665 QuorumPeerMain

[hadoop1]# $ZOOKEEPER_HOME/bin/zkServer.sh status
ZooKeeper JMX enabled by default
Using config: /home/hes/zookeeper-3.4.9/bin/../conf/zoo.cfg
Mode: follower
# mode 가 leader 아니면 follower 가 나온다.
```
