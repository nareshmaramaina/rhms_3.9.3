#include <libxml/tree.h>
#include <libxml/parser.h>
#include <header.h>



int parseStory (xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	FILE *fp;

	fp=fopen("/etc/Health_response","w");

	if(fp==NULL)
	{
		fprintf(stderr,"/etc/Health_response File Not Created\n");
		return -1;
	}
	cur = cur->xmlChildrenNode;

	while( cur != NULL)
	{
		key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ( key )
			fprintf(fp,"%s:%s\n", cur->name, key);
			fprintf(stdout,"%s:%s\n", cur->name, key);
		cur = cur->next;
	}
	xmlFree(key);

	fclose(fp);
	return 0;
}

int parseDoc(char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;


	doc = xmlParseFile(docname);


	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "POSHealthDetailsResponse")) {
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return -1;
	}
	parseStory (doc, cur);
	xmlFreeDoc(doc);
	return 0;
}

