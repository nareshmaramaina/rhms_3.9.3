#include<header.h>

int audio_test(void)
{
	int ret;

	ret = gl11_audio_power_on();

	memset(module.AUDIO,0,sizeof(module.AUDIO));
	if(ret!=0)
	{
		fprintf(stderr,"Unable to Poweron Audio Section\n");
		strcpy(module.AUDIO,"Failure");
		return -1;
	}

	msleep(20);

	ret = access("/usr/share/sounds/alsa/Side_Left.wav",F_OK);


	if( ret  != 0 )
	{
		strcpy(module.AUDIO,"Success");
		return 0;

	}

	// Check for the file, if file doesn't exists return success;

	ret = system ( "aplay /usr/share/sounds/alsa/Side_Left.wav &>/dev/null" );


	if(ret!=0)
	{
		strcpy(module.AUDIO,"Failure");
		printf("Audio test Failed\n");
		return -1;
	}
	else
	{
		strcpy(module.AUDIO,"Success");
		printf("Audio test success\n");
		return 0;
	}

}


