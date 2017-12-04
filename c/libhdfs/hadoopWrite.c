#include "hadoop.h"

static int setConInfo(hdfsConnInfo_t* connInfo);
static int setIn(in_t* in);
static int hadoopConnection(hdfsFS* fs, hdfsConnInfo_t *connInfo);

int hadoopWrite()
{
    hdfsFS fs = NULL;
	hdfsConnInfo_t connInfo;
	in_t in;
	out_t out;
	char* buffer = NULL;

    //메모리 초기화
	memset(&connInfo, 0x00, sizeof(hdfsConnInfo_t));
	memset(&in, 0x00, sizeof(in_t));
	memset(&out, 0x00, sizeof(out_t));
	memset(&fs,0x00, sizeof(hdfsFS));

    /* 접속정보 설정 */
	if(setConInfo(&connInfo) == ERROR)
	{
		printf("setConInfo() ERROR \n");
		return ERROR;
	}

    /* 입력정보 설정 */
	if(setIn(&in) == ERROR)
	{
		printf("setIn() ERROR \n");
		return ERROR;
	}

    /* hadoop Connect */
	if(hadoopConnection(&fs, &connInfo) == ERROR)
	{
		printf("hadoopConnection() ERROR \n");
		return ERROR;
	}

    if(hadoopWriteFile(&fs, &in) == ERROR)
    {
        printf("hadoopWriteFile() ERROR \n");
		return ERROR;
    }

    return SUCCESS;
}

static int setConInfo(hdfsConnInfo_t* connInfo)
{
	strcpy(connInfo->primaryIp,PRIMARYIP);
	connInfo->primaryPort = PRIMARYPORT;

	strcpy(connInfo->backupIp,BACKUPIP);
	connInfo->backupPort = BACKUPPORT;

	return SUCCESS;
}

static int setIn(in_t* in)
{
	strcpy(in->filePath,"/hello.dat");
	return SUCCESS;
}

static int hadoopConnection(hdfsFS* fs, hdfsConnInfo_t *connInfo)
{
	*fs = hdfsConnect(connInfo->primaryIp, connInfo->primaryPort);

	if(!*fs)
	{
		fprintf(stderr, "Oops! Failed to connect to primary node hdfs!\n");
		return ERROR;
	}

	return SUCCESS;
}

int hadoopWriteFile(hdfsFS* fs, in_t* in)
{
    hdfsFile writeFile = hdfsOpenFile(*fs, in->filePath, O_WRONLY|O_CREAT, 0, 0, 0);
    if(!writeFile) 
    {
        fprintf(stderr, "Failed to open %s for writing!\n", in->filePath);
        return ERROR;
    }
    
    fprintf(stderr, "Opened %s for writing successfully...\n", in->filePath);

    char* buffer = "Hello, World!";
    tSize num_written_bytes = hdfsWrite(*fs, writeFile, (void*)buffer, strlen(buffer)+1);
    fprintf(stderr, "Wrote %d bytes\n", num_written_bytes);

    tOffset currentPos = -1;
    if ((currentPos = hdfsTell(*fs, writeFile)) == -1) 
    {
        fprintf(stderr, 
                "Failed to get current file position correctly! Got %ld!\n",
                currentPos);
        return ERROR;
    }
    fprintf(stderr, "Current position: %ld\n", currentPos);

    if (hdfsFlush(*fs, writeFile)) 
    {
        fprintf(stderr, "Failed to 'flush' %s\n", in->filePath); 
        return ERROR;
    }
    fprintf(stderr, "Flushed %s successfully!\n", in->filePath); 

    hdfsCloseFile(*fs, writeFile);

    /* hdfsDisconnect */
    hdfsDisconnect(*fs);

    return SUCCESS;
}
