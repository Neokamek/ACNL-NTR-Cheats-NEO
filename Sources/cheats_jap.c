#include "cheats.h"

extern u32			g_find[100];
extern u32			g_replace[100];
extern int			g_i;
/*
OFFSET DIFFERENCE (From USA) : + 0x22A80
*/
void    coord_jap(void)
{
    static int           loc = 0;

    if (is_pressed(BUTTON_A))
    {
        loc = READU32(0x33099f84);  
    }
    if (loc == -1) //FFFFFFFF=outdoors
    {
        if (is_pressed(BUTTON_A + BUTTON_DD))
            ADDTOFLOAT(0x33099E58, 1.0);  
        if (is_pressed(BUTTON_A + BUTTON_DU))
            SUBTOFLOAT(0x33099E58, 1.0);  
        if (is_pressed(BUTTON_A + BUTTON_DL))
            SUBTOFLOAT(0x33099E50, 1.0);  
        if (is_pressed(BUTTON_A + BUTTON_DR))
            ADDTOFLOAT(0x33099E50, 1.0);  
    }
    else //if it's anything but FFFFFFFF then you're indoors
    {
        if (is_pressed(BUTTON_A + BUTTON_DD))
            ADDTOFLOAT(0x33099f84, 1.0);  
        if (is_pressed(BUTTON_A + BUTTON_DU))
            SUBTOFLOAT(0x33099f84, 1.0);  
        if (is_pressed(BUTTON_A + BUTTON_DL))
            SUBTOFLOAT(0x33099f7c, 1.0);  
        if (is_pressed(BUTTON_A + BUTTON_DR))
            ADDTOFLOAT(0x33099f7c, 1.0);  
    }
}

void    search_jap(void)
{
	u16			search;
	u16			replace;
	u16			*search_id;
	u16			*replace_id;
	char		id_str[5];
	int			i;

	if (is_pressed(BUTTON_L + BUTTON_DL))
	{
		search_id = (u16 *)0x32CD39E0;
		replace_id = search_id + 4;
		memset(id_str, '\0', 5);
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(search_id + i);
		search = (u16)strtoul(id_str, NULL, 16);
		memset(id_str, '\0', 5);
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(replace_id + i);
		replace = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(search, replace);
		find_and_replace_multiple((void *)0x31F9CED8, 0x5000);
		find_and_replace_multiple((void *)0x31FB98D8, 0x1000);
	}
}

