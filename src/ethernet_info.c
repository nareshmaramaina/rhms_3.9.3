#include<header.h>


int Ethernet_status(void)
{
	int check_cable=0;


	memset(module.ethernet,0,sizeof(module.ethernet));

	check_cable = Get_Ethernet_Status();

#if DEBUG
	printf("check cable presence%d\n",check_cable);
#endif
	if(check_cable == 1)
		strcpy(module.ethernet,"Connected");
	else 
		strcpy(module.ethernet,"NotConnected");
	fprintf(stdout,"Ethernet Status: %s\n",module.ethernet);


	return 0;

}


int Get_Ethernet_Status(void)
{
	FILE *fp_mod1;
	char status_file[80] = "/tmp/ethernet_status";
	short int i,ret;
	int status=0;
	for(i=0;i<10;i++)
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
		sleep(1);
	}
	return -1;
}

