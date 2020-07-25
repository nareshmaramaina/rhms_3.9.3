#include <header.h>
int battery_status(void)
{
	int    adapter_status = 0;

	int    battery_status = 0;

	int    battery_ADC    = 0;

	double filter_voltage = 0;

	int    ret            = 0;

	int    i              = 0;

	memset(module.Adapter,0,sizeof(module.Adapter));  // memset all rhms battery varibles	

	memset(module.Battery_status,0,sizeof(module.Battery_status));

	for (i=0;i<5;i++)
	{
		ret = gl11_GetBatteryInfo( &adapter_status, &battery_status, &battery_ADC ); // Getting Battery information
		if (ret == 0 )
			break;
		usleep(500*1000);	
	}

	if(ret!=0)  // If battery information getting failed
	{
		fprintf(stderr,"Failed to Get Battery Details\n");

		strcpy(module.Adapter,"ERROR");

		strcpy(module.Battery_status,"ERROR");

		return -1;
	}

	if (adapter_status) 
	{
		strcpy(module.Adapter,"Connected");
	}
	else
	{
		strcpy(module.Adapter,"NotConnected");
	}
	fprintf(stdout,"Adaptor Status:%s\n",module.Adapter);

	filter_voltage = ( 8.4 * battery_ADC ) / 1024;

	if(battery_ADC > 400)
	{
		fprintf(stdout,"Battery is Connected\n");

		if(battery_status && adapter_status)
		{
			fprintf(stdout,"Battery is Charging\n");
			sprintf(module.Battery_status,"Charging-%0.2fV",filter_voltage);
		}
		else  if( !battery_status && adapter_status )
		{

			fprintf(stdout,"Battery is Fully charged\n");
			sprintf(module.Battery_status,"Charged-%0.2fV",filter_voltage);
		}
		else if (!battery_status && !adapter_status )
		{
			fprintf(stdout,"Battery is Discharging\n");
			sprintf(module.Battery_status,"Discharging-%0.2fV",filter_voltage);
		}

	}
	else
	{
		fprintf(stdout,"Battery is Not Connected\n");
		sprintf(module.Battery_status,"NotConnected-0.00V");
	}
	return 0;
}
