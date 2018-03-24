# HADOOP 설치
>> hadoop 버전 : hadoop-2.7.2  
>> java 버전 : 1.8.0_121  
>> Red Hat Enterprise Linux Server 7.2 (Maipo)


### SingleNode 설치
* etc/hadoop/core-site.xml
```xml
<!-- 기본 파일 시스템의 이름. 스키마와 권한이 FileSystem 구현을 결정하는 URI. -->
<!--> namenode URI -->
<configuration>
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://localhost:9000</value>
    </property>

<!-- Number of replication for each chunk.
     single node에서는 1개, multi node 에서는 홀수로 구성  
-->
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>

<!--> 필수 옵션은 아님
    <property>
        <name>hadoop.tmp.dir</name>
        <value>/tmp/hadoop</value>
    </property>
-->
</configuration>
```

* hdfs-site.xml
```xml
</configuration>

# namenode 의 Fsimage(스냅샷) 저장위치
    <property>
        <name>dfs.namenode.name.dir</name>
        <value>/home/hduser/mydata/hdfs/namenode</value>
    </property>

<!-- 필수옵션은 아님 
    하지만 설정하지 않을 경우 기본 datadir 이 /tmp/hadoop-${user.name}/dfs/data 로 지정됨. 
    <property>
        <name>dfs.datanode.data.dir</name>
        <value>/home/hduser/mydata/hdfs/datanode</value>
    </property>
-->
```

* 인증없이 ssh localhost 에 접속할수 있는지 체크
```shell
    ssh localhost
    # 접속할수 없다면 아래 실행하여 ssh 키 생성
    ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
    cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
    chmod 0600 ~/.ssh/authorized_keys
```

* namenode 포멧
```shell
    bin/hdfs namenode -format
```

* namenode, datanode start
```shell
    sbin/start-dfs.sh
```

*namenode web interface 에서 확인
>> NameNode - http://localhost:50070/


