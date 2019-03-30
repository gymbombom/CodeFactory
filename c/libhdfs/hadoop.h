#include "hdfs.h"
#include <stdio.h>


#define SUCCESS 0
#define ERROR -1


/*
hadoop archive 된 har:// 에 접근할땐 아래와 같이 하여야한다. 

#define PRIMARYIP  "har://hdfs-127.0.0.1:9000/ar/test.har"
#define PRIMARYPORT  0
*/

#define PRIMARYIP  "111.111.111.111"
#define PRIMARYPORT  9000
#define BACKUPIP "222.222.222.222"
#define BACKUPPORT  9000


typedef struct hdfsConnInfo
{
	char primaryIp[50+1];
	int primaryPort;
	char backupIp[50+1];
	int backupPort;
}hdfsConnInfo_t;


typedef struct in
{
	char filePath[20+1];
}in_t;


typedef struct out
{
	long fileSize;
	char* data;
}out_t;
