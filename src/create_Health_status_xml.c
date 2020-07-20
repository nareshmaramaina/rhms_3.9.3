#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *Health_Status_file="/opt/Health_Status.xml";


/*int  create_xml_file(void)
  {
  short int ret=0;

  char remote_xml_bkp_file[32]="";

  char Path[24]="";


  remove(remote_status_file);

  xml_frame();

  ret=access(remote_status_file,F_OK);

  if(ret == -1)
  {
  fprintf(stderr," %s open failed\n",remote_status_file);
  return -1;
  }

  mkdir_p("/var/log/Health/");

//if( CONFIG.HWChanged )
copy_file("/var/log/Health/Last_remote_status.xml",remote_status_file);//des,src


memset(remote_xml_bkp_file,0,sizeof(remote_xml_bkp_file));

memset(Path,0,sizeof(Path));

sprintf(Path,"/var/log/Health/%c%c",module.Date_time[2],module.Date_time[3]);

mkdir_p(Path);

sprintf(remote_xml_bkp_file,"%s/day_%c%c.xml",Path,module.Date_time[0],module.Date_time[1]);

copy_file(remote_xml_bkp_file,remote_status_file);

return 0;

}*/



//int Health_Status_xml_frame()
int main()
{
	fprintf(stdout,"\n\n Health_Status.xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, childnode = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,  "HealthStatus");
	xmlDocSetRootElement(doc, root_node);


	xmlNewChild(root_node, NULL, BAD_CAST "SerialNo",BAD_CAST module.SerialNo);
	xmlNewChild(root_node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);
	
	//if( CONFIG.GPS || CONFIG.geo_location )
	childnode = xmlNewChild(root_node, NULL, BAD_CAST "GPS",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Latitude", BAD_CAST &module.GPS.Latitude);
		xmlNewChild(childnode, NULL, BAD_CAST "Longitude", BAD_CAST &module.GPS.Longitude);
		xmlNewChild(childnode, NULL, BAD_CAST "Captured_Time", BAD_CAST module.GPS.Captured_Time);
		xmlNewChild(root_node, NULL, BAD_CAST "IRIS", BAD_CAST module.IRIS);
	//if( CONFIG.Printer )
		xmlNewChild(root_node, NULL, BAD_CAST "PaperStatus", BAD_CAST module.paper);
	
	xmlNewChild(root_node, NULL, BAD_CAST "RTC", BAD_CAST module.RTC);
	xmlNewChild(root_node, NULL, BAD_CAST "Adapter", BAD_CAST module.Adapter);
	xmlNewChild(root_node, NULL, BAD_CAST "Battery", BAD_CAST module.Battery_status);
	xmlNewChild(root_node, NULL, BAD_CAST "Comm", BAD_CAST module.Comm);
	xmlNewChild(root_node, NULL, BAD_CAST "SIM1db", BAD_CAST module.Comm);
	xmlNewChild(root_node, NULL, BAD_CAST "SIM2db", BAD_CAST module.Comm);
	xmlNewChild(root_node, NULL, BAD_CAST "SIM1SignalMode", BAD_CAST module.Comm);
	xmlNewChild(root_node, NULL, BAD_CAST "SIM2SignalMode", BAD_CAST module.Comm);
	
	
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
