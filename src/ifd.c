#include<header.h>
int ifd_status(int card_select)
{
	int ret=0;
	ret = scr_open();

	if(ret < 0)
	{
		fprintf(stderr,"SCR Open Error\n");
		if( CONFIG.IFD1 )
			strcpy(module.IFD1,"ERROR");
		if( CONFIG.IFD2 )
			strcpy(module.IFD2,"ERROR");
		return -1;
	}

	select_card(card_select);

	ret = powerup_5v();
	if ( ret == 0 )
	{
		if ( CONFIG.IFD1 && card_select == 1 )
			strcpy(module.IFD1,"OK");

		else if( CONFIG.IFD2 && card_select == 2 )
			strcpy(module.IFD2,"OK");

	}
	else 
	{
		fprintf(stderr,"powerup_5v failed for IFD%d\n",card_select);
		if ( CONFIG.IFD1 &&  card_select == 1 )
			strcpy(module.IFD1,"ERROR");

		else if ( CONFIG.IFD2 &&  card_select == 2 )
			strcpy(module.IFD2,"ERROR");
	}
	scr_close();
	return ret;
}



