#include<header.h>
void xml_type_Autoapn_details()
{

	char *docname="/tmp/rhms_details.xml";

	char operator1[64]="";

	char operator2[64]="";


	Autoapn_xmlparse(docname);


	if(strlen(module.GSM_Module) == 0 )
		strcpy(module.GSM_Module,"NotFound");

	if(strlen(module.GSM_Version) == 0 )
		strcpy(module.GSM_Version,"NotFound");

	if(strlen(module.IMEI_no) == 0 )
		strcpy(module.IMEI_no,"NotFound");

	if(strlen(module.CCID) == 0 )
		strcpy(module.CCID,"NotFound");

	if(strlen(module.Sim2CCID) == 0 )
		strcpy(module.Sim2CCID,"NotFound");


	if(strlen(module.operator1_name) == 0 )
		strcpy(module.operator1_name,"NotFound");

	if(strlen(module.operator2_name) == 0 )
		strcpy(module.operator2_name,"NotFound");

	if(strlen(module.WIFI) == 0 )
		strcpy(module.WIFI,"NotFound");       

	if(strlen(module.ethernet) == 0 )
		strcpy(module.ethernet,"NotFound");   

	memset(operator1,0,sizeof(operator1));
	memset(operator2,0,sizeof(operator2));

	operator_check(module.operator1_name,operator1);
	operator_check(module.operator2_name,operator2);


	fprintf(stdout,"module.GSM_Version= %s\nmodule.IMEI_no= %s\nmodule.CCID= %s\nmodule.Sim2CCID= %s\nmodule.Sim1_db= %s\nmodule.Sim2_db= %s\nmodule.operator1_name= %s\nmodule.operator2_name= %s\nmodule.WIFI= %s\nmodule.ethernet = %s\n",module.GSM_Version,module.IMEI_no,module.CCID,module.Sim2CCID,module.Sim1_db,module.Sim2_db,module.operator1_name,module.operator2_name,module.WIFI,module.ethernet);	
	return;

}
