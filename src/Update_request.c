#include <header.h>
extern char Server_Addr[512];
extern char *Health_Status_file;
extern char *BootTime_Status_file;
extern char *Hardware_Status_file;
char *BootTime_response_xml_file="/opt/BootTime_response.xml";
char *Hardware_response_xml_file="/opt/Hardware_response.xml";
char *Health_response_xml_file="/opt/Health_response.xml";
int Update_request(int request) // arg 1 For Hardware request,arg 2 For BootTime request, arg 3 For Periodic Health request 
{
	char Response_xml_file[128];
	int ret=-1;
	FILE    *fp;
	char    cmd[1024];
	size_t len=0;
	char *str=NULL;
	char Upload_Status_file[128];
	memset(Response_xml_file,0,sizeof(Response_xml_file));	
	memset(Upload_Status_file,0,sizeof(Upload_Status_file));	
	memset(cmd,0,sizeof(cmd));
	if ( request == 1)
	{
		fprintf(stdout,"Hardware Status requesting\n");
		strcpy(Response_xml_file,Hardware_response_xml_file);
		strcpy(Upload_Status_file,Hardware_Status_file);
	sprintf(cmd,"curl  --cacert /vision/curl-ca-bundle.crt  -XPOST -H \"content-type: application/xml\" %s/api/HardwareStatus -d @%s > %s",Server_Addr,Upload_Status_file,Response_xml_file);


	}
	else if ( request == 2)
	{
		fprintf(stdout,"BootTime Status requesting\n");
		strcpy(Response_xml_file,BootTime_response_xml_file);
		strcpy(Upload_Status_file,BootTime_Status_file);
	sprintf(cmd,"curl --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/BootTimeStatus -d @%s > %s",Server_Addr,Upload_Status_file,Response_xml_file);

	}
	else if ( request == 3)
	{
		fprintf(stdout,"Periodic Health Status requesting\n");
		strcpy(Response_xml_file,Health_response_xml_file);
		strcpy(Upload_Status_file,Health_Status_file);
	sprintf(cmd,"curl  --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/HealthStatus -d @%s > %s",Server_Addr,Upload_Status_file,Response_xml_file);

	}
	else 
	{
		fprintf(stderr, "wrong Request Please Give Proper Request\n");
		return -1;
	}

	remove(Response_xml_file);


	system(cmd);

	puts(cmd);

	memset(cmd,0,sizeof(cmd));

	sprintf(cmd,"dos2unix %s",Response_xml_file);

	system(cmd);


	fp = fopen(Response_xml_file,"r");

	if (fp == NULL)
	{
		fprintf(stderr,"%s open error\n",Response_xml_file);
		return -1;
	}


	while((getline(&str,&len,fp)) != -1)
	{
		if  (strstr(str,"POSHealthDetailsResponse") != NULL )
		{
			ret = 0 ;
			break;
		}
		else if  (strstr(str,"Device is not registered") != NULL )
		{
			ret = -2;
			break;
		}

		puts(str);
	}

	free(str);
	str=NULL;
	fclose(fp);


	if ( ret == 0 )	
		ret = parseDoc(Response_xml_file);

	return ret;
}

