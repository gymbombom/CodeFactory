#include <stdio.h>
#include <string.h>

char* ltrim(char *s);

#if 0
int main()
{
    char* realStr = "aaa   bbb ccc ddd";
    char tempStr[50+1];
    char* delimeter = " ";
    int i = 0;

    strcpy(tempStr, realStr);


    for(i =0; i < 2;i ++)
    {
        char *ptr = NULL;

        ptr = strstr(tempStr,delimeter);

        if(ptr != NULL)
        {
            strcpy(tempStr, ptr+strlen(delimeter));
            ltrim(tempStr);
        }
    }


    printf("STR : [%s] \n", tempStr);
    
    return 0;
}
#endif

int main()
{
    char* realStr = "aaa   bbb ccc ddd";
    char tempstr[50+1];
    int i = 0;
    int ch;
    int spaceCnt = 0;

    strncpy(tempstr,realStr,50+1);

    for(i = 0; i < strlen(realStr); i++ )
    {
        if(spaceCnt >= 2)
        {
            break;
        }

        ch = realStr[i];

        if(ch == 0)
        {
            break;
        }
        
        if(isspace(ch) )
        {
            strncpy(tempstr, realStr+i,50+1);
            spaceCnt++;
            printf("tempstr : [%s] \n", tempstr);
        }

    }

}






char* ltrim(char *s) {
  char* begin;
  begin = s;

  while (*begin != '\0') {
    if (isspace(*begin))
      begin++;
    else {
      s = begin;
      break;
    }
  }

  return s;
}
