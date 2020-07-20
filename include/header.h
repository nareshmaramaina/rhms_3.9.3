#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
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
#include <net/if.h>
#include<unistd.h>
#include<termios.h>
#include<errno.h>
#include <netdb.h> 
#include <resolv.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <dirent.h>
#include "../include/gl11.h"
#include "../include/tfmapi.h"
#include "../include/tfmerror.h"
#include "../include/tfmtypes.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <dlfcn.h>


#define TEST_REAL 0
#define OPTICAL 1
#define CAPACITIVE 2
#define NO_DEVICE 3

struct rhms
{
//short int Comm;
short int DOT;
short int BatteryInfo;
short int Iris_or_Biomat;
short int IrisRDVer_and_SNo;
short int geo_location;
short int CamType;
short int WSSN;
short int Pinpad;
short int PinpadSN;
short int FPSRDVer;
short int GPS;
short int BarcodeSno;
short int BiomRDVer;
//short int BiomSno;
short int HWChanged;
//short int FingerPrint;
//short int FPScannerid;
short int Bluetooth;
short int SAM1;
short int SAM2;
//short int Ethernet;
short int Printer;
short int WIFI;
short int IFD1;
short int IFD2;
short int Camera;
//short int RTC;
//short int AUDIO;
short int Two_Simdetails_Autoapn;

}CONFIG;


struct struct_Day
{
	char date[9];
	char time[5];
	char weekday[5];

}Date_Time;

char DOT_FILE[64];

  //char Date_Time[64]

/*struct POS
{
  char SerialNo[50]
  char TerminalID[64]
  char Macid[64]
  char UbootImageName[64]
  char KernelImageName[64]
  char RootfsImageName[64]
  char IMEInumber[64]
  char UID[64]
  char IritechSno[24]
  char PinpadSN[64]
  char BarcodeSno[32]
  char GSMVersion[64]
  char GSM_Module[64]
  char WSSN[32]
  char CamType[12]
  char FPScannerid[64]

}Hardware; */

typedef struct Memory
{
char Total[16];
char Use[16];
char Free[16];
}MEMORY;

typedef struct device 
{
 double Longitude,Latitude;
 char Captured_Time[24];
}Location;
struct Device_on_time 
{
char Date[14];
int Slot1;
int Slot2;
int Slot3;
int Slot4;
};

struct device_battery 
{
char Date[14];
int Day_worked_mins;
int Day_adapter_mins;
int Day_charged_mins;
int Day_discharged_mins;
};
struct terminal_status
{
	char BarcodeSno[32];
	char GeoLocation[80];
	char CamType[12];
	char Comm[12];
	char IRIS_VERSION[12];
	char LIB_BIO[10];
	char IRIS_ID[16]; 
	char IRIS[32];
	char IritechRDVer[10];
	char IritechSno[24];
	char BiomRDVer[10];
	char WSSN[32];
	char pinpad[32];
	char PinpadSN[64];
	char FPSRDVer[10];
	char HWChanged[12];
	char IFD1[10];
	char IFD2[10];
	char SAM1[10];
	char SAM2[10];
	char Bluetooth[15];
	char Printer[10];
	char paper[15];
	char scanner_id[80];
	char FP_TYPE[80];
	char Camera[10];
	char WIFI[10];
	char Date_time[40];
	char macid[20];
	char RTC[10];
	char Date[40];
	char app_type[40];
	char app_version[40];
	char GSM_Version[50];
	char Battery_status[80];
	char Battery[30];
	char Adapter[30];
	char fingerprint[10];
	char ethernet[20];
	
	char Sim2CCID[50];
	char operator1_name[50];
	char operator2_name[50];
	char Sim1_Details[120];
	char Sim2_Details[120];
	char Sim1_db[32];
	char Sim2_db[32];
	
	char GSM_Module[64];
	char CCID[50];
	char Sim_Details[120];
	
	MEMORY	InternalMem_Sysuser;
	MEMORY	InternalMem_Jffs2;
	MEMORY	RAM;
	MEMORY	ExternalMem;
	MEMORY	Usbdevice;
	MEMORY	System_memory;
	Location GPS;
	struct Device_on_time DOT; 
	struct device_battery BatteryInfo; 
	
	char AUDIO[20];
	char IMEI_no[40];
	char MachineID[50];
	char SerialNo[50];
	char Uid_no[40];
	char UbootVersion[50];
	char KernelVersion[50];
	char rootfs_details[50];
	char PatchVersion[10];
	char PatchName[50];
}module;


