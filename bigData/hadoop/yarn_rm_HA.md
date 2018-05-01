# yarn ResourceManager  HA 설치방법

> hadoop 버전 : hadoop 2.7.2
> hadoop 설치가 완료된 후에 설정



### yarn-site.xml 추가
```xml
<property>
  <name>yarn.resourcemanager.ha.enabled</name>
  <value>true</value>
</property>

<property>
  <name>yarn.resourcemanager.cluster-id</name>
  <value>cluster1</value>
</property>

<property>
  <name>yarn.resourcemanager.ha.rm-ids</name>
  <value>rm1,rm2</value>
</property>

<property>
  <name>yarn.resourcemanager.hostname.rm1</name>
  <value>master1</value>
</property>

<property>
  <name>yarn.resourcemanager.hostname.rm2</name>
  <value>master2</value>
</property>

<property>
  <name>yarn.resourcemanager.webapp.address.rm1</name>
  <value>master1:8088</value>
</property>

<property>
  <name>yarn.resourcemanager.webapp.address.rm2</name>
  <value>master2:8088</value>
</property>

<property>
  <name>yarn.resourcemanager.zk-address</name>
  <value>zk1:2181,zk2:2181,zk3:2181</value>
</property>
```



### Standby 용 ResourceMAnager는 수동으로 시작해주어야함.

```shell
home/hadoop/sbin/yarn-daemon.sh start resourcemanager

# 상태확인
[root@server01]/home/hadoop/bin/yarn rmadmin -getServiceState rm1
active
[root@server01]/home/hadoop/bin/yarn rmadmin -getServiceState rm2
standby
```



HA가 도입되기 전, ResourceManager가 죽었다 살아났을 때 혹시나 죽기 전에 미처 처리하지 못한 것들을 다시 처리하기 위해 state-store에 application metadata를 저장했다가 죽기 전에 처리하지 못한 지점부터 처리하는 설정이 있었음.

2가지 방식이 있는데, 하나는 파일(FileSystemRMStateStore)에 저장하는 것이고, 다른 하나는 Zookeeper(ZKRMStateStore)에 저장하는 것.

기본값은 파일에 저장하는 FileSystemRMStateStore인데, 

Zookeeper가 atomic write를 보장하므로 따로 차단 메카니즘이 필요없기 때문에 **HA cluster에서는 ZKRMStateStore가 권장**됨.

(어차피 HA cluster를 구성하려면 Zookeeper가 필요하기도 하고...)

yarn-site.xml 에 아래 property를 추가하면 state-store를 Zookeeper로 지정가능.

```xml
<!-- ResourceManager 시작시 state 복구여부 -->
<property>
    <name>yarn.resourcemanager.recovery.enabled</name>
    <value>true</value>
</property>

<!-- persistent store로 사용할 class -->
<property>
    <name>yarn.resourcemanager.store.class</name>
    <value>org.apache.hadoop.yarn.server.resourcemanager.recovery.ZKRMStateStore</value>
</property>

<!-- Zookeeper 서버 리스트 -->
<property>
    <name>yarn.resourcemanager.zk-address</name>
    <value>server01:2181,server02:2181,server03:2181</value>
</property>
```



### Resource Manager Web 접속

> cloud1:8088
> cloud2:8088