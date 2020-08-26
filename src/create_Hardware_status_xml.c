#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *Hardware_Status_file="/opt/Hardware_Status.xml";


int Hardware_xml_frame();
int  create_Hardware_status_xml_file(void)
{
	short int ret=0;

	remove(Hardware_Status_file);

	Hardware_xml_frame();

	ret=access(Hardware_Status_file,F_OK);

	if(ret == -1)
	{
		fprintf(stderr," %s open failed\n",Hardware_Status_file);
		return -1;
	}

	return 0;

}



int Hardware_xml_frame()
{
	fprintf(stdout,"\n\nHardware xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr node = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	node = xmlNewNode(NULL,  "DeviceDetails");
	xmlDocSetRootElement(doc, node);

	xmlNewChild(node, NULL, BAD_CAST "SerialNo",BAD_CAST module.SerialNo);
	xmlNewChild(node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	xmlNewChild(node, NULL, BAD_CAST "TerminalIDExists",BAD_CAST module.TerminalIDExists);
	if( strcmp(module.TerminalIDExists,"Found") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "TerminalID",BAD_CAST module.TerminalID);
	else 
		xmlNewChild(node, NULL, BAD_CAST "TerminalID",NULL);

	xmlNewChild(node, NULL, BAD_CAST "MacidExists", BAD_CAST module.MacidExists);

	if( strcmp(module.MacidExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "Macid", BAD_CAST module.macid);
	else 
		xmlNewChild(node, NULL, BAD_CAST "Macid", NULL);

	xmlNewChild(node, NULL, BAD_CAST "UbootImageName", BAD_CAST module.UbootVersion);
	xmlNewChild(node, NULL, BAD_CAST "KernelImageName", BAD_CAST module.KernelVersion);
	xmlNewChild(node, NULL, BAD_CAST "RootfsImageName", BAD_CAST module.rootfs_details);

	xmlNewChild(node, NULL, BAD_CAST "IMEInumberExists", BAD_CAST module.IMEInumberExists);
	if( strcmp(module.IMEInumberExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "IMEInumber", BAD_CAST module.IMEI_no);
	else 
		xmlNewChild(node, NULL, BAD_CAST "IMEInumber", NULL);

	xmlNewChild(node, NULL, BAD_CAST "UIDExists", BAD_CAST module.UIDExists);
	if( strcmp(module.UIDExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "UID", BAD_CAST module.Uid_no);
	else 
		xmlNewChild(node, NULL, BAD_CAST "UID", NULL );

	if( CONFIG.IrisRDVer_and_SNo )
	{
		xmlNewChild(node, NULL, BAD_CAST "IritechSnoExists", BAD_CAST module.IritechSnoExists);
		if(  strcmp(module.IritechSnoExists,"Found") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "IritechSno", BAD_CAST module.IritechSno);
		else 
			xmlNewChild(node, NULL, BAD_CAST "IritechSno", NULL );
	}
	if( CONFIG.PinpadSN )
	{
		xmlNewChild(node, NULL, BAD_CAST "PinpadSNExists", BAD_CAST module.PinpadSNExists);    
		if(  strcmp(module.PinpadSNExists,"Found") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "PinpadSN", BAD_CAST module.PinpadSN);    
		else 
			xmlNewChild(node, NULL, BAD_CAST "PinpadSN", NULL);    
	}
	if( CONFIG.BarcodeSno )
	{
		xmlNewChild(node, NULL, BAD_CAST "BarcodeSnoExists", BAD_CAST module.BarcodeSnoExists);
		if(  strcmp(module.BarcodeSnoExists,"Found") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "BarcodeSno", BAD_CAST module.BarcodeSno);
		else 
			xmlNewChild(node, NULL, BAD_CAST "BarcodeSno", NULL);
	}
	xmlNewChild(node, NULL, BAD_CAST "GSMVersionExists",BAD_CAST module.GSMVersionExists);
	if( strcmp(module.GSMVersionExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "GSMVersion",BAD_CAST module.GSM_Version);
	else 
		xmlNewChild(node, NULL, BAD_CAST "GSMVersion",NULL );
	if( access("/etc/autoapn/autoapn_config.xml",F_OK) == 0 )
	{
		xmlNewChild(node, NULL, BAD_CAST "GSM_ModuleExists",BAD_CAST module.GSM_ModuleExists);
		if(  strcmp(module.GSM_ModuleExists,"Yes") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "GSM_Module",BAD_CAST module.GSM_Module);
		else 
			xmlNewChild(node, NULL, BAD_CAST "GSM_Module", NULL);
	}
	if( CONFIG.WSSN)
	{
		xmlNewChild(node, NULL, BAD_CAST "WSSNExists", BAD_CAST module.WSSNExists);
		if( strcmp(module.WSSNExists,"Found") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "WSSN", BAD_CAST module.WSSN);
		else 
			xmlNewChild(node, NULL, BAD_CAST "WSSN", NULL);
	}
	if( CONFIG.CamType )
	{
		xmlNewChild(node, NULL, BAD_CAST "CamTypeExists", BAD_CAST module.CamTypeExists);
		if(strcmp(module.CamTypeExists,"Found") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "CamType", BAD_CAST module.CamType);
		else 
			xmlNewChild(node, NULL, BAD_CAST "CamType", NULL);
	}
	xmlNewChild(node, NULL, BAD_CAST "FPScanneridExists", BAD_CAST module.FPScanneridExists);
	if( strcmp(module.FPScanneridExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "FPScannerid", BAD_CAST module.scanner_id);
	else 
		xmlNewChild(node, NULL, BAD_CAST "FPScannerid", NULL );
	xmlNewChild(node, NULL, BAD_CAST "HardwareIDExists", BAD_CAST module.HardwareIDExists);
	if ( strcmp(module.HardwareIDExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "HardwareID", BAD_CAST module.HardwareID);
	else 
		xmlNewChild(node, NULL, BAD_CAST "HardwareID", NULL );
	xmlNewChild(node, NULL, BAD_CAST "WifiMACIDExists", BAD_CAST module.WifiMACIDExists);
	if ( CONFIG.WIFI )
	{
		if ( strcmp(module.WifiMACIDExists,"Yes") == 0 )
			xmlNewChild(node, NULL, BAD_CAST "WifiMACID", BAD_CAST module.WifiMACID);
		else    
			xmlNewChild(node, NULL, BAD_CAST "WifiMACID", NULL );	
	}
	xmlSaveFormatFileEnc(Hardware_Status_file, doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;
}
