#include <header.h>

int sdcard_test(int ,int);

int update_sd_details(void);

int update_sdcard_info(void)
{
	FILE *fpr;

	char str[100]="";
	char MainBlock[20];
	char ChildBlock[20];
	int flag=0,ret =-1,blocknum;

	memset(str,0x00,100);
	memset(MainBlock,0,sizeof(MainBlock));
	memset(ChildBlock,0,sizeof(ChildBlock));
	fpr=fopen("/proc/partitions","r");
	if ( fpr == NULL)
	{	
		strcpy(module.ExternalMemExists,"No");
		return -1;

	}
	ret  = system("grep Hardware /proc/cpuinfo  |grep MX25 -q");
	if ( ret == 0 )
	{
		blocknum=0;
		strcpy(MainBlock,"mmcblk0");
		strcpy(ChildBlock,"mmcblk0p1");
	}
	else 
	{
		blocknum=1;
		strcpy(MainBlock,"mmcblk1");
		strcpy(ChildBlock,"mmcblk1p1");
	}

	while((fgets(str,80,fpr))!=NULL)
	{
		if(strstr(str,ChildBlock) != NULL)
		{
			printf("%s found\n",ChildBlock);
			flag=2;
			break;
		}
		else if((strstr(str,MainBlock)) != NULL)
			flag=1;

	}
	fclose(fpr);


	if (flag == 0)
		strcpy(module.ExternalMemExists,"No");
	else
	{
		ret = sdcard_test(flag,blocknum);
		if( ret == 0 )
			strcpy(module.ExternalMemExists,"Yes");
		else 
			strcpy(module.ExternalMemExists,"No");
		fprintf(stdout,"Externel Memory Total= %s Use= %s Free=%s\n",module.ExternalMem.Total,module.ExternalMem.Use,module.ExternalMem.Free);
	}
	fprintf(stdout," ExternalMemExists = %s \n",module.ExternalMemExists);

	return 0;

}

int sdcard_test(int partition_flag,int blocknum)
{
	int ret=0;

	FILE *fp3;

	char str[100]="";

	int flag=0;

	char cmd[64]="";

	fp3 = fopen("/etc/mtab","r");

	if (fp3==NULL)
	{
		printf("/etc/mtab file not exists\n");
		return -1;
	}

	while((fgets(str,80,fp3))!=NULL)
	{
		if((strstr(str,"/mnt/microsd")) != NULL)
		{
			fprintf(stderr,"Microsd found in /etc/mtab\n");
			flag=1;
			break;
		}	

	}
	fclose(fp3);

	if (flag == 0)
	{
		if(partition_flag == 1)
			sprintf(cmd,"mount  /dev/mmcblk%d  /mnt/microsd",blocknum);

		else if(partition_flag == 2)
			sprintf(cmd,"mount  /dev/mmcblk%dp1  /mnt/microsd",blocknum);

		ret=system(cmd);
		if(ret!=0)
		{
			fprintf(stdout," /mnt/microsd mounting failed \n");
			return -1;
		}

	}	


	ret = update_sd_details();


	if(flag == 0) 
		system("umount /mnt/microsd");

	return ret;
}

int update_sd_details(void)
{

	char  *line=NULL;
	size_t len=0;
	FILE *fp=NULL;

	char Partition[24];
	int success_flag=0;


	system("df  -h | grep /dev/mmcblk > /tmp/.sd_details");

	fp = fopen("/tmp/.sd_details","r");
	if( fp == NULL )
		return -1;

	while(getline(&line, &len, fp)> 0)
	{
		if(strstr(line,"/mnt/microsd") != NULL)
		{
			sscanf(line,"%s%s%s%s",Partition,module.ExternalMem.Total,module.ExternalMem.Use,module.ExternalMem.Free);
			success_flag=1;
			break;
		}
	}

	fclose(fp);
	free(line);
	line = NULL;
	remove("/tmp/.sd_details");

	if(success_flag)
		return 0;
	else
		return -1;
}