void    seed_jap(void) 
{
	u16        result;

	if (is_pressed(BUTTON_R + BUTTON_DD))
	{
		u16        *id = (u16 *)0x32CD39E0;
		char    id_str[5] = { 0 };
		int        i;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU16(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(0x20A7, result);
		find_and_replace_multiple((void *)0x31F9CED8, 0x5000);
		find_and_replace_multiple((void *)0x31FB98D8, 0x1000);
		wait_all_released();
	}
	if (is_pressed(BUTTON_R + BUTTON_DU))
	{
		u16        *id = (u16 *)0x32CD39E0;
		char    id_str[5] = { 0 };
		int        i;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU16(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x7FFE);
		find_and_replace_multiple((void *)0x31F9CED8, 0x5000);
		find_and_replace_multiple((void *)0x31FB98D8, 0x1000);
		wait_all_released();
	}
	if (is_pressed(BUTTON_R + BUTTON_DL))
	{
		u16        *id = (u16 *)0x32CD39E0;
		char    id_str[5] = { 0 };
		int        i;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU16(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x20A7);
		find_and_replace_multiple((void *)0x31F9CED8, 0x5000);
		find_and_replace_multiple((void *)0x31FB98D8, 0x1000);
		wait_all_released();
	}
}

void    text2item_jap(void) 
{
	u16		*id = (u16 *)0x32CD39E0;
	char		id_str[5] = { 0 };
	int		i;
	u16		result;
	u8		player;
	u32		offset;
	
	player = READU8(0xAA6990);
	if (player <= 0x3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	if (!is_pressed(BUTTON_X + BUTTON_DR))
		return;
	for (i = 0; i < 4; i++)
		id_str[i] = (char)READU16(id + i);
	result = (u16)strtoul(id_str, NULL, 16);
	WRITEU16(0x31F50670 + offset, result);
	wait_all_released();
}

void    teleport_jap(void) 
{
	static u32    indoor_X[3] = { 0 };
	static u32    indoor_Y[3] = { 0 };
	static u32    outdoor_X[3] = { 0 };
	static u32    outdoor_Y[3] = { 0 };
	static int    loc = 0;

	if (is_pressed(BUTTON_B)) //Pointer to define whether player is indoors or not
	{
		loc = READU32(0x33099f84);
	}
	if (is_pressed(BUTTON_B + BUTTON_DU))
	{
		if (loc == -1)
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				outdoor_X[2] = READU32(0x33099E50);
				outdoor_Y[2] = READU32(0x33099E58);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				outdoor_X[1] = READU32(0x33099E50);
				outdoor_Y[1] = READU32(0x33099E58);
			}
			else //If noting is pressed then save in slot0
			{
				outdoor_X[0] = READU32(0x33099E50);
				outdoor_Y[0] = READU32(0x33099E58);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				indoor_X[2] = READU32(0x33099f7c);
				indoor_Y[2] = READU32(0x33099f84);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				indoor_X[1] = READU32(0x33099f7c);
				indoor_Y[1] = READU32(0x33099f84);
			}
			else //If noting is pressed then save in slot0
			{
				indoor_X[0] = READU32(0x33099f7c);
				indoor_Y[0] = READU32(0x33099f84);
			}
		}
	}
	if (is_pressed(BUTTON_B + BUTTON_DD))
	{
		loc = READU32(0x33099f84);
		if (loc == -1)
		{

			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x33099E50, outdoor_X[2]);
				WRITEU32(0x33099E58, outdoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x33099E50, outdoor_X[1]);
				WRITEU32(0x33099E58, outdoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x33099E50, outdoor_X[0]);
				WRITEU32(0x33099E58, outdoor_Y[0]);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x33099f7c, indoor_X[2]);
				WRITEU32(0x33099f84, indoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x33099f7c, indoor_X[1]);
				WRITEU32(0x33099f84, indoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x33099f7c, indoor_X[0]);
				WRITEU32(0x33099f84, indoor_Y[0]);
			}
		}
	}
}

void	warping_jap(void)
{
	if (upper_left_touched())
	{
		WRITEU32(0x33099E58, 0x4427405E);
		WRITEU32(0x33099E54, 0x42E00000);
		WRITEU32(0x33099E50, 0x44253715);
		wait_keys_released(KEY_TOUCH);
	}
	if (upper_right_touched())
	{
		WRITEU32(0x33099E58, 0x442C4000);
		WRITEU32(0x33099E54, 0x42E00000);
		WRITEU32(0x33099E50, 0x45239943);
		wait_keys_released(KEY_TOUCH);
	}
	if (lower_left_touched())
	{
		WRITEU32(0x33099E58, 0x450A7F48);
		WRITEU32(0x33099E54, 0x42E00000);
		WRITEU32(0x33099E50, 0x4442761E);
		wait_keys_released(KEY_TOUCH);
	}
	if (lower_right_touched())
	{
		WRITEU32(0x33099E58, 0x45071000);
		WRITEU32(0x33099E54, 0x42E00000);
		WRITEU32(0x33099E50, 0x451E028E);
		wait_keys_released(KEY_TOUCH);
	}
}

void	speed_jap(void) 
{
	u32			  velocity;

	if (is_pressed(BUTTON_B))
	{
		velocity = READU32(0x33099E7C);
		if (velocity >= 0x41A79DB3)
		{
			WRITEU32(0x33099E7C, 0x41A79DB3);
		}
		else if (velocity > 0)
		{
			ADDTOFLOAT(0x33099E7C, 2.0);
		}
	}
}

void	weeder_jap(void)
{
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		reset_search();
		add_search_replace(0x0000007C, 0x00007FFE);
		add_search_replace(0x0000007D, 0x00007FFE);
		add_search_replace(0x0000007E, 0x00007FFE);
		add_search_replace(0x0000007F, 0x00007FFE);
		add_search_replace(0x000000CB, 0x00007FFE);
		add_search_replace(0x000000CC, 0x00007FFE);
		add_search_replace(0x000000CD, 0x00007FFE);
		add_search_replace(0x000000F8, 0x00007FFE);
		find_and_replace_multiple((void *)0x31F9CED8, 0x5000);
		wait_all_released();
	}
}

