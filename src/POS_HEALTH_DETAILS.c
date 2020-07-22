#include <header.h>
#include <pthread.h>
extern int GPS_Success;
inline void msleep(int arg)
{
	usleep(1000*arg);
}

void	POS_HEALTH_DETAILS(void)
{
	short int i;

	DEVICE_DETAILS();

	PERIPHERALS();


	check_net_connection(); //Blocking For autoapn details

	Get_autoapn_wrote_details();		

	if ( strcmp(module.Comm,"ERROR") == 0 || strlen(module.Comm) == 0 ) 
		check_net_connection(); //Blocking For autoapn details

	if ( CONFIG.geo_location || CONFIG.GPS )
	{
		for(i = 0 ; i < 12; i++)
		{

			if ( CONFIG.GPS &&  ( access("/var/.gps_data.txt",F_OK )== 0 ) ) 
			{
				fprintf(stdout,"GPS Found\n");
				GPS_Success = 1;
				break;
			}

			else if ( CONFIG.geo_location && ( access("/var/.geo_cell.txt",F_OK) == 0 ) )
			{
				fprintf(stdout,"Geo Found\n");
				break;
			}
			else 
			{
				fprintf(stdout,"Location file not found, /var/.gps_data.txt or /var/.geo_cell.txt Waiting for geo cell id locations\n");
				sleep(10);
			}

		}

		sleep(1);
		Location_info();
	}

	return;
}

void 	DEVICE_DETAILS()
{
	update_macid_details();

	get_device_serialnumber();
	
	IMAGES();

	Uid_info();

	return;
}



void *sam_thread_function( void *ptr )
{

	if( CONFIG.SAM1 )
		sam_status(1);

	if( CONFIG.SAM2 )
		sam_status(2);
	return 0;
}


int  PERIPHERALS(void)
{

	int ret=0;

	fprintf(stdout,"\n\nRunning... io module health status\n\n");

	ret = gl11_iodev_open();

	if ( ret != 0)
	{
		fprintf(stderr,"gl11_iodev_open failed\n");
		return -1;
	}

	gl11_host_pwron();

	sleep(6); 

	update_usb_info();
	update_sdcard_info();

	SerialNo_and_Version_Based_Tags();

	/*if ( strstr(module.USB_memory,"Not" ) != NULL)
	{
		fprintf(stdout," module.USB_memory = %s, retrying... \n",module.USB_memory);

		sleep(2);

		update_usb_info();

		fprintf(stdout," module.USB_memory = %s \n",module.USB_memory);

	} */

	if( CONFIG.IFD1 || CONFIG.IFD2 )
	{
		ret=gl11_ifd_control(1);	

		if( CONFIG.IFD1 )
			memset(module.IFD1,0,sizeof(module.IFD1));	

		if( CONFIG.IFD2 )
			memset(module.IFD2,0,sizeof(module.IFD2));	
		if(ret!=0)
		{

			strcpy(module.IFD1,"Not Inserted");
			strcpy(module.IFD2,"Not Inserted");
			fprintf(stderr,"IFD power on Failure\n");
		}
		else 
		{
			if( CONFIG.IFD1 )
				ifd_status(1);

			if( CONFIG.IFD2 )
			{
				sleep(1);
				ifd_status(2);
			}

			gl11_ifd_control(0);	
		}
	}

	if( CONFIG.SAM1 || CONFIG.SAM2 )
	{
		pthread_t thread;
		ret = pthread_create( &thread, NULL, sam_thread_function, (void*) "SAM Thead");
		if( ret )
		{
			fprintf(stderr,"pthread_create() Failed return %d\n",ret);
			return -1;
		}
		fprintf(stdout,"Waiting for SAM Thread Compleation\n");
		pthread_join(thread,NULL);

	}

	if( CONFIG.Bluetooth )
		bluetooth_status();

	audio_test();


	if( CONFIG.Printer )
		printer_status();

	short int i=0,pwron = 1;

	for(i=0;i<5;i++)
	{
		if ( pwron )
		{
			ret = gl11_optcap_pwron(); 
			if( ret == 0)
			{
				pwron = 0;
				sleep(1);
			}
		}
		else
		{	
			fprintf(stderr,"  gl11_optcap_pwron failed\n");
			msleep(200);
			continue;
		}
		ret = update_fp_scanner_info();
		if( ret == 0)
			break;

		msleep(500);
	}

	if(ret != 0)
	{
		fprintf(stdout,"Taking scanner status from file\n");
		update_fpfile_info();

	}

	if ( strlen(module.scanner_id) == 0 || strstr(module.scanner_id,"Not-Detected") != NULL  )
	{
		fprintf(stdout,"Fetching Details From /etc/scanner_type file \n");
		FPS_Id_and_version();
	}



	if( CONFIG.Camera )
		camera_status();

	fprintf(stdout,"\n\nSuccess: io module health status details\n\n");



	gl11_iodev_close();

	return 0;
}


void SerialNo_and_Version_Based_Tags()
{
	Applications_Details();

	FirmwareDetails();

	if( CONFIG.IrisRDVer_and_SNo ) 
	{
		Iris_version();

		Iris_Scanner_Id();
	}
	if( CONFIG.BiomRDVer ) 
		Biomatiques_RD_version();

	if( CONFIG.CamType )
		Camera_info();

	if( CONFIG.WSSN )
		weighing_serialid_details();


	if( CONFIG.Pinpad )
		pinpad_status();

	if( CONFIG.FPSRDVer )
		FPS_RD_version();

	if(  CONFIG.BarcodeSno )
		barcode_SerialNo();

	if( CONFIG.DOT )
		Device_work_records();
	return;
}
