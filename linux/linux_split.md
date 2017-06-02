#Linux split 사용법

```shell
   split -l <lineCount> <fileName>  #파일을 라인별로 나눔
   ex) split  -l 1000 test.log  #test.log 파일을 1000줄씩 나눔

   split -b <size> <fileName> #파일을 사이즈 별로 나눔
   ex) split  -b 10M test.log  #test.log 파일을 10m씩 나눔
```