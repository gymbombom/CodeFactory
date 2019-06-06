# aws(amazon web service) 디스크 볼륨 확장
* 아마존 웹 서비스의 경우 디스크 용량 확장 후 디스크를 제대로 인식하지 못하는 경우가 있다. 그럴땐 수동으로 디스크 볼륨을 확장해 주어야 한다.

### 디스크 포멧 확인 
```shell
    $ df -hl # 디스크 확인
    $ sudo file -s /dev/xvda* # df 로 파일시스템을 찾은 후 disk 파일시스템 확인
    	# ext2/ext3/ext4 파일시스템일 경우 resize2fs 명령을 사용해야 함.
    	# xfs 일경우 xfs_growfs 명령을 사용해야 함.
```

### 디스크 확장이 필요한지 확인 
```shell
$ lsblk
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
$ df -h
Filesystem            Size  Used Avail Use% Mounted on
/dev/xvda1            8.0G  943M  6.9G  12% /
tmpfs                 1.9G     0  1.9G   0% /dev/shm
/dev/xvdf            1014M   33M  982M   4% /mnt

$ sudo resize2fs /dev/xvdf1 # ext2/ext3/ext4 파일시스템의 경우 이 명령으로 디스크를 확장해 준다.
```

### AWS EC2 인스턴스 Centos 일 경우, resize2fs 로 디스크 확장이 안되는 경우도 있음

 ```shell
 root@cateye ~]$ lsblk 
NAME    MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
xvda    202:0    0  20G  0 disk 
└─xvda1 202:1    0   8G  0 part /
[root@cateye ~]# resize2fs /dev/xvda1
resize2fs 1.41.12 (17-May-2010)
The filesystem is already 2096896 blocks long.  Nothing to do!

[root@cateye ~]# resize2fs /dev/xvda
resize2fs 1.41.12 (17-May-2010)
resize2fs: Device or resource busy while trying to open /dev/xvda
Couldn't find valid filesystem superblock.
[root@cateye ~]# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/xvda1      7.8G  943M  6.5G  13% /
tmpfs           938M     0  938M   0% /dev/shm
[root@cateye ~]# fdisk /dev/xvda

WARNING: DOS-compatible mode is deprecated. It's strongly recommended to
         switch off the mode (command 'c') and change display units to
         sectors (command 'u').

Command (m for help): u
Changing display/entry units to sectors

Command (m for help): p

Disk /dev/xvda: 21.5 GB, 21474836480 bytes
255 heads, 63 sectors/track, 2610 cylinders, total 41943040 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00057cbb

    Device Boot      Start         End      Blocks   Id  System
/dev/xvda1   *        2048    16777215     8387584   83  Linux

Command (m for help): d
Selected partition 1

Command (m for help): n
Command action
   e   extended
   p   primary partition (1-4)
p
Partition number (1-4): 1
First sector (63-41943039, default 63): 2048
Last sector, +sectors or +size{K,M,G} (2048-41943039, default 41943039): ENTER
Using default value 41943039

Command (m for help): p

Disk /dev/xvda: 21.5 GB, 21474836480 bytes
255 heads, 63 sectors/track, 2610 cylinders, total 41943040 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00057cbb

    Device Boot      Start         End      Blocks   Id  System
/dev/xvda1            2048    41943039    20970496   83  Linux

Command (m for help): a
Partition number (1-4): 1

Command (m for help): w
The partition table has been altered!

Calling ioctl() to re-read partition table.

WARNING: Re-reading the partition table failed with error 16: Device or resource busy.
The kernel still uses the old table. The new table will be used at
the next reboot or after you run partprobe(8) or kpartx(8)
Syncing disks.

[root@cateye ~]# reboot

Broadcast message from root@cateye

[root@cateye ~]$ lsblk 
NAME    MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
xvda    202:0    0  20G  0 disk 
└─xvda1 202:1    0  20G  0 part /
[root@cateye ~]$ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/xvda1       20G  947M   18G   5% /
tmpfs           938M     0  938M   0% /dev/shm
 ```

 ```shell
 To expand on JD's self-accepted answer, here's exactly what to do:
df -h #print the name of your boot partition
lsblk #show info on all your block devices
You'll see from that output what the name of the disk is of your root partition. For example, you probably see something like this: 
xvde                               202:64   0   32G  0 disk 
└─xvde1                            202:65   0   8G  0 part /
Our goal is to make xvde1 use the whole available space from xvde. Here's how your resize your partition:
fdisk /dev/xvda (the disk name, not your partition) This enters into the fdisk utility.
u #Change the display to sectors
p #Print info
d #Delete the partition
n #New partition
p #Primary partition
1 #Partition number
2048 #First sector
Press Enter to accept the default
p #Print info
a #Toggle the bootable flag
1 #Select partition 1
w #Write table to disk and exit
Now, reboot your instance: reboot
After it comes back do:
resize2fs /dev/xvde1 (the name of your partition, not the block device)
And finally verify the new disk size: df -h
1 출처는 여기
http://stackoverflow.com/questions/26770655/ec2-storage-attached-at-sda-is-dev-xvde1-cannot-resize
 ```
