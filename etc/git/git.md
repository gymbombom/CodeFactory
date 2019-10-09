# GIT사용법

### 참고사이트
[https://git-scm.com/book/ko/v1/](https://git-scm.com/book/ko/v1/)  
[https://rogerdudler.github.io/git-guide/index.ko.html](https://rogerdudler.github.io/git-guide/index.ko.html)  
[gitignore 설정방법](http://emflant.tistory.com/127)
[git 설치](https://git-scm.com/download/linux)  

### Cheat Sheet
![](./git_cheat_sheet.png)

### git 서버 구축하기
```shell
     $ mkdir <repository name>
     ex)$ mkdir project.git #repository name  뒤에 .git 을 붙이는 것은 관례이다.
     $ cd <repository name>
     git init --bare --shared #git 저장소로 사용할 디렉토리로 이동하여 빈 저장소를 만든다.
```


### Repository 생성하기 (초기화)
```shell
    cd <repository_directory_name> # repository로 사용할 디렉토리로 이동
    git init      # repository 초기화
```

### git 사용자 정보등록

```shell
    # 이것을 등록하지 않으면 github 의 경우 contributions show 표시가 되지 않는다. 
    #Git은 커밋할 때마다 이 정보를 사용한다. 한 번 커밋한 후에는 정보를 변경할 수 없다
    $ git config --global user.name "John Doe"
    $ git config --global user.email johndoe@example.com
```

### 상태확인
```shell
    git status #파일의 상태를 확인(수정여부)
```

### 파일을 tracked(git 관리상태 추가)하기
```shell
    git add <filename>
```

### commit  하기
```shell
    git commit -m <message> #메세지와 함께 commit하기
```

### 원격 저장소 추가하기
```shell
    git remote add [remote repository name | default: origin] [remote URL]
    ex) remote add origin https://github.com/dlfrb2000/Note.git
```

### 원격 저장소에 push하기
```shell
    git push -u origin master # -u옵션이 정확이 무엇인지 모르겠음 
```

### 간단한 사용법
```shell
    git remote -v # 원격저장소 보기
    git remote set-url <remote repository name> <remote repository url> #원격 저장소 URL변경
        ex) git remote set-url origin https://github.com/user/repo.git
    git gc # git repository가 너무 커져서 속도가 저하할 경우, gc가 필요함.
```

### 로그 확인
```shell
    git log
```

### git push 되돌리기
```shell
    $ git reset HEAD^ # local repository commmit 한번 뒤로 되돌리고,
    $ git commit -m 'commit message' # 되돌린 후 다시 commit 하고,
    $ git push origin +master # 강제로 push 한다. +의 의미는 데이터가 손실되도 무시한다.
```

### git repository commit 내역까지 이동시키는 법
```shell
	$ git clone --mirror https://gitlab.com/dlfrb2002/codefactory.git # 과거 reposity 복사
	$ cd codefactory.git # 저장소로 이동
	$ git remote set-url --push origin https://github.com/likeel/secret.git # 이동시킬 저장소 url 설정
	$ git push --mirror #이동시킬 저장소로 Push
```
