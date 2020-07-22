#include <header.h>
char *Health_response_xml_file="/opt/Health_response.xml";
extern char *Health_Status_file;
int parseDoc(char *);
extern char Server_Addr[128];
int Send_Hardware_status_to_server (void)
{
	int ret = 0;
	int i=0;

	for (i=0; i<8; i++)
	{
		check_net_connection(); //Blocking For autoapn details

		ret = server_updation();

		if(ret == 0)
		{
			fprintf(stderr,"Health Updation Success\n");
			update_date_status_file();
			if( CONFIG.DOT )
				remove(DOT_FILE);
			break;
		}

		else if ( ret == -2 )
			break;

		else   
		{
			fprintf(stdout,"***** Health Updation Failure, retrying = %d, Waiting for 3mins****\n",i);
			sleep(180);
		}
	}

	return ret;
}

int server_updation(void)
{

	int ret;
	FILE    *fp;
	char    cmd[1024];
	size_t len=0;
	char *str=NULL;


	remove(Health_response_xml_file);

	memset(cmd,0,sizeof(cmd));

	sprintf(cmd,"curl -k -XPOST -H \"content-type: application/xml\" %s/api/HealthStatus -d @%s > %s",Server_Addr,Health_Status_file,Health_response_xml_file);

	system(cmd);

	puts(cmd);

	memset(cmd,0,sizeof(cmd));

	sprintf(cmd,"dos2unix %s",Health_response_xml_file);

	system(cmd);


	fp = fopen(Health_response_xml_file,"r");

	if (fp == NULL)
	{
		fprintf(stderr,"%s open error\n",Health_response_xml_file);
		return -1;
	}


	while((getline(&str,&len,fp)) != -1)
	{
		if  (strstr(str,"<Units>") != NULL )
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
		ret = parseDoc(Health_response_xml_file);

	return ret;
}
