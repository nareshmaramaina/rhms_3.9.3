#include <header.h>

void printer_status()
{
	int ther_ret = 0;

	ther_ret = check_status();


	if(ther_ret > 1250 && ther_ret < 4070)
	{
		strcpy(module.Printer,"Yes");
		paper_status();
	}
	else
	{
		strcpy(module.Printer,"No");
		strcpy(module.paper,"No");
	}

	fprintf(stdout,"module.Printer = %s\tmodule.paper = %s\n",module.Printer,module.paper);
	return;
}

int check_status()
{
	const char *node_name="/sys/devices/platform/imx6q-ecspi.1/spi_master/spi1/spi1.1/aux3";

	int ret=0, fd=0;

	short int i=3, j=0;

	char temp[6]="";

	while(i > 0)
	{
		if((fd = open(node_name, O_RDONLY)) <0){
			fprintf(stderr,"Node File Open Error %s\n",node_name);
			return -1;
		}
		if((j = read(fd, temp, 5)) <0){
			fprintf(stderr,"%s Node File Read Error\n",node_name);
			return -1;
		}
		temp[j] = '\0';
		close(fd);
		ret += atoi(temp);
		i--;
	}
	return (ret/3);
}

int paper_status(void)
{


	int ret;

	memset(module.paper,0,sizeof(module.paper));
	
	prn_open();

	ret = prn_paperstatus();

	if(ret != 0)
	{
		strcpy(module.paper,"NotPresent");
		prn_close();
		return -1;
	}
	else
		strcpy(module.paper,"Present");

	prn_close();

	return 0;
}




