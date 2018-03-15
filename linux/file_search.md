# 파일 내부 문자열 검색

### 파일 내부 문자열 검색

```shell
  $ find   ./ -name "*" -exec grep -r -n -i keword {} + 
  또는
  $ find ./ -name "*" | xargs grep -r -n -i  keword 
```