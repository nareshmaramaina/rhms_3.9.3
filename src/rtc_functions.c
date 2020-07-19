#include <header.h>

int update_date_status_file(void) //after rhms successfull update ,updating time stamp to /opt/rhms_date_update
{
	struct tm *intim;
	struct tm my_tm;
	struct timeval tv;

	char date_str[100]="";
	FILE *fp;

	fp=fopen("/opt/rhms_date_update","w");

	if(fp == NULL)
	{
		fprintf(stderr,"Date File Not created\n");
		return -1;
	}

	intim = &my_tm;

	memset(intim,0,sizeof(struct tm));

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;

	sprintf(date_str,"%02d%02d%04d",intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900);

	fprintf(fp,"Date:%s",date_str);

	fprintf(stdout,"Date:%s\n",date_str);

	fclose(fp);

	return 0;
}

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

int rhms_details_updated (int my_date,int my_month,int my_year)
{
	FILE *fp;

	char str[80]="";


	char temp[8];

	int no_days=0;

	int pre_date=0,pre_month=0,pre_year=0;

	fp = fopen("/opt/rhms_date_update","r");
	if (fp == NULL)
	{
		fprintf(stderr,"/opt/rhms_date_update File not Found\n");
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

	temp[0]=str[5];
	temp[1]=str[6];
	temp[2]=0x00;

	pre_date = atoi(temp);

	temp[0]=str[7];
	temp[1]=str[8];
	temp[2]=0x00;

	pre_month = atoi (temp);

	temp[0]=str[9];
	temp[1]=str[10];
	temp[2]=str[11];
	temp[3]=str[12];
	temp[4]=0x00;

	pre_year = atoi(temp);

	no_days = diff_bw_two_dates(my_date,my_month,my_year, pre_date, pre_month,pre_year);

	fprintf(stdout,"Diffrence between two dates %d\n",no_days);

	return no_days;

}

int RTC_info_and_Check_RHMS_run()
{
	struct tm my_tm;
	struct tm *intim;
	char str[100]="";

	struct timeval tv;

	memset(&my_tm,0,sizeof(struct tm));

	intim = &my_tm;

	printf("\nChecking... RHMS Last Success Date\n");



	if( gl11_getrtc (intim) == -1 )
	{
		fprintf(stderr,"RTC Read Error\n");
		sprintf(module.RTC,"ERROR");
	}

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;


	sprintf(str,"%02d%02d%04d%02d%02d%02d",intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900,intim->tm_hour,intim->tm_min,intim->tm_sec);

#if DEBUG	
	fprintf(stdout,"\nlocal time = %s str\n",str);
#endif
	memset(module.Date_time,0,sizeof(module.Date_time));

	sprintf(module.Date_time,"%s",str);

	if ( intim->tm_year+1900 < 2020 )
	{
		fprintf(stderr,"Date Wrong set - Year Error\n");
		sprintf(module.RTC,"ERROR");
		return -1;

	}
	sprintf(module.RTC,"OK");


	if ( access("/opt/rhms_date_update", F_OK) == 0 )
		return rhms_details_updated (intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900);

	else 
	{
		printf("/opt/rhms_date_update file not found\n");	
		return 1;
	}

}
