#include "ECW/ECW.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "HAL/HAL_Buttons.h"
#include <stdio.h>
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define R 32
#define C 51

//Globals
tContext g_sContext;
uint8_t head_r=0, head_c=0, tail_r=0, tail_c=0;
uint8_t facing = RIGHT;
uint8_t mat[R][C];
uint16_t no_of_turns = 0;


void lcd_init()
{
	Dogs102x64_UC1701Init();
	GrContextInit(&g_sContext, &g_sDogs102x64_UC1701);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
	GrClearDisplay(&g_sContext);
}

void reinitialise(uint8_t mat[][C])
{
	GrClearDisplay(&g_sContext);
	GrStringDrawCentered(&g_sContext, "Snake", 5, 51, 32, 0);
	delay_ms(1000);
	GrClearDisplay(&g_sContext);

	int i,j;
	head_r=0, head_c=0, tail_r=0, tail_c=0, no_of_turns=0;
	facing = RIGHT;
	//length = 1;
	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
		{
			mat[i][j] = 0;
		}
	}
	mat[0][0] = 1;
}

void Dogs_print_int(uint8_t column, uint8_t row,int n){
	char s[10];
	snprintf(s,10,"%d",n);
	Dogs102x6_stringDraw(column, row, s, 0x00);
}

void print_string(uint8_t column,uint8_t row,char *s){
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrStringDraw(&g_sContext,
    		s,
    		AUTO_STRING_LENGTH,
    		column,
    		row,OPAQUE_TEXT);
}

void print_int(uint8_t column,uint8_t row,int n){
    char s[10];
    uint8_t i;
    for(i=0; i<10; i++)
    {
    	s[i]='\0';
    }
    snprintf(s,10,"%d",n);

    print_string(column, row, s);
}

uint8_t moveSnake(uint8_t dir)
{
	switch(facing)
	{
	case RIGHT:
		switch(dir)
		{
		case LEFT:
			head_r=(R+head_r-1)%R;
			facing=UP;
			break;
		case RIGHT:
			head_r=(head_r+1)%R;
			facing=DOWN;
			break;
		case UP:
			head_c=(head_c+1)%C;
			facing=RIGHT;
			break;
		}
		break;

	case LEFT:
		switch(dir)
		{
		case LEFT:
			head_r=(head_r+1)%R;
			facing=DOWN;
			break;
		case RIGHT:
			head_r=(R+head_r-1)%R;
			facing=UP;
			break;
		case UP:
			head_c=(C+head_c-1)%C;
			facing=LEFT;
			break;
		}
		break;

	case UP:
		switch(dir)
		{
		case LEFT:
			head_c=(C+head_c-1)%C;
			facing=LEFT;
			break;
		case RIGHT:
			head_c=(head_c+1)%C;
			facing=RIGHT;
			break;
		case UP:
			head_r=(R+head_r-1)%R;
			facing=UP;
			break;
		}
		break;

	case DOWN:
		switch(dir)
		{
		case LEFT:
			head_c=(head_c+1)%C;
			facing=RIGHT;
			break;
		case RIGHT:
			head_c=(C+head_c-1)%C;
			facing=LEFT;
			break;
		case UP:
			head_r=(head_r+1)%R;
			facing=DOWN;
			break;
		}
		break;

	default:
		break;
	}

	if(mat[head_r][head_c]==1)
	{
		return 0;
	}
	if((head_r+head_c+2)%2 == 1)
	{
		mat[head_r][head_c]=1;
		//length++;

		Dogs102x64_UC1701PixelDraw(0, head_c, head_r, 0);
		//GrPixelDraw(&g_sContext, head_c, head_r);
	}
	else
	{
		mat[head_r][head_c]=1;
		mat[tail_r][tail_c]=0;

		Dogs102x64_UC1701PixelDraw(0, head_c, head_r, 0);
		Dogs102x64_UC1701PixelDraw(0, tail_c, tail_r, 1);
		//GrPixelDraw(&g_sContext, head_r, head_c);

		if(mat[(R+tail_r-1)%R][tail_c]==1) tail_r=(R+tail_r-1)%R;
		else if(mat[(tail_r+1)%R][tail_c]==1) tail_r=(tail_r+1)%R;
		else if(mat[tail_r][(C+tail_c-1)%C]==1) tail_c=(C+tail_c-1)%C;
		else if(mat[tail_r][(tail_c+1)%C]==1) tail_c=(tail_c+1)%C;
	}


	return 1;
}



void switch_init(){
	 __enable_interrupt();

	 Buttons_init(BUTTON_S1 );
	 Buttons_interruptEnable(BUTTON_S1 );

	 Buttons_init(BUTTON_S2 );
	 Buttons_interruptEnable(BUTTON_S2 );
}

/*
 * main.c
 */
int main(void) {
	stop_watchdog();
	
	// Set up LCD
	lcd_init();

	switch_init();

	buttonsPressed = 0;
	uint8_t i,j,play_again=0;
	uint8_t dir = UP;

	GrStringDrawCentered(&g_sContext, "Snake", 5, 51, 32, 0);
	delay_ms(1000);
	GrClearDisplay(&g_sContext);


	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			mat[i][j] = 0;
		}
	}
	mat[0][0] = 1;

	while(1){
		delay_ms(100);
		if (buttonsPressed & BUTTON_S1){
			buttonsPressed = 0;
			dir = RIGHT;
			no_of_turns++;
		}
		else if (buttonsPressed & BUTTON_S2){
			buttonsPressed = 0;
			dir = LEFT;
			no_of_turns++;
		}
		else{
			dir = UP;
		}

		if(moveSnake(dir))
		{
			continue;
		}
		else
		{
			print_string(2, 45, "No of Turns: ");
			print_int(78, 45, no_of_turns);
			delay_ms(100);

			print_string(2, 53, "S1=Play S2=Quit");
			while(1)
			{
				if(buttonsPressed & BUTTON_S1)
				{
					buttonsPressed = 0;
					play_again=1;
					break;
				}
				if (buttonsPressed & BUTTON_S2)
				{
					buttonsPressed = 0;
					play_again=0;
					break;
				}
			}
			if(play_again)
			{
				reinitialise(mat);
				play_again=0;
				continue;
			}
			else
			{
				break;
			}
		}

	}


	return 0;
}
