# homebrew


### homebrew 설치
```shell
	$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### homebrew 사용법
```shell
	$ brew update # homebrew 신규버전 업데이트
	$ brew upgrade <package_name> # 설치한 패키지 업그레이드
	$ brew install <package_name> # 패키지설치
	$ brew remove <package_name> #패키지삭제
	$ brew list # 설치된 패키지 보기
	$ brew search <package_name> # 패키지 검색
	$ brew -v # 버전확인
	$ brew info <package_name> # 패키지 상세보기
```

### homebrew 설치제거 ??
```shell
	$ cd `brew --prefix`
	$ rm -rf Cellar
	$ brew prune
	$ rm `git ls-files`
	$ rmdir Library/Homebrew Library/Aliases Library/Formula Library/Contributions
	$ rm -rf .git
	$ rm -rf ~/Library/Caches/Homebrew
```

### homebrew 패키지 설치위치
```shell
	/usr/local/Cellar/ # homebrew로 설치한 패키지는 해당경로에 설치
	/usr/local/bin/ # 심볼릭링크가 걸려있다.
```