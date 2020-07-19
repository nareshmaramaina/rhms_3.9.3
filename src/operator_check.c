#include<header.h>
void operator_check(char *operator_buff,char *operator)
{
	int i;

	for(i=0;operator_buff[i];i++)
		if(isupper(operator_buff[i]))
			operator_buff[i]+=32;

	if((strstr(operator_buff,"airtel")!=0))
		strcpy(operator,"airtel");
	else if (strstr(operator_buff,"idea")!=0 || (strstr(operator_buff,"!dea") != 0)  )
		strcpy(operator,"idea");
	else if (strstr(operator_buff,"vodafone")!=0)
		strcpy(operator,"vodafone");
	else if (strstr(operator_buff,"bsnl")!=0)
		strcpy(operator,"bsnl");
	else if (strstr(operator_buff,"videocon")!=0)
		strcpy(operator,"videocon");
	else if(strstr(operator_buff,"uninor")!=0)
		strcpy(operator,"uninor");
	else if(strstr(operator_buff,"reliance")!=0)
		strcpy(operator,"reliance");
	else if	(strstr(operator_buff,"aircel")!=0)
		strcpy(operator,"aircel");
	else if(strstr(operator_buff,"tata")!=0)
		strcpy(operator,"Docomo");
	else if(strstr(operator_buff,"jio")!=0)
		strcpy(operator,"jio");

	else strcpy(operator,"ERROR");

	return ;
}