void quench_jap()
{
  // define flowers (include wilted)
static const u16 flowers[] = {
    // src, replace
    0x009F, 0x009F, // Red Tulips
    0x00A0, 0x00A0, // White Tulips
    0x00A1, 0x00A1, // Yellow Tulips
    0x00A2, 0x00A2, // Pink Tulips
    0x00A3, 0x00A3, // Purple Tulips
    0x00A4, 0x00A4, // Black Tulips
    0x00A5, 0x00A5, // Orange Tulips
    0x00A6, 0x00A6, // White Pansies
    0x00A7, 0x00A7, // Yellow Pansies
    0x00A8, 0x00A8, // Red Pansies
    0x00A9, 0x00A9, // Purple Pansies
    0x00AA, 0x00AA, // Orange Pansies
    0x00AB, 0x00AB, // Blue Pansies
    0x00AC, 0x00AC, // White Comsos
    0x00AD, 0x00AD, // Red Cosmos
    0x00AE, 0x00AE, // Sun Cosmos
    0x00AF, 0x00AF, // Pink Cosmos
    0x00B0, 0x00B0, // Orange Cosmos
    0x00B1, 0x00B1, // Black Cosmos
    0x00B2, 0x00B2, // Red Roses
    0x00B3, 0x00B3, // White Roses
    0x00B4, 0x00B4, // Yellow Roses
    0x00B5, 0x00B5, // Pink Roses
    0x00B6, 0x00B6, // Orange Roses
    0x00B7, 0x00B7, // Purple Roses
    0x00B8, 0x00B8, // Black Roses
    0x00B9, 0x00B9, // Blue Roses
    0x00BB, 0x00BB, // Red Carnations
    0x00BC, 0x00BC, // Pink Carnations
    0x00BD, 0x00BD, // White Carnations
    0x00BE, 0x00BE, // White Lilies
    0x00BF, 0x00BF, // Yellow Lilies
    0x00C0, 0x00C0, // Red Lilies
    0x00C1, 0x00C1, // Orange Lilies
    0x00C2, 0x00C2, // Pink Lilies
    0x00C3, 0x00C3, // Black Lilies
    0x00C4, 0x00C4, // Purple Violets
    0x00C5, 0x00C5, // Blue Violets
    0x00C6, 0x00C6, // White Violets
    0x00C7, 0x00C7, // Yellow Violets
    0x00C8, 0x00C8, // Jacob's Ladder
    0x00CE, 0x009F, // Red Tulips (Wilted)
    0x00CF, 0x00A0, // White Tulips (Wilted)
    0x00D0, 0x00A1, // Yellow Tulips (Wilted)
    0x00D1, 0x00A2, // Pink Tulips (Wilted)
    0x00D2, 0x00A3, // Purple Tulips (Wilted)
    0x00D3, 0x00A4, // Black Tulips (Wilted)
    0x00D4, 0x00A5, // Orange Tulips (Wilted)
    0x00D5, 0x00A6, // White Pansies (Wilted)
    0x00D6, 0x00A7, // Yellow Pansies (Wilted)
    0x00D7, 0x00A8, // Red Pansies (Wilted)
    0x00D8, 0x00A9, // Purple Pansies (Wilted)
    0x00D9, 0x00AA, // Orange Pansies (Wilted)
    0x00DA, 0x00AB, // Blue Pansies (Wilted)
    0x00DB, 0x00AC, // White Cosmos (Wilted)
    0x00DC, 0x00AD, // Red Cosmos (Wilted)
    0x00DD, 0x00AE, // Sun Cosmos (Wilted)
    0x00DE, 0x00AF, // Pink Cosmos (Wilted)
    0x00DF, 0x00B0, // Orange Cosmos (Wilted)
    0x00E0, 0x00B1, // Black Cosmos (Wilted)
    0x00E1, 0x00B2, // Red Roses (Wilted)
    0x00E2, 0x00B3, // White Roses (Wilted)
    0x00E3, 0x00B4, // Yellow Roses (Wilted)
    0x00E4, 0x00B5, // Pink Roses (Wilted)
    0x00E5, 0x00B6, // Orange Roses (Wilted)
    0x00E6, 0x00B7, // Purple Roses (Wilted)
    0x00E7, 0x00B8, // Black Roses (Wilted)
    0x00E8, 0x00B9, // Blue Roses (Wilted)
    0x00E9, 0x00BA, // Gold Roses (Wilted)
    0x00EA, 0x00BB, // Red Carnations (Wilted)
    0x00EB, 0x00BC, // Pink Carnations (Wilted)
    0x00EC, 0x00BD, // White Carnations (Wilted)
    0x00ED, 0x00BE, // White Lilies (Wilted)
    0x00EE, 0x00BF, // Yellow Lilies (Wilted)
    0x00EF, 0x00C0, // Red Lilies (Wilted)
    0x00F0, 0x00C1, // Orange Lilies (Wilted)
    0x00F1, 0x00C2, // Pink Lilies (Wilted)
    0x00F2, 0x00C3, // Black Lilies (Wilted)
    0x00F3, 0x00C4, // Purple Violets (Wilted)
    0x00F4, 0x00C5, // Blue Violets (Wilted)
    0x00F5, 0x00C6, // White Violets (Wilted)
    0x00F6, 0x00C7, // Yellow Violets (Wilted)
    0x00F7, 0x00C8, // Jacob's Ladder (Wilted)
};
  int i;
  u32 address, item;
	if (is_pressed(BUTTON_R + BUTTON_A))
  // find all items in Town
  for(address = OFFSET_TOWN_ITEMS; address < OFFSET_TOWN_ITEMS_JAP + RANGE_TOWN_ITEMS; address += ITEM_BYTES){
    item = READU16(address);

    // find flowers
    for(i = 0; i < sizeof(flowers) / sizeof(u16); i += 2){
      if(item == flowers[i]){
        // replace item
        WRITEU16(address, flowers[i + 1]);

        // add water flag
        WRITEU16(address + 0x02, 0x4000);
        break;
			}
		}
	}
}

