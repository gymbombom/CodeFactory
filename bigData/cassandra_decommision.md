# Cassandra decommission 테스트

* Case1. 노드 decom시 데이터가 이동 하는가?
* Case2. decom된 노드의 데이터를 강제 삭제하고 join시에 데이터 구성은 어찌되는가?
* Case3 decom된 노드를 다시 join시에 기존데이터가 디시들어노는가? 그리고 신규 입력된 데이터는 join 노드에 입력되는가?

> 환경 : Cassandra 4노드 구성
```sql
    //키스페이스 test
    CREATE TABLE test.test01 (
           col01 text,
           PRIMARY KEY (col01)
    );

 insert into test.test01(col01) values('1');
 insert into test.test01(col01) values('2');
 insert into test.test01(col01) values('3');
 insert into test.test01(col01) values('4');
```

>Case1. 노드 decom시 데이터가 이동 하는가?
```shell
   cqlsh> CREATE TABLE test.test01 (
   ...     col01 text,
   ...     PRIMARY KEY (col01)
   ... );

   cqlsh>  
   cqlsh> insert into test.test01(col01) values('1');

   [lik@ip-172-31-9-255 bin]$ ./nodetool getendpoints test test01 1
    172.31.6.252
    172.31.9.255
    172.31.9.192
```

```shell
   #nodetool decommission
   [lik@ip-172-31-9-255 bin]$ ./nodetool status
    Datacenter: dc1
    ===============
    Status=Up/Down
    |/ State=Normal/Leaving/Joining/Moving
    --  Address       Load       Tokens       Owns (effective)  Host ID                               Rack
    UN  172.31.9.255  263.77 KiB  256          75.3%             cf5fc3a0-3b4d-410e-9e92-2fc48060c088  rack1
    UN  172.31.3.159  233.79 KiB  256          75.1%             12cdf47e-1802-4337-9f75-9cc2ec01c39b  rack1
    UN  172.31.6.252  253.85 KiB  256          74.1%             928e8692-03bd-439f-840c-e1593f95fe90  rack1
    UN  172.31.9.192  258.8 KiB  256          75.5%             4d6b406b-b70f-4bda-b242-992f054cabcc  rack1

    [lik@ip-172-31-9-192 bin]$ ./nodetool -h 172.31.9.192 decommission

    [lik@ip-172-31-9-255 bin]$ ./nodetool status
    [lik@ip-172-31-9-255 bin]$ ./nodetool status
    Datacenter: dc1
    ===============
    Status=Up/Down
    |/ State=Normal/Leaving/Joining/Moving
    --  Address       Load       Tokens       Owns (effective)  Host ID                               Rack
    UN  172.31.9.255  243.83 KiB  256          100.0%            cf5fc3a0-3b4d-410e-9e92-2fc48060c088  rack1
    UN  172.31.3.159  243.74 KiB  256          100.0%            12cdf47e-1802-4337-9f75-9cc2ec01c39b  rack1
    UN  172.31.6.252  258.98 KiB  256          100.0%            928e8692-03bd-439f-840c-e1593f95fe90  rack1

    [lik@ip-172-31-9-255 bin]$ ./nodetool getendpoints test test01 1
    172.31.9.255
    172.31.3.159
    172.31.6.252

    #테스트 결과 클러스터에서 Decom결과 데이터가 이동하는것을 확인
```

> case2. decom된 노드의 데이터를 강제 삭제하고 join시에 데이터 구성은 어찌되는가?

```shell
    [lik@ip-172-31-9-192 test]$ ls -alh *
    test01-134a969018fc11e79316e927472ac210:
    total 40K
    drwxrwxr-x. 3 lik lik 4.0K Apr  4 02:54 .
    drwxrwxr-x. 4 lik lik   96 Apr  4 02:00 ..
    drwxrwxr-x. 2 lik lik    6 Apr  4 02:00 backups
    -rw-rw-r--. 1 lik lik   43 Apr  4 02:54 mc-1-big-CompressionInfo.db
    -rw-rw-r--. 1 lik lik   30 Apr  4 02:54 mc-1-big-Data.db
    -rw-rw-r--. 1 lik lik    9 Apr  4 02:54 mc-1-big-Digest.crc32
    -rw-rw-r--. 1 lik lik   16 Apr  4 02:54 mc-1-big-Filter.db
    -rw-rw-r--. 1 lik lik    5 Apr  4 02:54 mc-1-big-Index.db
    -rw-rw-r--. 1 lik lik 4.5K Apr  4 02:54 mc-1-big-Statistics.dbㅍ
    -rw-rw-r--. 1 lik lik   92 Apr  4 02:54 mc-1-big-TOC.txt
```

