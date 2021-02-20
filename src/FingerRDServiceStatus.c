#include<header.h>
void FingerRDServiceStatus()
{
	DIR *dp;
	int ret = 0;
	memset(module.FingerRDServiceStatus,0,sizeof(module.FingerRDServiceStatus));
	dp=opendir("/home/rdservice/");
	if(dp == NULL)
	{
		printf("\033[1;31m RD-Service Not installed and icon Red\n\033[0m");
		strcpy(module.FingerRDServiceStatus,"Red");
		return;
	}
	closedir(dp);

	ret = system("pidof rds > /dev/null");
	if(ret == 0)
	{
		printf("\033[0;32mRD-Service Runing and icon green\n\033[0m");
		strcpy(module.FingerRDServiceStatus,"Green");
	}
	else
	{
		strcpy(module.FingerRDServiceStatus,"Blue");
		printf("\033[0;34mRD-Service installed but rd not runing icon blue\n\033[0m");
	}
	return ;
}
int Wait_If_RD_Is_Blue()
{
	static int In=0,Blue=0;
	int i;

	if (  In == 0 )
	{
		In++;
		for ( i=0;i<6;i++)
		{
			FingerRDServiceStatus();
			if ( strcmp(module.FingerRDServiceStatus,"Blue") == 0)
			{
				Blue=1;
				fprintf(stderr,"Very First Time, RD is not Running, Waiting for 30secs\n");
				sleep(30);	
			}
			else 
				break;
		}
	}

	else if ( In == 1 && Blue == 1 )
	{

		In++;
		for ( i=0;i<60;i++)
		{
			FingerRDServiceStatus();
			if ( strcmp(module.FingerRDServiceStatus,"Blue") == 0)
			{
				fprintf(stderr,"Second Time, RD is not Running, Waiting for 30secs\n");
				sleep(30);
			}
			else if ( strcmp(module.FingerRDServiceStatus,"Green") == 0)
			{
				check_net_connection(); //Blocking For autoapn details

				Periodic_Health_Status_Details();

				External_Devices_SerialNo_info();

				printf("RD Is Green So, Send the Health updation details again\n");

				return 1;

			}
			else break;
		}


	}
	return 0;
}
