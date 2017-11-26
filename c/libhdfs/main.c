#include "hdfs.h"
#include <stdio.h>

#define SUCCESS 0 
#define ERROR -1  

#define PRIMARYIP  "11.111.111.111"
#define PRIMARYPORT  8020  		
#define BACKUPIP "22.222.222.222"
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


typedef struct out
{
	long fileSize;
	char* data;
}out_t;


int main()
{
	hdfsFS fs = NULL;
	hdfsConnInfo_t connInfo;
	in_t in;
	out_t out;
	char* buffer = NULL;

	//memset
	memset(&connInfo, 0x00, sizeof(hdfsConnInfo_t));
	memset(&in, 0x00, sizeof(in_t));
	memset(&out, 0x00, sizeof(out_t));

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

	if(getHadoopFileInfo(&fs, &in, &out)== ERROR)
	{
		printf(" getHadoopFileInfo() ERROR \n");
	}

	/* Buffer Memory Allocate */
	buffer = malloc(sizeof(char) * out.fileSize);


	if(hadoopfileget(&fs, &in , &out, buffer) == ERROR)
	{
		printf("hadoopfileget() ERROR \n");

	}

	/* out 데이터를 Hadoop 에서 읽은 버퍼데이터의 포인터를 할당 */
	out.data = buffer;


	if(printOut(&out) == ERROR)
	{
		printf("printOut() ERROR \n");
	}

	if(__testFileCreate(&out) == ERROR)
	{
	       printf("printOut() ERROR \n");
	}



	/* memory Free */
	free(buffer);


	return SUCCESS;
}


int setConInfo(hdfsConnInfo_t* connInfo)
{

#if 0  //테스트로 막음
	strcpy(connInfo->primaryIp,PRIMARYIP);
	connInfo->primaryPort = PRIMARYPORT;

	strcpy(connInfo->backupIp,BACKUPIP);
	connInfo->backupPort = BACKUPPORT;
#endif


	strcpy(connInfo->primaryIp,BACKUPIP);
	connInfo->primaryPort = BACKUPPORT;

	strcpy(connInfo->backupIp,PRIMARYIP);
	connInfo->backupPort = PRIMARYPORT;


	return SUCCESS;
}

