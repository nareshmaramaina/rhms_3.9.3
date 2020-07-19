#include<header.h>
extern char var_gprs[30];
void Get_autoapn_wrote_details()
{


	char *docname="/tmp/rhms_details.xml";

	short int ret=0;

	short int i = 100;

	ret = access("/etc/autoapn/autoapn_config.xml",F_OK);

	if ( ret == 0 )
	{
		while(i--) 
		{
			ret = access(docname,F_OK);
			if( ret	== 0 )
				break;

			fprintf(stdout,"\n%d) %s file not found \tret= %d, Waiting 5secs ...\n",i,docname,ret);
			sleep(5);	
		}


		sleep(5);

		xml_type_Autoapn_details();
	}

	else
		Non_xml_type_Autoapn_details();


	return;

}
