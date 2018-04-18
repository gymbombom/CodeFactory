# Hadoop httpfs 설정
* HDFS 파일 시스템 작업 (읽기 및 쓰기)을 지원하는 REST HTTP 게이트웨이를 제공하는 서버  
* 다른 버전의 Hadoop을 실행하는 클러스터간에 데이터를 전송하는 데 사용할 수 있음.(RPC 문제 극복)  
* 방화벽 뒤의 클러스터에서 HDFS의 데이터에 액세스하는 데 사용할 수 있음.  
* Hadoop 프록시 사용자 지원을 제공

## 설정 방법

```xml
<!-- core-site.xml 에 아래내용 추가 -->
 <property>
    <name>hadoop.proxyuser.#HTTPFSUSER#.hosts</name>
    <value>*</value>
</property>

<property>
    <name>hadoop.proxyuser.#HTTPFSUSER#.groups</name>
    <value>*</value>
</property>
```

```xml
<!-- httpfs-site.xml 에 아래내용 추가 -->
<!-- 아래 설정이 없으면, 
      http://13.125.167.96:14000/webhdfs/v1/tmp?op=LISTSTATUS&user.name=aaa 과 같이 url 에 user.name 파라미터를 추가해야함. -->
<!-- 설정 이후에 hadoop restart 해야함. -->
 <property>
    <name>httpfs.proxyuser.#HTTPFSUSER#.hosts</name>
    <value>*</value>
</property>

<property>
    <name>httpfs.proxyuser.#HTTPFSUSER#.groups</name>
    <value>*</value>
</property>
```

## httpfs 실행
```shell
bin/httpfs.sh start
```

### test
```text
1 webhdfs
http://13.125.167.96:50070/webhdfs/v1/tmp?op=LISTSTATUS

2 webhdfs
http://13.125.81.136:50070/webhdfs/v1/tmp?op=LISTSTATUS

3.httpfs
http://13.125.167.96:14000/webhdfs/v1/tmp?op=LISTSTATUS&user.name=aaa
```

1 webhdfs
http://13.125.167.96:50070/webhdfs/v1/tmp?op=LISTSTATUS

2 webhdfs
http://13.125.81.136:50070/webhdfs/v1/tmp?op=LISTSTATUS

3.httpfs
http://13.125.167.96:14000/webhdfs/v1/tmp?op=LISTSTATUS&user.name=aaa
