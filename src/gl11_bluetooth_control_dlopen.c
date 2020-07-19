#include<header.h>

int gl11_bluetooth_control_dlopen(int arg)
{
	void *handle;
	char (*bluetooth)(char);
	char *error;
	int ret =-1;

	handle = dlopen ("libgl11pos.so", RTLD_NOW);
	if (!handle) {
		fputs (dlerror(), stderr);
		return -1;
	}

	bluetooth = dlsym(handle, "gl11_bluetooth_control");
	if ((error = dlerror()) != NULL) 
       	{
		fputs(error, stderr);
		return -1;
	}
	ret =  (*bluetooth)(1);

	dlclose(handle);
	return ret;

}
/*int main()
{

	gl11_bluetooth_control_dlopen(1); 

}*/
