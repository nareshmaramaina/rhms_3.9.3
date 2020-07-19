#include <libxml/tree.h>
#include <libxml/parser.h>
#include <header.h>


void Autoapn_xmlparseStory (xmlDocPtr doc, xmlNodePtr cur) 
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;


	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"MODULE"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			if(key)
				strcpy(module.GSM_Module,(const char *)key);
			fprintf(stdout,"MODULE : %s\n", key);

			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"FIRMWARE")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.GSM_Version,(const char *)key);

			fprintf(stdout,"FIRMWARE : %s\n", key);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"IMEI"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.IMEI_no,(const char *)key);

			fprintf(stdout,"IMEI : %s\n", key);

			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"CCID1"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.CCID,(const char *)key);

			fprintf(stdout,"CCID1 : %s\n", key);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"CCID2"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.Sim2CCID,(const char *)key);

			fprintf(stdout,"CCID2 : %s\n", key);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Signal1"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.Sim1_db,(const char *)key);
			fprintf(stdout,"Signal1 : %s\n", key);
			xmlFree(key);
		}




		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Signal2"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.Sim2_db,(const char *)key);
			fprintf(stdout,"Signal2 : %s\n", key);
			xmlFree(key);
		}


		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Operator1"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.operator1_name,(const char *)key);
			fprintf(stdout,"Operator1 : %s\n", key);
			xmlFree(key);
		}


		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Operator2"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)
				strcpy(module.operator2_name,(const char *)key);
			fprintf(stdout,"Operator2 : %s\n", key);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"WIFI"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			fprintf(stdout,"WIFI : %s\n", key);

			if(key && strcmp((const char *)key,"0") != 0 )
				strcpy(module.WIFI,"OK");
			else strcpy(module.WIFI,"ERROR");


			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"ETHERNET"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key && strcmp((const char *)key,"0") != 0 )
				strcpy(module.ethernet,"Alive");
			else 	
				strcpy(module.ethernet,"ERROR");
			fprintf(stdout,"ETHERNET : %s\n", key);
			xmlFree(key);
		}
		cur = cur->next;
	}

	return ;
}
int Autoapn_xmlparse( char *docname )
{
	xmlDocPtr doc;
	xmlNodePtr cur;



	doc = xmlParseFile(docname);


	if (doc == NULL ) 
	{
		fprintf(stderr,"%s Document not parsed successfully. \n",docname);
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr,"%s empty document\n",docname);
		xmlFreeDoc(doc);
		return -1;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "RHMS_DETAILS")) 
	{
		fprintf(stderr,"%s document of the wrong type, root node != story",docname);
		xmlFreeDoc(doc);
		return -1;
	}

	Autoapn_xmlparseStory (doc, cur);
	
	xmlFreeDoc(doc);
	
	return 0;
}

