#include<header.h>
extern char *Hardware_filename;
extern char *BootTime_filename;
extern char *Periodic_filename; 
void update_Hardware_status_date_file(void) //after rhms successfull update ,updating time stamp to 
{
	FILE *fp;

	char Date[15]="";

	Get_Current_Date(Date);

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
