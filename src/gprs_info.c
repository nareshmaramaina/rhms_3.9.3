#include <header.h>

extern char var_gprs[30];

int gprs_details(void)
{
	short int i=0,rev_operator_ret,SimDetails_ret=0,GPRS_update_ret=0;
	int sim_num=0,bars=0,Sig_Strength=0;
	char operator[16]="";
	char Sig_status='0';
	char signal_strength[30]="";
	char IMEI_NUM[80]="";
	char gsm_version[50]="";
	char CCID_NUM[60]="";

	for ( i=0 ; i <  2 ; i++ )
	{	
		SimDetails_ret = retrieve_sim_details(CCID_NUM,IMEI_NUM);

		if ( SimDetails_ret == -1)
			sleep(1);
		else 
			break;	
	}	

	memset(module.IMEI_no,0,sizeof(module.IMEI_no));
	memset(module.CCID,0,sizeof(module.CCID));

	if(SimDetails_ret != 0)
	{
		strcpy(module.IMEI_no,"ERROR");
		strcpy(module.CCID,"ERROR");

		printf("\nmodule.IMEI_no:%s\n",module.IMEI_no);
		printf("module.CCID_no:%s\n",module.CCID);

	}

	else
	{
		strcpy(module.IMEI_no,IMEI_NUM);
		strcpy(module.CCID,CCID_NUM);

		printf("module.IMEI_no:%s\n",module.IMEI_no);
		printf("module.CCID_no:%s\n",module.CCID);
	}


	for ( i=0 ; i <  2 ; i++ )
	{

		if( strcmp(module.Comm,"GSM") == 0 )
		{
			strcpy(signal_strength,var_gprs);
			GPRS_update_ret = 0;

		}

		else
			GPRS_update_ret = retrieve_signal_details(signal_strength,"/tmp/gprs_update");

		if ( GPRS_update_ret == -1)
			sleep(1);
		else 
			break;	

	}

	if(GPRS_update_ret == 0 )	
	{
		sscanf(signal_strength,"%d,%c,%d,%d,",&sim_num,&Sig_status,&bars,&Sig_Strength);
		if( Sig_status != 'E' && Sig_status != 'H' && Sig_status != 'L')	
		{
			Sig_status='0';
			sim_num =0;
			Sig_Strength=0;
			printf("Sim not found\n");
		}	
		( Sig_status  == 'E') ?  (Sig_status ='2') : (( Sig_status  == 'H') ? ( Sig_status ='3') : (( Sig_status  == 'L')  ? Sig_status ='4':1));
	}
	else 
	{
		sim_num =0;
		Sig_status='0';
		Sig_Strength=0;
		printf("Getting Signal Details Failed\n");
	}

	rev_operator_ret = read_revision_operator_details(operator,gsm_version);

	memset(module.GSM_Version,0,sizeof(module.GSM_Version));
	if( rev_operator_ret != 0)
	{
		strcpy(module.GSM_Version,"ERROR");
		strcpy(operator,"ERROR");
		printf("module.GSM_Version:%s\n",module.GSM_Version);
	}
	else
	{
		strcpy(module.GSM_Version,gsm_version);
		printf("module.GSM_Version:%s\n",module.GSM_Version);

	}


	memset(module.Sim_Details,0,sizeof(module.Sim_Details));
	if( strcmp(module.Comm,"GSM") == 0 )
		sprintf(module.Sim_Details,"SIM%d/%ddb/%s/%cG",sim_num,Sig_Strength,operator,Sig_status);
	else 
		sprintf(module.Sim_Details,"SIM%d/%ddb/%s/G",sim_num,Sig_Strength,operator);
	printf("module.Sim_Details:%s\n",module.Sim_Details);

#if DEBUG
	printf("sim_num = %01d, Sig_status = %c,bars = %01d,Sig_Strength= %02d\n",sim_num,Sig_status,bars,Sig_Strength);
#endif

	if((rev_operator_ret != 0) || (GPRS_update_ret != 0 ) || (SimDetails_ret != 0 ))
	{
		fprintf(stderr,"---> Failed to fetch gprs details\n");
		return -1;
	}

	return 0;
}


