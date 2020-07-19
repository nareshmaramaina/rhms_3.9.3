#include <header.h>

int  get_app_details()
{

	FILE *fp;

	int i=0,j=0,k=0;
	char buff[256];
	char A_type[50]="";
	char A_ver[50]="";

	fp = fopen("/mnt/sysuser/app_ver","r");

	if (fp==NULL)
	{
		strcpy(module.app_type,"ERROR");
		strcpy(module.app_version,"ERROR");
		fprintf(stderr,"Application Version File open error\n");
		return -1;
	}

	for (i=0;i<4;i++)
	{
		memset(buff,0x00,256);
		fscanf(fp, "%s",buff); 


		if (i==0)
		{	
			for(j=0;j<100;j++)
			{
				if (buff[j]==':')
				{	
					for (k=0;k<(strlen(buff)-j);k++)	
						A_type[k]=buff[j+k+1];
					fprintf (stdout, "Application Type:%s\n",A_type);
					break;
				}




			}



		}


		if (i==1)
		{
			for(j=0;j<100;j++)
			{
				if (buff[j]==':')
				{
					for (k=0;k<(strlen(buff)-j);k++)

						A_ver[k]=buff[j+k+1];

					fprintf (stdout, "Application Version:%s\n",A_ver);
					break;
				}




			}

		}
	}


	memset(module.app_type,0,sizeof(module.app_type));

	if ( strlen(A_type) != 0 )	
	strcpy(module.app_type,A_type);
	else 
		strcpy(module.app_type,"ERROR");


	memset(module.app_version,0,sizeof(module.app_version));

	if ( strlen(A_ver) != 0 )	
	strcpy(module.app_version,A_ver);
	else 
		strcpy(module.app_version,"ERROR");

	return 0;



}

