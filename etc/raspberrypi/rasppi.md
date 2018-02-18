# 라즈베리파이 설정법

### xrdp
``` shell
apt-get install xrdp
```
### 라즈베리파이 한글설정
``` shell
sudo apt-get -y install ibus-hangul
sudo apt-get install fonts-unfonts-core
```
~~sudo apt-get -y install ttf-unfonts-core~~

### 라즈베리파이 디스크 포멧 추가
``` shell
#NTFS
apt-get install ntfs-3g
#EXFAT
apt-get install exfat-fuse
```