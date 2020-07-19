//#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
char *config_file=".RHMS_config.xml";
#define CONFIG_Two_Simdetails_Autoapn "1"
#define	CONFIG_geo_location		"1"
#define CONFIG_BarcodeSno	"0"
#define CONFIG_Ethernet		"0"
#define CONFIG_Comm            	"1"
#define CONFIG_DOT              "1"
#define CONFIG_BatteryInfo      "1"
#define CONFIG_BiomRDVer      "1"
#define CONFIG_Iris_or_Biomat             "1"
#define CONFIG_IrisRDVer_and_SNo     "0"
#define CONFIG_IritechSno     	"0"
#define CONFIG_CamType 	        "1"
#define CONFIG_WSSN             "1"
#define CONFIG_Pinpad           "1"
#define CONFIG_PinpadSN		"1"
#define CONFIG_GPS              "1"
#define CONFIG_FPSRDVer         "1"
#define CONFIG_Bluetooth        "1"
#define CONFIG_SAM1             "1"
#define CONFIG_SAM2             "1"
#define CONFIG_Printer          "1"
#define CONFIG_WIFI             "1"
#define CONFIG_IFD1             "1"
#define CONFIG_IFD2             "1"
#define CONFIG_Camera           "1"
#define CONFIG_RTC		"0"
#define CONFIG_AUDIO		"0"
#define CONFIG_HWChanged        "1"
#define CONFIG_FingerPrint	"0"
#define CONFIG_FPScannerid	"0"
int main()
{
	remove(config_file);
	fprintf(stdout,"\n\nxml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr node = NULL ;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	node = xmlNewNode(NULL,  "RHMS_Settings");
	xmlDocSetRootElement(doc, node);


//	xmlNewChild(node, NULL, BAD_CAST "Comm", BAD_CAST CONFIG_Comm);
	xmlNewChild(node, NULL, BAD_CAST "DOT", BAD_CAST CONFIG_DOT);
	xmlNewChild(node, NULL, BAD_CAST "BatteryInfo", BAD_CAST CONFIG_BatteryInfo);
	xmlNewChild(node, NULL, BAD_CAST "Iris_or_Biomat", BAD_CAST CONFIG_Iris_or_Biomat);
	xmlNewChild(node, NULL, BAD_CAST "IrisRDVer_and_SNo", BAD_CAST CONFIG_IrisRDVer_and_SNo);
	xmlNewChild(node, NULL, BAD_CAST "BiomRDVer", BAD_CAST CONFIG_BiomRDVer);
	xmlNewChild(node, NULL, BAD_CAST "CamType", BAD_CAST CONFIG_CamType);
	xmlNewChild(node, NULL, BAD_CAST "WSSN", BAD_CAST CONFIG_WSSN);
	xmlNewChild(node, NULL, BAD_CAST "Pinpad", BAD_CAST CONFIG_Pinpad);
	xmlNewChild(node, NULL, BAD_CAST "PinpadSN", BAD_CAST CONFIG_PinpadSN);    
	xmlNewChild(node, NULL, BAD_CAST "FPSRDVer", BAD_CAST CONFIG_FPSRDVer);
	xmlNewChild(node, NULL, BAD_CAST "GPS", BAD_CAST CONFIG_GPS);
	xmlNewChild(node, NULL, BAD_CAST "geo_location", BAD_CAST CONFIG_geo_location);
	xmlNewChild(node, NULL, BAD_CAST "BarcodeSno", BAD_CAST CONFIG_BarcodeSno);
	xmlNewChild(node, NULL, BAD_CAST "HWChanged", BAD_CAST CONFIG_HWChanged);
	xmlNewChild(node, NULL, BAD_CAST "Bluetooth", BAD_CAST CONFIG_Bluetooth);
	xmlNewChild(node, NULL, BAD_CAST "SAM1", BAD_CAST CONFIG_SAM1);
	xmlNewChild(node, NULL, BAD_CAST "SAM2", BAD_CAST CONFIG_SAM2);
	xmlNewChild(node, NULL, BAD_CAST "Printer", BAD_CAST CONFIG_Printer);
	xmlNewChild(node, NULL, BAD_CAST "WIFI", BAD_CAST CONFIG_WIFI);
	xmlNewChild(node, NULL, BAD_CAST "IFD1", BAD_CAST CONFIG_IFD1);
	xmlNewChild(node, NULL, BAD_CAST "IFD2", BAD_CAST CONFIG_IFD2);
	xmlNewChild(node, NULL, BAD_CAST "Camera", BAD_CAST CONFIG_Camera);
	xmlNewChild(node, NULL, BAD_CAST "Two_Simdetails_Autoapn",BAD_CAST CONFIG_Two_Simdetails_Autoapn);

	xmlSaveFormatFileEnc(config_file, doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();
	fprintf(stdout,"\nSuccessfully created %s file...\n",config_file);

	return 0;

}
