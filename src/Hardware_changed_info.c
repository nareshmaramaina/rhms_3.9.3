#include<header.h>
void Hardware_changed_info()
{

	int ret = 0;

	char *docname="/var/log/Health/Last_remote_status.xml";


	ret = access(docname,F_OK);

	if ( ret != 0 )
	{
		fprintf(stdout," %s file not found",docname);
		strcpy(module.HWChanged,"YES");
		return;
	}

	ret = Is_Hardware_changed (docname);

	if ( ret == 1 )
		strcpy(module.HWChanged,"YES");

	else if ( ret == 0 )	
		strcpy(module.HWChanged,"NO");

	else 	
		strcpy(module.HWChanged,"ERROR");

	return ;
}
