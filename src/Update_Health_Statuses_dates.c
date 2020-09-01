#include<header.h>
extern char *Hardware_filename;
extern char *BootTime_filename;
extern char *Periodic_filename; 
extern char *Hardware_Status_file;
void update_Hardware_status_date_file(void) //after rhms successfull update ,updating time stamp to 
{


	FILE *fp;

	char Date[15]="";

	char remote_xml_bkp_file[64]="";

	char Path[24]="";

	mkdir_p("/var/log/Health/");

//	copy_file("/var/log/Health/Last_Hardware_Status.xml",Hardware_Status_file); Commented for External Pheripharals

	memset(remote_xml_bkp_file,0,sizeof(remote_xml_bkp_file));

	memset(Path,0,sizeof(Path));

	Get_Current_Date(Date);
	
	sprintf(Path,"/var/log/Health/%c%c",Date[2],Date[3]);

	mkdir_p(Path);

	sprintf(remote_xml_bkp_file,"%s/day_%c%c_Hardware_Status.xml",Path,Date[0],Date[1]);

	copy_file(remote_xml_bkp_file,Hardware_Status_file);


	fp=fopen(Hardware_filename,"w");

	if(fp == NULL)
	{
		fprintf(stderr,"Date  File Not created\n");
		return;
	}

	fprintf(fp,"Date:%s",Date);

	fclose(fp);

	return;
}

void update_BootTime_status_date_file(void) 
{
	FILE *fp;

	char Date[15]="";

	Get_Current_Date(Date);

	fp=fopen(BootTime_filename,"w");

	if(fp == NULL)
	{
		fprintf(stderr,"Date  File Not created\n");
		return;
	}

	fprintf(fp,"Date:%s",Date);

	fclose(fp);

	return;

}
void update_Periodic_Health_status_date_file(void)
{
	FILE *fp;

	char Date[15]="";

	Get_Current_Date(Date);

	fp=fopen(Periodic_filename,"w");

	if(fp == NULL)
	{
		fprintf(stderr,"Date  File Not created\n");
		return;
	}

	fprintf(fp,"Date:%s",Date);

	fclose(fp);

	return;

}
