#include "libftp.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1

#define GET_FTP_IP ""
#define GET_FTP_LOGIN_ID ""
#define GET_FTP_LOGIN_PSWD ""
#define GET_FTP_SRC_FILEPATH ""
#define GET_FTP_SRC_FILENAME ""
#define GET_FTP_DEST_FILEPATH ""
#define GET_FTP_DEST_FILENAME ""


#define PUT_FTP_IP ""
#define PUT_FTP_LOGIN_ID ""
#define PUT_FTP_LOGIN_PSWD ""
#define PUT_FTP_SRC_FILEPATH ""
#define PUT_FTP_SRC_FILENAME ""
#define PUT_FTP_DEST_FILEPATH ""
#define PUT_FTP_DEST_FILENAME ""


typedef struct ftpConnectInfo
{
    char getFtpIp[50+1];
    char getFtpLoginId[50+1];
    char getFtpLoginPassword[50+1];  

    char putFtpIp[50+1];
    char putFtpLoginId[50+1];
    char putFtpLoginPassword[50+1];  
}ftpConnectInfo_t;


typedef struct ftpFileInfo
{
    char getFtpSrcFilePath[50+1];
    char getFtpSrcFileName[50+1];
    char getFtpDestFilePath[50+1];
    char getFtpDestFileName[50+1];

    char putFtpSrcFilePath[50+1];
    char putFtpSrcFileName[50+1];
    char putFtpDestFilePath[50+1];
    char putFtpDestFileName[50+1];
    
    int fileSize;
}ftpFileInfo_t;


int getConnectInfo(ftpConnectInfo_t* ftpConnectInfo);
int getFtpFileInfo(ftpFileInfo_t* ftpFileInfo);
int ftpFileGet(ftpConnectInfo_t* ftpConnectInfo, ftpFileInfo_t* ftpFileInfo);
int ftpFilePut(ftpConnectInfo_t* ftpConnectInfo, ftpFileInfo_t* ftpFileInfo);
void itoa(int value, char *str, int base);
void strreverse(char *begin, char * end);