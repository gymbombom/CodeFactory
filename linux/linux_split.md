#Linux split 사용법  
[split 욥션설명](https://opentutorials.org/module/782/6083)

```shell
   split -l <lineCount> <fileName>  #파일을 라인별로 나눔
   ex) split  -l 1000 test.log  #test.log 파일을 1000줄씩 나눔

   split -b <size> <fileName> #파일을 사이즈 별로 나눔
   ex) split  -b 10M test.log  #test.log 파일을 10m씩 나눔

   split --suffix-length=5 # split 파일명 접미사 증가시키기
```