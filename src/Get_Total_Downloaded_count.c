#include<header.h>
char *Install_Applications_file="/mnt/sysuser/Software-Upgrade/Applications_Downloads/Install_Applications.info";
char *Install_Firmwares_file="/mnt/sysuser/Software-Upgrade/Firmware_Downloads/Install_Firmwares.info";
extern char *Standard_Apps_path;
extern char *Standard_Firmwares_path;
int Get_Total_Downloaded_Updates(int type)
{
        FILE *fp=NULL;
        char filename[128];
        char *line=NULL;
        char path[128];
        size_t len=0;
        int Updates=0;
        memset(filename,0,sizeof(memset));
        memset(path,0,sizeof(path));

        if ( type == FIRMWARE )
        {
                strcpy(path,Standard_Firmwares_path);
                strcpy(filename,Install_Firmwares_file);
        }
        else if ( type == APPLICATION )
        {
                strcpy(path,Standard_Apps_path);
                strcpy(filename,Install_Applications_file);
        }
        else
        {
                fprintf(stdout,"Unknown type Requested\n");
                return -1;
        }
        fp = fopen(filename,"r");
        if ( fp == NULL )
        {
                fprintf(stdout,"%s file not found\n",filename);
                return -1;
        }

        while( (getline(&line, &len, fp) > 0) )
                if((strstr(line,path)) != NULL)
                        Updates++;
        free(line);
        line=NULL;
        fclose(fp);
        return Updates;
}

