#include <header.h>


void Uid_info()
{
	char uid_buff[40]="";
	short int ret;
	ret = gl11_getuid(uid_buff);

	if(ret!=0)
		strcpy(module.UIDExists,"Error");

	else
	{
		strcpy(module.Uid_no,uid_buff);
		strcpy(module.UIDExists,"Yes");
	}
	fprintf(stdout," UIDExists =%s\tmodule.Uid_no = %s\n",module.UIDExists,module.Uid_no);	

	return;
}



void get_device_serialnumber(void)  // Updating Device serial number in RHMS health structures
{
	short int ret=0;

	char machineid[50];

	memset(machineid,0x00,sizeof(machineid));

	memset(module.SerialNo,0,sizeof(module.SerialNo));

	ret = get_machineid(machineid);
	if(ret != 0 )
	{
		fprintf(stdout,"MachineID Error\n");
		strcpy(module.SerialNo,"Error");
		strcpy(module.TerminalIDExists,"NotFound");
	}
	else if ( strlen(machineid) != 10)
	{
		fprintf(stdout,"MachineID Invalid\n");
		strcpy(module.SerialNo,"Error");
		strcpy(module.TerminalIDExists,"Invalid");
		strcpy(module.TerminalID,machineid);
	}

	else 
	{
		strcpy(module.TerminalIDExists,"Found");
		strcpy(module.TerminalID,machineid);

		if(machineid[0]=='1' && machineid[1]=='1')
			sprintf(module.SerialNo,"1%s",machineid);

		else if (machineid[0]=='1' && machineid[1]>'4')
			sprintf(module.SerialNo,"11%s",machineid);

		else if(machineid[1] == '0')
			sprintf(module.SerialNo,"111%s",machineid);

		else
			sprintf(module.SerialNo,"Error");
	}


	if ( (strcmp(module.SerialNo,"Error") ) == 0 || strlen(module.SerialNo) == 0 )
	{
		memset(module.SerialNo,0,sizeof(module.SerialNo));
		
		strcpy(module.SerialNo,module.macid);

	}	
	fprintf(stdout,"module.TerminalIDExists =%s\tmodule.TerminalID = %s\tmodule.SerialNo = %s\n",module.TerminalIDExists,module.TerminalID,module.SerialNo);
	return;
}


int get_machineid(char *machineid)
{

	short int ret=0,i;
	FILE *fp=NULL;
	char Buffer[64]="";
	for ( i=0; i< 5;i++)
	{
		ret = system("fw_printenv  machineid > /tmp/.RHMSmachineid");
		if ( ret == 0)
			break;
		sleep(1);
	}

	if ( ret != 0 )
	{
		fprintf(stderr,"Machine ID not Found \n");
		return ret;
	}

	fp = fopen("/tmp/.RHMSmachineid", "r");

	if(fp ==NULL)
	{

		fprintf(stderr,"LIB#Unable To Open The /tmp/.RHMSmachineid\n");
		return -1;

	}
	fread(Buffer,sizeof(Buffer),1,fp);	
	fclose(fp);
	if ( strlen(Buffer) > 60 )
	{
		fprintf(stdout,"String length of machineid is  more than 50 digits\n");
		return ret;
	}
	strcpy(machineid,Buffer+10);
	if( machineid[strlen(machineid)-1] == '\n')
		machineid[strlen(machineid)-1] = '\0';

	remove("/tmp/.RHMSmachineid");
	return ret;
}

void update_macid_details()
{
	char mac_buff[30];
	int ret;

	memset(mac_buff,0x00,sizeof(mac_buff));
	memset(module.macid,0,sizeof(module.macid));

	ret = gl11_getmacid(mac_buff);

	if(ret == 0)
	{
		strcpy(module.macid,mac_buff);
		strcpy(module.MacidExists,"Yes");

	}
	else
		strcpy(module.MacidExists,"Error");

	fprintf(stdout,"module.MacidExists, = %s\tmodule.macid = %s\n",module.MacidExists,module.macid);

	return;
}