void	tree_jap(void)
{
	if (is_pressed(BUTTON_X))
	{
		reset_search();
		add_search_replace(0x003A, 0x003E);
		add_search_replace(0x003F, 0x0043);
		add_search_replace(0x0044, 0x0048);
		add_search_replace(0x0049, 0x004D);
		add_search_replace(0x004E, 0x0052);
		add_search_replace(0x0022, 0x0026);
		add_search_replace(0x0027, 0x002B);
		add_search_replace(0x002C, 0x0030);
		add_search_replace(0x0031, 0x0035);
		add_search_replace(0x0036, 0x0039);
		add_search_replace(0x0053, 0x0057);
		add_search_replace(0x0058, 0x005C);
		add_search_replace(0x005D, 0x0061);
		add_search_replace(0x0062, 0x0066);
		add_search_replace(0x0067, 0x006B);
		add_search_replace(0x006C, 0x0043);
		find_and_replace_multiple((void *)0x31F9CED8, 0x5000);
		find_and_replace_multiple((void *)0x31FB98D8, 0x1000);

	}
}

void	duplicate_jap(void)
{
	u32			dupe = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x31F50670);
		WRITEU32(0x31F50674, dupe);
	}
}

void	grass_jap(void)
{
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		int i;

		for (i = 0x31FA3300; i < 0x31FA5AFF; i++)
			*(u32 *)i = 0xFFFFFFFF;
		wait_all_released();
	}
}

void	desert_jap(void)
{
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		int i;
	
		for (i = 0x31FA3300; i < 0x31FA5AFF; i++)
			*(u32 *)i = 0x00000000;
		wait_all_released();
	}
}

//Nook Upgrades

void	nook1_jap(void)
{
	WRITEU16(0x31FABC64, 0x0101);
	WRITEU8(0x31FB00F4, 0x2);
}

void	nook2_jap(void)
{	
	WRITEU16(0x31FABC64, 0x0202);
	WRITEU8(0x31FB00F4, 0x2);
}

void	nook3_jap(void)
{
	WRITEU16(0x31FABC64, 0x0303);
	WRITEU8(0x31FB00F4, 0x3);
}

