#include <header.h>

int  Update_Configured_Server_Addr(char *Server_Addr)
{
	FILE *fp;
	size_t len=0;
	char *str=NULL; 


	fp = fopen("/etc/.RHMS_Server.config","r");

	if (fp == NULL)
	{
		fprintf(stderr," /etc/.RHMS_Server.config open error\n");
		return -1;
	}

	while((getline(&str,&len,fp)) != -1)
	{
		if  (strstr(str,"ServerAddress:") != NULL )
		{
			strcpy(Server_Addr,str+14);
			break;
		}
	}
	free(str);
	str=NULL;	
	fclose(fp);

	if(Server_Addr[strlen(Server_Addr)-1] == '\n')
		Server_Addr[strlen(Server_Addr)-1]='\0';

	return 0;
}
