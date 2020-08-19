#include<header.h>
int Get_Device_Applications_Count()
{
        FILE *fp = NULL;

        char *line=NULL;
        int i,j;
        size_t len;
        fp = fopen("/etc/visiontek_Application_release","r");
        if(fp == NULL)
        {
                fprintf(stdout," /etc/visiontek_Application_release  file not found \n");
        	return -1;
	}

        else
        {
                for(i=0,j=0;getline(&line, &len, fp) > 0;)
                {
                        if( strstr(line,"ApplicationType:") != NULL)
                                i++;
                        else if( strstr(line,"ApplicationName:") != NULL)
                                j++;

                }
                if( i != j )
                {
                        fprintf(stdout,"Wrong Format in /etc/visiontek_Application_release, moving /etc/visiontek_Application_release to bkp apply All application patches \n");
			
                	return -1;
		}
                fclose(fp);

        }
        return i;
}

