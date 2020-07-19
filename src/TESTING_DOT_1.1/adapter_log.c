#include"header.h"
#if BTINFO
int Adapter_status(int *adapter, int *Charging, int *Discharging)
{
	int	adapter_status = 0;

	int	battery_status = 0;

	int	battery_ADC    = 0;

	//double	filter_voltage = 0;

	int	ret            = 0;

	int	i              = 0;

	*adapter = 0, *Charging = 0, *Discharging = 0;

	ret = gl11_iodev_open();
	if ( ret != 0 )
	{
		fprintf(stderr," gl11_iodev_open failed\n");
		return -1;
	}

	for (i=0;i<5;i++)
	{
		ret = gl11_GetBatteryInfo( &adapter_status, &battery_status, &battery_ADC ); // Getting Battery information
		if (ret == 0 )
			break;
		usleep(500*1000);	
	}
	gl11_iodev_close();
	if(ret!=0)  // If battery information getting failed
	{
		fprintf(stderr,"Failed to Get Battery Details\n");

		return -1;
	}

	fprintf(stdout,"Adaptor Status:%d\n",adapter_status);


	//filter_voltage = ( 8.4 * battery_ADC ) / 1024;

	if(battery_ADC > 400)
	{
		fprintf(stdout,"Battery is Connected\n");

		if(battery_status && adapter_status)
		{
			fprintf(stdout,"Battery is Charging\n");
			*Charging = 1;
		}
		else  if( !battery_status && adapter_status )
		{

			fprintf(stdout,"Battery is Fully charged\n");

			*adapter = 1;

		}

		else if (!battery_status && !adapter_status )
		{
			fprintf(stdout,"Battery is Discharging\n");
			*Discharging = 1;
		}

	}
	else
	{
		*adapter = 1;
		fprintf(stdout,"Battery is Not Connected\n");
	}
	return 0;
}
#endif
