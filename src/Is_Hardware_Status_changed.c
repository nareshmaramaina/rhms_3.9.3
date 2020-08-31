#include <header.h>
int parse_device_details (xmlDocPtr doc, xmlNodePtr cur) 
{
	short int IrisRDVer_and_SNo=0,PinpadSN=0,BarcodeSno=0,CamType=0,WSSN=0,autoapn_config=0,WiFiMACID=0;
	xmlChar *key = NULL;
	for ( cur = cur->xmlChildrenNode; cur != NULL;key=NULL, cur = cur->next)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"SerialNo")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);


			if ( 	key != NULL  &&  strcmp(module.SerialNo,(const char *)key) != 0 )
			{
				printf("Changed present module.Serialno = %s , Last xml SerialNo  %s\n", module.SerialNo,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.SerialNo) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.SerialNo = %s\n",module.SerialNo);
				xmlFree(key);
				return 1;	
			}
			xmlFree(key);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"TerminalID")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if ( 	key != NULL  &&  strcmp(module.TerminalID,(const char *)key) != 0 )
			{
				printf("Changed present module.TerminalID = %s , Last xml TerminalID =  %s\n", module.TerminalID,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.TerminalID) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.TerminalID = %s\n",module.TerminalID);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"Macid")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  && strcmp(module.macid,(const char *)key) != 0 )
			{
				printf("Changed present module.macid = %s , Last xml macid %s\n", module.macid,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.macid) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.macid = %s\n",module.macid);
				xmlFree(key);
				return 1;
			}


			xmlFree(key);

		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"UbootImageName")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  && strcmp(module.UbootVersion,(const char *)key) != 0 )
			{
				printf("Changed present module.UbootVersion = %s , Last xml UbootVersion %s\n", module.UbootVersion,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.UbootVersion) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.UbootVersion = %s\n",module.UbootVersion);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"KernelImageName")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  && strcmp(module.KernelVersion,(const char *)key) != 0 )
			{
				printf("Changed present module.KernelVersion = %s , Last xml KernelVersion %s\n", module.KernelVersion,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.KernelVersion) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.KernelVersion = %s\n",module.KernelVersion);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RootfsImageName")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  && strcmp(module.rootfs_details,(const char *)key) != 0 )
			{
				printf("Changed present module.rootfs_details = %s , Last xml rootfs_details %s\n", module.rootfs_details,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.rootfs_details) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.rootfs_details = %s\n",module.rootfs_details);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}


		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"IMEInumber")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if ( 	key != NULL && strcmp(module.IMEI_no,(const char *)key) != 0 )
			{
				printf("Changed present module.IMEI_no = %s , Last xml IMEI_no %s\n", module.IMEI_no,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.IMEI_no) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.IMEI_no = %s\n",module.IMEI_no);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}

		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"UID")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if( (key != NULL )  && strcmp(module.Uid_no,(const char *)key) != 0 )
			{
				printf("Changed present module.Uid_no = %s , Last xml Uid_no %s\n", module.Uid_no,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.Uid_no) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.Uid_no = %s\n",module.Uid_no);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);


		}

		else if (CONFIG.IrisRDVer_and_SNo && (!xmlStrcmp(cur->name, (const xmlChar *)"IritechSnoExists")))
			IrisRDVer_and_SNo=1;

		else if (CONFIG.IrisRDVer_and_SNo && (!xmlStrcmp(cur->name, (const xmlChar *)"IritechSno")))
		{

			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if( ( key != NULL )  && strcmp(module.IritechSno,(const char *)key) != 0 )
			{
				printf("Changed present module.IritechSno = %s , Last xml IritechSno %s\n", module.IritechSno,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.IritechSno) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.IritechSno = %s\n",module.IritechSno);
				xmlFree(key);
				return 1;
			}

			xmlFree(key);

		}
		else if (CONFIG.PinpadSN && (!xmlStrcmp(cur->name, (const xmlChar *)"PinpadSNExists")))
			PinpadSN=1;
		else if (CONFIG.PinpadSN && (!xmlStrcmp(cur->name, (const xmlChar *)"PinpadSN")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.PinpadSN,(const char *)key) != 0 )
			{
				printf("Changed present module.PinpadSN = %s , Last xml PinpadSN %s\n", module.PinpadSN,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.PinpadSN) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.PinpadSN = %s\n",module.PinpadSN);
				xmlFree(key);
				return 1;
			}


			xmlFree(key);

		}
		else if (CONFIG.BarcodeSno && (!xmlStrcmp(cur->name, (const xmlChar *)"BarcodeSnoExists")))
			BarcodeSno = 1;
		else if (CONFIG.BarcodeSno && (!xmlStrcmp(cur->name, (const xmlChar *)"BarcodeSno")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.BarcodeSno,(const char *)key) != 0 )
			{
				printf("Changed present module.BarcodeSno = %s , Last xml BarcodeSno %s\n", module.BarcodeSno,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.BarcodeSno) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.BarcodeSno = %s\n",module.BarcodeSno);
				xmlFree(key);
				return 1;
			}


			xmlFree(key);

		}
		else if ( (!xmlStrcmp(cur->name, (const xmlChar *)"GSMVersion")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.GSM_Version,(const char *)key) != 0 )
			{
				printf("Changed present module.GSM_Version = %s , Last xml GSM_Version %s\n", module.GSM_Version,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.GSM_Version) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.GSM_Version = %s\n",module.GSM_Version);
				xmlFree(key);
				return 1;
			}


			xmlFree(key);

		}
		else if (access("/etc/autoapn/autoapn_config.xml",F_OK) == 0 && (!xmlStrcmp(cur->name, (const xmlChar *)"GSM_ModuleExists")))
			autoapn_config =1;
		else if (access("/etc/autoapn/autoapn_config.xml",F_OK) == 0 && (!xmlStrcmp(cur->name, (const xmlChar *)"GSM_Module")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.GSM_Module,(const char *)key) != 0 )
			{
				printf("Changed present module.GSM_Module = %s , Last xml GSM_Module %s\n", module.GSM_Module,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.GSM_Module) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.GSM_Module = %s\n",module.GSM_Module);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}

		else if (CONFIG.CamType && (!xmlStrcmp(cur->name, (const xmlChar *)"CamTypeExists")))
			CamType=1;
		else if (CONFIG.CamType && (!xmlStrcmp(cur->name, (const xmlChar *)"CamType")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.CamType,(const char *)key) != 0 )
			{
				printf("Changed present module.CamType = %s , Last xml CamType %s\n", module.CamType,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.CamType) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.CamType = %s\n",module.CamType);
				xmlFree(key);
				return 1;
			}

			xmlFree(key);

		}

		else if ( CONFIG.WSSN && (!xmlStrcmp(cur->name, (const xmlChar *)"WSSNExists")) )
			WSSN=1;
		else if (CONFIG.WSSN && (!xmlStrcmp(cur->name, (const xmlChar *)"WSSN")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.WSSN,(const char *)key) != 0 )
			{
				printf("Changed present module.WSSN = %s , Last xml WSSN %s\n", module.WSSN,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.WSSN) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.WSSN = %s\n",module.WSSN);
				xmlFree(key);
				return 1;
			}


			xmlFree(key);

		}
		else if (   (!xmlStrcmp(cur->name, (const xmlChar *)"FPScannerid")) )
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if( (key != NULL )  && strcmp(module.scanner_id,(const char *)key) != 0 )
			{
				printf("Changed present module.scanner_id = %s , Last xml scanner_id %s\n", module.scanner_id,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.scanner_id) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.scanner_id = %s\n",module.scanner_id);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else if (   (!xmlStrcmp(cur->name, (const xmlChar *)"HardwareID")) )
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if( (key != NULL )  && strcmp(module.HardwareID,(const char *)key) != 0 )
			{
				printf("Changed present module.HardwareID = %s , Last xml HardwareID %s\n", module.HardwareID,key);
				xmlFree(key);
				return 1;
			}
			else if ( key == NULL && strlen(module.HardwareID) > 0 )
			{
				fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.HardwareID = %s\n",module.HardwareID);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		 else if (CONFIG.WIFI && (!xmlStrcmp(cur->name, (const xmlChar *)"WiFiMACIDExists")))
                        WiFiMACID=1;
                else if (CONFIG.WIFI && (!xmlStrcmp(cur->name, (const xmlChar *)"WiFiMACID")))
                {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        if( (key != NULL )  &&  strcmp(module.WiFiMACID,(const char *)key) != 0 )
                        {
                                printf("Changed present module.WiFiMACID = %s , Last xml WiFiMACID %s\n", module.WiFiMACID,key);
                                xmlFree(key);
                                return 1;
                        }
                        else if ( key == NULL && strlen(module.WiFiMACID) > 0 )
                        {
                                fprintf(stdout,"Last_Hardware xml has NULL, But current value having module.WiFiMACID = %s\n",module.WiFiMACID);
                                xmlFree(key);
                                return 1;
                        }


                        xmlFree(key);

                }

	}
	if( (CONFIG.IrisRDVer_and_SNo && IrisRDVer_and_SNo == 0 )|| (CONFIG.PinpadSN &&  PinpadSN == 0 ) || (CONFIG.BarcodeSno && BarcodeSno == 0 ) || (CONFIG.CamType && CamType == 0 ) || ( CONFIG.WSSN && WSSN == 0) || ( access("/etc/autoapn/autoapn_config.xml",F_OK) == 0  && autoapn_config == 0 ) || (CONFIG.WIFI && WiFiMACID == 0 ) )
	{
		printf("New Tag Enabled, (IrisRDVer_and_SNo/PinpadSN/BarcodeSno/CamType/WSSN/autoapn_config/WiFiMACID) \n");
		return 1;
	}
	printf("IrisRDVer_and_SNo = %d,PinpadSN = %d,BarcodeSno = %d,CamType = %d,WSSN = %d,autoapn_config = %d WiFiMACID =%d \n",IrisRDVer_and_SNo,PinpadSN,BarcodeSno,CamType,WSSN,autoapn_config,WiFiMACID);
	return 0;
}

