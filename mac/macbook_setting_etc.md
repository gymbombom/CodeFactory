# 맥북 세팅방법

### 맥북 숨김파일표시
```shell
 	defaults write com.apple.finder AppleShowAllFiles -bool true  #맥북 숨김파일 표시
 	defaults write com.apple.finder AppleShowAllFiles -bool false  #맥북 숨김파일 숨김
```

### 미션컨트룰 화면고정
 ```shell
 	System Preferences
 	Mission Control > Automatically rearrange Spaces based on most recent use: 체크 안함
 ```

### 텍스트 자동대치 비활성화
 ```shell
 System Preferences
 	Keyboard > Text: 모든 자동 변경 옵션 끄기
 ```

### Finder 기본 화면 설정
 ```shell
 	Finder를 실행하고 Finder > Preferences선택
 	General > New Finder windows show (다운로드 선택)
 ```

### 모든파일 확장자 표시
 ```shell
 	Advanced > Show all filename extensions
 ```

### 날짜별로 파일정렬
 ```shell
 	Downloads 폴더로 이동 
 	View > Show View Options
 	Arrange By:Date added, Sort By:Name
 ```

###  맥북 Sleep모드 확인

```shell
pmset -g
System-wide power settings:
Currently in use:
 standbydelay         10800 #hibernatemode delay시간
 standby              1
 womp                 1
 halfdim              1
 hibernatefile        /var/vm/sleepimage
 powernap             1
 gpuswitch            2
 networkoversleep     0
 disksleep            10
 sleep                1
 autopoweroffdelay    28800
 hibernatemode        3
    #hibernatemode 0 : 선잠자기(Simple Sleep).
	#hibernatemode 1 : 깊은 잠자기(Deep Sleep). 동면. 하이버네이션.
    #hibernatemode 3 : 안전 잠자기(Safe Sleep). 0 + 1 모드 함께 사용.
 autopoweroff         1
 ttyskeepawake        1
 displaysleep         10
 tcpkeepalive         1
 acwake               0
 lidwake              1
```

```shell
#### 시간및 모드 변경#####
$sudo pmset -a standbydelay [초] 
$sudo pmset -a hibernatemode [모드] 
```

