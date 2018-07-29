# Cassandra MultiNode 설치

> Cassandra SingleNode 가 먼저 구성된 상태에서 진행



### Default DataSet 삭제

```shell
$ rm -rf /var/lib/cassandra/data/system/* #default Dataset은 이미 Cassandra Single Node에서 실행했을 경우에 삭제한다.
```



### cassandra.yaml 파일 설정

```yaml
# Cluster 이름설정
cluster_name: 'cloud cluster'

...

# seeds 는 클러스터에 연결된 각 노드의 IP를 쉼표로 구분하여 입력
seed_provider:
  - class_name: org.apache.cassandra.locator.SimpleSeedProvider
    parameters:
         - seeds: "your_server_ip,your_server_ip_2,...your_server_ip_n"
         
# 클러스터의 다른 노드가 현재 노드를 연결할때 필요한 IP주소로 노드 자기자신의 IPAddress 가 입력되어야 함.
listen_address: your_server_ip

# 원격 프로 시저 호출에 대한 IP 주소입니다. 기본값은 localhost입니다. 서버의 호스트 이름이 올바르게 구성되어 있으면 그대로 두십시오. 그렇지 않으면 서버의 IP 주소 또는 루프백 주소로 변경하십시오.
rpc_address: 127.0.0.1

# 이 설정은 옵션....
# 네트워크가 어떻게 생겼는지에 대해 카산드라에게 알려주는 것입니다. 이 기본값은 하나의 데이터 센터에있는 네트워크에 사용되는 SimpleSnitch입니다.
# endpoint_snitch: GossipingPropertyFileSnitch

...

# 이 지시문은 구성 파일에 없으므로 추가하고 false로 설정해야합니다. 그러면 새 노드가 자동으로 올바른 데이터를 사용하게됩니다. 기존 클러스터에 노드를 추가하는 경우 선택 사항이지만 새 클러스터를 초기화 할 때, 즉 데이터가없는 클러스터가 필요한 경우 필요합니다.
auto_bootstrap: false


```



###  Cassandra Pakage 압축 및 클러스터 서버 전송

```shell
$ tar -cvf apache-cassandra-3.10.tar apache-cassandra-3.10/
```

### 클러스터 서버 배포 스크립트

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

### 각 노드의 listen_address 변경

```yaml
listen_address: your_server_ip #각 노드의 IPAddress 가 입력되어야 함.
```



### 포트설명

* `7000`, 명령과 데이터를위한 TCP 포트입니다.
* `9042`, 네이티브 전송 서버의 TCP 포트입니다. Cassandra 명령 행 유틸리티 인 cqlsh는이 포트를 통해 클러스터에 연결합니다.

