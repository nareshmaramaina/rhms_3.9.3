#include <header.h>
char *Hardware_filename = "/opt/.rhms_Hardware_status_date_update";
char *BootTime_filename = "/opt/.rhms_BootTime_status_date_update";
char *Periodic_filename = "/opt/.rhms_Periodic_Health_status_date_update";


static int diff_bw_two_dates(int firstDate, int firstMonth, int firstYear, int secondDate, int secondMonth, int secondYear)
{
	int FirstNoOfDays=0;
	int SecondNoOfDays=0;

	firstMonth = (firstMonth + 9) % 12;
	firstYear = firstYear - firstMonth / 10;
	FirstNoOfDays = 365 * firstYear + firstYear/4 - firstYear/100 + firstYear/400 + (firstMonth * 306 + 5) /10 + ( firstDate - 1 );

	secondMonth = (secondMonth + 9) % 12;
	secondYear = secondYear - secondMonth / 10;
	SecondNoOfDays = 365 * secondYear + secondYear/4 - secondYear/100 + secondYear/400 + (secondMonth * 306 + 5) /10 + ( secondDate - 1 );

	return FirstNoOfDays - SecondNoOfDays; /* uses absolute if the first date is smaller so it wont give negative number */
}

int Get_Difference_Days_of_Today_with_Last_updated_day (char *filename,int my_date,int my_month,int my_year)
{
	FILE *fp;

	char str[80]="";

	int no_days=0;

	int pre_date=0,pre_month=0,pre_year=0;

	fp = fopen(filename,"r");
	if (fp == NULL)
	{
		fprintf(stderr,"%s File not Found\n",filename);
		return -1;
	}

	memset(str,0x00,80);

	fscanf(fp, "%s",str);

	fclose(fp);

	if (strlen(str) != 13)
	{
		fprintf(stderr,"Invalid date format\n");
		return -1;
	}

	sscanf(str+5,"%02d%02d%4d",&pre_date,&pre_month,&pre_year);

	no_days = diff_bw_two_dates(my_date,my_month,my_year, pre_date, pre_month,pre_year);

	fprintf(stdout,"Diffrence between two dates %d\n",no_days);

	return no_days;

}

int Check_RHMS_All_requests_run(int *Hardware_run,int *BootTime_run,int *Periodic_run)
{
	char CurrentDate[15]="";

	int CurrentDay=0, CurrentMonth=0, CurrentYear=0;	


	Get_Current_Date(CurrentDate);

	sscanf(CurrentDate,"%02d%02d%4d",&CurrentDay, &CurrentMonth, &CurrentYear);
	fprintf(stdout,"Curernt = %02d%02d%4d\n",CurrentDay, CurrentMonth, CurrentYear);

	if ( CurrentYear < 2020 )
	{
		fprintf(stderr,"Date Wrong set - Year Error\n");
		return -1;

	}


	if ( access(Hardware_filename, F_OK) == 0 )
		*Hardware_run =	Get_Difference_Days_of_Today_with_Last_updated_day (Hardware_filename,CurrentDay, CurrentMonth, CurrentYear);
	else *Hardware_run = -1;


	if ( access(BootTime_filename, F_OK) == 0 )
		*BootTime_run =	Get_Difference_Days_of_Today_with_Last_updated_day (BootTime_filename,CurrentDay, CurrentMonth, CurrentYear);
	else *BootTime_run = -1;

	if ( access(Periodic_filename, F_OK) == 0 )
		*Periodic_run =	Get_Difference_Days_of_Today_with_Last_updated_day (Periodic_filename,CurrentDay, CurrentMonth, CurrentYear);
	else *Periodic_run = -1;


	if ( *Hardware_run == 0 &&  *BootTime_run == 0 && *Periodic_run ==  0 )
		return 0;

	else return -2;
}
void RTC_info()
{
	struct tm my_tm;
	struct tm *intim;
	memset(&my_tm,0,sizeof(struct tm));

	intim = &my_tm;

	if( gl11_getrtc (intim) == -1 )
		sprintf(module.RTC,"Failure");

	else 	sprintf(module.RTC,"Success");

	fprintf(stderr,"module.RTC = %s \n",module.RTC);

	return;
}

void Get_Current_Date(char *Date)
{
	struct tm *Today=NULL;
	struct timeval tv;

	gettimeofday (&tv,NULL);

	Today = localtime (&tv.tv_sec) ;

	sprintf(Date,"%02d%02d%04d",Today->tm_mday,Today->tm_mon+1,Today->tm_year+1900);

	fprintf(stdout,"Today Date (DDMMYYYY): %s \n",Date);

	return;
}

void Update_Current_Date_with_Time()
{
	struct tm *Today=NULL;
	struct timeval tv;

	memset(module.Date_time,0,sizeof(module.Date_time));

	gettimeofday (&tv,NULL);

	Today = localtime (&tv.tv_sec) ;

	sprintf(module.Date_time,"%04d-%02d-%02dT%02d:%02d:%02d",Today->tm_year+1900,Today->tm_mon+1,Today->tm_mday,Today->tm_hour,Today->tm_min,Today->tm_sec);
	fprintf(stdout,"Today Date and Time, %s \n",module.Date_time);

	return;
}
int Can_i_reboot()
{
	int DD,MM,YYYY,Hr=9;
	Update_Current_Date_with_Time();
	sscanf(module.Date_time,"%02d%02d%04d%02d",&DD,&MM,&YYYY,&Hr);

	fprintf(stdout,"%d %d %d %d\n",DD,MM,YYYY,Hr);

	if( YYYY < 2020 )
		fprintf(stdout," Wrong Date Set, So We Can't decide to reboot\n");
	else if( Hr >= 0 && Hr <=4 )
	{
		fprintf(stdout," Reboot the device: Date Changed and Valid time(12:00AM to 04:00AM) to reboot\n");
		return 0;	
	}
	else fprintf(stdout,"Not Valid Time for Reboot\n");
	return -1;
}