struct Details1{

	char Server_IP1[25];
	char Port_Num1[10];
};


struct Details1 SMS_Details1;
int Pos_Details( void );


int patch(void);
int get_machineid(char *);
void get_device_serialnumber(void);
void update_macid_details(void);
int get_app_details(void);
int battery_status(void);
int Ethernet_status(void);
int paper_status(void);
void printer_status(void);
int sam_status(int);
int Wifi_Status(void);
int dev_details(void);
int OS_Details(void);
int patch_ver(void);
int patch_name(void);
int internal_memory_status(void);
int update_sdcard_info(void);
int update_usb_info(void);
int update_ram_info(void);
int gprs_details(void);
int xml_frame(void);
int remote_server_update();
int Parsing_ACK_from_Server(void);
int battery_status(void);
int gl11_gsm_operator_name(char *);
int gl11_gsm_firmware_version(char *);
int run_io_health_status(void);
void optical_scanner_id(void);
void capacitive_scanner_id(void);
int server_updation(void);
int sim_operator_name(void);
int read_revision_operator_details(char *,char*);
int retrieve_signal_details(char *,char *);
void operator_check(char *,char *);
int create_xml_file(void);
int is_rhms_details_updated(void);
int update_date_status_file(void);
int usb_device_presence(char *,char *);
int update_pendrive_details(void);
int Get_Wifi_Status(void);
int check_status();
int camera_status(void);
int ifd_status(int);
int Send_to_Server( void );
int  get_project_details(char *server_ip, char *port_num, char *Project_name);
int audio_test(void);
int fp_type(void);
int bluetooth_status(void);
int opt_scanner_id(char *);
int cap_scanner_id(char *);
int Check_Physical_Existence(void);
inline void msleep(int arg);
int update_fp_scanner_info(void);
int send_health_info_to_server (void);
int copy_file (char *dest,char *src);
int update_internal_memory_info(void);
int Get_Ethernet_Status(void);
void update_fpfile_info(void);
int  check_presence(int times);
int fp_detect_type(void);
int iris_status(void);
void library_check(void);
void pinpad_status(void);
void Iris_version(void);
void Iris_Scanner_Id(void);
void attendence_record(void);
int  Device_work_records(void);
void weighing_serialid_details(void);
void FPS_RD_version();
void get_bluetooth_macid(char *);
int  GPS_info(char *);
int PINPAD_ModemOpen(char * );
int  (*PINPAD_Modemclose) (void);
int (*handshake)(void);
int (*Get_Pinpad_Serial_No)(unsigned char *);
int (*print_error_resp) (int );
int   PinpadSerialNo_info_by_dev_name(char *);
void Camera_info(void);
int parse_remote_staus_xml ();
void Uid_info(void);
int get_logname(char *file);
int retrieve_sim_details(char *ccid_buff,char *imei_buff);
int mkdir_p(char *dirname);
void Hardware_changed_info();
int Is_Hardware_changed(char *docname);
void Get_autoapn_wrote_details();
int Get_Two_Simdetails_info(void);
int read_two_revision_operator_details(char *operator1,char *operator2,char *revision_buff);
int retrieve_two_signal_details(char *SIM1,char *SIM2);
int retrieve_two_sim_details(char *ccid_buff,char *imei_buff,char *ccid1_buff);
void	POS_HEALTH_DETAILS(void);
void 	IMAGES(void);
int  PERIPHERALS(void);
void 	DEVICE_DETAILS();
int parse_config_file (xmlDocPtr doc, xmlNodePtr cur) ;
int Get_Config_Settings();
void check_net_connection();
int Check_internet_by_hostname(char *host,char *);
int Autoapn_xmlparse(char *);
int is_RHMS_multiple_run();
int RTC_info_and_Check_RHMS_run();
int get_Usb_device_serialno(char *Vendorid,char *ProductId,char *serialno);
void  barcode_SerialNo();
void xml_type_Autoapn_details();
void Non_xml_type_Autoapn_details();
int gl11_bluetooth_control_dlopen(int arg);
void Update_Comm_media(char *ip);
int Get_interface_name(char *interface,char *);
int Check_internet_by_hostname(char *host,char *ip);
void Biomatiques_RD_version();
int  GeoLocation_info(char *file);
void FPS_Id_and_version();
int  Location_info();
void SerialNo_and_Version_Based_Tags();
void Periodic_tags(void);
void Second_Time_Health_Info_sending_for_GPS();
void reboot_device(char last_digit); 
int  Get_Server_Addr(char *Server_Addr);

