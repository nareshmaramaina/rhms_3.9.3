#include<header.h>
/*int main(void)
{
	Iris_Scanner_Id();

}*/
void Iris_Scanner_Id(void)
{
	int ret;	
	FILE *fp = NULL;
	char *line = NULL;
	size_t len = 0;
	char *data=NULL;
	char *scanner_id=NULL;

	ret = system("cat /proc/bus/usb/devices | grep IriShield >> /dev/null");
	if(ret == 0)
	{
		fp = popen("tac /var/log/mk2120ul-mgmtserv.log","r");
		if(fp == NULL)
		{
		strcpy(module.IritechSno,"ERROR");
			printf("/var/log/mk2120ul-mgmtserv.log Error in open a file\n");
			return;
		}
		while(getline(&line, &len, fp) != -1)
		{
			line = strtok_r(line,"D",&data);
			if(strlen(data) > 14)
			{
				scanner_id = strtok_r(data,"A",&data);
				fprintf(stdout,"Iritech Scanner Id = %s\n",scanner_id);
				if(strlen(scanner_id) == 14)
				{
					strcpy(module.IritechSno,scanner_id);
					free(line);
					line=NULL;
					pclose(fp);
					return;
				}
			}
		}

		pclose(fp);
	}
	free(line);
	line=NULL;
	strcpy(module.IritechSno,"ERROR");
	fprintf(stderr,"module.IritechSno = %s, Iris Scanner Not connected\n",module.IritechSno);
	return;
}

