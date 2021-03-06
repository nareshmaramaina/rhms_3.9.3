#include<header.h>
void pinpad_status()
{
	short int i,ret;
	memset(module.pinpad,0x00,sizeof(module.pinpad));
	memset(module.PinpadSN,0x00,sizeof(module.PinpadSN));
	memset(module.PinpadSNExists,0x00,sizeof(module.PinpadSNExists));

	char PinpadSno[80]="";

	for(i=0;i<3;i++)
	{

		ret = usb_device_presence ("0483","5740");// kf311 pinpad vendorid productid

		if(ret == 0)
			break;

		ret = usb_device_presence ("15a2","0300");// P90 pinpad vendorid productid
		if(ret == 0)
			break;

		fprintf(stdout,"%d Searching pinpad Status ...\n",i+1);
		sleep(2);
	}
	if( ret == 0)
	{
		strcpy(module.pinpad,"Connected");

		if( CONFIG.PinpadSN )
		{


			FILE *fp = popen("/vision/Pinpad_SerialNo","r");
			if(fp == NULL)
			{
				fprintf(stderr,"/vision/Pinpad_SerialNo app Not found\n");
				strcpy(module.PinpadSNExists,"NotFound");
			}

			else
			{
				fprintf(stdout,"Waiting for Pinpad SerialNo ...\n");
				while(  fgets( PinpadSno,sizeof(PinpadSno),fp) != NULL ) 
				{
					if ( strstr(PinpadSno,"Pinpad_SerialNo:") != NULL )
					{
						strcpy(module.PinpadSNExists,"Found");
						sscanf(PinpadSno+16,"%s",module.PinpadSN);
						break;
					}
					memset(PinpadSno,0,sizeof(PinpadSno));
				}
				if ( strlen(module.PinpadSN) == 0 )
				{
					fprintf(stderr,"Pinpad_SerialNo: Not found\n");
					strcpy(module.PinpadSNExists,"NotFound");
				}
				fclose(fp);
			}	
			printf(" module.PinpadSN = %s\n",module.PinpadSN);	

		}		

	}

	else	
	{	
		strcpy(module.pinpad,"NotConnected");

		if ( CONFIG.PinpadSN )
			strcpy(module.PinpadSNExists,"NotFound");
		fprintf(stdout,"module.pinpad = %s\n",module.pinpad);
	}
	return;
}
/*int main()
  {

  pinpad_status();
  printf("module.pinpad = %s\n",module.pinpad);
  return 0;
  }*/
