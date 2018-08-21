# hadoop HA(HighAvailability) setting  
[참고자료](https://hadoop.apache.org/docs/r2.6.0/hadoop-project-dist/hadoop-hdfs/HDFSHighAvailabilityWithQJM.html)  
[NameNode HA(HighAvailability)](http://bloodguy.tistory.com/entry/Hadoop-NameNode-HAHighAvailability)

### hadoop HA 구성예(clustering 까지 완료상태에서 진행해야함.)
> hadoop1 : namenode(active), datanode  
> hadoop2 : namenode(standby), datanode  
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
# zookeeper가 설치된 모든 서버에서 mode 가 leader 아니면 follower 가 나온다.
```

### Hadoop 설정
```shell
rm $HADOOP_HOME/etc/hadoop/masters # masters 파일 삭제
# Secondary Namenode가 뜨지 않으므로  masters 파일 삭제
```

### core-site.xml 추가 
```xml
<configuration>
    <!-- 기본 파일시스템 명 -->
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://hes-cluster</value>
    </property>
    <!-- zookeeper 서버 리스트 -->
    <property>
        <name>ha.zookeeper.quorum</name>
        <value>hadoop1:2181,hadoop2:2181,hadoop3:2181</value>
    </property>
</configuration>
```

### hdfs-site.xml 추가
```xml
<configuration>
    
    <!-- 특정 시점에 구성된 fsimage snapshot 이후로 발생된 변경 사항을 edit log라 한다. -->
    <!--  Journalnode 의 역할은 NameNode 동기화 상태를 유지하고 Active namenode 에서만 저널에 쓸수 있게 함. -->
    <property>
        <name>dfs.journalnode.edits.dir</name>
        <value>/home/hes/data/hdfs/journalnode</value>
    </property>

    <!--  네임서비스 리스트. 콤마(,)로 구분하여 여러개 설정가능. -->
    <property>
        <name>dfs.nameservices</name>
        <value>hes-cluster</value>
    </property>

    <!-- hes-cluster 네임서비스의 NameNode ID -->
    <property>
        <name>dfs.ha.namenodes.hes-cluster</name>
        <value>nn1,nn2</value>
    </property>


    <!-- nn1 NameNode의 RPC 포트 -->
    <property>
        <name>dfs.namenode.rpc-address.hes-cluster.nn1</name>
        <value>server01:8020</value>
    </property>


    <!-- nn2 NameNode의 RPC 포트 -->
    <property>
        <name>dfs.namenode.rpc-address.hes-cluster.nn2</name>
        <value>server02:8020</value>
    </property>

    <!-- nn1 NameNode의 Web UI 포트 -->
    <property>
        <name>dfs.namenode.http-address.hes-cluster.nn1</name>
        <value>server01:50070</value>
    </property>

    <!-- nn2 NameNode의 Web UI 포트 -->
    <property>
        <name>dfs.namenode.http-address.hes-cluster.nn2</name>
        <value>server02:50070</value>
    </property>

    <!-- NameNode가 edit log를 쓰고 읽을 JournalNode URI -->
    <property>
        <name>dfs.namenode.shared.edits.dir</name>
        <value>qjournal://server01:8485;server02:8485;server03:8485/hes-cluster</value>
    </property>

    <!-- HDFS 클라이언트가 active NameNode에 접근할 때 사용되는 Java class -->
    <property>
        <name>dfs.client.failover.proxy.provider.hes-cluster</name>
        <value>org.apache.hadoop.hdfs.server.namenode.ha.ConfiguredFailoverProxyProvider</value>
    </property>

    <!-- Failover 상황에서 기존 active NameNode를 차단할 때 사용할 방법 지정 -->
    <property>
        <name>dfs.ha.fencing.methods</name>
        <value>sshfence</value>
    </property>
    <!-- 
        ha.fencing.method를 sshfence로 지정했을 경우 ssh를 경유해 기존 active NameNode를 죽이는데,
        이때 passphrase를 통과하기 위해 SSH private key file을 지정해야 함.
     -->
    <property>
        <name>dfs.ha.fencing.ssh.private-key-files</name>
        <value>/home/hes/.ssh/id_rsa</value>
    </property>

    <!-- 장애복구를 자동으로 한다고 지정 -->
    <property>
        <name>dfs.ha.automatic-failover.enabled</name>
        <value>true</value>
    </property>

</configuration>
```

> 파일 압축해서 전체서버에 배포

### Zookeeper 초기화
```shell
# zookeeper Format
[server1] $HADOOP_HOME/bin/hdfs zkfc -formatZK

# 초기화 확인 위해 Zookeeper 접속
[server01] $ZOOKEEPER_HOME/bin/zkCli.sh
# hadoop-ha 아래에 dfs.nameservices 지정한 nameserviceID 노드가 있으면 성공
ls /hadoop-ha
        [hes-cluster]
# quit
[zk: localhost:2181(CONNECTED) 1] quit
```

### Server 1 ~3 에서 JournalNode 실행
```shell
[server01] $HADOOP_HOME/sbin/hadoop-daemon.sh start journalnode

[server02] $HADOOP_HOME/sbin/hadoop-daemon.sh start journalnode

[server03] $HADOOP_HOME/sbin/hadoop-daemon.sh start journalnode
```

### Journal 초기화
```shell
[server01] $HADOOP_HOME/bin/hdfs namenode -initializeSharedEdits
```

### Active NameNode 실행 및 Active ZKFC 실행
```shell
[server01] $HADOOP_HOME/sbin/hadoop-daemon.sh start namenode

[server01] $HADOOP_HOME/sbin/hadoop-daemon.sh start zkfc

# 아래와 같이 4개가 나와야 정상
[server01]$ jps
1832 QuorumPeerMain
2040 JournalNode
2184 NameNode
2270 DFSZKFailoverController
```

### 모든 클러스터 DataNode 실행
```shell
[server01] $HADOOP_HOME/sbin/hadoop-daemon.sh start datanode

[server02] $HADOOP_HOME/sbin/hadoop-daemon.sh start datanode

[server03] $HADOOP_HOME/sbin/hadoop-daemon.sh start datanode
```

### Standby NameNode 준비 및 실행 Standby NameNode 용 ZKFC 실행
```shell
[server02] $HADOOP_HOME/bin/hdfs namenode -bootstrapStandby

[server02] $HADOOP_HOME/sbin/hadoop-daemon.sh start namenode

[server02] $HADOOP_HOME/sbin/hadoop-daemon.sh start zkfc
  #NameNode HA 설정완료
```

### 나머지 YARN, JobHistoryServer를 실행
```shell
[server01] $HADOOP_HOME/sbin/start-yarn.sh
[server01] $HADOOP_HOME/sbin/mr-jobhistory-daemon.sh start historyserver
```
### 각 네임노드 상태확인
```shell
# namenode Web UI : http://server01:50070 , http://server02:50070
[server01]$HADOOP_HOME/bin/hdfs haadmin -getServiceState nn1
active
[server01]$HADOOP_HOME/bin/hdfs haadmin -getServiceState nn2
standby
```