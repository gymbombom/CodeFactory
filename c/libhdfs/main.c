#include "hdfs.h"
#include <stdio.h>

#define SUCCESS 0
#define ERROR -1

#define PRIMARYIP  "111.222.333.444"
#define PRIMARYPORT  8020
#define BACKUPIP "222.333.444.555"
#define BACKUPPORT  8020

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

int main()
{
	hdfsFS fs = NULL;
	hdfsConnInfo_t connInfo;
	in_t in;

	//memset
	memset(&connInfo, 0x00, sizeof(hdfsConnInfo_t));
	memset(&in, 0x00, sizeof(in_t));

	if(setConInfo(&connInfo) == ERROR)
	{
		printf("setConInfo ERROR \n");
	}

	if(setIn(&in) == ERROR)
	{
		printf("setIn ERROR \n");
	}

	if(hadoopConnection(&fs, &connInfo, &in) == ERROR)
	{
		printf("hadoopConnection ERROR \n");
	}



	return SUCCESS;
}


int setConInfo(hdfsConnInfo_t* connInfo)
{
	strcpy(connInfo->primaryIp,PRIMARYIP);
	connInfo->primaryPort = PRIMARYPORT;

	strcpy(connInfo->backupIp,BACKUPIP);
	connInfo->backupPort = BACKUPPORT;

	return SUCCESS;
}

int setIn(in_t* in)
{
	strcpy(in->filePath,"/tmp/hello.txt");
	return SUCCESS;
}


int hadoopConnection(hdfsFS* fs, hdfsConnInfo_t *connInfo, in_t* in)
{
	int exists;

	*fs = hdfsConnect(connInfo->primaryIp, connInfo->primaryPort);

	if(!*fs)
	{
		fprintf(stderr, "Oops! Failed to connect to primaty node hdfs!\n");
		return ERROR;
	}

	exists = hdfsExists(*fs, in->filePath);

	if(exists > -1)
	{
		printf("primary node file exists \n");
		return SUCCESS;
	}else
	{
		printf("primary node file not  exists reconnect backup node \n");
		*fs = hdfsConnect(connInfo->backupIp, connInfo->backupPort);

		if(!*fs)
		{
			fprintf(stderr, "Oops! Failed to connect to backup node hdfs!\n");
			return ERROR;
		}

		exists = hdfsExists(*fs, in->filePath);
		if(exists > -1)
		{
			printf("backup node file exists \n");
			return SUCCESS;
		}else
		{
			printf("backup node file not exists \n");
			return ERROR;
		}
	}


	return SUCCESS;
}

