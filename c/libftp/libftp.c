#include "libftp_example.h"


int main()
{
    ftpConnectInfo_t ftpConnectInfo;
    ftpFileInfo_t ftpFileInfo;
    char* fileBuffer = NULL;

    /* memset */
    memset(&ftpConnectInfo,0x00,sizeof(ftpConnectInfo_t));
    memset(&ftpFileInfo,0x00,sizeof(ftpFileInfo_t));

    if(getConnectInfo(&ftpConnectInfo) == ERROR)
    {
        printf("getConnectInfo() ERROR!!  \n");
        return ERROR;
    }

    if(getFtpFileInfo(&ftpFileInfo)== ERROR)
    {
        printf("getFtpFileInfo() ERROR!!  \n");
        return ERROR;
    }

    if(ftpFileGet(&ftpConnectInfo,&ftpFileInfo) == ERROR)
    {
        printf("ftpFileGet() ERROR!!  \n");
        return ERROR;
    }

    if(ftpFilePut(&ftpConnectInfo,&ftpFileInfo) == ERROR)
    {
        printf("ftpFilePut() ERROR!!  \n");
        return ERROR;
    }

    //fileBuffer = malloc(sizeof(char) * ftpFileInfo.fileSize+1);

#if 0
    if(fileReadData(&ftpFileInfo,&fileBuffer) == ERROR)
    {
        printf("fileReadData() ERROR!!  \n");
        return ERROR;
        
    }
#endif

#if 0
    printf("fileData : %s",fileBuffer);
#endif

    return SUCCESS;
}

int getConnectInfo(ftpConnectInfo_t* ftpConnectInfo)
{
    /*Get Ftp Server Info */
    strcpy(ftpConnectInfo->getFtpIp,GET_FTP_IP);
    strcpy(ftpConnectInfo->getFtpLoginId,GET_FTP_LOGIN_ID);
    strcpy(ftpConnectInfo->getFtpLoginPassword,GET_FTP_LOGIN_PSWD);

     /*Put Ftp Server Info */
    strcpy(ftpConnectInfo->putFtpIp,PUT_FTP_IP);
    strcpy(ftpConnectInfo->putFtpLoginId,PUT_FTP_LOGIN_ID);
    strcpy(ftpConnectInfo->putFtpLoginPassword,PUT_FTP_LOGIN_PSWD);

    return SUCCESS;
}


int getFtpFileInfo(ftpFileInfo_t* ftpFileInfo)
{
    /* getFtp */
    strcpy(ftpFileInfo->getFtpSrcFilePath,GET_FTP_SRC_FILEPATH);
    strcpy(ftpFileInfo->getFtpSrcFileName,GET_FTP_SRC_FILENAME);
    strcpy(ftpFileInfo->getFtpDestFilePath,GET_FTP_DEST_FILEPATH);
    strcpy(ftpFileInfo->getFtpDestFileName,GET_FTP_DEST_FILENAME);

    /*putFtp */
    strcpy(ftpFileInfo->putFtpSrcFilePath,PUT_FTP_SRC_FILEPATH);
    strcpy(ftpFileInfo->putFtpSrcFileName,PUT_FTP_SRC_FILENAME);
    strcpy(ftpFileInfo->putFtpDestFilePath,PUT_FTP_DEST_FILEPATH);
    strcpy(ftpFileInfo->putFtpDestFileName,PUT_FTP_DEST_FILENAME);

    return SUCCESS;
}

int ftpFileGet(ftpConnectInfo_t* ftpConnectInfo, ftpFileInfo_t* ftpFileInfo)
{
    char src[100+1];
    char dest[100+1];

    netbuf* netBuf = NULL;

    memset(dest,0x00,sizeof(dest));
    memset(src,0x00,sizeof(src));
   
    /* init libftp */
    FtpInit();

    if(FtpConnect(ftpConnectInfo->getFtpIp,&netBuf) != 1)
    {
        printf("FtpConnect() Connection Failed!!! \n");
        return ERROR;
    }

    if(FtpLogin(ftpConnectInfo->getFtpLoginId,ftpConnectInfo->getFtpLoginPassword,netBuf) != 1)
    {
        FtpQuit(netBuf);
        printf("FtpLogin() Failed!!! \n");
        return ERROR;
    }

    sprintf(dest,"%s/%s",ftpFileInfo->getFtpDestFilePath, ftpFileInfo->getFtpDestFileName);
    sprintf(src,"%s/%s",ftpFileInfo->getFtpSrcFilePath, ftpFileInfo->getFtpSrcFileName);

     printf("ftpFileGet() src : %s \n",src);
     printf("ftpFileGet() dest : %s \n",dest);

    if(FtpSize(dest,(&ftpFileInfo->fileSize),FTPLIB_IMAGE,netBuf) != 1)
    {
        FtpQuit(netBuf);
        printf("FtpSize() Failed!!! \n");
        return ERROR;
    }

    printf("ftpGet() fileSize : %d \n",ftpFileInfo->fileSize);
    
     if(FtpGet(src,dest,FTPLIB_IMAGE,netBuf) != 1 )
     {
         FtpQuit(netBuf);
         printf("FtpGet() ERROR !!!!  \n");
         return ERROR;
     }

     FtpClose(netBuf);

    return SUCCESS;
}


