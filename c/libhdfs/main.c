#include "hadoop.h"

int main()
{

#if 0
	if(hadoopReadFile() == ERROR)
	{
		printf("hadoopReadFile() ERROR \n");
		return ERROR;
	}
#endif

	if(hadoopWrite() == ERROR)
	{
		printf("hadoopWrite() ERROR \n");
		return ERROR;
	}

	return SUCCESS;
}
