#include <header.h>
int parse_device_details (xmlDocPtr doc, xmlNodePtr cur) 
{
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
			xmlFree(key);


		}

		else if (CONFIG.IrisRDVer_and_SNo && (!xmlStrcmp(cur->name, (const xmlChar *)"IritechSno")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if( (key != NULL )  && strcmp(module.IritechSno,(const char *)key) != 0 )
			{
				printf("Changed present module.IritechSno = %s , Last xml IritechSno %s\n", module.IritechSno,key);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else if (CONFIG.PinpadSN && (!xmlStrcmp(cur->name, (const xmlChar *)"PinpadSN")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.PinpadSN,(const char *)key) != 0 )
			{
				printf("Changed present module.PinpadSN = %s , Last xml PinpadSN %s\n", module.PinpadSN,key);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else if (CONFIG.BarcodeSno && (!xmlStrcmp(cur->name, (const xmlChar *)"BarcodeSno")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.BarcodeSno,(const char *)key) != 0 )
			{
				printf("Changed present module.BarcodeSno = %s , Last xml BarcodeSno %s\n", module.BarcodeSno,key);
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
			xmlFree(key);

		}
		else if (access("/etc/autoapn/autoapn_config.xml",F_OK) == 0 && (!xmlStrcmp(cur->name, (const xmlChar *)"GSM_Module")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.GSM_Module,(const char *)key) != 0 )
			{
				printf("Changed present module.GSM_Module = %s , Last xml GSM_Module %s\n", module.GSM_Module,key);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}

		else if (CONFIG.CamType && (!xmlStrcmp(cur->name, (const xmlChar *)"CamType")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.CamType,(const char *)key) != 0 )
			{
				printf("Changed present module.CamType = %s , Last xml CamType %s\n", module.CamType,key);
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}

		else if (CONFIG.WSSN && (!xmlStrcmp(cur->name, (const xmlChar *)"WSSN")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if( (key != NULL )  &&  strcmp(module.WSSN,(const char *)key) != 0 )
			{
				printf("Changed present module.WSSN = %s , Last xml WSSN %s\n", module.WSSN,key);
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
			xmlFree(key);

		}
	}
	return 0;
}
int Is_Hardware_Status_changed()
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	short int ret=0;
	char *docname="/var/log/Health/Last_Hardware_status.xml";
	
	ret = access(docname,F_OK);
        if ( ret != 0 )
        {
                fprintf(stdout," %s file not found",docname);
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
	
	if ( ret == 0 )
		fprintf(stdout,"No changes in Hardware info \n");
	else 
		fprintf(stdout,"changed in Hardware info\n");
	return ret;
}
