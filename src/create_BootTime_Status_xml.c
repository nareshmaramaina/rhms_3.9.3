#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int BootTime_Status_xml_frame();
extern int Total_Device_Apps;

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
		fprintf(stderr," %s open failed\n",BootTime_Status_file);
		return -1;
	}

	mkdir_p("/var/log/Health/");

	if( CONFIG.HWChanged )
		copy_file("/var/log/Health/Last_BootTime_Status.xml",BootTime_Status_file);//des,src


	memset(remote_xml_bkp_file,0,sizeof(remote_xml_bkp_file));

	memset(Path,0,sizeof(Path));

	sprintf(Path,"/var/log/Health/%c%c",module.Date_time[2],module.Date_time[3]);

	mkdir_p(Path);

	sprintf(remote_xml_bkp_file,"%s/day_%c%c_BootTime_Status.xml",Path,module.Date_time[0],module.Date_time[1]);

	copy_file(remote_xml_bkp_file,BootTime_Status_file);

	return 0;

}


int BootTime_Status_xml_frame()
{
	Applications_Details();
	int i=0;
	fprintf(stdout,"\n\n BootTime_Status.xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, childnode = NULL,childofchildnode = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,  "BOOT_STATUS");
	xmlDocSetRootElement(doc, root_node);


	xmlNewChild(root_node, NULL, BAD_CAST "SerialNo",BAD_CAST module.SerialNo);
	xmlNewChild(root_node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	if( CONFIG.DOT )
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
	xmlNewChild(root_node, NULL, BAD_CAST "AUDIO", BAD_CAST module.AUDIO);
	if( CONFIG.BatteryInfo )
	{
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "BatteryInfo",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Date", BAD_CAST module.BatteryInfo.Date);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_worked_mins", BAD_CAST module.BatteryInfo.Day_worked_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_adapter_mins", BAD_CAST module.BatteryInfo.Day_adapter_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_charged_mins", BAD_CAST module.BatteryInfo.Day_charged_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_discharged_mins", BAD_CAST module.BatteryInfo.Day_discharged_mins);
	}

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofApplications",NULL);

	for ( i=0;i<Total_Device_Apps;i++)
	{
		childofchildnode = xmlNewChild(childnode, NULL, BAD_CAST "Application",NULL);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationType", BAD_CAST module.Application[i].Type);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationName", BAD_CAST module.Application[i].Name);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationVer", BAD_CAST module.Application[i].Version);
	}

	xmlNewChild(root_node, NULL, BAD_CAST "FirmwareName", BAD_CAST module.FirmwareName);
	xmlNewChild(root_node, NULL, BAD_CAST "FirmwareVersion", BAD_CAST module.FirmwareVersion);

	if( CONFIG.IrisRDVer_and_SNo  )
		xmlNewChild(root_node, NULL, BAD_CAST "IritechRDVer", BAD_CAST module.IritechRDVer);

	if( CONFIG.BiomRDVer )
		xmlNewChild(root_node, NULL, BAD_CAST "BiomRDVer", BAD_CAST module.BiomRDVer);
	if( CONFIG.FPSRDVer )
		xmlNewChild(root_node, NULL, BAD_CAST "FPSRDVer", BAD_CAST module.FPSRDVer);

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "ExternalMem",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.ExternalMem.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.ExternalMem.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.ExternalMem.Free);
	childnode = xmlNewChild(root_node, NULL, BAD_CAST "Usbdevice",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.Usbdevice.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.Usbdevice.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.Usbdevice.Free);

	xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumber", BAD_CAST module.CCID);
	xmlNewChild(root_node, NULL, BAD_CAST "SIM1Operator", BAD_CAST "Operator");

	xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumber", BAD_CAST module.Sim2CCID); /* New ccid1 tag */
	xmlNewChild(root_node, NULL, BAD_CAST "SIM2Operator", BAD_CAST "Operator");





	xmlSaveFormatFileEnc(BootTime_Status_file,doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;

}
