#include<header.h>
int  Location_info()
{
	FILE *fp=NULL;
	char *line=NULL;
	char *temp=NULL;
	size_t len;
	char *file="/var/.location_backup.txt";
	double Longitude,Latitude;
	int File_day=0,File_month=0,File_year=0,File_Hr=0,File_Min=0;
	int flag = 0;

	memset(&module.GPS,0,sizeof(module.GPS));

	fp = fopen(file,"r");

	if(fp == NULL)
	{
		strcpy(module.GPS.Captured_Time,"NotFound");
		fprintf(stderr,"%s file not found\n",file);
		return -1;
	}

	fprintf(stdout,"Fetching GeoLocation details from %s file\n",file);

	while( getline(&line,&len,fp) != -1 )
	{
		if( ( temp = strstr(line,"Latitude:") ) != NULL)
		{
			sscanf(temp+9,"%lf",&Latitude);

			if( ( temp = strstr(line,"Longitude:") ) != NULL)
				sscanf(temp+10,"%lf",&Longitude);

			if( ( temp = strstr(line,"Date:") ) != NULL)
				sscanf(temp+5,"%02d/%02d/%04d-%02d:%02d",&File_day,&File_month,&File_year,&File_Hr,&File_Min);

			//			if( ( temp = strstr(line,"Mode:") ) != NULL)
			//				sscanf(temp+5,"%c",&Mode);

			flag =1;
			break;
		}
	}

	if ( flag )
	{
		sprintf(module.GPS.Latitude,"%lf",Latitude);
		sprintf(module.GPS.Longitude,"%lf",Longitude);
		sprintf(module.GPS.Captured_Time,"%04d-%02d-%02dT%02d:%02d:00",File_year,File_month,File_day,File_Hr,File_Min);
	}
	//	else
	//		strcpy(module.GPS.Captured_Time,"Error");

	fprintf(stdout,"Latitude = %s , Longitude = %s module.GPS = %s  \n", module.GPS.Latitude,module.GPS.Longitude,module.GPS.Captured_Time);
	free(line);
	fclose(fp);
	line=NULL;
	return flag;
}
