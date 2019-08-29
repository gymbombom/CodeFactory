# Cassandra SingleNode 설치

> Cassandra version : 3.10
> Java version : 1.8.0_121
[cassandra Achive Download Pages](https://archive.apache.org/dist/cassandra/)  

### Cassandra Binary Download
```shell
$ curl -O https://archive.apache.org/dist/cassandra/3.10/apache-cassandra-3.10-bin.tar.gz # Cassandra binary Download
$ tar -xvzf apache-cassandra-3.10-bin.tar.gz # 압축해제
```

###  환경변수 추가
```shell
$ vi .bashrc
#Cassandra Export
export CASSANDRA_HOME="/home/hes/apache-cassandra-3.10";
export PATH="$PATH:$CASSANDRA_HOME/bin";
```

### Cassadra 설정파일 변경
```yaml
# vi cassandra.yaml 아래항목 설정
data_file_directories:
     - /home/hes/datadir/cassandra/data
     - /home/hes/datadir2/cassandra/data #필수는 아님 다음과 같이 data_directory를 여러개 쓸수도 있음.
commitlog_directory: /home/hes/datadir/cassandra/commitlog
saved_caches_directory: /home/hes/datadir/cassandra/saved_caches
hints_directory: /home/hes/datadir/cassandra/hints
```

### Cassnadra 실행 및 확인
```shell
$ $CASSANDRA_HOME/bin/cassandra # Cassandra 실행
$ $CASSANDRA_HOME/bin/nodetool status # Cassandra 상태확인
Datacenter: datacenter1
=======================
Status=Up/Down
|/ State=Normal/Leaving/Joining/Moving
--  Address    Load       Tokens       Owns (effective)  Host ID                               Rack
UN  127.0.0.1  103.68 KiB  256          100.0%            fce23ff3-8649-4545-9020-cddcb9eda4c9  rack1
```

### Cassandra Stop Script 변경
```shell
#vi stop-server 에서 아래부분 주석제거
 user=`whoami`
 pgrep -u $user -f cassandra | xargs kill -9
```

### Cassandra 종료
```shell
$ $CASSANDRA_HOME/bin/stop-server
```
