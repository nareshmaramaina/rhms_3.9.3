#include<header.h>

int copy_file (char *dest,char *src)
{
	unsigned char *str=NULL;

	int in=0, out=0,n=0;

	in = open(src , O_RDONLY);

	out = open(dest, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);

	if (in == -1 || out == -1)
	{
		fprintf(stderr,"unable to open source or destination files %d %d\n" ,in,out);
		return -1;
	}

	str = calloc(512,sizeof(char));

	while(1)
	{
		n=read(in,str,512);

		if (n == 0)
			break;
		write(out,str,n);
	}

	free(str);

	close(in);

	close(out);

	return 0;
}
