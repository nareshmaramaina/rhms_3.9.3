#include<header.h>
int mkdir_p(char *dirname)
{
	DIR *dp;
	
	dp = opendir(dirname);
	if ( dp == NULL )
	{
		remove(dirname);
		return mkdir(dirname,0777);
	}

	closedir(dp);
	return 0;
}
