#ifndef DEBUGSPEED_H
#define DEBUGSPEED_H

#include "string.h"
#include "time.h"
#include "video.h"
#include "libs/DrawPrimitives/draw_primitives.h"

#define MAXDEBUGSPEEDS 100
#define USEPERCENTAGES true
#define MAXDEBUGSPEEDSENABLED false

int[MAXDEBUGSPEEDS] DebugSpeedMaxValues;
int[MAXDEBUGSPEEDS] DebugSpeedValues;
int[MAXDEBUGSPEEDS] DebugSpeedCycles;
int[MAXDEBUGSPEEDS] DebugSpeedFrames;
int[MAXDEBUGSPEEDS] DebugSpeedsPrevLenText;

int[MAXDEBUGSPEEDS] DebugSpeedGPUMaxValues;
int[MAXDEBUGSPEEDS] DebugSpeedGPUValues;
int[MAXDEBUGSPEEDS] DebugSpeedsGPUPrevLenText;

int MemoryUsed()
{
	int result = 0;
	malloc_block* block = malloc_first_block;
	while(block)
	{
		if(!block->free)
			result += block->size;
		block = block->next;
	}
	return result;
}

int getRemainingPixels()
{
	int RemainingPixels = 0;
    
    asm
    {
        "in R0, GPU_RemainingPixels"
        "mov {RemainingPixels}, R0"
    }
	
	return RemainingPixels;
}

int GetGPULoadPercentage()
{
   
    return ((9 * 640 * 360) - getRemainingPixels()) * 100 / (9 * 640 * 360);
}

int CpuUsed()
{
	return get_cycle_counter() * 100 /250000;
}

int* _faststrcat( int* dest, int* src )
{
     while (*dest) dest++;
     while (*dest++ = *src++);
     return --dest;
}


void _printSpeedInternal(int DebugSpeedValue, int DebugSpeedMaxValue, int* DebugSpeedMaxTextLengthArrayItem, int percentageValue, int percentageMultiplyer, int Percentagedivisor, int percentageMaxValue, int percentageMaxMultiplyer, int PercentageMaxdivisor, int Nr, int x, int y, int* prefix, int* internalprefix)
{
	int[10] debugNr;
	int[100] Msg;
	int* PMsg;
	if(USEPERCENTAGES)
		itoa(percentageMaxValue * percentageMaxMultiplyer /PercentageMaxdivisor, debugNr, 10);
	else
		itoa(DebugSpeedMaxValue, debugNr, 10);
	PMsg = Msg; *PMsg = 0; PMsg = _faststrcat(PMsg, prefix);
	PMsg = _faststrcat(PMsg, internalprefix);
	PMsg = _faststrcat(PMsg, debugNr);
	PMsg = _faststrcat(PMsg, "/");
	if(USEPERCENTAGES)
		itoa(percentageValue * percentageMultiplyer /Percentagedivisor, debugNr, 10);
	else
		itoa(DebugSpeedValue, debugNr, 10);
	PMsg = _faststrcat(PMsg, debugNr);
	if(DebugSpeedMaxValue > 0)
	{
		set_multiply_color(color_white);
		if(*DebugSpeedMaxTextLengthArrayItem > 0)
		{
			draw_filled_rectangle(x-1,y-1, x -1 + 2 + *DebugSpeedMaxTextLengthArrayItem * bios_character_width , y-1 + 2 + bios_character_height);	
		}
		draw_filled_rectangle(x-1,y-1, x -1 + 2 + strlen(Msg) * bios_character_width , y-1 + 2 + bios_character_height);
		set_multiply_color(color_black);
		print_at(x,y, Msg);
		set_multiply_color(color_white);
		*DebugSpeedMaxTextLengthArrayItem = strlen(Msg);
	}
}

void printDebugSpeed(int Nr, int x, int y, int* prefix)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if(Nr < MAXDEBUGSPEEDS)
	{
		_printSpeedInternal(DebugSpeedValues[Nr], DebugSpeedMaxValues[Nr], &DebugSpeedsPrevLenText[Nr], DebugSpeedValues[Nr], 100, 250000, DebugSpeedMaxValues[Nr], 100, 250000, Nr, x, y, prefix, "CPU:");
		_printSpeedInternal(DebugSpeedGPUValues[Nr], DebugSpeedGPUMaxValues[Nr], &DebugSpeedsGPUPrevLenText[Nr], DebugSpeedGPUValues[Nr],100, (9 * 640 * 360) , DebugSpeedGPUMaxValues[Nr], 100,  (9 * 640 * 360), Nr, x, y+bios_character_height, prefix, "GPU:");
	}
}

void initDebugSpeed()
{
	for (int i = 0; i < MAXDEBUGSPEEDS; i++)
	{
		DebugSpeedMaxValues[i] = 0;
		DebugSpeedCycles[i] = 0;
		DebugSpeedValues[i] = 0;
		DebugSpeedFrames[i] = 0;
		DebugSpeedsPrevLenText[i] = 0;
	}
}

void StartDebugSpeed(int Nr)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if (Nr < MAXDEBUGSPEEDS)
	{
		DebugSpeedFrames[Nr] = get_frame_counter();
   	 	DebugSpeedCycles[Nr] = get_cycle_counter();	
		DebugSpeedValues[Nr] = 0;
		DebugSpeedGPUValues[Nr] = getRemainingPixels();
	}
}

void StopDebugSpeed(int Nr)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if (Nr < MAXDEBUGSPEEDS)
	{
		int endframes = get_frame_counter();
		int endcycles = get_cycle_counter();
		if(endframes - DebugSpeedFrames[Nr] > 0)
		{
			DebugSpeedValues[Nr] = 250000 - DebugSpeedCycles[Nr];
			DebugSpeedValues[Nr] += 250000 * (endframes - DebugSpeedFrames[Nr]-1) ;
			DebugSpeedValues[Nr] += endcycles;
		}
		else
		{
			DebugSpeedValues[Nr] = endcycles - DebugSpeedCycles[Nr];
		}		
		DebugSpeedGPUValues[Nr] = (((9 * 640 * 360) - getRemainingPixels()) - ((9 * 640 * 360) - DebugSpeedGPUValues[Nr]) );
		if(DebugSpeedValues[Nr] > DebugSpeedMaxValues[Nr])
			DebugSpeedMaxValues[Nr] = DebugSpeedValues[Nr];		
		if(DebugSpeedGPUValues[Nr] > DebugSpeedGPUMaxValues[Nr])
			DebugSpeedGPUMaxValues[Nr] = DebugSpeedGPUValues[Nr];		
	}
}

void ResetDebugSpeedMaxValue(int Nr)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if (Nr < MAXDEBUGSPEEDS)
	{
		DebugSpeedMaxValues[Nr] = 0;
		DebugSpeedGPUMaxValues[Nr] = 0;
	}	
}

void ResetAllDebugSpeedMaxValues()
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	for (int i=0; i < MAXDEBUGSPEEDS; i++)
	{
		DebugSpeedMaxValues[i] = 0;
		DebugSpeedGPUMaxValues[i] = 0;
	}
}

#endif