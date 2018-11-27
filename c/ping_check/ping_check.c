#include "ping_check.h"



void pingChk(char* ip)
{
    printf("ip2 : %s \n", ip);
    printf("Thread #%u working on task1\n", (int)pthread_self());
    return SUCCESS;
}


int lineCount(char* fileName)
{
    char buf[STR_LEN];
    int len;
    int count = 0; // 라인수를 세어 주는 변수
    
    FILE *fp = fopen(fileName,"rt"); // 파일 읽기
 
    while(1)
    {
        fgets(buf,STR_LEN,fp); // fgets함수는 한줄 읽고 넘어간다(파일포인터는 다음줄을 가리킴)
        len  = strlen(buf); // buf의 길이수를 센다
   
        if(len==0)  // 라인 수가 0이면 브레이크
        break;
  
        count++; // 라인수 증가
        buf[0]= '\0'; // 버퍼 초기화
    }

    fclose(fp);

    return count;
}

char* rtrim(char* s) {
  char t[MAX_STR_LEN];
  char *end;

  // Visual C 2003 이하에서는
   strcpy(t, s);
  // 이렇게 해야 함
  //strcpy_s(t, s); // 이것은 Visual C 2005용
  end = t + strlen(t) - 1;
  while (end != t && isspace(*end))
    end--;
  *(end + 1) = '\0';
  s = t;

  return s;
}

int main()
{
     FILE *pFile = NULL;
     int lineCnt = 0;
     int i = 0;
     ipList_t* ipList = NULL;

    /*thread pool 갯수 지정 */
    threadpool thpool = thpool_init(THREAD_CNT);

    /* 읽을 파일의 라인수를 체크 */
    lineCnt = lineCount(CHECKLIST_FILE_PATH);

    printf("lineCnt :[%d] \n",lineCnt);

    ipList = (ipList_t*)malloc(sizeof(ipList_t)*(lineCnt+10));
    memset(ipList,0x00, sizeof(ipList_t)*(lineCnt+10));
   
   
    pFile = fopen( CHECKLIST_FILE_PATH, "r" );
    
    if( pFile != NULL )
    {
        char strTemp[255];
        char *pStr;

        while( !feof( pFile ) )
        {
            char* ss = NULL;
            pStr = fgets( strTemp, sizeof(strTemp), pFile ); 
			
            printf( "pStr:[%s] \n", pStr );
            printf( "strTemp:[%s] \n", strTemp );

            //thpool_add_work(thpool, (void*)pingChk, &s);
            ss = rtrim(strTemp);
            strncpy((ipList+i)->ip, ss, STR_LEN);
            i++;
        }

        fclose( pFile );
    }

    for(i =0;i < lineCnt;i++)
    {
        printf("ipList[%d]:[%s] \n",i,(ipList+i)->ip);
        thpool_add_work(thpool, (void*)pingChk, (ipList+i)->ip);
    }

   thpool_wait(thpool);
    
   thpool_destroy(thpool);



#if 0
    pthread_t p_thread[THREAD_CNT]; 
    int thr_id; //쓰레드ID
    int status;

    //char p1[] = "thread_1";   // 1번 쓰레드 이름
    //char p2[] = "thread_2";   // 2번 쓰레드 이름
    //char pM[] = "thread_m";   // 메인 쓰레드 이름
 
        // 파일 읽기
        if(fRead() == ERROR)
        {
            printf("FRead Error \n");        }
        Fread();





    sleep(2);  // 2초 대기후 쓰레드 생성
 


    sys

    // ① 1번 쓰레드 생성
    // 쓰레드 생성시 함수는 t_function
    // t_function 의 매개변수로 p1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)p1);

    // pthread_create() 으로 성공적으로 쓰레드가 생성되면 0 이 리턴됩니다
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
 
    // ② 2번 쓰레드 생성
    thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
 
    // ③ main() 함수에서도 쓰레드에서 돌아가고 있는 동일한 함수 실행
    //t_function((void *)pM);
 
    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
 
    printf("언제 종료 될까요?\n");
 #endif

    return SUCCESS;
}


#if 0
int fRead()
{
    FILE *pFile = NULL;
    pFile = fopen( "/filePath/", "r" );

    if( pFile != NULL )
    {
        char strTemp[255];
        char *pStr;

        while( !feof( pFile ) )
        {
            pStr = fgets( strTemp, sizeof(strTemp), pFile );
			printf( "%s", strTemp );
			printf( "%s", pStr );
        }

    }



    return SUCCESS;
}
#endif