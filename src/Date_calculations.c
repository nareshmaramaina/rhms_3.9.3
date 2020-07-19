#include<header.h>
int Give_date(char *file_name)
{
	struct tm my_tm;
	struct tm *intim;
	struct timeval tv;

	memset(&my_tm,0,sizeof(struct tm));
	memset(file_name,0,sizeof(file_name));

	intim = &my_tm;

	if( gl11_getrtc (intim) == -1 )
	{
		fprintf(stderr,"RTC Read Error\n");
	} 

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;

	sprintf(file_name,"%02d%02d%04d",intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900);

	if ( intim->tm_year+1900 < 2019 )
	{
		fprintf(stderr,"Date Wrong set - Year Error\n");
		return -1;

	}

	else
		return 0;
}
