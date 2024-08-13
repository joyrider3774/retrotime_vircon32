#ifndef TITLESCREENBACKGROUND_H
#define TITLESCREENBACKGROUND_H

#include "video.h"
#include "misc.h"
#include "common.h"
#include "CImage.h"

#define NumColsRandomBackground (int)((ScreenWidth/(320 * xscale))*2) //320 = width quarter size game screen preview
#define NumRowsRandomBackground (int)((ScreenHeight/(180 * yscale))*2) //180 = height quarter size game screen preview

int[NumColsRandomBackground][NumRowsRandomBackground] RandomBackground;
int menubackgroundx;
int menubackgroundy;
int menubackgrounddx;
int menubackgrounddy;


void CGame_CreateRandomBackground()
{
	int x = 0;
	int y = 0;
	int r = rand() % Games;
	int prevr = r;

	
	while (y < NumRowsRandomBackground)
	{
		x = 0;
		while(r == prevr)
			r = rand() % Games;
		prevr = r;

		while (x < NumColsRandomBackground)
		{
			r += 1;
			if (r == Games)
				r = 0;
			RandomBackground[x][y] = r;
			x +=1;
		}
		y += 1;
	}

	menubackgroundx = rand() % ScreenWidth;
	menubackgroundy = rand() % ScreenHeight;
	if(rand() % 2 == 0)
		menubackgrounddx =  1;
	else
		menubackgrounddx = -1;
	if(rand() % 2 == 0)
		menubackgrounddy =  1;
	else
		menubackgrounddy =  -1;
}

void CGame_DrawTitleBackground()
{
	menubackgroundx += menubackgrounddx;
	menubackgroundy += menubackgrounddy;
	if ((menubackgroundx == 0) || (menubackgroundx == ScreenWidth))
		menubackgrounddx *= -1;

	if ((menubackgroundy == 0) || (menubackgroundy == ScreenHeight))
		menubackgrounddy *= -1;

	for (int y = 0; y < NumRowsRandomBackground; y++)
		for(int x = 0; x < NumColsRandomBackground; x++)
		{
			CImage_DrawImageFuze(GFXPrevewID, RandomBackground[x][y], false, -ScreenWidth+menubackgroundx + (int)(x*320*xscale), -ScreenHeight+menubackgroundy + (int)(y*180*yscale), 0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		}
}

#endif