#include<header.h>
int get_Usb_device_serialno(char *Vendorid,char *ProductId,char *serialno)
{
	DIR *dir,*sub_dir;
	struct dirent *entry;
	char *usb_devs_path="/sys/bus/usb/devices/";
	char sub_dir_path[320]="";
	char id_path[360]="";
	char id[20]="";
	FILE *fp = NULL;



	if ((dir = opendir (usb_devs_path)) == NULL) 
	{
		perror ("No such file or Directory\n");
		return -1;
	}



	while ((entry = readdir (dir)) != NULL) 
	{

		memset(sub_dir_path,0x00,sizeof(sub_dir_path));

		sprintf(sub_dir_path,"%s%s",usb_devs_path,entry->d_name);

		if ((sub_dir = opendir (sub_dir_path)) != NULL)
		{

			memset(id_path,0x00,sizeof(id_path));
			sprintf(id_path,"%s/idVendor",sub_dir_path);

			fp = fopen(id_path,"r");
			if (fp == NULL)
			{
				continue;
			}
			memset(id,0x00,sizeof(id));
			fscanf(fp,"%s",id);

			fclose(fp);




			if ( strcmp(id,Vendorid) == 0)
			{
				memset(id_path,0x00,sizeof(id_path));
				sprintf(id_path,"%s/idProduct",sub_dir_path);
				//	puts(id_path);

				fp = fopen(id_path,"r");
				if (fp == NULL)
				{
					continue;
				}
				memset(id,0x00,sizeof(id));
				fscanf(fp,"%s",id);

				fclose(fp);

				if ( strcmp(id,ProductId) == 0)
				{
					memset(id_path,0x00,sizeof(id_path));
					sprintf(id_path,"%s/%s",sub_dir_path,"serial");
					fp = fopen(id_path,"r");
					if (fp == NULL)
					{
						closedir(sub_dir);
						break;
					}
					memset(serialno,0x00,sizeof(serialno));
					fscanf(fp,"%s",serialno);

					fclose(fp);
					closedir(sub_dir);
					closedir(dir);
					return 0;
				}

			}

			closedir(sub_dir);

		}

	}

	closedir (dir);
	return -1;
}

