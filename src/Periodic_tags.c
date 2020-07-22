#include<header.h>
extern char var_gprs[30];
extern int GPS_Success;
void Second_Time_Health_Info_sending_for_GPS()
{
	short int i,ret;

	for ( i = 0 ; i < 15 ; i++ )
	{

		ret = access("/var/.gps_data.txt",F_OK );
		if ( ret == 0 )
		{
			GPS_Success = 1;

			Location_info();

			fprintf(stdout,"GPS Success\n");

			break;	
		}

		fprintf(stderr,"/var/.gps_data.txt file not found, Waiting for GPS information ...\n");
		sleep(60);
	}

	return;
}
void Periodic_tags(void)
{
	short int ret;

	if ( CONFIG.geo_location || CONFIG.GPS )
		Location_info();

	if( CONFIG.Iris_or_Biomat )
		iris_status();


	ret = gl11_iodev_open();
	if ( ret != 0)
	{
		fprintf(stderr,"gl11_iodev_open failed\n");
		return;
	}

	else 
	{
		if( CONFIG.Printer )
			printer_status();

		battery_status();


		gl11_iodev_close();

	}

	Update_Simdb_and_Signalmode();	
	update_internal_memory_info();
	update_ram_info();

	return;
}
void Update_Simdb_and_Signalmode()
{
	int sim_num=0,bars=0,Sig_Strength=0;
	char Sig_status='0';
	memset(module.SIM1SignalMode,0,sizeof(module.SIM1SignalMode));
	memset(module.SIM2SignalMode,0,sizeof(module.SIM2SignalMode));

	if(strlen(module.Sim1_db) == 0 )
		strcpy(module.Sim1_db,"Not Found");
	else 
	{
		Sig_Strength=atoi(module.Sim1_db);
		Sig_Strength = (Sig_Strength*2)-113;
		sprintf(module.Sim1_db,"%dDB",Sig_Strength);
	}

	if(strlen(module.Sim2_db) == 0 )
		strcpy(module.Sim2_db,"Not Found");
	else 
	{
		Sig_Strength=atoi(module.Sim2_db);
		Sig_Strength = (Sig_Strength*2)-113;
		sprintf(module.Sim2_db,"%dDB",Sig_Strength);
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

		Sig_Strength = (Sig_Strength*2)-113;
		if ( sim_num == 1 )
		{	
			memset(module.Sim1_db,0,sizeof(module.Sim1_db));
			sprintf(module.Sim1_db,"%dDB",Sig_Strength);
			sprintf(module.SIM1SignalMode,"%cG",Sig_status);	
			strcpy(module.SIM2SignalMode,"No");
		}
		else if ( sim_num == 2 )
		{
			memset(module.Sim2_db,0,sizeof(module.Sim2_db));
			sprintf(module.Sim2_db,"%dDB",Sig_Strength);
			sprintf(module.SIM2SignalMode,"%cG",Sig_status);	
			strcpy(module.SIM1SignalMode,"No");

		}
		else fprintf(stderr," var_gprs data error %s\n",var_gprs);

	}

	else 
	{
		strcpy(module.SIM1SignalMode,"No");
		strcpy(module.SIM2SignalMode,"No");
	}
	fprintf(stdout,"module.Sim1_db = %s,module.SIM1SignalMode, = %s, module.Sim2_db = %s,module.SIM2SignalMode, = %s\n",module.Sim1_db,module.SIM1SignalMode,module.Sim2_db,module.SIM2SignalMode);
	return;
}	
