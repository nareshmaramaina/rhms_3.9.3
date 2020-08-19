#include <header.h>
void Update_Comm_media(char *ip)
{
	char interface[99];
	memset(interface,0,sizeof(interface));

	Get_interface_name(interface,ip);
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

int Get_interface_name(char *interface,char *ip)
{

	char cmd[128]="";
	//	ip route get 216.58.197.67 | egrep -o "eth0|ppp0|wlan0|usb0|eth1"
	sprintf(cmd,"ip route get %s | egrep -o \"eth0|ppp0|wlan0|usb0|eth1\" > /tmp/.ip_address",ip); 
	fprintf(stdout,"cmd = %s \n",cmd);
	system(cmd);

	FILE *fp = fopen("/tmp/.ip_address", "r");
	if ( fp == NULL )
	{
		fprintf(stderr," /proc/net/arp file not found \n");
		return -1;
	}
	fread(interface,99,1,fp);
	
	fclose(fp);
        
	if(interface[strlen(interface)-1] == '\n')
                interface[strlen(interface)-1]='\0';

	remove("/tmp/.ip_address");
	return 0;
}
