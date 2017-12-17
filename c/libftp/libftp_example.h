#include "libftp.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1



typedef struct ftpConnectInfo
{
    char ip[50+1];
    char loginID[50+1];
    char loginPassword[50+1];  
}ftpConnectInfo_t;


typedef struct ftpFileInfo
{
    char srcFilePath[50+1];
    char srcFileName[50+1];

    char destFilePath[50+1];
    char destFileName[50+1];
    int fileSize;
}ftpFileInfo_t;
