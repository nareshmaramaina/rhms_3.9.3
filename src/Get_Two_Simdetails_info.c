#include <header.h>
int Get_Two_Simdetails_info(void)
{

	short int i=0,sim_details_ret=0,gprs_update_ret=0,operator_details_ret=0;
	char op_buff[80]="";
	char op1_buff[80]="";
	char IMEI_NUM[80]="";
	char gsm_version[50]="";
	char CCID_NUM[80]="";
	char CCID1_NUM[80]="";
	fprintf(stdout,"Configured Two Sim Details autoapn Mode\n");
	for ( i=0 ; i <  10 ; i++ )
	{
		sim_details_ret = retrieve_two_sim_details(CCID_NUM,IMEI_NUM,CCID1_NUM);
		if ( sim_details_ret == -1)
			sleep(2);
		else 
			break;	
	}	

	memset(module.IMEI_no,0,sizeof(module.IMEI_no));
	memset(module.CCID,0,sizeof(module.CCID));
	memset(module.Sim2CCID,0,sizeof(module.Sim2CCID));

	if(sim_details_ret != 0)
	{
		strcpy(module.IMEInumberExists,"Error");
		strcpy(module.SIM1CCIDnumberExists,"NO_SIM");
		strcpy(module.SIM2CCIDnumberExists,"NO_SIM");

	}
	else
	{
		if(strlen(IMEI_NUM) > 0 )
		{
			strcpy(module.IMEInumberExists,"Yes");
			strcpy(module.IMEI_no,IMEI_NUM);
		}
		else 
			strcpy(module.IMEInumberExists,"Error");
		if(strlen(CCID_NUM) > 0 && strstr(CCID_NUM,"NO_SIM") == NULL )
		{
			strcpy(module.SIM1CCIDnumberExists,"Yes");
			strcpy(module.CCID,CCID_NUM);
		}
		else 
			strcpy(module.SIM1CCIDnumberExists,"NO_SIM");

		if(strlen(CCID1_NUM) > 0 && strstr(CCID1_NUM,"NO_SIM") == NULL  )
		{
			strcpy(module.SIM2CCIDnumberExists,"Yes");
			strcpy(module.Sim2CCID,CCID1_NUM);
		}
		else 
			strcpy(module.SIM2CCIDnumberExists,"NO_SIM");

	}


	/*for ( i=0 ; i <  2 ; i++ )
	{
		gprs_update_ret = retrieve_two_signal_details(module.Sim1_db,module.Sim2_db);
		if ( gprs_update_ret == -1)
			sleep(1);
		else 
			break;	

	}*/


	operator_details_ret = read_two_revision_operator_details(op_buff,op1_buff,gsm_version);

	memset(module.operator1_name,0,sizeof(module.operator1_name));
	memset(module.operator2_name,0,sizeof(module.operator1_name));
	memset(module.GSM_Version,0,sizeof(module.GSM_Version));

	if( operator_details_ret != 0)
	{
		strcpy(module.operator1_name,"NotFound");
		strcpy(module.operator2_name,"NotFound");
		strcpy(module.GSMVersionExists,"Error");
	}
	else
	{
		strcpy(module.GSMVersionExists,"Yes");
		if(strlen(gsm_version) > 0 )
		{
			strcpy(module.GSMVersionExists,"Yes");
			strcpy(module.GSM_Version,gsm_version);
		}
		else 
			strcpy(module.GSMVersionExists,"Error");

		strcpy(module.operator1_name,op_buff);
		strcpy(module.operator2_name,op1_buff);
		strcpy(module.GSM_Version,gsm_version);

	}

	if( sim_details_ret != 0 || gprs_update_ret != 0 || operator_details_ret != 0)
	{
		printf("---> Failed to fetch Two SIM gprs details\n");
		return -1;
	}
	return 0;

}


