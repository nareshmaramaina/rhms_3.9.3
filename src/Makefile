CC =arm-none-linux-gnueabi-gcc -Wall

CFLAGS = -I ../include 

OBJS = main.o copy_file.o battery_info.o memory_info.o os_info.o  patch_info.o printer_info.o Update_Configured_Server_Addr.o usb_info.o dev_info.o xmlparser.o get_app_info.o POS_HEALTH_DETAILS.o fp_info.o sam_info.o audio_info.o   rtc_functions.o bt_info.o  ifd.o camera.o fpfile.o  iris.o pinpad_status.o FPS_RDVersion.o Device_work_records.o  iris_version.o get_iris_scanner.o weighing_serialid_details.o  Camera_type.o  Update_request.o  mkdir_p.o  operator_check.o  parse_rhms_config.o check_net_connection.o Get_autoapn_details.o check_internet_by_hostname.o autoapn_xmlparser.o is_RHMS_multiple_run.o barcode_SerialNo.o get_usbdevice_serialno.o Get_Two_Simdetails_info.o gprs_info.o Non_xml_type_Autoapn_details.o xml_type_Autoapn_details.o ethernet_info.o wifi_info.o gl11_bluetooth_control_dlopen.o Update_Comm_media.o biomatiques.o Location_info.o FPS_Id_and_version.o reboot_device.o Periodic_tags.o create_BootTime_Status_xml.o  create_Hardware_status_xml.o  create_Health_status_xml.o Send_Hardware_status_to_server.o Send_BootTime_Helath_status_to_server.o   Send_Periodic_Helath_status_to_server.o Update_Health_Statuses_dates.o Is_Hardware_Status_changed.o AutoapnAppVersionDetails.o  FingerRDServiceStatus.o Running_Apps_Details.o hwid.o ApplicationDownloadsDetails.o FirmwareDownloadsDetails.o  Get_Total_Downloaded_count.o Downloaded_DateAndTime_Version_Details.o Get_Tokens_of_Patchfile.o RHMSAppversionDetails.o Run_Loop.o

app:$(OBJS)
	$(CC) -g -o RHMSClientApp  $(OBJS) -L ../lib/ -lgl11pos -ltfm -lpcsclite -lxml2 -lz -lpthread   $(CFLAGS) 
	arm-none-linux-gnueabi-strip RHMSClientApp
	rm -rf *.o

main.o:main.c
	$(CC) -c main.c $(CFLAGS)

dev_info.o:dev_info.c
	$(CC) -c dev_info.c $(CFLAGS)

ifd.o:ifd.c
	$(CC) -c ifd.c $(CFLAGS)
fpfile.o:fpfile.c
	$(CC) -c fpfile.c $(CFLAGS)

bt_info.o:bt_info.c
	$(CC) -c bt_info.c $(CFLAGS)

rtc_functions.o:rtc_functions.c
	$(CC) -c rtc_functions.c $(CFLAGS)

sam_info.o:sam_info.c
	$(CC) -c sam_info.c $(CFLAGS)

camera.o:camera.c
	$(CC) -c camera.c $(CFLAGS)
POS_HEALTH_DETAILS.o:POS_HEALTH_DETAILS.c
	$(CC) -c POS_HEALTH_DETAILS.c $(CFLAGS)

get_app_info.o:get_app_info.c
	$(CC) -c get_app_info.c $(CFLAGS)


printer_info.o:printer_info.c
	$(CC) -c printer_info.c $(CFLAGS)

fp_info.o:fp_info.c
	$(CC) -c fp_info.c $(CFLAGS)

battery_info.o:battery_info.c
	$(CC) -c battery_info.c $(CFLAGS)

memory_info.o:memory_info.c
	$(CC) -c memory_info.c $(CFLAGS) 

os_info.o:os_info.c
	$(CC) -c os_info.c $(CFLAGS)


xmlparser.o:xmlparser.c
	$(CC) -c xmlparser.c $(CFLAGS) 

patch_info.o:patch_info.c
	$(CC) -c patch_info.c $(CFLAGS)

Update_Configured_Server_Addr.o:Update_Configured_Server_Addr.c
	$(CC) -c Update_Configured_Server_Addr.c $(CFLAGS)


usb_info.o:usb_info.c
	$(CC) -c usb_info.c $(CFLAGS)

audio_info.o:audio_info.c
	$(CC) -c audio_info.c $(CFLAGS)
copy_file.o:copy_file.c
	$(CC) -c copy_file.c $(CFLAGS)
iris.o:iris.c
	$(CC) -c iris.c $(CFLAGS)
pinpad_status.o:pinpad_status.c
	$(CC) -c pinpad_status.c $(CFLAGS)
FPS_RDVersion.o:FPS_RDVersion.c
	$(CC) -c FPS_RDVersion.c $(CFLAGS)
	
Device_work_records.o:Device_work_records.c
	$(CC) -c Device_work_records.c $(CFLAGS)
iris_version.o:iris_version.c
	$(CC) -c iris_version.c $(CFLAGS)
get_iris_scanner.o:get_iris_scanner.c
	$(CC) -c get_iris_scanner.c $(CFLAGS)

weighing_serialid_details.o:weighing_serialid_details.c
	$(CC) -c weighing_serialid_details.c $(CFLAGS)
Camera_type.o:Camera_type.c
	$(CC) -c Camera_type.c $(CFLAGS)
Update_request.o:Update_request.c
	$(CC) -c Update_request.c $(CFLAGS)
mkdir_p.o:mkdir_p.c
	$(CC) -c mkdir_p.c $(CFLAGS)
operator_check.o:operator_check.c  
	$(CC) -c operator_check.c $(CFLAGS)
parse_rhms_config.o:parse_rhms_config.c
	$(CC) -c parse_rhms_config.c $(CFLAGS)
