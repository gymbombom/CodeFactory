# Hadoop Multinode 설치
> Singgle 노드 먼저 구성후, Multinode로 넘어가는것을 추천
> hadoop 버전 : hadoop-2.7.2  
> java 버전 : 1.8.0_121  
> Red Hat Enterprise Linux Server 7.2 (Maipo)

### /etc/hosts 파일수정
* /etc/hosts 파일
```shell
192.168.1.109 hadoop-master 
192.168.1.145 hadoop-slave-1 
192.168.56.1 hadoop-slave-2

# 위의 예시와 같이 수정 후 테스트(cluster 에 포함된 모든 노드에서 수정)
$ ping hadoop-master
$ ping hadoop-slave-1
$ ping hadoop-slave-2
```

### 환경변수 설정
* $(HOME)/.bashrc
```shell
# vi .bashrc

#java
export JAVA_HOME="$HOME/jdk1.8.0_121";
export PATH="$PATH:$JAVA_HOME/bin";

#hadoopexport HADOOP_HOME="$HOME/hadoop-2.7.2";
export HADOOP_HOME="$HOME/hadoop-2.7.2";
export PATH="$PATH:$HADOOP_HOME/bin";
```
```shell
$ source ./.bashrc
```


### ssh key 생성
```shell
# cluster 에 포함된 모든 노드에서 ssh key 생성 후 배포하여야 한다.
$ ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa  #ssh-key 생성
```

### ssh key 배포
```shell
# cluster 에 포함된 모든 노드에서 배포해야 함.
$ ssh-copy-id -i ~/.ssh/id_rsa.pub hes@hadoop-master;
$ ssh-copy-id -i ~/.ssh/id_rsa.pub hes@hadoop-slave-1;
$ ssh-copy-id -i ~/.ssh/id_rsa.pub hes@hadoop-slave-2;
$ chmod 0600 ~/.ssh/authorized_keys;
```

### core-site.xml 파일 설정
```xml
<configuration>
   <property> 
      <name>fs.default.name</name> 
      <value>hdfs://hadoop-master:9000/</value> 
   </property> 

<!-- 아래 dfs.replication 설정의 경우, hdfs-site.xml 설정해도 되는거 같음. -->  
   <property>
        <name>dfs.replication</name>
        <value>3</value>
  </property>

<!--아래 dfs.permissions 의 경우, hdfs-site.xml 에 설정해도 되는거 같음. -->
  <property> 
      <name>dfs.permissions</name> 
      <value>false</value> 
  </property>

<!-- temp 디렉토리 경로  default는 아닐듯... -->
  <property>
      <name>hadoop.tmp.dir</name>
      <value>/home/hes/data/tmp</value>
  </property>

<!-- 아래 설정은 default 는 아닌듯...
   <property> 
      <name>dfs.permissions</name> 
      <value>false</value> 
   </property> 
 -->
</configuration>
```

### hdfs-site.xml 설정
```xml
<configuration>

<!-- 아래와 같이 final 이 선언되면 이후에 로드되는 자원이 해당 값을 더이상 변경할수 없음.
   <property> 
      <name>dfs.data.dir</name> 
      <value>/opt/hadoop/hadoop/dfs/name/data</value> 
      <final>true</final> 
   </property> 

   <property> 
      <name>dfs.name.dir</name> 
      <value>/opt/hadoop/hadoop/dfs/name</value> 
      <final>true</final> 
   </property> 

-->

 <property>
        <name>dfs.namenode.name.dir</name>
        <value>/home/hes/data/hdfs/namenode</value>
 </property>

  <property>
        <name>dfs.datanode.data.dir</name>
        <value>/home/hes/data/hdfs/datanode</value>
  </property>

  <!--아래 dfs.permissions 의 경우, hdfs-site.xml, core-site.xml 어디에다  설정해도 되는거 같음. 여기선 core-site.xml 에 설정
  <property> 
      <name>dfs.permissions</name> 
      <value>false</value> 
  </property>
  -->

<!-- 아래 설정의 경우 core-site.xml, hdfs-site.xml 어디에다 설정해도 되는거 같음. 여기서는 core-site.xml 에 설정
  <property>
        <name>dfs.replication</name>
        <value>3</value>
  </property>
-->  
</configuration>
```

### hadoop-env.sh 설정(변경)
```shell
export JAVA_HOME=${JAVA_HOME}
```

### master node 설정
```shell
# vi $HADOOP_HOME/etc/hadoop/masters
hadoop-master
```

### Slave node 설정
```shell
# vi $HADOOP_HOME/etc/hadoop/slaves
hadoop-slave-1
hadoop-slave-2
```


### 클러스터링 할 모든 node에 배포
```shell
#/bin/bash

#server variables
SERVER_IP=("hadoop-master" "hadoop-slave-1" "hadoop-slave-2")
SERVER_USER="user"

#client variables
CLIENT_PWD=`pwd | xargs`;
CLIENT_FILENAME=$1;

#run script
for i in ${SERVER_IP[@]}
do
	scp -r $CLIENT_FILENAME $SERVER_USER@$i:$CLIENT_PWD
done
```

### namenode Format
```shell
hadoop namenode –format
```

### shell scropt 작성
```shell
#!/bin/bash

function print_usage()
{
        echo "start :hadoop start"
}

case "$1" in

start)
        $HADOOP_HOME/sbin/start-all.sh
;;

stop)
        $HADOOP_HOME/sbin/stop-all.sh
;;

*)
        print_usage
        exit 1
;;

esac
```

### hadoop start
```shell
$ hadoop.sh start
```


> resourcemanager port : 8088  
> namenode port : 50070  
> datanode port : 50075  
> secondary namenode port : 50090
