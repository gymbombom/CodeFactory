# 라즈베리파이 설정법


[라즈베리파이 지원SD카드 확인](https://elinux.org/RPi_SD_cards#Working_.2F_Non-working_SD_cards)
### 라즈비안OS설치법
```shell
$ df -hl
Filesystem     Size   Used  Avail Capacity iused               ifree %iused  Mounted on
/dev/disk1s1  234Gi   63Gi  169Gi    28%  694924 9223372036854080883    0%   /
/dev/disk1s4  234Gi  1.0Gi  169Gi     1%       1 9223372036854775806    0%   /private/var/vm
/dev/disk2s1   41Mi   21Mi   20Mi    51%       0                   0  100%   /Volumes/boot
```

```shell
$ diskutil list # 디스크 번호 알아내기
/dev/disk2 (internal, physical): # 2번이 디스크 번호
```

```shell
$ diskutil unmountDisk /dev/disk2 # 디스크 언마운트
sudo dd bs=1m if=/path/image.img of=/dev/rdisk2 # disk명 앞에 r을 붙여야함. Ctrl+T 로 진행상황 확인
sudo diskutil eject /dev/rdisk2 # 작업이 끝나면 디스크 꺼냄
```

### xrdp
``` shell
apt-get install xrdp
```
### 라즈베리파이 한글설정
``` shell
sudo apt-get -y install ibus-hangul
sudo apt-get install fonts-unfonts-core -y #이것만 설치해도 한글은 나오는거 같음 xwindow
```
~~sudo apt-get -y install ttf-unfonts-core~~

### 라즈베리파이 인식되는 디스크 파일시스템 추가
``` shell
#NTFS
apt-get install ntfs-3g -y
#EXFAT
apt-get install exfat-fuse -y
```