void	nook4_jap(void)
{
	WRITEU16(0x31FABC64, 0x0404);
	WRITEU8(0x31FB00F4, 0x4);
}

void	moonjump_jap(void)
{
	int		loc;
	u32		Z;

    if (!(any_is_pressed(R)) && is_pressed(BUTTON_L)) //it's better to test the negation first
	{
		loc = READU32(0x33099f84);
		Z = READU32(0x33099E54);
		if (Z >= 0x440F0000)
		{
			if (loc == -1)
			{
				WRITEU32(0x33099E54, 0x440F0000);
			}
			else
			{
				WRITEU32(0x173B8CC0, 0x440F0000);
			}
		}
		else
		{
			if (loc == -1)
			{
				ADDTOFLOAT(0x33099E54, 6.0);
			}
			else
			{
				ADDTOFLOAT(0x173B8CC0, 6.0);
			}
		}	
	}
}

void	timeMachine_jap(void)
{
    u16         *id = (u16 *)0x32CD39E0;
    char        yy_str[3] = { 0 };
    char        mm_str[3] = { 0 };
    char        dd_str[3] = { 0 };
    char        hh_str[3] = { 0 };
    char        mz_str[3] = { 0 };
    char        pm_str[2] = { 0 };
    s64         res_year = 0;
    s64         res_month = 0;
    s64         res_day = 0;
    s64         res_hour = 0;
    s64         res_min = 0;
    s64         res_nansec = 0;
    s64         res_plmn = 1;

    if (is_pressed(BUTTON_Y + BUTTON_DR))
	{
		yy_str[0] = (char)READU8(id + 0);
		yy_str[1] = (char)READU8(id + 1);
		mm_str[0] = (char)READU8(id + 2);
		mm_str[1] = (char)READU8(id + 3);
		dd_str[0] = (char)READU8(id + 4);
		dd_str[1] = (char)READU8(id + 5);
		hh_str[0] = (char)READU8(id + 6);
		hh_str[1] = (char)READU8(id + 7);
		mz_str[0] = (char)READU8(id + 8);
		mz_str[1] = (char)READU8(id + 9);
		if ((char)READU8(id + 10) == 45) //minus
			res_plmn = -1;
		res_year = (s64)strtoul(yy_str, NULL, 16);
			res_month = (s64)strtoul(mm_str, NULL, 16);
		res_day = (s64)strtoul(dd_str, NULL, 16);
		res_hour = (s64)strtoul(hh_str, NULL, 16);
		res_min = (s64)strtoul(mz_str, NULL, 16);
	
		res_year = res_year * (365 * 24 * 60 * 60) * (1000000000); //(year to seconds) * (seconds to nanoseconds)
		res_month = res_month * (28 * 24 * 60 * 60) * (1000000000); //("month" to seconds) * (seconds to nanoseconds)
		res_day = res_day * (24 * 60 * 60) * (1000000000); //(day to seconds) * (seconds to nanoseconds)
		res_hour = res_hour * (60 * 60) * (1000000000); //(hour to seconds) * (seconds to nanoseconds)
		res_min = res_min * (60) * (1000000000); //(minute to seconds) * (seconds to nanoseconds)
	
		res_nansec = (res_year + res_month + res_day + res_hour + res_min) * res_plmn;

		ADD64(0x31FABBA0, res_nansec);
		ADD64(0x955500, res_nansec);
		wait_keys_released(DR);
	}
	
	if (is_pressed(BUTTON_Y + BUTTON_DL))
	{
		yy_str[0] = (char)READU8(id + 0);
		yy_str[1] = (char)READU8(id + 1);
		mm_str[0] = (char)READU8(id + 2);
		mm_str[1] = (char)READU8(id + 3);
		dd_str[0] = (char)READU8(id + 4);
		dd_str[1] = (char)READU8(id + 5);
		hh_str[0] = (char)READU8(id + 6);
		hh_str[1] = (char)READU8(id + 7);
		mz_str[0] = (char)READU8(id + 8);
		mz_str[1] = (char)READU8(id + 9);
		if ((char)READU8(id + 10) == 45) //minus
			res_plmn = -1;
		res_year = (s64)strtoul(yy_str, NULL, 16);
		res_month = (s64)strtoul(mm_str, NULL, 16);
		res_day = (s64)strtoul(dd_str, NULL, 16);
		res_hour = (s64)strtoul(hh_str, NULL, 16);
		res_min = (s64)strtoul(mz_str, NULL, 16);
	
		res_year = res_year * (365 * 24 * 60 * 60) * (1000000000); //(year to seconds) * (seconds to nanoseconds)
		res_month = res_month * (28 * 24 * 60 * 60) * (1000000000); //("month" to seconds) * (seconds to nanoseconds)
		res_day = res_day * (24 * 60 * 60) * (1000000000); //(day to seconds) * (seconds to nanoseconds)
		res_hour = res_hour * (60 * 60) * (1000000000); //(hour to seconds) * (seconds to nanoseconds)
		res_min = res_min * (60) * (1000000000); //(minute to seconds) * (seconds to nanoseconds)
	
		res_nansec = (res_year + res_month + res_day + res_hour + res_min) * res_plmn;

		SUB64(0x31FABBA0, res_nansec);
		SUB64(0x955500, res_nansec);
		wait_keys_released(DL);
	}
}

