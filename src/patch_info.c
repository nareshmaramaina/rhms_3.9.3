#include <header.h>


int patch_ver()
{
	FILE *fp = NULL;

	char *line=NULL,*str=NULL;

	size_t len=20;
	char buff[20]="";
	fp = fopen("/etc/visiontek_release","r");
	if(fp == NULL)
	{
		fprintf(stdout,"Patch Details Unavailable\n");
		sprintf(module.PatchVersion,"0");
		return -1;
	}
	while((getline(&line, &len, fp)) > 0)
	{
		if((str = (char *)strstr(line,"PATCH_VERSION=")) != NULL)
		{

			strcpy(buff,str+14);
			if(buff[strlen(buff)-1] == '\n')
				buff[strlen(buff)-1]='\0';

			printf("PATCH_VERSION=%s\n",buff);
			memset(module.PatchVersion,0,sizeof(module.PatchVersion));
			sprintf(module.PatchVersion,"%s",buff);
			break;
		}
		else
			sprintf(module.PatchVersion,"0");

	}
	free(line);
	line=NULL;
	fclose(fp);
	return 0;
}


int patch_name(void)
{
	char patch_buff[80]="";
	sprintf(patch_buff,"patch-%s.zip",module.PatchVersion);
	memset(module.PatchName,0,sizeof(module.PatchName));
	strcpy(module.PatchName,patch_buff);
	printf("Patch Name is %s\n",module.PatchName);
	return 0;
}





