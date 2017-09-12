# tcpdump 사용법

```shell
    $ tcpdump host 111.222.333.444 -w dump.pcap # 111.222.333.444 호스트로 전송중인 패킷을 캡쳐하여 dump.pcap 파일로 저장한다.
    $ tcpdump host 111.222.333.444 and tcp port 23 -w dump.pcap # 해당 호스트의 23번 포트로 흐르는 tcp 패킷을 캡쳐하여 파일로 저장
```