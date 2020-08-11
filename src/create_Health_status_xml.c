#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *Health_Status_file="/opt/Health_Status.xml";

int Health_Status_xml_frame();

int  create_Health_Status_xml_file(void)
{
	short int ret=0;

	char remote_xml_bkp_file[64]="";

	char Path[24]="";

	remove(Health_Status_file);

	Health_Status_xml_frame();

	ret=access(Health_Status_file,F_OK);

	if(ret == -1)
	{
		fprintf(stderr," %s open failed\n",Health_Status_file);
		return -1;
	}

	mkdir_p("/var/log/Health/");

	copy_file("/var/log/Health/Last_Health_Status.xml",Health_Status_file);//des,src


	memset(remote_xml_bkp_file,0,sizeof(remote_xml_bkp_file));

	memset(Path,0,sizeof(Path));

	sprintf(Path,"/var/log/Health/%c%c",module.Date_time[5],module.Date_time[6]);

	mkdir_p(Path);

	sprintf(remote_xml_bkp_file,"%s/day_%c%c_Health_Status.xml",Path,module.Date_time[8],module.Date_time[9]);
	
	copy_file(remote_xml_bkp_file,Health_Status_file);

	return 0;

}



int Health_Status_xml_frame()
{
	int sim_num =0;
	int Apps_Downloads=0,Firmware_Downloads=0;

	fprintf(stdout,"\n\n Health_Status.xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, childnode = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,  "HealthStatus");
	xmlDocSetRootElement(doc, root_node);


	xmlNewChild(root_node, NULL, BAD_CAST "SerialNo",BAD_CAST module.SerialNo);
	xmlNewChild(root_node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	if( CONFIG.GPS || CONFIG.geo_location )
	{
		if ( strcmp(module.GPS.Captured_Time,"NotFound") == 0 )
			fprintf(stderr," GPS File not found, module.GPS.Captured_Time = %s\n",module.GPS.Captured_Time);
		else 
		{
			childnode = xmlNewChild(root_node, NULL, BAD_CAST "GPS",NULL);
			xmlNewChild(childnode, NULL, BAD_CAST "Latitude", BAD_CAST module.GPS.Latitude);
			xmlNewChild(childnode, NULL, BAD_CAST "Longitude", BAD_CAST module.GPS.Longitude);
			if ( strstr(module.GPS.Captured_Time,"0000-00-00") != NULL )
				fprintf(stdout,"Date Not found, module.GPS.Captured_Time = %s\n",module.GPS.Captured_Time);
			else 
				xmlNewChild(childnode, NULL, BAD_CAST "Captured_Time", BAD_CAST module.GPS.Captured_Time);
		}
	}
	Firmware_Downloads = Get_Total_Downloaded_Updates(FIRMWARE);
	if ( Firmware_Downloads > 0 )
	{
		fprintf(stdout,"%d Firmware Downloads are Found \n",Firmware_Downloads);
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofFirmwareDownloads",NULL);
		FirmwareDownloadsDetails(Firmware_Downloads,childnode);		
	}
	else
	{
		fprintf(stdout,"No Firmware Downloads Found\n");
	}
	Apps_Downloads = Get_Total_Downloaded_Updates(APPLICATION);
	if ( Apps_Downloads > 0 )
	{
		fprintf(stdout,"%d Application Downloads are Found \n",Apps_Downloads);
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofApplicationDownloads",NULL);
		ApplicationDownloadsDetails(Apps_Downloads,childnode);

	}
	else
		fprintf(stdout,"No Application Downloads Found\n");

	if( CONFIG.Iris_or_Biomat )
		xmlNewChild(root_node, NULL, BAD_CAST "IRIS", BAD_CAST module.IRIS);
	if( CONFIG.Printer )
		xmlNewChild(root_node, NULL, BAD_CAST "PaperStatus", BAD_CAST module.paper);

	xmlNewChild(root_node, NULL, BAD_CAST "RTC", BAD_CAST module.RTC);
	xmlNewChild(root_node, NULL, BAD_CAST "Adapter", BAD_CAST module.Adapter);
	xmlNewChild(root_node, NULL, BAD_CAST "Battery", BAD_CAST module.Battery_status);
	xmlNewChild(root_node, NULL, BAD_CAST "BatteryVoltage", BAD_CAST module.BatteryVoltage);

	xmlNewChild(root_node, NULL, BAD_CAST "Comm", BAD_CAST module.Comm);

	if( strcmp(module.Comm,"GSM") == 0 )
	{
		sim_num = Update_Simdb_and_Signalmode();	
		if ( sim_num == 1)
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1db", BAD_CAST module.Sim1_db);
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1SignalMode", BAD_CAST module.SIM1SignalMode);
		}
		else if ( sim_num == 2)
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2db", BAD_CAST module.Sim2_db);
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2SignalMode", BAD_CAST module.SIM2SignalMode);
		}
	}

	xmlNewChild(root_node, NULL, BAD_CAST "FingerRDServiceStatus", BAD_CAST module.FingerRDServiceStatus);

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "System_memory",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.System_memory.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.System_memory.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.System_memory.Free);

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "InternalMem_Sysuser",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.InternalMem_Sysuser.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.InternalMem_Sysuser.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.InternalMem_Sysuser.Free);


	childnode = xmlNewChild(root_node, NULL, BAD_CAST "InternalMem_Jffs2",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.InternalMem_Jffs2.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.InternalMem_Jffs2.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.InternalMem_Jffs2.Free);


	childnode = xmlNewChild(root_node, NULL, BAD_CAST "RAM",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.RAM.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.RAM.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.RAM.Free);



	xmlSaveFormatFileEnc(Health_Status_file,doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;

}
