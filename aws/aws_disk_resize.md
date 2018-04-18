# aws(amazon web service) 디스크 볼륨 확장
* 아마존 웹 서비스의 경우 디스크 용량 확장 후 디스크를 제대로 인식하지 못하는 경우가 있다. 그럴땐 수동으로 디스크 볼륨을 확장해 주어야 한다.

### 디스크 포멧 확인 
```shell
    df -hl # 디스크 확인
    sudo file -s /dev/xvda* # df 로 파일시스템을 찾은 후 disk 파일시스템 확인
    # ext2/ext3/ext4 일 경우 resize2fs 명령을 사용해야 함.
    # xfs 일경우 xfs_growfs 명령을 사용해야 함.
```

### 디스크 확장이 필요한지 확인 
```shell
[ec2-user ~]$ lsblk
NAME    MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
xvda    202:0    0  30G  0 disk
└─xvda1 202:1    0  30G  0 part /
xvdb    202:16   0  30G  0 disk /mnt
xvdf    202:80   0  35G  0 disk
└─xvdf1 202:81   0   8G  0 part
# xvda1 파티션의 경우 상위 xvda 와 용량이 같으므로 확장 필요없음.
# xvdf1 파티션의 경우 상위 xvdf 파티션과 크기가 다르므로 디스크 확장하여야 함.
```

```shell
[ec2-user ~]$ df -h
Filesystem            Size  Used Avail Use% Mounted on
/dev/xvda1            8.0G  943M  6.9G  12% /
tmpfs                 1.9G     0  1.9G   0% /dev/shm
/dev/xvdf            1014M   33M  982M   4% /mnt

sudo resize2fs /dev/xvdf1 # ext2/ext3/ext4 파일시스템의 경우 이 명령으로 디스크를 확장해 준다.
```