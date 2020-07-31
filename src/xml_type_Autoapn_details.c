#include<header.h>
void xml_type_Autoapn_details()
{

	char *docname="/tmp/rhms_details.xml";


	Autoapn_xmlparse(docname);


	if(strlen(module.GSM_Module) == 0 )
		strcpy(module.GSM_ModuleExists,"Error");
	else 	
		strcpy(module.GSM_ModuleExists,"Yes");

	if(strlen(module.GSM_Version) == 0 )
		strcpy(module.GSMVersionExists,"Error");
	
	else strcpy(module.GSMVersionExists,"Yes");

	if(strlen(module.IMEI_no) == 0 )
		strcpy(module.IMEInumberExists,"Error");
	else 	
		strcpy(module.IMEInumberExists,"Yes");

	if(strlen(module.CCID) == 0 || strcmp(module.CCID,"NO_SIM") == 0  )
		strcpy(module.SIM1CCIDnumberExists,"NO_SIM");
	else
		strcpy(module.SIM1CCIDnumberExists,"Yes");

	if(strlen(module.Sim2CCID) == 0 || strcmp(module.Sim2CCID,"NO_SIM") == 0 )
		strcpy(module.SIM2CCIDnumberExists,"NO_SIM");
	else
		strcpy(module.SIM2CCIDnumberExists,"Yes");

	if(strlen(module.operator1_name) == 0 )
		strcpy(module.operator1_name,"NotFound");

	else 	Check_and_Set_Operator_name(module.operator1_name);

	if(strlen(module.operator2_name) == 0 )
		strcpy(module.operator2_name,"NotFound");

	else Check_and_Set_Operator_name(module.operator2_name);

	if(strlen(module.WIFI) == 0 )
		strcpy(module.WIFI,"No");       

	if(strlen(module.ethernet) == 0 )
		strcpy(module.ethernet,"NotConnected");   




	fprintf(stdout,"module.GSM_Version= %s\nmodule.IMEI_no= %s\nmodule.CCID= %s\nmodule.Sim2CCID= %s\nmodule.Sim1_db= %s\nmodule.Sim2_db= %s\nmodule.operator1_name= %s\nmodule.operator2_name= %s\nmodule.WIFI= %s\nmodule.ethernet = %s\n",module.GSM_Version,module.IMEI_no,module.CCID,module.Sim2CCID,module.Sim1_db,module.Sim2_db,module.operator1_name,module.operator2_name,module.WIFI,module.ethernet);	
	return;

}
