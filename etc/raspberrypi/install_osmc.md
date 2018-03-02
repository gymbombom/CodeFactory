# OSMC 설치
> Open Source Media Center 로 라즈베리파이 오픈소스 미디어 센터를 구성할수 있는 OS

### OSMC 설치
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
> 최초 설정 시 English로 설정해야 함 한글로 설정해도 어차피 한글은 깨져서 사용하지 못한다.

### 안드로이드 리모컨 설정
> 안드로이드 마켓에서 yeste 다운로드