#include<header.h>
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


		sleep(1);

		xml_type_Autoapn_details();
	}

	else
	{
		fprintf(stdout,"/etc/autoapn/autoapn_config.xml file not found\n");
		Non_xml_type_Autoapn_details();
	}

	fprintf(stdout,"module.GSM_Version= %s\nmodule.IMEI_no= %s\nmodule.CCID= %s\nmodule.Sim2CCID= %s\nmodule.Sim1_db= %s\nmodule.Sim2_db= %s\nmodule.operator1_name= %s\nmodule.operator2_name= %s\nmodule.WIFI= %s\nmodule.ethernet = %s\n",module.GSM_Version,module.IMEI_no,module.CCID,module.Sim2CCID,module.Sim1_db,module.Sim2_db,module.operator1_name,module.operator2_name,module.WIFI,module.ethernet);	
	return;

}
