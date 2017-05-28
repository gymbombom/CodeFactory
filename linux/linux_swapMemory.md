#리눅스 스왑(swap) 메모리 늘리기
###1.swap메모리 확인

```shell
	swapon –s, free 
	또는
	cat /proc/swaps
```


###2. swap 파일 생성

```shell
dd if=/dev/zero of=<filePath> bs=1024 count=<fileSize>
ex) dd if=/dev/zero of=/home/swapfile bs=1024 count=100000 # 1G 파일사이즈의 /home/swapfile 위치에 스왑파일 생성
```

###3.swapfile 로 포멧
```shell
mkswap <fileName> # 스왑파일 형식으로 포멧 
ex)mkswap /home/swapfile 
```

###4.swap파일로 활성화
```shell
swapon <fileName> #스왑파일 활성화
swapon /home/swapfile
```

###재부팅시에도 swap 파일 활성화
```shell
echo "swapon /home/swapfile" >> /etc/rc.d/rc.local #  "swapon /home/swapfile" 를 etc/rc.d/rc.local내용 추가
# 위의 내용을 추가하면 리부팅시에도 스왑파일이 추가된다.
```