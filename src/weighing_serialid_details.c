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

	memset(module.WSSN,0,sizeof(module.WSSN));

	ret = system("/etc/rc.d/init.d/bluetooth start &> /dev/null");

	if ( ret != 0 )
	{
		fprintf(stderr," /etc/rc.d/init.d/bluetooth start command failed\n");
		strcpy(module.WSSNExists,"NotFound");
		return;
	}

	for( i = 0 ; i < 3 ; i++ )	
	{
		memset( macid , 0 , sizeof(macid) );

		get_bluetooth_macid(macid); // Function To get macid of  APPDS_VNTK@2015 device 

		if( strlen(macid) != 0)
		{
			strcpy(module.WSSN,macid);
			strcpy(module.WSSNExists,"Found");
			fprintf(stdout,"Macid of APPDS_VNTK@2015 BT device  = %s\nmodule.WSSN = %s\n",macid,module.WSSN);
			break;
		}

		else 
		{
			strcpy(module.WSSNExists,"NotFound");
			sleep(30);	

			fprintf(stderr,"%d Macid of APPDS_VNTK@2015 BT device  = %s\nmodule.WSSN = %s\n",i,macid,module.WSSN);
		}

	}
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
