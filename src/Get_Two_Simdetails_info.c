#include <header.h>
int Get_Two_Simdetails_info(void)
{

	short int i=0,sim_details_ret=0,gprs_update_ret=0,operator_details_ret=0;
	char op_buff[80]="";
	char op1_buff[80]="";
	int imei_ccid=0;
	int op_rev=0;
	char IMEI_NUM[80]="";
	char gsm_version[50]="";
	char CCID_NUM[80]="";
	char CCID1_NUM[80]="";

	for ( i=0 ; i <  2 ; i++ )
	{
		sim_details_ret=retrieve_two_sim_details(CCID_NUM,IMEI_NUM,CCID1_NUM);
		if ( sim_details_ret == -1)
			sleep(1);
		else 
			break;	
	}	

	memset(module.IMEI_no,0,sizeof(module.IMEI_no));
	memset(module.CCID,0,sizeof(module.CCID));
	memset(module.Sim2CCID,0,sizeof(module.Sim2CCID));

	if(sim_details_ret != 0)
	{

		strcpy(module.IMEI_no,"NotFound");
		strcpy(module.CCID,"NotFound");
		strcpy(module.Sim2CCID,"NotFound");

		printf("module.IMEI_no:%s\n",module.IMEI_no);
		printf("module.CCID_no:%s\n",module.CCID);
		printf("module.Sim2CCID_no:%s\n",module.Sim2CCID);

	}
	else
	{
		strcpy(module.IMEI_no,IMEI_NUM);
		strcpy(module.CCID,CCID_NUM);
		strcpy(module.Sim2CCID,CCID1_NUM);

		printf("module.IMEI_no:%s\n",module.IMEI_no);
		printf("module.CCID_no:%s\n",module.CCID);
		printf("module.Sim2CCID_no:%s\n",module.Sim2CCID);
	}


	for ( i=0 ; i <  2 ; i++ )
	{
		gprs_update_ret = retrieve_two_signal_details(module.Sim1_db,module.Sim2_db);
		if ( gprs_update_ret == -1)
			sleep(1);
		else 
			break;	

	}


	operator_details_ret = read_two_revision_operator_details(op_buff,op1_buff,gsm_version);

	memset(module.operator1_name,0,sizeof(module.operator1_name));
	memset(module.operator2_name,0,sizeof(module.operator1_name));
	memset(module.GSM_Version,0,sizeof(module.GSM_Version));

	if( operator_details_ret != 0)
	{
		strcpy(module.operator1_name,"NotFound");
		printf("Operator1 Name %s\n",module.operator1_name);
		strcpy(module.operator2_name,"NotFound");
		printf("Operator2 Name %s\n",module.operator2_name);

		strcpy(module.GSM_Version,"NotFound");
		printf("GSM Firmware Version %s\n",module.GSM_Version);
		op_rev=1;
	}
	else
	{
		strcpy(module.operator1_name,op_buff);
		strcpy(module.operator2_name,op1_buff);
		strcpy(module.GSM_Version,gsm_version);
#if DEBUG
		printf("Operator Names  1) %s  2) %s \n ",module.operator1_name,module.operator2_name);
		printf("GSM Firmware Version %s\n",module.GSM_Version);
#endif
		op_rev=0;

	}

	printf("Flags op_rev **%d**\n,imei_ccid **%d**\n",op_rev,imei_ccid);
	if( sim_details_ret != 0 || gprs_update_ret != 0 || operator_details_ret != 0)
	{
		printf("---> Failed to fetch gprs details\n");
		return -1;
	}
	return 0;

}


int read_two_revision_operator_details(char *operator1,char *operator2,char *revision_buff)
{
	FILE *fd;
	int i=0;
	int j=0;
	char tmpbuf[256]="";
	char operator1_buff[50]="";
	char operator2_buff[50]="";
	char other_details_buff[150]="";
	memset(other_details_buff,0,sizeof(other_details_buff));

	fd=fopen("/tmp/revision_operator_details","r");
	if(fd==NULL)
	{
		fprintf(stderr,"/tmp/revision_operator_details open error\n");
		return -1;
	}

	fread(other_details_buff,1,150,fd);
#if DEBUG
	printf("Revision_Operator_Details---->%s\n",other_details_buff);
#endif
	fclose(fd);
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
	operator_check(operator1_buff,operator1);
	operator_check(operator2_buff,operator2);

	if(strlen(revision_buff)==0)
		strcpy(revision_buff,"NotFound");
#if DEBUG

	printf("Operator1 %s : ****buff = %s**** \t Operator2:%s *****buff= %s ***** Revision:****%s*** \n",operator1,operator1_buff,operator2,operator2_buff,revision_buff);
#endif
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
#if DEBUG 
	fprintf(stdout,"BUFF:***%s***\n",buff);
#endif
	fclose(fp);

	memset(SIM1,0,sizeof(SIM1));
	memset(SIM2,0,sizeof(SIM2));

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
	int i=0,j;
	char *tmpbuf="";
	char sim_details_buff[256]="";

	memset(sim_details_buff,0,sizeof(sim_details_buff));
	fp=fopen("/tmp/sim_details","r");

	if(fp == NULL)
	{
		fprintf(stderr,"/tmp/sim_details file Not Found\n");
		return -1;
	}

	fgets(sim_details_buff,sizeof(sim_details_buff),fp);

	if(	sim_details_buff[strlen(sim_details_buff)-1] == '\n')
		sim_details_buff[strlen(sim_details_buff)-1]='\0';

	for(j=0;sim_details_buff[j];j++)
	{
		if(sim_details_buff[j] == ' ')
		{
			memmove(sim_details_buff+j,sim_details_buff+j+1,strlen(sim_details_buff+j+1)+1);
			j--;
		}
	}

	fclose(fp);
	tmpbuf=sim_details_buff;

	memset(ccid_buff,0,sizeof(ccid_buff));
	for(i=0;i<40;i++)
	{
		if (tmpbuf[i]!=',')
			ccid_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	strcpy(tmpbuf,tmpbuf+i);
	memset(ccid1_buff,0,sizeof(ccid1_buff));

	for(i=0;i<40;i++)
	{
		if (tmpbuf[i] != ',')
			ccid1_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	strcpy(tmpbuf,tmpbuf+i);
	memset(imei_buff,0,sizeof(imei_buff));

	for(i=0;i<40;i++)
	{
		if (tmpbuf[i]!=',')
			imei_buff[i]=tmpbuf[i];
		else
			break;
	}

	if(strlen(ccid_buff) == 0)
		strcpy(ccid_buff,"NotFound");

	if(strlen(imei_buff) == 0)
		strcpy(imei_buff,"NotFound");

	if(strlen(ccid1_buff) == 0)
		strcpy(ccid1_buff,"NotFound");
	printf("IMEI:****%s****\t CCID:****%s***\t CCID1:%s \n",imei_buff,ccid_buff,ccid1_buff);
	return 0;

}

