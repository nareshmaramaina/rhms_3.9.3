#include <header.h>
//void Update_Comm_media()
int main()
{
	char interface[99];
	Get_interface_name(interface);
	if ( strlen(interface) == 0 )
		strcpy(module.Comm,"ERROR");
	else if ( strcmp(interface,"ppp0") == 0 )
		strcpy(module.Comm,"GSM");
	else if ( strcmp(interface,"wlan0") == 0 )
		strcpy(module.Comm,"WIFI");
	else if ( strcmp(interface,"eth0") == 0 )
		strcpy(module.Comm,"ETHERNET");
	else 
		strcpy(module.Comm,interface);

	fprintf(stdout," Interface found  by gethost is %s %s\n",interface,module.Comm);
	return;
}

int Get_interface_name(char *interface)
{
	char ip[99], hw[99], flags[99], mac[99], mask[99], dev[99]="", dummy[99]="";

	FILE *fp = fopen("/proc/net/arp", "r");
	if ( fp == NULL )
	{
		fprintf(stderr," /proc/net/arp file not found \n");
		return -1;
	}
	fgets(dummy, 99, fp); //header line

	fscanf(fp, "%s %s %s %s %s %s\n", ip, hw, flags, mac, mask, dev); 
	strcpy(interface,dev);	

	fclose(fp);

	return 0;
}
