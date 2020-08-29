#include <header.h>
extern char Server_Addr[512];
extern char *Health_Status_file;
extern char *BootTime_Status_file;
extern char *Hardware_Status_file;
extern char *Default_RHMS_Server_Address;
char *Error_log_filename="/opt/.RHMSClientApp_Error.log";
char *BootTime_response_xml_file="/opt/BootTime_response.xml";
char *Hardware_response_xml_file="/opt/Hardware_response.xml";
char *Health_response_xml_file="/opt/Health_response.xml";
int Update_request(int request) // arg 1 For Hardware request,arg 2 For BootTime request, arg 3 For Periodic Health request 
{
	char Response_xml_file[128];
	int ret=-1;
	short int FramingError=0;
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
		sprintf(cmd,"curl  --cacert /vision/curl-ca-bundle.crt  -XPOST -H \"content-type: application/xml\" %s/api/HardwareStatus -d @%s 1> %s 2>%s",Server_Addr,Upload_Status_file,Response_xml_file,Error_log_filename);


	}
	else if ( request == 2)
	{
		fprintf(stdout,"BootTime Status requesting\n");
		strcpy(Response_xml_file,BootTime_response_xml_file);
		strcpy(Upload_Status_file,BootTime_Status_file);
		sprintf(cmd,"curl --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/BootTimeStatus -d @%s 1> %s 2>%s",Server_Addr,Upload_Status_file,Response_xml_file,Error_log_filename);

	}
	else if ( request == 3)
	{
		fprintf(stdout,"Periodic Health Status requesting\n");
		strcpy(Response_xml_file,Health_response_xml_file);
		strcpy(Upload_Status_file,Health_Status_file);
		sprintf(cmd,"curl  --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/HealthStatus -d @%s 1>%s 2>%s",Server_Addr,Upload_Status_file,Response_xml_file,Error_log_filename);

	}
	else 
	{
		fprintf(stderr, "wrong Request Please Give Proper Request\n");
		return -1;
	}

	remove(Response_xml_file);
	remove(Error_log_filename);

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
		else if (strstr(str,"<Error><MVC-Empty>") != NULL )
		{
			FramingError = 1;
			break;
		}
		fprintf(stderr,"RequestNo %d Error: %s	",request,str);
	}

	free(str);
	str=NULL;
	fclose(fp);


	if ( ret == 0 )	
		ret = parseDoc(Response_xml_file);
	else if (  ret != -2 && FramingError != 1 )
		Check_Address_Error_and_Update_Server_Addr_If_Error_Present();

	return ret;
}
int Check_Address_Error_and_Update_Server_Addr_If_Error_Present()
{
	FILE    *fp;
	size_t len=0;
	char *str=NULL;

	fp = fopen(Error_log_filename,"r");

	if (fp == NULL)
	{
		fprintf(stderr,"%s open error\n",Error_log_filename);
		return -1;
	}


	while((getline(&str,&len,fp)) != -1)
	{
		if ( strstr(str,"Average Speed   Time" ) != NULL || strstr(str,"Dload  Upload") != NULL || strstr(str,"--:--:--")!= NULL)
		{
			continue;
		}
		if ( strstr(str,"Couldn't resolve host") != NULL )
		{
			memset(Server_Addr,0,sizeof(Server_Addr));
			strcpy(Server_Addr,Default_RHMS_Server_Address);
			fprintf(stderr,"ServerAddress Error: %s so Proceeding with Default Server Address = %s\n",str,Server_Addr);
			break;
		}
		
		fprintf(stderr,"Curl Commad Error Log: %s\n",str);
	}
	if ( strstr(str,"curl") != NULL )
		fprintf(stderr,"curl related issue\n");
	else 
		fprintf(stderr,"\033[1;31m RHMS Server Network Issue\033[0m\n");
	free(str);
	str=NULL;
	fclose(fp);
	return 0;
}