int Is_Hardware_Status_changed()
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	short int ret=0;
	char *docname="/var/log/Health/Last_Hardware_Status.xml";

	ret = access(docname,F_OK);
	if ( ret != 0 )
	{
		fprintf(stdout," %s file not found\n",docname);
		return -1;
	}


	doc = xmlParseFile(docname);
	if (doc == NULL )
	{
		fprintf(stderr,"%s Document not parsed successfully. \n",docname);
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
	{
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "DeviceDetails")) 
	{
		fprintf(stderr,"%s document of the wrong type, root node != story\n",docname);
		xmlFreeDoc(doc);
		return -1;
	}


	ret = parse_device_details(doc,cur); 

	xmlFreeDoc(doc);
	//	printf("module.SerialNo= %s, module.TerminalID= %s, module.macid= %s, module.UbootVersion= %s, module.KernelVersion= %s, module.rootfs_details= %s, module.IMEI_no= %s, module.Uid_no= %s, module.IritechSno= %s, module.PinpadSN= %s, module.BarcodeSno= %s, module.GSM_Version= %s, module.GSM_Module= %s, module.CamType= %s, module.WSSN= %s, module.scanner_id= %s, module.HardwareID= %s\n", module.SerialNo, module.TerminalID, module.macid, module.UbootVersion, module.KernelVersion, module.rootfs_details, module.IMEI_no, module.Uid_no, module.IritechSno, module.PinpadSN, module.BarcodeSno, module.GSM_Version, module.GSM_Module, module.CamType, module.WSSN, module.scanner_id, module.HardwareID);

	if ( ret == 0 )
		fprintf(stdout,"No changes in Hardware info \n");
	else 
		fprintf(stdout,"changed in Hardware info\n");
	return ret;
}