int ftpFilePut(ftpConnectInfo_t* ftpConnectInfo, ftpFileInfo_t* ftpFileInfo)
{
    char src[100+1];
    char dest[100+1];

    netbuf* netBuf = NULL;

    memset(dest,0x00,sizeof(dest));
    memset(src,0x00,sizeof(src));

    FtpInit();

    if(FtpConnect(ftpConnectInfo->putFtpIp,&netBuf) != 1)
    {
        printf("FtpConnect() Connection Failed!!! \n");
        return ERROR;
    }

    if(FtpLogin(ftpConnectInfo->putFtpLoginId,ftpConnectInfo->putFtpLoginPassword,netBuf) != 1)
    {
        printf("FtpLogin() Failed!!! \n");
        return ERROR;
    }

    sprintf(dest,"%s/%s",ftpFileInfo->putFtpDestFilePath, ftpFileInfo->putFtpDestFileName);
    sprintf(src,"%s/%s",ftpFileInfo->putFtpSrcFilePath, ftpFileInfo->putFtpSrcFileName);

    printf("ftpFilePut src : %s \n",src);
    printf("ftpFilePut dest : %s \n",dest);

    if(FtpPut(src,dest,FTPLIB_IMAGE, netBuf) != 1)
    {
        printf("FtpPut() Failed!!! \n");
        return ERROR;
    }

    FtpClose(netBuf);

    return SUCCESS;
}


#if 0
int fileReadData(ftpFileInfo_t* ftpFileInfo, char** fileBuffer)
{
    FILE *fp = NULL;
    char fileName[100+1];
    long int file_length;
    int *px;
    int i;
    char temp;

    strcat(fileName,ftpFileInfo->destFilePath);
    strcat(fileName,ftpFileInfo->destFileName);

    
/*
    if(fopen_s(&fp, fileName, "rb") != 0) 
    {
        printf("Connot Open file \n");
        return ERROR;
    }
*/
  
    fp = fopen(fileName, "rb");

    fseek(fp, 0L, SEEK_END);
    file_length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    px = (int*)malloc(file_length);
    *fileBuffer = malloc(sizeof(char) * file_length+1);

    if(px == NULL)
    {
        printf("malloc Falied !! \n");
        return ERROR;
    }

    fread(px, sizeof(int),100,fp);
    fclose(fp);

    for(i =0; i < file_length / sizeof(int); i++)
    {
        //memset(&temp,0x00,sizeof(temp));
        printf("%d |",px[i]);
    }

    free(px);

    return SUCCESS;
 
 #if 0
 char *buffer;
    int size;
    int count;
    char fileName[100+1];

    strcat(fileName,ftpFileInfo->destFilePath);
    strcat(fileName,ftpFileInfo->destFileName);

    FILE *fp = fopen(fileName, "r");    // hello.txt 파일을 읽기 모드(r)로 열기.
                                           // 파일 포인터를 반환

    fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
    size = ftell(fp);          // 파일 포인터의 현재 위치를 얻음

    buffer = malloc(size + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
    memset(buffer, 0, size + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화

    fseek(fp, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
    count = fread(buffer, size, 1, fp);    // hello.txt에서 파일 크기만큼 값을 읽음

    printf("%s size: %d, count: %d\n", buffer, size, count);
                    // Hello world! size: 13, count: 1: 파일의 내용, 파일 크기, 읽은 횟수 출력

    fclose(fp);     // 파일 포인터 닫기

    free(buffer);   // 동적 메모리 해제

    return 0;
#endif


}
#endif

void itoa(int value, char *str, int base) { static char num[]="0123456789abcdefghijklmnopqrstuvwxyz"; char *wstr=str; int sign; if(base<2 || base>35){ *wstr='\0'; return; } if((sign=value) <0) value=-value; do *wstr++=num[value%base]; while(value/=base); if(sign<0) *wstr='\0'; strreverse(str, wstr-1); }

void strreverse(char *begin, char * end) { char aux; while(end>begin) aux=*end, *end--=*begin, *begin++=aux; }
