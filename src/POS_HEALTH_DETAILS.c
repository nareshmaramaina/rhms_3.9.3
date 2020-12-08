#include <header.h>
#include <pthread.h>
extern int GPS_Success;
inline void msleep(int arg)
{
	usleep(1000*arg);
}

void	POS_HEALTH_DETAILS(void)
{

	Hardware_Status_Details();

	BootTime_Status_Details();

	Periodic_Health_Status_Details();

	return;
}

void 	Hardware_Status_Details()
{
	int ret;
	update_macid_details();

	get_device_serialnumber();


	ret  = system("grep Hardware /proc/cpuinfo  |grep MX25 -q");
	if ( ret == 0 )
	{
		imx25_IMAGES();
		imx25_Uid_info();
		fprintf(stdout,"This is Imx25 device\n");
	}
	else 
	{	
		IMAGES();
		Uid_info();
	}

	HardwareID_Details();

	External_Devices_SerialNo_info();

	return;
}

void  External_Devices_SerialNo_info()
{
	if ( CONFIG.WIFI &&  ( strcmp(module.WiFiMACIDExists,"Yes") != 0 ) )
	{
		fprintf(stdout,"Taking Wifi MACID Details At External Devices details\n");
		update_Wifi_MACID_details();
	}
	if( CONFIG.IrisRDVer_and_SNo ) 
		Iris_Scanner_Id();

	if( CONFIG.CamType )
		Camera_info();

	if( CONFIG.WSSN )
		weighing_serialid_details();

	if(  CONFIG.BarcodeSno )
		barcode_SerialNo();

	if( CONFIG.PinpadSN )
		pinpad_status();
}

void *sam_thread_function( void *ptr )
{

	if( CONFIG.SAM1 )
		sam_status(1);

	if( CONFIG.SAM2 )
		sam_status(2);
	return 0;
}


int  BootTime_Status_Details(void)
{

	short int i=0,pwron = 1,ret=0;

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

	Version_Based_Tags();

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

			strcpy(module.IFD1,"NotInserted");
			strcpy(module.IFD2,"NotInserted");
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

	if( CONFIG.Pinpad )
		pinpad_status(); 

	fprintf(stdout,"\n\nSuccess: io module health status details\n\n");



	gl11_iodev_close();

	check_net_connection(); //Blocking For autoapn details

	Get_autoapn_wrote_details();		

	if ( strcmp(module.Comm,"ERROR") == 0 || strlen(module.Comm) == 0 ) 
		check_net_connection(); //Blocking For autoapn details

	if ( CONFIG.WIFI &&  ( strcmp(module.WiFiMACIDExists,"Yes") != 0 ) )
	{
		fprintf(stdout,"module.WiFiMACIDExists Error, So Taking Wifi MACID Details After autoapn details\n");
		ret = update_Wifi_MACID_details();
		if ( ret != 0 )
		{
			system("ifconfig wlan0 up &");
			sleep(1);
			update_Wifi_MACID_details();
		}
	}

	if(strlen(module.AutoapnAppVersion) == 0)
		strcpy(module.AutoapnAppVersion,"NotFound");

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
				sleep(5);
			}

		}

		sleep(1);
		Location_info();
	}

	return 0;
}


void Version_Based_Tags()
{
	RHMSAppVersionDetails();

	FirmwareDetails();


	if( CONFIG.IrisRDVer_and_SNo ) 
		Iris_version();

	if( CONFIG.FPSRDVer )
	{
		FPS_RD_version();
		FPS_RD_SDK_version();
	}
	if( CONFIG.BiomRDVer ) 
		Biomatiques_RD_version();


	if( CONFIG.DOT )
		Device_work_records();
	return;
}
