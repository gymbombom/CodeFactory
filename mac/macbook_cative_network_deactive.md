# 맥북 captive Network 비활성화

### 비활성화 방법
```shell
	$ sudo defaults write /Library/Preferences/SystemConfiguration/com.apple.captive.control Active -boolean false
```

### 활성화 방법
```shell
	$ sudo defaults write /Library/Preferences/SystemConfiguration/com.apple.captive.control Active -boolean true
```