int read_two_revision_operator_details(char *operator1,char *operator2,char *revision_buff)
{
	FILE *fp;
	int i=0;
	int j=0;
	char tmpbuf[256]="";
	char operator1_buff[50]="";
	char operator2_buff[50]="";
	char other_details_buff[150]="";
	memset(other_details_buff,0,sizeof(other_details_buff));

	fp=fopen("/tmp/revision_operator_details","r");
	if(fp==NULL)
	{
		fprintf(stderr,"/tmp/revision_operator_details open error\n");
		return -1;
	}

	fread(other_details_buff,sizeof(other_details_buff),1,fp);
	
	fclose(fp);
	
	for(j=0;other_details_buff[j];j++)
	{
		if(other_details_buff[j]==' '||other_details_buff[j]=='\n'||other_details_buff[j]=='\t')
		{
			memmove(other_details_buff+j,other_details_buff+j+1,strlen(other_details_buff+j+1)+1);
			j--;
		}
	}
	sprintf(tmpbuf,"%s",other_details_buff);
	memset(operator1_buff,0,sizeof(operator1_buff));
	for(i=0;i<25;i++)
	{
		if (tmpbuf[i]!=',')
			operator1_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	strcpy(tmpbuf,tmpbuf+i);
	memset(operator2_buff,0,sizeof(operator2_buff));
	for(i=0;i<25;i++)
	{
		if (tmpbuf[i]!=',')
			operator2_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	strcpy(tmpbuf,tmpbuf+i);
	memset(revision_buff,0,sizeof(revision_buff));

	for(i=0;i<25;i++)
	{
		if (tmpbuf[i]!=',')
			revision_buff[i]=tmpbuf[i];
		else
			break;
	}

	Check_and_Set_Operator_name(operator1_buff);
	Check_and_Set_Operator_name(operator2_buff);

	strcpy(operator1,operator1_buff);
	strcpy(operator2,operator2_buff);

	return 0;
}


int retrieve_two_signal_details(char *SIM1,char *SIM2)
{
	FILE *fp;
	char buff[10]="";
	int i=0;


	fp=fopen("/tmp/gprs_update","r");

	if(fp==NULL)
	{
		fprintf(stderr,"/tmp/gprs_update file not found\n");
		return -1;
	}

	fread(buff,9,1,fp);
	
	fclose(fp);

	for(i=0;i<12;i++)
	{
		if (buff[i]!=',')
			SIM1[i]=buff[i];
		else
			break;
	}
	i++;
	strcpy(buff,buff+i);

	for(i=0;i<12;i++)
	{
		if (buff[i]!=',')
			SIM2[i]=buff[i];
		else
			break;
	}
	return 0;
}

int retrieve_two_sim_details(char *ccid_buff,char *imei_buff,char *ccid1_buff)
{
	FILE *fp;
	int i=0;
	char *tmpbuf="";
	char sim_details_buff[256]="";

	memset(sim_details_buff,0,sizeof(sim_details_buff));
	fp=fopen("/tmp/sim_details","r");

	if(fp == NULL)
	{
		fprintf(stderr,"/tmp/sim_details file Not Found\n");
		return -1;
	}

	fread(sim_details_buff,sizeof(sim_details_buff),1,fp);

	fclose(fp);

	if( sim_details_buff[strlen(sim_details_buff)-1] == '\n')
		sim_details_buff[strlen(sim_details_buff)-1]='\0';
	tmpbuf=sim_details_buff;

	for(i=0;i<40;i++)
	{
		if (tmpbuf[i]!=',')
			ccid_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	strcpy(tmpbuf,tmpbuf+i);

	for(i=0;i<40;i++)
	{
		if (tmpbuf[i] != ',')
			ccid1_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	strcpy(tmpbuf,tmpbuf+i);

	for(i=0;i<40;i++)
	{
		if (tmpbuf[i]!=',')
			imei_buff[i]=tmpbuf[i];
		else
			break;
	}

	printf("IMEI:****%s****\t CCID:****%s***\t CCID1:%s \n",imei_buff,ccid_buff,ccid1_buff);
	return 0;

}

