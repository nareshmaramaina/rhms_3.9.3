#include <header.h>

int main()
{
	int ret=0;
	char FP_type[50]="";
	char FP_id[55]="";
	memset(FP_type,0x00,50);
	memset(FP_id,0x00,55);
	ret=get_fp_details(FP_type,FP_id);
	printf("ret is %d\n",ret);
	if(ret==0)
	{

#if DEBUG 
		fprintf(stdout,"FP_TYPE:%s\n",FP_type);
#endif
		memset(module.FP_TYPE,0,sizeof(module.FP_TYPE));
		if(strcmp(FP_type,"OPTICAL")
		
				sprintf(module.FP_TYPE,"OK/Optical");
				else if(strcmp(FP_type,"CAPACITIVE")
					sprintf(module.FP_TYPE,"OK/Capacitive");
					fprintf(stdout,"FP_id:%s\n",FP_id);
#endif
					memset(module.scanner_id,0x00,sizeof(module.scanner_id));

					sprintf(module.scanner_id,"%s",FP_id);
					sprintf(module.FP_type,"%s",FP_id);
					return 0;
					}

					printf("ERROR");

					return -1;
					}

					int get_fp_details(char *fp_type,char *fp_id)
					{

					FILE *fp;
					int j=0,k=0;
					char buff[256]="";
					fp = fopen("/etc/scanner_type","r");

					if (fp == NULL)
					{
						fprintf(stderr,"Configuration File open error\n");
						return -1;
					}

					memset(buff,0x00,256);

					fscanf(fp,"%s",buff);

					for(j=0;j<strlen(buff);j++)	
					{
						if (buff[j]==':')
						{
							for (k=0;k<(strlen(buff)-j);k++)
								fp_type[k]=buff[j+k+1];
							fprintf (stdout, "Server IP from ACK file ##%s##\n",fp_type);
							break;
						}
					}

					memset(buff,0x00,256);
					fscanf(fp,"%s",buff);


					for(j=0;j<strlen(buff);j++)
					{
						if (buff[j]==':')
						{
							for (k=0;k<(strlen(buff)-j);k++)
								fp_id[k]=buff[j+k+1];
							fprintf (stdout, "Server Port from ACK file ##%s##\n",fp_id);
							break;
						}


					}
					fclose(fp);

					return 0;
					}

