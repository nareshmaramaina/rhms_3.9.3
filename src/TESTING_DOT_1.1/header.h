#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include<sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <termios.h>
#include<unistd.h>
#include <dirent.h>
#define BTINFO 1
#define DEBUG 1
int gl11_iodev_open(void);
int gl11_iodev_close(void);
int gl11_GetBatteryInfo(int *Apresent, int *Bpresent, int *Bvolts);
int  Device_working_secs();
int Adapter_status(int *adapter, int *Charging, int *Discharging);
int Calculate_time_diff(char *file_name);
int makedir_p(char *dirname);
