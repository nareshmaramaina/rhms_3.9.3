#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int BootTime_Status_xml_frame();

char *BootTime_Status_file="/opt/BootTime_Status.xml";

int  create_BootTime_Status_xml_file(void)
{

	short int ret=0;

	char remote_xml_bkp_file[64]="";

	char Path[24]="";


	remove(BootTime_Status_file);

	BootTime_Status_xml_frame();

	ret=access(BootTime_Status_file,F_OK);

	if(ret == -1)
	{
		fprintf(stderr," %s file not created\n",BootTime_Status_file);
		return -1;
	}

	mkdir_p("/var/log/Health/");

	copy_file("/var/log/Health/Last_BootTime_Status.xml",BootTime_Status_file);//des,src


	memset(remote_xml_bkp_file,0,sizeof(remote_xml_bkp_file));

	memset(Path,0,sizeof(Path));

	sprintf(Path,"/var/log/Health/%c%c",module.Date_time[5],module.Date_time[6]);

	mkdir_p(Path);

	sprintf(remote_xml_bkp_file,"%s/day_%c%c_BootTime_Status.xml",Path,module.Date_time[8],module.Date_time[9]);

	copy_file(remote_xml_bkp_file,BootTime_Status_file);

	return 0;

}


int BootTime_Status_xml_frame()
{
	int Total_Server_Apps=0,Total_Running_apps=0;
	fprintf(stdout,"\n\n BootTime_Status.xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, childnode = NULL, Runningchildnode = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,  "BootStatus");
	xmlDocSetRootElement(doc, root_node);


	xmlNewChild(root_node, NULL, BAD_CAST "SerialNo",BAD_CAST module.SerialNo);
	xmlNewChild(root_node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	if( CONFIG.DOT && strlen(module.DOT.Date) > 5)
	{
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "DOT",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Date", BAD_CAST module.DOT.Date);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot1", BAD_CAST module.DOT.Slot1);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot2", BAD_CAST module.DOT.Slot2);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot3", BAD_CAST module.DOT.Slot3);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot4", BAD_CAST module.DOT.Slot4);
	}


	if( CONFIG.Pinpad )
		xmlNewChild(root_node, NULL, BAD_CAST "Pinpad", BAD_CAST module.pinpad);

	xmlNewChild(root_node, NULL, BAD_CAST "Ethernet", BAD_CAST module.ethernet);
	xmlNewChild(root_node, NULL, BAD_CAST "FingerPrint", BAD_CAST module.FP_TYPE);

	if( CONFIG.SAM1 )
		xmlNewChild(root_node, NULL, BAD_CAST "SAM1", BAD_CAST module.SAM1);

	if( CONFIG.SAM2 )
		xmlNewChild(root_node, NULL, BAD_CAST "SAM2", BAD_CAST module.SAM2);

	if( CONFIG.IFD1 )
		xmlNewChild(root_node, NULL, BAD_CAST "IFD1", BAD_CAST module.IFD1);

	if( CONFIG.IFD2 )
		xmlNewChild(root_node, NULL, BAD_CAST "IFD2", BAD_CAST module.IFD2);


	if( CONFIG.Printer )
		xmlNewChild(root_node, NULL, BAD_CAST "Printer", BAD_CAST module.Printer);

	if( CONFIG.Bluetooth )
		xmlNewChild(root_node, NULL, BAD_CAST "Bluetooth", BAD_CAST module.Bluetooth);

	if( CONFIG.WIFI )
		xmlNewChild(root_node, NULL, BAD_CAST "WIFI", BAD_CAST module.WIFI);
	if( CONFIG.Camera )
		xmlNewChild(root_node, NULL, BAD_CAST "Camera", BAD_CAST module.Camera);
	xmlNewChild(root_node, NULL, BAD_CAST "Audio", BAD_CAST module.AUDIO);
	if( CONFIG.BatteryInfo && strlen(module.BatteryInfo.Date) > 5 ) 
	{
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "BatteryInfo",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Date", BAD_CAST module.BatteryInfo.Date);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_worked_mins", BAD_CAST module.BatteryInfo.Day_worked_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_adapter_mins", BAD_CAST module.BatteryInfo.Day_adapter_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_charged_mins", BAD_CAST module.BatteryInfo.Day_charged_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_discharged_mins", BAD_CAST module.BatteryInfo.Day_discharged_mins);
	}

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofApplications",NULL);
	

	Total_Server_Apps = Get_Total_Server_Apps();

	fprintf(stdout," Total Server Apps = %d\n",Total_Server_Apps);

	if ( Total_Server_Apps > 0 )
		Applications_Details(Total_Server_Apps,childnode);

	Runningchildnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofRunningApplications",NULL);
	Total_Running_apps = Get_Total_Device_Apps();

	fprintf(stdout," Total_Running_apps = %d\n",Total_Running_apps);

	if ( Total_Running_apps > 0 )
		Running_Apps_Details(Total_Running_apps,Runningchildnode);

	xmlNewChild(root_node, NULL, BAD_CAST "FirmwareName", BAD_CAST module.FirmwareName);

	xmlNewChild(root_node, NULL, BAD_CAST "FirmwareVersion", BAD_CAST module.FirmwareVersion);

	if( CONFIG.IrisRDVer_and_SNo  )
		xmlNewChild(root_node, NULL, BAD_CAST "IritechRDVer", BAD_CAST module.IritechRDVer);

	if( CONFIG.BiomRDVer )
		xmlNewChild(root_node, NULL, BAD_CAST "BiomRDVer", BAD_CAST module.BiomRDVer);
	if( CONFIG.FPSRDVer )
	{
		xmlNewChild(root_node, NULL, BAD_CAST "FPSRDVer", BAD_CAST module.FPSRDVer);
		xmlNewChild(root_node, NULL, BAD_CAST "FPSRDSDKVer", BAD_CAST module.FPS_RD_SDK_Ver);
	}

	xmlNewChild(root_node, NULL, BAD_CAST "ExternalMemExists", BAD_CAST module.ExternalMemExists);
	if ( strcmp(module.ExternalMemExists,"Yes") == 0 )
	{
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "ExternalMem",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.ExternalMem.Total);
		xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.ExternalMem.Use);
		xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.ExternalMem.Free);
	}
	xmlNewChild(root_node, NULL, BAD_CAST "UsbdeviceExists", BAD_CAST module.UsbdeviceExists);
	if ( strcmp(module.UsbdeviceExists,"Yes") == 0 )
	{
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "Usbdevice",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.Usbdevice.Total);
		xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.Usbdevice.Use);
		xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.Usbdevice.Free);
	}
	if( CONFIG.Two_Simdetails_Autoapn )
	{
		xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumberExists", BAD_CAST module.SIM1CCIDnumberExists);
		if( strcmp(module.SIM1CCIDnumberExists,"Yes") == 0 )
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumber", BAD_CAST module.CCID);
		xmlNewChild(root_node, NULL, BAD_CAST "SIM1Operator", BAD_CAST module.operator1_name);

		xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumberExists", BAD_CAST module.SIM2CCIDnumberExists);
		if( strcmp(module.SIM2CCIDnumberExists,"Yes") == 0 )
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumber", BAD_CAST module.Sim2CCID); /* New ccid1 tag */
		xmlNewChild(root_node, NULL, BAD_CAST "SIM2Operator", BAD_CAST module.operator2_name);
	}
	else 
	{
		if ( strcmp(module.SIM2CCIDnumberExists,"Yes") == 0 )
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumberExists", BAD_CAST module.SIM2CCIDnumberExists);
			if( strcmp(module.SIM2CCIDnumberExists,"Yes") == 0 )
				xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumber", BAD_CAST module.Sim2CCID); /* New ccid1 tag */
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2Operator", BAD_CAST module.operator2_name);

		}	
		else 
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumberExists", BAD_CAST module.SIM1CCIDnumberExists);
			if( strcmp(module.SIM1CCIDnumberExists,"Yes") == 0 )
				xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumber", BAD_CAST module.CCID);
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1Operator", BAD_CAST module.operator1_name);

		}

	}
	xmlNewChild(root_node, NULL, BAD_CAST "RHMSClientVersion", BAD_CAST module.RHMSClientVersion);
	xmlNewChild(root_node, NULL, BAD_CAST "AutoapnAppVersion", BAD_CAST module.AutoapnAppVersion);



	xmlSaveFormatFileEnc(BootTime_Status_file,doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;

}
