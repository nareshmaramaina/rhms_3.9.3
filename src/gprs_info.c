#include <header.h>


int gprs_details(void)
{
	short int i=0,rev_operator_ret,SimDetails_ret=0,GPRS_update_ret=0;
	char IMEI_NUM[80]="";
	char gsm_version[50]="";
	char CCID_NUM[60]="";
	char operator_buff[30]="";
	int sim=0;
	memset(operator_buff,0,sizeof(operator_buff));

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
                strcpy(module.IMEInumberExists,"Error");
		strcpy(module.SIM1CCIDnumberExists,"NO_SIM");

	}

	else
	{
                strcpy(module.IMEInumberExists,"Yes");
		strcpy(module.SIM1CCIDnumberExists,"Yes");
		strcpy(module.IMEI_no,IMEI_NUM);
		strcpy(module.CCID,CCID_NUM);

		printf("module.IMEI_no:%s\n",module.IMEI_no);
		printf("module.CCID_no:%s\n",module.CCID);
	}


	rev_operator_ret = read_revision_operator_details(operator_buff,gsm_version);

	memset(module.GSM_Version,0,sizeof(module.GSM_Version));
	if( rev_operator_ret != 0)
	{
		strcpy(module.GSMVersionExists,"Error");
		strcpy(operator_buff,"NotFound");
	}
	else
	{
		Check_and_Set_Operator_name(operator_buff);
       		strcpy(module.GSMVersionExists,"Yes");
		strcpy(module.GSM_Version,gsm_version);
		printf("module.GSM_Version:%s\n",module.GSM_Version);

	}

	sim = Get_Sim_num();
	if ( sim == 1)
		strcpy(module.operator1_name,operator_buff);	
	else if( sim == 2)
		strcpy(module.operator2_name,operator_buff);	



	if((rev_operator_ret != 0) || (GPRS_update_ret != 0 ) || (SimDetails_ret != 0 ))
	{
		fprintf(stderr,"---> Failed to fetch gprs details\n");
		return -1;
	}

	return 0;
}


int read_revision_operator_details(char *operator_buff,char *revision_buff)
{
	FILE *fp;
	int i=0;
	int j=0;
	char *tmpbuf=NULL;
	char file_buff[50]="";
	memset(file_buff,0,sizeof(file_buff));

	fp = fopen("/tmp/revision_operator_details","r");

	if(fp == NULL)
	{
		fprintf(stderr,"/tmp/revision_operator_details file not found\n");
		return -1;
	}

	fread(file_buff,1,50,fp);
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

	return 0;
}
int Get_Sim_num()
{
	FILE *fp;
	char buff[30]="";


	fp=fopen("/tmp/gprs_update","r");

	if(fp == NULL)
	{
		fprintf(stderr," /tmp/gprs_update file not found\n");
		return -1;
	}

	fread(buff,12,1,fp);

	fclose(fp);

	return atoi(buff);
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

	return 0;
}


