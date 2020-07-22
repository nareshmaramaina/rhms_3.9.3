#include<header.h>
void Camera_info(void)
{
	int flag=0;	
	FILE *fp = NULL;
	char *line = NULL,*temp=NULL;
	size_t len = 0;
	char VendorID[5]="", ProductID[5]="";
	
	

	fp = popen("udevadm info --name=/dev/video2 --attribute-walk | grep ATTRS{id | head -2","r");
	if(fp == NULL)
	{
		return;
	}
	while(getline(&line, &len, fp) != -1)
	{
		if ( (temp = strstr(line,"ATTRS{idVendor}==") ) != NULL )
		{
			temp = temp+18;
			VendorID[0]=temp[0];
			VendorID[1]=temp[1];
			VendorID[2]=temp[2];
			VendorID[3]=temp[3];
			VendorID[4]='\0';
		}
		else if ( (temp = strstr(line,"ATTRS{idProduct}==") ) != NULL )
		{
			temp = temp+19;
			ProductID[0]=temp[0];
			ProductID[1]=temp[1];
			ProductID[2]=temp[2];
			ProductID[3]=temp[3];
			ProductID[4]='\0';
			flag=1;
		}


	}

	if(flag)
		sprintf(module.CamType,"%s:%s",VendorID,ProductID);
	else
		strcpy(module.CamType,"Not connected");
	fprintf(stdout," %s \n",module.CamType);
	free(line);
	line=NULL;
	pclose(fp);
	return;
}
