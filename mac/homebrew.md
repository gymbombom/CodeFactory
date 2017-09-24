# homebrew


### homebrew 설치
```shell
	$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### homebrew 사용법
```shell
	$ brew install <package_name> # 패키지설치
	$ brew remove <package_name> #패키지삭제
	$ brew list # 설치된 패키지 보기
	$ brew search <package_name> # 패키지 검색
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