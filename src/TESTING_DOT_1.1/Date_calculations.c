#include"header.h"
int Calculate_time_diff(char *file_name)
{
	struct tm my_tm;
	struct tm *intim;
	struct timeval tv;

	memset(&my_tm,0,sizeof(struct tm));

	intim = &my_tm;

	/*if( gl11_getrtc (intim) == -1 )
	  {
	  fprintf(stderr,"RTC Read Error\n");
	  }*/

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;

	sprintf(file_name,"/var/log/DOT/.%02d%02d%04d_work.log",intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900);

	if ( intim->tm_year+1900 < 2018 )
	{
		fprintf(stderr,"Date Wrong set - Year Error\n");
		return -1;

	}

	if(intim->tm_hour < 8 )
		return 1;// 12AM to 8AM - Slot 1 
	else if(intim->tm_hour >= 8 && intim->tm_hour < 14 )
		return 2;// 8AM to 2PM   - Slot 2
	else if(intim->tm_hour >= 14 && intim->tm_hour < 20)
		return 3;// 2PM to 8PM   - Slot 3
	else if(intim->tm_hour >= 20 && intim->tm_hour <= 23)
		return 4;// 8PM to 12AM – Slot 4
	else
	{
		fprintf(stderr,"Error Slot\n");
		return -1;
	}
}
