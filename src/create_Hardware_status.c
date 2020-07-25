#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *Hardware_Status_file="/opt/Hardware_status.xml";


int  create_Hardware_status_xml_file(void)
{
	short int ret=0;

	char remote_xml_bkp_file[64]="";

	char Path[24]="";

	remove(Hardware_Status_file);

	Hardware_xml_frame();

	ret=access(Hardware_Status_file,F_OK);

	if(ret == -1)
	{
		fprintf(stderr," %s open failed\n",Hardware_Status_file);
		return -1;
	}

	mkdir_p("/var/log/Health/");

	copy_file("/var/log/Health/Last_Hardware_status.xml",Hardware_Status_file);//des,src


	memset(remote_xml_bkp_file,0,sizeof(remote_xml_bkp_file));

	memset(Path,0,sizeof(Path));

	sprintf(Path,"/var/log/Health/%c%c",module.Date_time[2],module.Date_time[3]);

	mkdir_p(Path);

	sprintf(remote_xml_bkp_file,"%s/day_%c%c_Hardware_status.xml",Path,module.Date_time[0],module.Date_time[1]);

	copy_file(remote_xml_bkp_file,Hardware_Status_file);

	return 0;

}



int Hardware_xml_frame()
{
	fprintf(stdout,"\n\nxml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr node = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	node = xmlNewNode(NULL,  "DeviceDetails");
	xmlDocSetRootElement(doc, node);

	xmlNewChild(node, NULL, BAD_CAST "SerialNo",BAD_CAST module.SerialNo);
	xmlNewChild(node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);
	xmlNewChild(node, NULL, BAD_CAST "TerminalID",BAD_CAST module.MachineID);
	xmlNewChild(node, NULL, BAD_CAST "Macid", BAD_CAST module.macid);
	xmlNewChild(node, NULL, BAD_CAST "UbootImageName", BAD_CAST module.UbootVersion);
	xmlNewChild(node, NULL, BAD_CAST "KernelImageName", BAD_CAST module.KernelVersion);
	xmlNewChild(node, NULL, BAD_CAST "RootfsImageName", BAD_CAST module.rootfs_details);
	xmlNewChild(node, NULL, BAD_CAST "IMEInumber", BAD_CAST module.IMEI_no);
	xmlNewChild(node, NULL, BAD_CAST "UID", BAD_CAST module.Uid_no);
	if( CONFIG.IrisRDVer_and_SNo  )
		xmlNewChild(node, NULL, BAD_CAST "IritechSno", BAD_CAST module.IritechSno);

	if( CONFIG.PinpadSN )
		xmlNewChild(node, NULL, BAD_CAST "PinpadSN", BAD_CAST module.PinpadSN);    

	if( CONFIG.BarcodeSno )
		xmlNewChild(node, NULL, BAD_CAST "BarcodeSno", BAD_CAST module.BarcodeSno);
	
	xmlNewChild(node, NULL, BAD_CAST "GSMVersion",BAD_CAST module.GSM_Version);
	
		if( access("/etc/autoapn/autoapn_config.xml",F_OK) == 0 )
	xmlNewChild(node, NULL, BAD_CAST "GSM_Module",BAD_CAST module.GSM_Module);

	if( CONFIG.WSSN )
		xmlNewChild(node, NULL, BAD_CAST "WSSN", BAD_CAST module.WSSN);
	if( CONFIG.CamType )
		xmlNewChild(node, NULL, BAD_CAST "CamType", BAD_CAST module.CamType);
	xmlNewChild(node, NULL, BAD_CAST "FPScannerid", BAD_CAST module.scanner_id);

	xmlSaveFormatFileEnc(Hardware_Status_file, doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;
}
