#include <header.h>
void IMAGES()
{
	char buf[150];
	int ret;

	memset(buf,0,sizeof(buf));
	ret = kernel_details(buf);
	if(ret == 0)
		strcpy(module.KernelVersion,buf);
	else
		strcpy(module.KernelVersion,"NotFound");

	memset(buf,0,sizeof(buf));
	ret = rootfs_details(buf);
	if(ret == 0)
		sscanf(buf,"%s",module.rootfs_details);
	//	strcpy(module.rootfs_details,buf);
	else
		strcpy(module.rootfs_details,"NotFound");

	memset(buf,0,sizeof(buf));

	ret = bootloader_details(buf);
	if(ret == 0)
		strcpy(module.UbootVersion,buf);
	else
		strcpy(module.UbootVersion,"NotFound");


	fprintf(stdout,"module.UbootVersion =  %s\nmodule.KernelVersion =  %s\nmodule.rootfs_details =  %s\n",module.UbootVersion,module.KernelVersion,module.rootfs_details);
	return;
}


void imx25_IMAGES()
{
	char buf[150];
	int ret;

	memset(buf,0,sizeof(buf));
	ret = imx25_kernel_details(buf);
	if(ret == 0)
		strcpy(module.KernelVersion,buf);
	else
		strcpy(module.KernelVersion,"NotFound");

	memset(buf,0,sizeof(buf));
	ret = rootfs_details(buf);
	if(ret == 0)
		sscanf(buf,"%s",module.rootfs_details);
		//strcpy(module.rootfs_details,buf);
	else
		strcpy(module.rootfs_details,"NotFound");

	memset(buf,0,sizeof(buf));

	ret = imx25_bootloader_details(buf);
	if(ret == 0)
		strcpy(module.UbootVersion,buf);
	else
		strcpy(module.UbootVersion,"NotFound");


	fprintf(stdout,"module.UbootVersion =  %s\nmodule.KernelVersion =  %s\nmodule.rootfs_details =  %s\n",module.UbootVersion,module.KernelVersion,module.rootfs_details);
	return;
}














