#include<header.h>
void Non_xml_type_Autoapn_details()
{
	
	if( CONFIG.Two_Simdetails_Autoapn )
		Get_Two_Simdetails_info();	

	else 
		gprs_details();


	if( CONFIG.WIFI )
		Wifi_Status();

	Ethernet_status();

	return;

}

