# SSH SFTP 인증키 생성
>ssh 및 sftp 인증키 작업을 해놓으면 로그인 과정없이 접속가능해짐.(자동접속 스크립트 작성시 용이)

###참고사이트
[https://opentutorials.org/module/432/3742](https://opentutorials.org/module/432/3742)


###Client 작업
```shell
ssh-keygen -t rsa /*1.rsa 공개키 방식으로 암호화키 생성 ~/.ssh/ 위치에 생성됨.*/
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa #enter 키 입력없이 바로 key생성
```

```shell
/*permition 은 아래와 같아야 한다.(보안을 위해)*/
chmod 700 ~/.ssh
chmod 600 ~/.ssh/id_rsa
chmod 644 ~/.ssh/id_rsa.pub  
chmod 644 ~/.ssh/authorized_keys
chmod 644 ~/.ssh/known_hosts
```

```shell
scp  ~/.ssh/id_rsa.pub user@111.222.333.444:id_rsa.pub /*접속할 서버의 홈디렉토리로 공개키 파일 이동*/
ssh-copy-id -i ~/.ssh/id_rsa.pub hes@hadoop-master; #ssh 공개키 배포
```

###Server 작업
```shell
cat ~/id_rsa.pub >> $HOME/.ssh/authorized_keys /*Server의 authorized_keys파일에 공개키 추가 */
```

###참고
```shell
# CentOS 에서는, .ssh directory를 700, authorized_keys 를 600 으로 권한 설정을 하지 않으면 동작하지 않습니다. 
```
