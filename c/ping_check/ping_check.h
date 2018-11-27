#include <stdio.h>
#include <pthread.h>
#include "thpool.h"


/*define */
#define SUCCESS 0
#define ERROR -1

#define STR_LEN 254+1
#define THREAD_CNT 50 /* Thread갯수 */
#define CHECKLIST_FILE_PATH "/home/pi/test/thread/iplist.dat"

typedef struct iplist
{
    char ip[STR_LEN];
}ipList_t;
