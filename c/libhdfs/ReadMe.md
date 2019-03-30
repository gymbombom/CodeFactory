# libhdfs (hadoop C api)
> hadoop 2.7.3  32 bit library



```shell

--hdfs file delete
hdfs dfs -rm /test1/test1.txt;
hdfs dfs -rm /test2/test2.txt;
hdfs dfs -rm /test3/test3.txt;


hdfs dfs -rmr /ar/test.har;



--hdfs put file command 
hdfs dfs -put ./test1.txt /test1/test1.txt;
hdfs dfs -put ./test2.txt /test2/test2.txt;
hdfs dfs -put ./test3.txt /test3/test3.txt;



--hadoop archive command 
hadoop archive -archiveName test.har -p / test1/test1.txt test2/test2.txt test3/test3.txt  /ar



-- hadoop archive file print
hdfs dfs -text har:///ar/test.har/test1/test1.txt;

```