int read_revision_operator_details(char *operator,char *revision_buff)
{
	FILE *fp;
	int i=0;
	int j=0;
	char *tmpbuf=NULL;
	char operator_buff[30]="";
	char file_buff[50]="";
	memset(file_buff,0,sizeof(file_buff));

	fp = fopen("/tmp/revision_operator_details","r");

	if(fp == NULL)
	{
		fprintf(stderr,"/tmp/revision_operator_details file not found\n");
		return -1;
	}

	fread(file_buff,1,50,fp);
#if DEBUG
	printf("Revision_Operator_Details buff = %s\n",file_buff);
#endif
	fclose(fp);





	for(j=0;file_buff[j];j++)
	{
		if(file_buff[j]==' '||file_buff[j]=='\n'||file_buff[j]=='\t')
		{
			memmove(file_buff+j,file_buff+j+1,strlen(file_buff+j+1)+1);
			j--;
		}
	}
	tmpbuf = file_buff;

	memset(operator_buff,0,sizeof(operator_buff));
	for(i=0;i<25;i++)
	{
		if (tmpbuf[i]!=',')
			operator_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;
	tmpbuf = tmpbuf+i;

	memset(revision_buff,0,sizeof(revision_buff));
	for(i=0;i<25;i++)
	{
		if (tmpbuf[i]!=',')
			revision_buff[i]=tmpbuf[i];
		else
			break;
	}

	if(strlen(revision_buff)==0)
		strcpy(revision_buff,"ERROR");

	for(i=0;operator_buff[i];i++)
		if(isupper(operator_buff[i]))
			operator_buff[i]+=32;

	operator_check(operator_buff,operator);
#if DEBUG
	printf("operator_buff = %s, Operator:****%s****\t Revision:****%s***\n",operator_buff,operator,revision_buff);
#endif

	return 0;
}

int retrieve_signal_details(char *sigval_buff,char *file)
{
	FILE *fp;
	char buff[30]="";

	fp=fopen(file,"r");

	if(fp == NULL)
	{
		fprintf(stderr,"%s file not found\n",file);
		return -1;
	}

	fread(buff,12,1,fp);

#if DEBUG
	printf("GPRS INFO:***%s***\n",buff);
#endif	
	strcpy(sigval_buff,buff);

	fclose(fp);
	if(strlen(sigval_buff) == 0 )
		return -1;
	return 0; 
}

int retrieve_sim_details(char *ccid_buff,char *imei_buff)
{
	FILE *fp;
	short int i=0,j;
	char *tmpbuf=NULL;
	char sim_details_buff[128]="";

	memset(sim_details_buff,0,sizeof(sim_details_buff));
	fp=fopen("/tmp/sim_details","r");

	if(fp == NULL)
	{
		fprintf(stderr,"/tmp/sim_details file not found\n");
		return -1;
	}

	fgets(sim_details_buff,80,fp);

	if(sim_details_buff[strlen(sim_details_buff)-1]=='\n')
		sim_details_buff[strlen(sim_details_buff)-1]='\0';

	for(j=0;sim_details_buff[j];j++)
	{
		if(sim_details_buff[j]==' ')
		{
			memmove(sim_details_buff+j,sim_details_buff+j+1,strlen(sim_details_buff+j+1)+1);
			j--;
		}
	}

	fclose(fp);

	tmpbuf = sim_details_buff;

	memset(ccid_buff,0,sizeof(ccid_buff));

	for(i=0; i<40 ;i++)
	{
		if (tmpbuf[i]!=',')
			ccid_buff[i]=tmpbuf[i];
		else
			break;
	}
	i++;

	tmpbuf=tmpbuf+i;

	memset(imei_buff,0,sizeof(imei_buff));

	for(i=0;i<40;i++)
	{
		if (tmpbuf[i] != ',')
			imei_buff[i]=tmpbuf[i];
		else
			break;
	}

	if(strlen(ccid_buff) == 0)
		strcpy(ccid_buff,"ERROR");

	if(strlen(imei_buff) == 0)
		strcpy(imei_buff,"ERROR");

#if DEBUG
	printf("IMEI:****%s****\t CCID:****%s***\n",imei_buff,ccid_buff);
#endif
	return 0;
}