```shell
    test-9e1012a0144211e7a9197d818d8b0cee:
    total 0b
    drwxrwxr-x. 4 lik lik 36 Mar 29 01:53 .
    drwxrwxr-x. 4 lik lik 96 Apr  4 02:00 ..
    drwxrwxr-x. 2 lik lik  6 Mar 29 01:43 backups
    drwxrwxr-x. 3 lik lik 39 Mar 29 01:53 snapshots
    [lik@ip-172-31-9-192 test]$ rm -rf *
```

```java
    // ./nodetool -h  172.31.9.192 join  시 조인 안됨. 재기동 후 

    Fatal configuration error; unable to start server.  See log for stacktrace.
    ERROR [main] 2017-04-05 02:47:41,544 CassandraDaemon.java:752 - Fatal configuration error
    org.apache.cassandra.exceptions.ConfigurationException: This node was decommissioned and will not rejoin the ring unless cassandra.override_decommission=true has been set, or all existing data is removed and the node is bootstrapped again
	at org.apache.cassandra.service.StorageService.prepareToJoin(StorageService.java:766) ~[apache-cassandra-3.10.jar:3.10]
	at org.apache.cassandra.service.StorageService.initServer(StorageService.java:666) ~[apache-cassandra-3.10.jar:3.10]
	at org.apache.cassandra.service.StorageService.initServer(StorageService.java:612) ~[apache-cassandra-3.10.jar:3.10]
	at org.apache.cassandra.service.CassandraDaemon.setup(CassandraDaemon.java:394) [apache-cassandra-3.10.jar:3.10]
	at org.apache.cassandra.service.CassandraDaemon.activate(CassandraDaemon.java:601) [apache-cassandra-3.10.jar:3.10]
	at org.apache.cassandra.service.CassandraDaemon.main(CassandraDaemon.java:735) [apache-cassandra-3.10.jar:3.10]
    INFO  [StorageServiceShutdownHook] 2017-04-05 02:47:41,640 HintsService.java:221 - Paused hints dispatch
```

```shell
    [lik@ip-172-31-9-192 bin]$ ./cassandra -Dcassandra.override_decommission=true  #기동 및 조인성공 
```

```shell
    [lik@ip-172-31-9-192 bin]$ ./nodetool status
    Datacenter: dc1
    ===============
    Status=Up/Down
    |/ State=Normal/Leaving/Joining/Moving
    --  Address       Load       Tokens       Owns (effective)  Host ID                               Rack
    UN  172.31.9.255  243.83 KiB  256          75.3%             cf5fc3a0-3b4d-410e-9e92-2fc48060c088  rack1
    UN  172.31.3.159  243.74 KiB  256          75.1%             12cdf47e-1802-4337-9f75-9cc2ec01c39b  rack1
    UN  172.31.6.252  258.98 KiB  256          74.1%             928e8692-03bd-439f-840c-e1593f95fe90  rack1
    UN  172.31.9.192  247.79 KiB  256          75.5%             4d6b406b-b70f-4bda-b242-992f054cabcc  rack1

    [lik@ip-172-31-9-192 bin]$ ./nodetool getendpoints test test01 1
    172.31.6.252
    172.31.9.255
    172.31.9.192
    
    #노드 decommission시  데이터는 다른 노드에 이동하였다가 다시 rejoin후 원래 노드로 데이터가 복제되는것을 확인
```

> case3. decom된 노드를 다시 join시에 기존데이터가 디시들어노는가? 그리고 신규 입력된 데이터는 join 노드에 입력되는가?

```shell
    cqlsh> insert into test.test01(col01) values('2');
    cqlsh> quit
    [lik@ip-172-31-9-255 bin]$
    [lik@ip-172-31-9-255 bin]$
    [lik@ip-172-31-9-255 bin]$ ./nodetool getendpoints test test01 2
    172.31.9.192
    172.31.6.252
    172.31.9.255

    #노드 조인시 신규 데이터가 정상적으로 조인된 노드에 삽입이 된다.
```
