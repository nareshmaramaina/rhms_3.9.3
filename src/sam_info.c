#include<header.h>
int sam_status(int card_select)
{
	int ret=0;

	ret = SAM_Open();

	if(ret<0)
	{
		fprintf(stderr,"SAM Open Error\n");
		if( CONFIG.SAM1 )
			strcpy(module.SAM1,"Not Inserted");
		if( CONFIG.SAM2 )
			strcpy(module.SAM2,"Not Inserted");

		return -1;
	}

	if(card_select ==1 )

	{	
		printf("in first card\n");
		ret=SAM_ColdReset(2);
		if(ret)
		{

#if DEBUG 

			printf("Powerup the card1 Failed card not present and ret=%d\n",ret);
#endif

			memset(module.SAM1,0,sizeof(module.SAM1));	
			strcpy(module.SAM1,"Not Inserted");
			fprintf(stdout,"SAM Card1 Status:%s\n",module.SAM1);

			SAM_Close();
			return -1;

		}

		else if(ret==0)
		{
			memset(module.SAM1,0,sizeof(module.SAM1));	
			strcpy(module.SAM1,"Inserted");

		}

	}

	else if(card_select==2)
	{

		printf("in second card\n");
		ret=SAM_ColdReset(5);

		if(ret)	
		{

#if DEBUG
			printf("Powerup the card2 Failed card not present and ret=%d\n",ret);
#endif

			memset(module.SAM2,0,sizeof(module.SAM2));	
			strcpy(module.SAM2,"Not Inserted");
			fprintf(stdout,"SAM Card2 Status:%s\n",module.SAM2);
			SAM_Close();
			return -1;

		}
		else if(ret==0)
		{

			memset(module.SAM2,0,sizeof(module.SAM2));
			strcpy(module.SAM2,"Inserted");


#if DEBUG
			fprintf(stdout,"SAM Card2 Status:%s\n",module.SAM2);
#endif	
		}




	}

	SAM_Close();
	return 0;
}