int update_ram_info(void)
{
	FILE *fp = fopen("/proc/meminfo", "r");
	int total_memory = 0;
	int free_memory =0;

	char buff[32];
	char buff1[32];

	memset(&module.RAM,0,sizeof(module.RAM));

	if ( fp == NULL )
		return -1;

	fscanf(fp,"%s %d %s",buff,&total_memory,buff1);
	fscanf(fp,"%s %d",buff,&free_memory);

	fclose(fp);

	sprintf(module.RAM.Total,"%dMB", total_memory/1024);
	sprintf(module.RAM.Use,"%dMB", (total_memory-free_memory)/1024);
	sprintf(module.RAM.Free,"%dMB", free_memory/1024);

	fprintf(stdout,"RAM Memory Total= %s Use= %s Free=%s\n",module.RAM.Total,module.RAM.Use,module.RAM.Free);
	return 0;
}

int update_internal_memory_info(void)
{
	size_t len=0;
	FILE *fp;
	char Partition[24],*str=NULL;
	short int ret,sysuser=0,jffs2=0,System_memory=0;
	ret = system ("df -h | grep /dev/ > /tmp/.emmc_details");

	memset(&module.System_memory,0,sizeof(module.System_memory));
	memset(&module.InternalMem_Sysuser,0,sizeof(module.InternalMem_Sysuser));
	memset(&module.InternalMem_Jffs2,0,sizeof(module.InternalMem_Jffs2));
	if (ret != 0)
	{
		fprintf(stderr,"INT $ Mem not Mounted\n");
		return -1;
	}


	fp = fopen("/tmp/.emmc_details","r");

	if(fp == NULL)
		return -1;
	while((getline(&str,&len,fp)) != -1)
	{
		memset(Partition,0,sizeof(Partition));
		if  (strstr(str,"/dev/root") != NULL )
		{

			sscanf(str,"%s%s%s%s",Partition,module.System_memory.Total,module.System_memory.Use,module.System_memory.Free);

			System_memory=1;
		}

		else if  (strstr(str,"sysuser") != NULL )
		{
			sscanf(str,"%s%s%s%s",Partition,module.InternalMem_Sysuser.Total,module.InternalMem_Sysuser.Use,module.InternalMem_Sysuser.Free);
			sysuser =1;
		}
		else if  (strstr(str,"jffs2") != NULL )
		{
			sscanf(str,"%s%s%s%s",Partition,module.InternalMem_Jffs2.Total,module.InternalMem_Jffs2.Use,module.InternalMem_Jffs2.Free);
			jffs2=1;
		}
	}


	fclose(fp);

	if ( System_memory == 0 )
	{
		strcpy(module.System_memory.Total,"NotFound");
		strcpy(module.System_memory.Use,"NotFound");
		strcpy(module.System_memory.Free,"NotFound");

	}
	if ( sysuser == 0 )
	{
		strcpy(module.InternalMem_Sysuser.Total,"NotFound");
		strcpy(module.InternalMem_Sysuser.Use,"NotFound");
		strcpy(module.InternalMem_Sysuser.Free,"NotFound");

	}

	if ( jffs2 == 0 )
	{
		strcpy(module.InternalMem_Jffs2.Total,"NotFound");
		strcpy(module.InternalMem_Jffs2.Use,"NotFound");
		strcpy(module.InternalMem_Jffs2.Free,"NotFound");
	}

	fprintf(stdout,"System  Memory Total= %s Use= %s Free=%s\n",module.System_memory.Total,module.System_memory.Use,module.System_memory.Free);
	fprintf(stdout,"sysuser Memory Total= %s Use= %s Free=%s\n",module.InternalMem_Sysuser.Total,module.InternalMem_Sysuser.Use,module.InternalMem_Sysuser.Free);
	fprintf(stdout,"jffs2  Memory Total= %s Use= %s Free=%s\n",module.InternalMem_Jffs2.Total,module.InternalMem_Jffs2.Use,module.InternalMem_Jffs2.Free);

	remove("/tmp/.emmc_details");

	return 0;
}
/*int main()
  {
  update_internal_memory_info();
  update_sdcard_info();
  update_ram_info();
  return;
  }*/

