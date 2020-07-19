#include<header.h>

void library_check(void)
{
	int ret=0;
	ret=access("/root/Biomatiques/BiomatiquesRDS",F_OK);

	printf("**************************RET VALUE Is %d\n",ret);


	memset(module.LIB_BIO,0,10);
	if(!ret)
	{
		sprintf(module.LIB_BIO,"OK");
		fprintf(stdout,"LIBRARY EXISTS"  );
	}
	else 
	{
		sprintf(module.LIB_BIO,"ERROR");
		fprintf(stdout,"LIBRARY NOT EXISTS");
	}
	return;
}
