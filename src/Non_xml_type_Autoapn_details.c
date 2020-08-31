#include<header.h>
void Non_xml_type_Autoapn_details()
{
	int Current_Mode=0;	
	if( CONFIG.Two_Simdetails_Autoapn )
	{
		Get_Two_Simdetails_info();	
		Current_Mode = Get_Current_autoapn_simdetails_mode();
		if ( Current_Mode == 1 )
		{
			CONFIG.Two_Simdetails_Autoapn=0;
			system("sed 's:<Two_Simdetails_Autoapn>1<:<Two_Simdetails_Autoapn>0<:g' -i /etc/.RHMS_config.xml"); // Auto Correction
			fprintf(stdout,"Wrong autoapn mode configured in /etc/.RHMS_config.xml\nAuto Corrected ( Disabled Two_Simdetails_Autoapn ) for autoapn sim mode details in /etc/.RHMS_config.xml \n");
			gprs_details();
		}
		else 
			fprintf(stdout,"Two Sim Details taken Success\n");
	}
	else
	{	
		gprs_details();
		Current_Mode = Get_Current_autoapn_simdetails_mode();
		if ( Current_Mode == 2 )
		{
			CONFIG.Two_Simdetails_Autoapn=1;
			system("sed 's:<Two_Simdetails_Autoapn>0<:<Two_Simdetails_Autoapn>1<:g' -i /etc/.RHMS_config.xml"); // Auto Correction
			fprintf(stdout,"Wrong autoapn mode configured in /etc/.RHMS_config.xml\nAuto Corrected ( Enabled Two_Simdetails_Autoapn ) for autoapn sim mode details in /etc/.RHMS_config.xml \n");
			Get_Two_Simdetails_info();	
		}
		else
			fprintf(stdout,"Single Sim Details taken Success\n");
	}
	if( CONFIG.WIFI )
		Wifi_Status();

	Ethernet_status();

	return;

}
int Get_Current_autoapn_simdetails_mode()
{
	int Comma_count=0,gprs_Comma_count=0;
	FILE *fp = NULL;
	fp = popen("cat /tmp/sim_details /tmp/revision_operator_details | grep -o ',' | wc -l","r");
	if(fp == NULL)
	{
		fprintf(stderr,"popen failed for Comma count\n");
		return -1;
	}

	fscanf(fp,"%d",&Comma_count);
	pclose(fp);
	fprintf(stdout," Comma count = %d\n",Comma_count);

	fp = popen("cat /tmp/gprs_update | grep -o ',' | wc -l","r");
	if(fp == NULL)
	{
		fprintf(stderr,"popen1 failed for Comma count\n");
		return -1;
	}

	fscanf(fp,"%d",&gprs_Comma_count);
	pclose(fp);

	if ( Comma_count == 6 && gprs_Comma_count == 2 )
		return 2; // SIM2 Details
	else if ( Comma_count == 4 && gprs_Comma_count == 4 )
		return 1; // SIM1 Details

	return 0;
}

