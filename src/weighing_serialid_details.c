#include<header.h>
/*int main()
  {

  weighing_serialid_details();

  }*/
void weighing_serialid_details()
{

	char macid[20] ="";
	int i;
	short int  ret;
	static int Only_once=0;
	memset(module.WSSN,0,sizeof(module.WSSN));
	memset(module.WSSNExists,0,sizeof(module.WSSNExists));

	if ( Only_once == 0 )
	{
		fprintf(stdout," Running.. /etc/rc.d/init.d/bluetooth start command\n");
		ret = system("/etc/rc.d/init.d/bluetooth start &> /dev/null");

		if ( ret != 0 )
		{
			fprintf(stderr," /etc/rc.d/init.d/bluetooth start command failed\n");
			strcpy(module.WSSNExists,"NotFound");
			return;
		}
		Only_once=1;
	}

	for( i = 0 ; i < 3 ; i++ )	
	{
		memset( macid , 0 , sizeof(macid) );

		get_bluetooth_macid(macid); // Function To get macid of  APPDS_VNTK@2015 device 

		if( strlen(macid) != 0)
		{
			strcpy(module.WSSNExists,"Found");
			strcpy(module.WSSN,macid);
			fprintf(stdout,"Macid of APPDS_VNTK@2015 BT device  = %s\nmodule.WSSN = %s\n",macid,module.WSSN);
			return;
		}

		else 
		{
			sleep(30);	
			fprintf(stderr,"%d Macid of APPDS_VNTK@2015 BT device  = %s\nmodule.WSSN = %s\n",i,macid,module.WSSN);
		}

	}
	strcpy(module.WSSNExists,"NotFound");
	return;
}
void get_bluetooth_macid(char *macid)
{
	FILE *fp;
	char Buff[20]="";

	fprintf(stderr,"\nBluetooth device Scanning .....\n");


	system("hcitool scan | grep APPDS_VNTK@2015 > /tmp/BT_MACID.txt");

	fp = fopen("/tmp/BT_MACID.txt","r");

	if(fp == NULL)
	{
		fprintf(stderr,"unable to open scaning file \n");
		return ;
	}


	fread(Buff,20,1,fp);

	sscanf(Buff,"%s",macid);	

	fclose(fp);

	remove("/tmp/BT_MACID.txt");

	return;
}
