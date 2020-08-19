#include <header.h>

int Wifi_Status()
{
	
	int ret=0;
	ret = Get_Wifi_Status();	
	
	if(ret==1)
	{
		memset(module.WIFI,0,sizeof(module.WIFI));
		strcpy(module.WIFI,"Yes");
	}
	else
	{

		memset(module.WIFI,0,sizeof(module.WIFI));
		strcpy(module.WIFI,"No");
	}

	return ret;
}
int Get_Wifi_Status(void)
{
	FILE *fp_mod1;
	char status_file[80]="/tmp/wifi_status";
	short int ret=0,i=0;
	int status=0;

	for( i=0; i < 10;i++)
	{
		ret=access(status_file,F_OK);
		if(ret == 0)
		{
			fp_mod1=fopen(status_file,"r");
			if(fp_mod1 == NULL)
			{
				return -1;
			}

			fscanf(fp_mod1,"%d",&status);
			fclose(fp_mod1);
			return status;
		}
		else 
		{
			fprintf(stdout,"%s file not found\n",status_file);
			sleep(1);
		}
	}
		return -1;
}


