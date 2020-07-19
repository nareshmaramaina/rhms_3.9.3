#include<header.h>
extern char var_gprs[30];
void xml_type_Autoapn_details()
{

	char *docname="/tmp/rhms_details.xml";

	char operator1[64]="";

	char operator2[64]="";

	char operator[64]="";

	int sim_num=0,bars=0,Sig_Strength=0;

	char Sig_status='0';

	int Num=0;



	Autoapn_xmlparse(docname);


	if(strlen(module.GSM_Module) == 0 )
		strcpy(module.GSM_Module,"ERROR");

	if(strlen(module.GSM_Version) == 0 )
		strcpy(module.GSM_Version,"ERROR");

	if(strlen(module.IMEI_no) == 0 )
		strcpy(module.IMEI_no,"ERROR");

	if(strlen(module.CCID) == 0 )
		strcpy(module.CCID,"ERROR");

	if(strlen(module.Sim2CCID) == 0 )
		strcpy(module.Sim2CCID,"ERROR");

	if(strlen(module.Sim1_db) == 0 )
		strcpy(module.Sim1_db,"ERROR");

	if(strlen(module.Sim2_db) == 0 )
		strcpy(module.Sim2_db,"ERROR");

	if(strlen(module.operator1_name) == 0 )
		strcpy(module.operator1_name,"ERROR");

	if(strlen(module.operator2_name) == 0 )
		strcpy(module.operator2_name,"ERROR");

	if(strlen(module.WIFI) == 0 )
		strcpy(module.WIFI,"ERROR");       

	if(strlen(module.ethernet) == 0 )
		strcpy(module.ethernet,"ERROR");   

	memset(operator1,0,sizeof(operator1));
	memset(operator2,0,sizeof(operator2));

	operator_check(module.operator1_name,operator1);
	operator_check(module.operator2_name,operator2);

	if ( strcmp(operator1,"ERROR") != 0  || strcmp(module.Sim1_db,"ERROR") != 0 )
	{
		Num=1;
		strcpy(operator,operator1);
	}
	else if ( strcmp(operator2,"ERROR") != 0 || strcmp(module.Sim2_db,"ERROR") != 0 ) 
	{	
		Num=2;
		strcpy(operator,operator2);
	}
	else 
	{
		strcpy(operator,"ERROR");
		Num = 0;
	}


	if( CONFIG.Two_Simdetails_Autoapn == 0)
	{
		if (	strstr(module.CCID,"ERROR") != NULL )	
			strcpy(module.CCID,module.Sim2CCID); //For Single CCID case, when sim2 ccid enbled
	}



	if( strcmp(module.Comm,"GSM") == 0 )
	{

		sscanf(var_gprs,"%d,%c,%d,%d,",&sim_num,&Sig_status,&bars,&Sig_Strength);
		if (sim_num==0 && Sig_status == 0 )
		{
			sim_num = atoi(var_gprs);
			Sig_status = var_gprs[2];
		}
		( Sig_status  == 'E') ?  (Sig_status ='2') : (( Sig_status  == 'H') ? ( Sig_status ='3') : (( Sig_status  == 'L')  ? Sig_status ='4':1));

		if( CONFIG.Two_Simdetails_Autoapn )
		{
			if ( sim_num == 1 )
			{
				sprintf(module.Sim1_Details,"SIM%d/%ddb/%s/%cG",sim_num,Sig_Strength,operator1,Sig_status);
				sprintf(module.Sim2_Details,"SIM2/%sdb/%s/G",module.Sim2_db, operator2);

			}
			else if ( sim_num == 2 )
			{
				sprintf(module.Sim1_Details,"SIM1/%sdb/%s/G",module.Sim1_db, operator1);
				sprintf(module.Sim2_Details,"SIM%d/%ddb/%s/%cG",sim_num,Sig_Strength,operator2,Sig_status);

			}
			else fprintf(stderr," var_gprs data error %s\n",var_gprs);

		}

		else
			sprintf(module.Sim_Details,"SIM%d/%ddb/%s/%cG",sim_num,Sig_Strength,operator,Sig_status);
	}

	else 
	{	

		if( CONFIG.Two_Simdetails_Autoapn )
		{
			sprintf(module.Sim1_Details,"SIM1/%sdb/%s/G",module.Sim1_db, operator1);
			sprintf(module.Sim2_Details,"SIM2/%sdb/%s/G",module.Sim2_db, operator2);

		}
		else
		{	
			if( Num == 1 )
				sprintf(module.Sim_Details,"SIM1/%sdb/%s/G",module.Sim1_db,operator);
			else if( Num == 2 )
				sprintf(module.Sim_Details,"SIM2/%sdb/%s/G",module.Sim2_db,operator);
			else 
				sprintf(module.Sim_Details,"SIM%d/ERRORdb/%s/G",Num,operator);
		}

	}


	fprintf(stdout,"module.GSM_Version= %s\nmodule.IMEI_no= %s\nmodule.CCID= %s\nmodule.Sim2CCID= %s\nmodule.Sim1_db= %s\nmodule.Sim2_db= %s\nmodule.operator1_name= %s\nmodule.operator2_name= %s\nmodule.WIFI= %s\nmodule.ethernet = %s\n",module.GSM_Version,module.IMEI_no,module.CCID,module.Sim2CCID,module.Sim1_db,module.Sim2_db,module.operator1_name,module.operator2_name,module.WIFI,module.ethernet);	
	fprintf(stdout,"module.Sim1_Details = %s\nmodule.Sim2_Details = %s\n module.Sim_Details = %s\n",module.Sim1_Details,module.Sim2_Details,module.Sim_Details);
	return;

}
