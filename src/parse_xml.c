#include <header.h>
int parse_device_details (xmlDocPtr doc, xmlNodePtr cur) 
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"SerialNo")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			printf("present module.SerialNo = %s , Last used SerialNo: %s\n", module.SerialNo,key);

			if ( 	(key != NULL )	&& (strcmp((const char *)key,"ERROR") != 0 ) && ( strcmp(module.SerialNo,"ERROR") != 0 )	&&	 (strlen(module.SerialNo) != 0 ) ) 	
			{
				if( strcmp(module.SerialNo,(const char *)key) != 0 )
				{
					xmlFree(key);
					return 1;
				}
				xmlFree(key);

			}
			else	printf("Ignoring Hardware change on key=ERROR / NULL case, In SerialNo tag \n");

		}

		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"IMEInumber")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			printf("present module.IMEI_no = %s , Last xml IMEI_no %s\n", module.IMEI_no,key);
			if ( 	(key != NULL )	&& (strcmp((const char *)key,"ERROR") != 0 ) && ( strcmp(module.IMEI_no,"ERROR") != 0 )	&&	 (strlen(module.IMEI_no) != 0 ) ) 	
			{
				if( strcmp(module.IMEI_no,(const char *)key) != 0 )
				{
					xmlFree(key);
					return 1;
				}
				xmlFree(key);

			}
			else	printf("Ignoring Hardware change on key=ERROR / NULL case, In IMEInumber tag\n");
		}

		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"UID")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			printf("present module.Uid_no = %s , Last xml Uid_no %s\n", module.Uid_no,key);
			if ( 	(key != NULL )	&&  (strcmp((const char *)key,"ERROR") != 0 ) && ( strcmp(module.Uid_no,"ERROR") != 0 )	&&	 (strlen(module.Uid_no) != 0 ) ) 	
			{
				if( strcmp(module.Uid_no,(const char *)key) != 0 )
				{
					xmlFree(key);
					return 1;
				}
				xmlFree(key);

			}
			else	printf("Ignoring Hardware change on key=ERROR / NULL case, In UID tag \n");

		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"Macid")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("present module.macid = %s , Last xml macid %s\n", module.macid,key);
			if ( 	(key != NULL )	&&(strcmp((const char *)key,"ERROR") != 0 ) &&	( strcmp(module.macid,"ERROR") != 0 )	&&	 (strlen(module.macid) != 0 ) ) 	
			{
				if( strcmp(module.macid,(const char *)key) != 0 )
				{
					xmlFree(key);
					return 1;
				}
				xmlFree(key);

			}
			else	printf("Ignoring Hardware change on key=ERROR / NULL case, In Macid tag\n");
		}

		key=NULL;
		cur = cur->next;
	}
	return 0;
}
int parse_peripherals (xmlDocPtr doc, xmlNodePtr cur) 
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if (   (!xmlStrcmp(cur->name, (const xmlChar *)"FPScannerid")) )
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("present module.scanner_id = %s , Last xml scanner_id %s\n", module.scanner_id,key);

			if ( 	(key != NULL )	&& (strcmp((const char *)key,"ERROR") != 0 ) && ( strcmp(module.scanner_id,"ERROR") != 0 )	&&	 (strlen(module.scanner_id) != 0 ) ) 	
			{
				if( strcmp(module.scanner_id,(const char *)key) != 0 )
				{
					xmlFree(key);
					return 1;
				}
				xmlFree(key);

			}
			else	printf("Ignoring Hardware change on key=ERROR / NULL case, In FPScannerid tag\n");
			//			}
	}
	else if (CONFIG.IrisRDVer_and_SNo && (!xmlStrcmp(cur->name, (const xmlChar *)"IritechSno")))
	{
		key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		printf("present module.IritechSno = %s , Last xml IritechSno %s\n", module.IritechSno,key);

		if ( 	(key != NULL )	&& (strcmp((const char *)key,"ERROR") != 0 ) &&	( strcmp(module.IritechSno,"ERROR") != 0 )	&&	 (strlen(module.IritechSno) != 0 ) ) 	
		{
			if( strcmp(module.IritechSno,(const char *)key) != 0 )
			{
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else	printf("Ignoring Hardware change on key=ERROR / NULL case, In IritechSno tag\n");
	}
	else if (CONFIG.WSSN && (!xmlStrcmp(cur->name, (const xmlChar *)"WSSN")))
	{
		key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		printf("present module.WSSN = %s , Last xml WSSN %s\n", module.WSSN,key);
		if ( 	(key != NULL )	&& (strcmp((const char *)key,"ERROR") != 0 ) &&	( strcmp(module.WSSN,"ERROR") != 0 )	&&	 (strlen(module.WSSN) != 0 ) ) 	
		{
			if( strcmp(module.WSSN,(const char *)key) != 0 )
			{
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else	printf("Ignoring Hardware change on key=ERROR / NULL case, In WSSN tag\n");
	}
	else if (CONFIG.BarcodeSno && (!xmlStrcmp(cur->name, (const xmlChar *)"BarcodeSno")))
	{
		key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		printf("present module.BarcodeSno = %s , Last xml BarcodeSno %s\n", module.BarcodeSno,key);
		if ( 	(key != NULL )	&& (strcmp((const char *)key,"ERROR") != 0 ) &&	( strcmp(module.BarcodeSno,"ERROR") != 0 )	&&	 (strlen(module.BarcodeSno) != 0 ) ) 	
		{
			if( strcmp(module.BarcodeSno,(const char *)key) != 0 )
			{
				xmlFree(key);
				return 1;
			}
			xmlFree(key);

		}
		else	printf("Ignoring Hardware change on key=ERROR / NULL case, In BarcodeSno tag\n");
	}
	key=NULL;
	cur = cur->next;
}
return 0;
}
int Is_Hardware_changed(char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	short int ret=0,Change_flag =0;

	doc = xmlParseFile(docname);
	if (doc == NULL )
	{
		fprintf(stderr,"Document not parsed successfully. \n");
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
	{
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "POSHEALTHDETAILS")) 
	{
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return -1;
	}

	cur = cur->xmlChildrenNode;

	while (cur != NULL) 
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"DEVICE_DETAILS")))
		{
			ret = 	parse_device_details (doc, cur);
			if ( ret == 1 )
			{
				Change_flag = 1;
				printf("DEVICE Hardware Changed %d\n",ret);
				break;
			}
			else 
				printf("DEVICE Hardware not  Changed %d\n",ret);

		}

		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PERIPHERALS")))
		{
			ret = parse_peripherals (doc, cur);
			if ( ret == 1 )
			{
				Change_flag = 1;
				printf("PERIPHERALS Hardware Changed %d\n",ret);
				break;

			}
			else 
				printf("PERIPHERALS Hardware not  Changed %d\n",ret);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);

	if( Change_flag)
		return 1;
	else 
		return 0;
}
