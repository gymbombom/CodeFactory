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

    //fileBuffer = malloc(sizeof(char) * ftpFileInfo.fileSize+1);

    if(fileReadData(&ftpFileInfo,&fileBuffer) == ERROR)
    {
        printf("fileReadData() ERROR!!  \n");
        return ERROR;
        
    }

    printf("fileData : %s",fileBuffer);

    return SUCCESS;
}

int getConnectInfo(ftpConnectInfo_t* ftpConnectInfo)
{
    strcpy(ftpConnectInfo->ip,"11111");
    strcpy(ftpConnectInfo->loginID,"iiii");
    strcpy(ftpConnectInfo->loginPassword,"ppppp");

    return SUCCESS;
}


int getFtpFileInfo(ftpFileInfo_t* ftpFileInfo)
{
    strcpy(ftpFileInfo->srcFilePath,"aaaa");
    strcpy(ftpFileInfo->srcFileName,"bbbb");

    strcpy(ftpFileInfo->destFilePath,"ddddd/");
    strcpy(ftpFileInfo->destFileName,"get.dat");

    return SUCCESS;
}

int ftpFileGet(ftpConnectInfo_t* ftpConnectInfo, ftpFileInfo_t* ftpFileInfo)
{
    char src[100+1];
    char dest[100+1];

    netbuf* netBuf = NULL;
    //netbuf* dataBuf = NULL;

    memset(src,0x00,sizeof(src));
    memset(dest,0x00,sizeof(dest));


    /* init libftp */
    FtpInit();

    if(FtpConnect(ftpConnectInfo->ip,&netBuf) != 1)
    {
        printf("FtpConnect() Connection Failed!!! \n");
        return ERROR;
    }

    if(FtpLogin(ftpConnectInfo->loginID,ftpConnectInfo->loginPassword,netBuf) != 1)
    {
        printf("FtpLogin() Connection Failed!!! \n");
        return ERROR;
    }

     strcat(src,ftpFileInfo->srcFilePath);
     strcat(src,ftpFileInfo->srcFileName);

     strcat(dest,ftpFileInfo->destFilePath);
     strcat(dest,ftpFileInfo->destFileName);

     printf("src : %s \n",src);
     printf("dest : %s \n",dest);

    if(FtpSize(src,(&ftpFileInfo->fileSize),FTPLIB_IMAGE,netBuf) != 1)
    {
        printf("FtpSize() Connection Failed!!! \n");
        return ERROR;
    }

    printf("fileSize : %d \n",ftpFileInfo->fileSize);
    
     if(FtpGet(dest,src,FTPLIB_IMAGE,netBuf) != 1 )
     {
         printf("FtpGet() ERROR !!!!  \n");
         return ERROR;
     }

     

    return SUCCESS;
}


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



int fileWriteData()
{
    return SUCCESS;
}


void itoa(int value, char *str, int base) { static char num[]="0123456789abcdefghijklmnopqrstuvwxyz"; char *wstr=str; int sign; if(base<2 || base>35){ *wstr='\0'; return; } if((sign=value) <0) value=-value; do *wstr++=num[value%base]; while(value/=base); if(sign<0) *wstr='\0'; strreverse(str, wstr-1); }

void strreverse(char *begin, char * end) { char aux; while(end>begin) aux=*end, *end--=*begin, *begin++=aux; }

