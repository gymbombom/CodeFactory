# apt-get 사용법
### 참고
[https://blog.outsider.ne.kr/346](https://blog.outsider.ne.kr/346)  
[https://www.hugeserver.com/kb/install-use-tcpdump-capture-packets](https://www.hugeserver.com/kb/install-use-tcpdump-capture-packets)

### 사용법
```shell
    sudo apt-get update #패키지 목록 가져오기
    sudo apt-get upgrade #가져온 패키지 목록 업그레이드
    sudo apt-get install <pakage Name> # 새로운 패키지 설치
    sudo apt-get dist-upgrade  #의존성 검사하며 업그레이드
    sudo apt-get --reinstall install <package Name> # 재설치
    sudo apt-get --purge autoremove <pakage Name>  #의존성 검사하며 설정파일까지 삭제
    sudo sudo apt-cache  search <pakage Name> #패키지 검색
```

