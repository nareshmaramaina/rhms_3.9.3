#include<stdio.h>
       #include <dlfcn.h>

int gl11_wifi_rfcontrol_dlopen(int arg)
{
	void *handle;
	int (*wifi_rf)(int);
	char *error;
	int ret =-1;

	handle = dlopen ("libgl11pos.so", RTLD_LAZY);
	if (!handle) {
		fputs (dlerror(), stderr);
		return -1;
	}

	wifi_rf = dlsym(handle, "gl11_wifi_rfcontrol");
	if ((error = dlerror()) != NULL)  {
		fputs(error, stderr);
		return -1;
	}
	ret =  (*wifi_rf)(arg);
	dlclose(handle);
	return ret;

}
int main()
{

	gl11_wifi_rfcontrol_dlopen(1); 

}
