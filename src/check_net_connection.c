#include<header.h>
char var_gprs[30];
static int retrieve_nw_details(void)
{
	FILE *fp;
	char buff[30]="";
	//int i=0;

	memset(buff,0x00,30);

	fp=fopen("/var/gprs","r");

	if(fp==NULL)
	{
		strcpy(module.Comm,"ERROR");
		return -1;
	}

	fread(buff,1,sizeof(buff),fp);


	fclose(fp);

	if( ( buff[2]  == 'E' ) || ( buff[2]  == 'H' ) || ( buff[2]  == 'L' ))
	{

		strcpy(module.Comm,"GSM");

		strcpy(var_gprs,buff);


		return 0;
	}

	else if	( buff[2]  == 'W' )
	{
		strcpy(module.Comm,"WIFI");
		fprintf(stdout,"%s Connection Available\n",module.Comm );
		return 0;

	}
	else if ( buff[2]  == 'X' )  
	{
		strcpy(module.Comm,"ETHERNET");
		fprintf(stdout,"%s Connection Available\n",module.Comm );
		return 0;

	}
	else
	{
		strcpy(module.Comm,"ERROR");
		fprintf(stderr,"module.comm  %s\n",module.Comm);
		fprintf(stderr,"Internet not  found, retrying...\nNetwork Buffer:###%s###\n",buff);
		return -1;
	}
}

void check_net_connection()
{
	short int ret,count=0,sleep_secs=0;
	char ip[90]="";
	while(1)
	{
		ret = retrieve_nw_details();

		if(ret == 0)
		{
			printf("Network Details sucess\n");
			break;
		}
		else if ( (count > 18 )		&&	( Check_internet_by_hostname("google.co.in", ip) == 0 )  )
		{
			fprintf(stdout,"Internet Found by hostname api\n");
			Update_Comm_media(ip);
			if ( strcmp(module.Comm,"ERROR") != 0 && strlen(module.Comm) != 0 ) 
				return;
		}

		if ( count < 8 )
			sleep_secs = 30;
		else if ( count < 16 )
			sleep_secs = 60;
		else if ( count < 32 )
			sleep_secs = 120;
		else 
			sleep_secs = 300;

		sleep(sleep_secs); 
		count++;
		printf("checking for network details,\nCount = %d sleep secs = %d\n",count+1,sleep_secs);

	}
	return;
}
