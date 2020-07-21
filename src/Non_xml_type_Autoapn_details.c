#include<header.h>
void Non_xml_type_Autoapn_details()
{
	
	if(strlen(module.GSM_Module) == 0 )
		strcpy(module.GSM_Module,"Not Found"); // GSM_Module Error because xml not found
	
	if( CONFIG.Two_Simdetails_Autoapn )
		Get_Two_Simdetails_info();	

	else 
		gprs_details();


	if( CONFIG.WIFI )
		Wifi_Status();

	Ethernet_status();

	return;

}

