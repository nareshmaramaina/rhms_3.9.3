#include<header.h>
void FingerRDServiceStatus()
{
	DIR *dp;
	int ret = 0;
	dp=opendir("/home/rdservice/");
	if(dp == NULL)
	{
		printf("\033[1;31m RD-Service Not installed and icon Red\n\033[0m");
		strcpy(module.FingerRDServiceStatus,"Red");
		return;
	}

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

