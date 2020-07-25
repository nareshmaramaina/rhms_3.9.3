#include<header.h>
int ifd_status(int card_select)
{
	int ret=0;
	ret = scr_open();

	if(ret < 0)
	{
		fprintf(stderr,"SCR Open Error\n");
	}

	else 
	{
		select_card(card_select);

		ret = powerup_5v();
		if ( ret == 0 )
		{
			if ( CONFIG.IFD1 && card_select == 1 )
				strcpy(module.IFD1,"Inserted");

			else if( CONFIG.IFD2 && card_select == 2 )
				strcpy(module.IFD2,"Inserted");

			return 0;
		}
		else 
			fprintf(stderr,"powerup_5v failed for IFD%d\n",card_select);
		scr_close();
	}
	if ( CONFIG.IFD1 &&  card_select == 1 )
		strcpy(module.IFD1,"NotInserted");

	else if ( CONFIG.IFD2 &&  card_select == 2 )
		strcpy(module.IFD2,"NotInserted");
	return ret;
}



