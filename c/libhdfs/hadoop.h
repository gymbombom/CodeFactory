#include "hdfs.h"
#include <stdio.h>


#define SUCCESS 0
#define ERROR -1

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