void	timeTravel_jap(void)
{
	if(is_pressed(BUTTON_B + BUTTON_DR))
	{
		ADD64(0x31FABBA0, 0x34630B8A000);
		ADD64(0x955500, 0x34630B8A000);
		wait_keys_released(DR);
	}
	if(is_pressed(BUTTON_B + BUTTON_DL))
	{
		SUB64(0x31FABBA0, 0x34630B8A000);
		SUB64(0x955500, 0x34630B8A000);
		wait_keys_released(DL);
	}
	if(is_pressed(BUTTON_B + BUTTON_DD))
	{
		WRITES64(0x31FABBA0, 0x0000000000000000);
		WRITES64(0x955500, 0x0000000000000000);
	}
	if(is_pressed(BUTTON_R + BUTTON_DR))
	{
		ADD64(0x31FABBA0, 0xdf8475800);
		ADD64(0x955500, 0xdf8475800);
	}
	if(is_pressed(BUTTON_R + BUTTON_DL))
	{
		SUB64(0x31FABBA0, 0xdf8475800);
		SUB64(0x955500, 0xdf8475800);
	}
}

void	real_jap(void)
{
	u32 x;
	u32 y;
	u32 reg0;
	u32 reg1;
	u32 offset;
	u16		*id = (u16 *)0x32CD39E0;
	char		id_str[5] = { 0 };
	int		i;
	u16		result;
	if (is_pressed(BUTTON_R + BUTTON_DD))
	{
	x = READU32 (0x3309A2B8);
	y = READU32 (0x3309A2BC);
		if (x >= 0x10 && y >= 0x10)
		{
			x -= 0x10;
			y -= 0x10;
			reg0 = x % 0x10;
			x /= 0x10;
			reg1 = y % 0x10;
			y /= 0x10;
			reg0 *= 0x4;
			reg1 *= 0x40;
			x *= 0x400;
			y *= 0x1400;
			offset = reg0 + reg1 + x + y;			
			id = (u16 *)0x32CD39E0;
			for (i = 0; i < 4; i++)
				id_str[i] = (char)READU8(id + i);
			result = (u16)strtoul(id_str, NULL, 16);
			WRITEU16(0x31F9CED8 + offset, result);
		}
	}	
}

void	tan_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x0);
}

void	tan1_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x1);
}

void	tan2_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x2);
}

void	tan3_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x3);
}

void	tan4_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x4);
}

void	tan5_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x5);
}

void	tan6_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x6);
}

void	tan7_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x7);
}

void	tan8_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x8);
}

void	tan9_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0x9);
}

void	tan10_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0xA);
}

void	tan11_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0xB);
}

void	tan12_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0xC);
}

void	tan13_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0xD);
}

void	tan14_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0xE);
}

void	tan15_jap(void)
{
	u8 player;
	u32 offset;
	offset = 0;
	player = READU8(0xAA6990);
	if (player <= 0x3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
	{
		offset = player * 0xa480;
	}
	WRITEU8(0x31F49AA8 + offset, 0xF);
}