check_net_connection.o:check_net_connection.c
	$(CC) -c check_net_connection.c $(CFLAGS)
Get_autoapn_details.o:Get_autoapn_details.c
	$(CC) -c Get_autoapn_details.c $(CFLAGS)
check_internet_by_hostname.o:check_internet_by_hostname.c
	$(CC) -c check_internet_by_hostname.c $(CFLAGS)
autoapn_xmlparser.o:autoapn_xmlparser.c
	$(CC) -c autoapn_xmlparser.c $(CFLAGS)
biomatiques.o:biomatiques.c
	$(CC) -c biomatiques.c $(CFLAGS)
is_RHMS_multiple_run.o:is_RHMS_multiple_run.c
	$(CC) -c is_RHMS_multiple_run.c $(CFLAGS)
barcode_SerialNo.o:barcode_SerialNo.c
	$(CC) -c barcode_SerialNo.c $(CFLAGS)
get_usbdevice_serialno.o:get_usbdevice_serialno.c
	$(CC) -c get_usbdevice_serialno.c $(CFLAGS)
Get_Two_Simdetails_info.o:Get_Two_Simdetails_info.c
	$(CC) -c Get_Two_Simdetails_info.c $(CFLAGS)
gprs_info.o:gprs_info.c
	$(CC) -c gprs_info.c $(CFLAGS)
Non_xml_type_Autoapn_details.o:Non_xml_type_Autoapn_details.c
	$(CC) -c Non_xml_type_Autoapn_details.c $(CFLAGS)
xml_type_Autoapn_details.o:xml_type_Autoapn_details.c
	$(CC) -c xml_type_Autoapn_details.c $(CFLAGS)
ethernet_info.o:ethernet_info.c
	$(CC) -c ethernet_info.c $(CFLAGS)
wifi_info.o:wifi_info.c
	$(CC) -c wifi_info.c $(CFLAGS)
gl11_bluetooth_control_dlopen.o:gl11_bluetooth_control_dlopen.c
	$(CC) -c gl11_bluetooth_control_dlopen.c $(CFLAGS)
Update_Comm_media.o:Update_Comm_media.c
	$(CC) -c Update_Comm_media.c $(CFLAGS)
Location_info.o:Location_info.c
	$(CC) -c Location_info.c $(CFLAGS)
FPS_Id_and_version.o:FPS_Id_and_version.c
	$(CC) -c FPS_Id_and_version.c $(CFLAGS)
reboot_device.o:reboot_device.c
	$(CC) -c reboot_device.c $(CFLAGS)
Periodic_tags.o:Periodic_tags.c
	$(CC) -c Periodic_tags.c $(CFLAGS)
create_BootTime_Status_xml.o:create_BootTime_Status_xml.c 
	$(CC) -c create_BootTime_Status_xml.c $(CFLAGS)
create_Hardware_status_xml.o:create_Hardware_status_xml.c
	$(CC) -c create_Hardware_status_xml.c $(CFLAGS)
create_Health_status_xml.o:create_Health_status_xml.c
	$(CC) -c  create_Health_status_xml.c $(CFLAGS)
Send_Hardware_status_to_server.o:Send_Hardware_status_to_server.c
	$(CC) -c Send_Hardware_status_to_server.c $(CFLAGS)
Send_BootTime_Helath_status_to_server.o:Send_BootTime_Helath_status_to_server.c
	$(CC) -c Send_BootTime_Helath_status_to_server.c $(CFLAGS)
Send_Periodic_Helath_status_to_server.o:Send_Periodic_Helath_status_to_server.c
	$(CC) -c Send_Periodic_Helath_status_to_server.c $(CFLAGS)
Update_Health_Statuses_dates.o:Update_Health_Statuses_dates.c
	$(CC) -c  Update_Health_Statuses_dates.c $(CFLAGS)
Is_Hardware_Status_changed.o:Is_Hardware_Status_changed.c	
	$(CC) -c  Is_Hardware_Status_changed.c $(CFLAGS)
AutoapnAppVersionDetails.o:AutoapnAppVersionDetails.c  
	$(CC) -c AutoapnAppVersionDetails.c $(CFLAGS)
FingerRDServiceStatus.o:FingerRDServiceStatus.c
	$(CC) -c FingerRDServiceStatus.c $(CFLAGS)
Running_Apps_Details.o:Running_Apps_Details.c
	$(CC) -c Running_Apps_Details.c $(CFLAGS)
hwid.o:hwid.c
	$(CC) -c hwid.c $(CFLAGS)
ApplicationDownloadsDetails.o:ApplicationDownloadsDetails.c
	$(CC) -c ApplicationDownloadsDetails.c $(CFLAGS)
FirmwareDownloadsDetails.o:FirmwareDownloadsDetails.c
	$(CC) -c FirmwareDownloadsDetails.c $(CFLAGS)
Get_Total_Downloaded_count.o:Get_Total_Downloaded_count.c
	$(CC) -c Get_Total_Downloaded_count.c $(CFLAGS)
Downloaded_DateAndTime_Version_Details.o:Downloaded_DateAndTime_Version_Details.c
	$(CC) -c Downloaded_DateAndTime_Version_Details.c $(CFLAGS)
Get_Tokens_of_Patchfile.o:Get_Tokens_of_Patchfile.c
	$(CC) -c Get_Tokens_of_Patchfile.c $(CFLAGS)
RHMSAppversionDetails.o:RHMSAppversionDetails.c
	$(CC) -c RHMSAppversionDetails.c $(CFLAGS)
Run_Loop.o:Run_Loop.c
	$(CC) -c Run_Loop.c $(CFLAGS)
clean:
	rm -rf *.o RHMSClientApp