int setIn(in_t* in)
{
	strcpy(in->filePath,"/lik.dat");
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


int hadoopfileget(hdfsFS* fs, in_t* in, out_t* out, char* buffer)
{

    tSize bufferSize = out->fileSize;

    hdfsFile readFile = hdfsOpenFile(*fs, in->filePath, O_RDONLY, bufferSize, 0, 0);
    if (!readFile)
    {
	fprintf(stderr, "Failed to open %s for writing!\n", in->filePath);
	exit(-2);
    }


    fprintf(stderr, "hdfsAvailable: %d\n", hdfsAvailable(*fs, readFile));

    tOffset seekPos = 1;
    if(hdfsSeek(*fs, readFile, seekPos)) {
        fprintf(stderr, "Failed to seek %s for reading!\n", in->filePath);
        exit(-1);
    }

    tOffset currentPos = -1;
    if((currentPos = hdfsTell(*fs, readFile)) != seekPos) {
        fprintf(stderr,
                "Failed to get current file position correctly! Got %ld!\n",
                currentPos);
        exit(-1);
    }
    fprintf(stderr, "Current position: %ld\n", currentPos);

    printf(" buffer size : %d \n",out->fileSize);

    tSize num_read_bytes = hdfsRead(*fs, readFile, (void*)buffer,
            out->fileSize);
    fprintf(stderr, "Read following %d bytes: \n",num_read_bytes);
    //fprintf(stderr, "Read following %d bytes:\n%s\n",
    //        num_read_bytes, buffer);

    num_read_bytes = hdfsPread(*fs, readFile, 0, (void*)buffer,
            out->fileSize);

    fprintf(stderr, "Read following %d bytes: \n",num_read_bytes);


    //fprintf(stderr, "Read following %d bytes:\n%s\n",
     //       num_read_bytes, buffer);

    /* close File */
    hdfsCloseFile(*fs, readFile);


#if 0
	// data to be written to the file
    if(buffer == NULL) {
	return -2;
    }
	// read from the file
    tSize curSize = bufferSize;
    printf("curSize : %ld \n",curSize);
    printf("curSize : %ld \n",bufferSize);

     for (; curSize == bufferSize;) {
        curSize = hdfsRead(*fs, readFile, (void*)buffer, curSize);
    }

	hdfsCloseFile(*fs, readFile);
	hdfsDisconnect(*fs);
#endif


#if 0
 	/*FileInfomation Get */
 	hdfsFileInfo *fileInfo = NULL;

 	if((fileInfo = hdfsGetPathInfo(*fs, in->filePath)) != NULL)
 	 {
            fprintf(stderr, "hdfsGetPathInfo - SUCCESS!\n");
            fprintf(stderr, "Name: %s \n", fileInfo->mName);
            fprintf(stderr, "Type: %c \n", (char)(fileInfo->mKind));
            fprintf(stderr, "Replication: %d \n", fileInfo->mReplication);
            fprintf(stderr, "BlockSize: %ld \n", fileInfo->mBlockSize);
            fprintf(stderr, "Size: %ld \n", fileInfo->mSize);
            fprintf(stderr, "LastMod: %s \n", ctime(&fileInfo->mLastMod));
            fprintf(stderr, "Owner: %s \n", fileInfo->mOwner);
            fprintf(stderr, "Group: %s \n", fileInfo->mGroup);

            fprintf(stderr, "long Modify Date : %ld \n", fileInfo->mLastMod);
            //char permissions[10];
            //permission_disp(fileInfo->mPermissions, permissions);
            //fprintf(stderr, "Permissions: %d (%s)\n", fileInfo->mPermissions, permissions);

            out->fileSize = fileInfo->mSize;
            hdfsFreeFileInfo(fileInfo, 1);
     }


   	tSize bufferSize = out->fileSize;
 #endif

#if 0
   	tSize bufferSize = 15;
    hdfsFile readFile = hdfsOpenFile(*fs, in->filePath, O_RDONLY, bufferSize, 0, 0);
	if (!readFile) {
		fprintf(stderr, "Failed to open %s for writing!\n", in->filePath);
		exit(-2);
    }
	// data to be written to the file
	char* buffer = malloc(sizeof(char) * bufferSize);
	if(buffer == NULL) {
		return -2;
    }
	// read from the file
    tSize curSize = bufferSize;
	for (; curSize == bufferSize;) {
        curSize = hdfsRead(*fs, readFile, (void*)buffer, curSize);
    }
	printf("%s",buffer);
	free(buffer);
	hdfsCloseFile(*fs, readFile);
	hdfsDisconnect(*fs);
#endif

#if 0
     	/* hdfs File Read */
     	hdfsFile readFile = hdfsOpenFile(*fs, in->filePath, O_RDONLY, 0, 0, 0);
     	if (!readFile) {
           fprintf(stderr, "Failed to open %s for reading!\n", in->filePath);
           exit(-1);
        }


        fprintf(stderr, "hdfsAvailable: %d\n", hdfsAvailable(*fs, readFile));

        tOffset seekPos = 1;
        if(hdfsSeek(*fs, readFile, seekPos)) {
            fprintf(stderr, "Failed to seek %s for reading!\n", in->filePath);
            exit(-1);
        }

        tOffset currentPos = -1;
        if((currentPos = hdfsTell(*fs, readFile)) != seekPos) {
            fprintf(stderr,
                    "Failed to get current file position correctly! Got %ld!\n",
                    currentPos);
            exit(-1);
        }
        fprintf(stderr, "Current position: %ld\n", currentPos);

        static char buffer[32];
        tSize num_read_bytes = hdfsRead(*fs, readFile, (void*)buffer,
                sizeof(buffer));
        fprintf(stderr, "Read following %d bytes:\n%s\n",
                num_read_bytes, buffer);

        num_read_bytes = hdfsPread(*fs, readFile, 0, (void*)buffer,
                sizeof(buffer));
        fprintf(stderr, "Read following %d bytes:\n%s\n",
                num_read_bytes, buffer);

        /* close File */
        hdfsCloseFile(*fs, readFile);
#endif

	return SUCCESS;
}


int printOut(out_t* out)
{
	printf("fileSize : %ld \n ",out->fileSize);
	//printf("Buffer Data \n");
	//printf("data : %s \n", out->data);

	return SUCCESS;
}


int getHadoopFileInfo(hdfsFS* fs, in_t* in, out_t* out)
{
	 /*FileInfomation Get */
 	hdfsFileInfo *fileInfo = NULL;

 	if((fileInfo = hdfsGetPathInfo(*fs, in->filePath)) != NULL)
 	 {
            fprintf(stderr, "hdfsGetPathInfo - SUCCESS!\n");
            fprintf(stderr, "Name: %s \n", fileInfo->mName);
            fprintf(stderr, "Type: %c \n", (char)(fileInfo->mKind));
            fprintf(stderr, "Replication: %d \n", fileInfo->mReplication);
            fprintf(stderr, "BlockSize: %ld \n", fileInfo->mBlockSize);
            fprintf(stderr, "Size: %ld \n", fileInfo->mSize);
            fprintf(stderr, "LastMod: %s \n", ctime(&fileInfo->mLastMod));
            fprintf(stderr, "Owner: %s \n", fileInfo->mOwner);
            fprintf(stderr, "Group: %s \n", fileInfo->mGroup);

            fprintf(stderr, "long Modify Date : %ld \n", fileInfo->mLastMod);
            //char permissions[10];
            //permission_disp(fileInfo->mPermissions, permissions);
            //fprintf(stderr, "Permissions: %d (%s)\n", fileInfo->mPermissions, permissions);

            out->fileSize = fileInfo->mSize;
            hdfsFreeFileInfo(fileInfo, 1);
     }
	 return SUCCESS;
}


int __testFileCreate(out_t* out)
{

    FILE *fp = fopen("/test.dat", "w");    // hello.txt 파일을 쓰기 모드(w)로 열기.

    fputs(out->data, fp);   // 파일에 문자열 저장

    fclose(fp);    // 파일 포인터 닫기

    return SUCCESS;
}

