# 맥북 로그인 소리제거

###1.스크립트 작성
```shell
#fileName : mute_on.sh
#!bin/bash
osascript -e 'set Volume with output muted'
```

```shell
#fileName: mute_off.sh
#!bin/bash
osascript -e 'set volume without output muted'
```

###2.스크립트 파일 이동
```shell
mv ./mute_on /Library
mv ./mute_off /Library
```

###3.console 에서 명령실행
```shell
sudo defaults write com.apple.loginwindow LoginHook /Library/mute_off.sh
sudo defaults write com.apple.loginwindow LogoutHook /Library/mute_on.sh
```

###4. 원상복구
```shell
sudo defaults delete com.apple.loginwindow LogoutHook
sudo defaults delete com.apple.loginwindow LoginHook
```