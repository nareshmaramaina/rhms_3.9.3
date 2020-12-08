#include<header.h>

void imx25_Uid_info()
{
	char uid_buff[40]="";
	short int ret;
	ret = imx25_uid(uid_buff);

	if(ret!=0)
		strcpy(module.UIDExists,"Error");

	else
	{
		strcpy(module.Uid_no,uid_buff);
		strcpy(module.UIDExists,"Yes");
	}
	fprintf(stdout," UIDExists =%s\tmodule.Uid_no = %s\n",module.UIDExists,module.Uid_no);

	return;
}
int imx25_uid(char *buff)
{
	FILE *fp=NULL;
	fp = fopen("/proc/uid","r");
	if ( fp == NULL )
	{
		printf("/proc/uid file not found\n");
		return -1;
	}
	fgets(buff,40,fp);
	if(buff[strlen(buff)-1]=='\n')
		buff[strlen(buff)-1]='\0';
	fclose(fp);

	if ( strlen(buff) == 0 )
		return -1;
	else return 0;
}
int imx25_kernel_details (char *buff)
{
	FILE *fp=NULL;
	char temp[80]="";
	fp=fopen("/dev/mtd1","r");
	if ( fp == NULL )
	{
		printf("/dev/mtd1 file not found\n");
		return -1;
	}
	fseek(fp,32,SEEK_CUR);
	fgets(temp,80,fp);
	fclose(fp);
	if ( strlen(temp) == 0 )
		return -1;
	else
	{ 
		sprintf(buff,"%s.IMG",temp);
		return 0;
	}
}
int imx25_bootloader_details( char *buff)
{
	FILE *fp;

	fp = popen("fw_printenv ver | cut -c5-32 ","r");
	if ( fp == NULL )
	{
		fprintf(stdout," U-boot info not found\n");
		return -1;
	}
	fgets(buff,40,fp);
	pclose(fp);
	if(buff[strlen(buff)-1]=='\n')
		buff[strlen(buff)-1]='\0';
	if ( strlen(buff) == 0 )
		return -1;
	else return 0;
}
