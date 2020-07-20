#include <header.h>


void Uid_info()
{
	char uid_buff[40]="";
	short int ret;
	ret = gl11_getuid(uid_buff);

	if(ret!=0)
		strcpy(module.Uid_no,"ERROR");
	else
		strcpy(module.Uid_no,uid_buff);
	fprintf(stdout,"module.Uid_no = %s\n",module.Uid_no);	
	return;
}



void get_device_serialnumber(void)  // Updating Device serial number in RHMS health structures
{
	short int ret=0;

	char machineid[30];

	memset(machineid,0x00,sizeof(machineid));

	memset(module.SerialNo,0,sizeof(module.SerialNo));

	ret = get_machineid(machineid);

	if(ret != 0 || strlen(machineid) != 10)
	{
		fprintf(stdout,"MachineID Error\n");
		strcpy(module.SerialNo,"ERROR");
		strcpy(module.TerminalID,"ERROR");
	}

	else 
	{
		strcpy(module.TerminalID,machineid);

		if(machineid[0]=='1' && machineid[1]=='1')
			sprintf(module.SerialNo,"1%s",machineid);

		else if (machineid[0]=='1' && machineid[1]>'4')
			sprintf(module.SerialNo,"11%s",machineid);

		else if(machineid[1] == '0')
			sprintf(module.SerialNo,"111%s",machineid);

		else
			sprintf(module.SerialNo,"ERROR");
	}


	if ( (strcmp(module.SerialNo,"ERROR") ) == 0 || strlen(module.SerialNo) == 0 )
	{
		memset(module.SerialNo,0,sizeof(module.SerialNo));

		sprintf(module.SerialNo,"%c%c%c%c%c%c%c%c%c%c%c%c",module.macid[0],module.macid[1],module.macid[3],module.macid[4],module.macid[6],module.macid[7],module.macid[9],module.macid[10],module.macid[12],module.macid[13],module.macid[15],module.macid[16]);

	}	
	fprintf(stdout,"module.TerminalID = %s\tmodule.SerialNo = %s\n",module.TerminalID,module.SerialNo);
	return;
}


int get_machineid(char *machineid)
{

	short int ret=0,i;
	FILE *fp=NULL;

	for ( i=0; i< 5;i++)
	{
		ret = system("fw_printenv  machineid | cut -d '=' -f2 > /tmp/.RHMSmachineid");

		if ( ret == 0)
			break;

		sleep(1);
	}

	fp = fopen("/tmp/.RHMSmachineid", "r");

	if(fp ==NULL)
	{

		fprintf(stderr,"LIB#Unable To Open The /tmp/.RHMSmachineid\n");
		return -1;

	}

	fscanf(fp,"%s",machineid);
	fclose(fp);
	remove("/tmp/.RHMSmachineid");

	return 0;
}

void update_macid_details()
{
	char mac_buff[30];
	int ret;

	memset(mac_buff,0x00,sizeof(mac_buff));
	memset(module.macid,0,sizeof(module.macid));

	ret = gl11_getmacid(mac_buff);

	if(ret == 0)
		strcpy(module.macid,mac_buff);
	else
		strcpy(module.macid,"ERROR");

	fprintf(stdout,"module.macid = %s\n",module.macid);

	return;
}


