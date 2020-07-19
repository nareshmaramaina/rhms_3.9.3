int update_sd_details(void)
{

        char  *line=NULL;
        size_t len=0;
        FILE *fp=NULL;

        char Partition[24];
        int success_flag=0;


        system("df  -h | grep /dev/sda > /tmp/.USB_details");

        fp = fopen("/tmp/.USB_details","r");


        while(getline(&line, &len, fp)> 0)

                if(strstr(line,"/mnt/usb_test") != NULL)
                {
                        sscanf(line,"%s%s%s%s",Partition,module.Usbdevice.Total,module.Usbdevice.Use,module.Usbdevice.Free);

                        success_flag=1;
                        break;
                }


        fclose(fp);
        free(line);
        line = NULL;
        remove("/tmp/.USB_details");

        if(success_flag)
        {
                fprintf(stdout,"Externel Memory Total= %s Use= %s Free=%s\n",module.Usbdevice.Total,module.Usbdevice.Use,module.Usbdevice.Free);
                return 0;
        }
        else
        {
                return -1;
        }
}
