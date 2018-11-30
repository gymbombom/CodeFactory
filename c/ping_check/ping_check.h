#include <stdio.h>
#include <pthread.h>
#include <errno.h> 
#include "thpool.h"


/*define */
#define SUCCESS 0
#define ERROR -1

#define STR_LEN 254+1
#define COMMAND_LEN 1000+1
#define THREAD_CNT 200 /* Thread갯수 */
#define CHECKLIST_FILE_PATH "/home/pi/test/thread/iplist.dat"

typedef struct iplist
{
    char ip[STR_LEN];
}ipList_t;
