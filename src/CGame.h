#ifndef CGAME_H
#define CGAME_H

#include "texture.h"
#include "string.h"
#include "time.h"
#include "video.h"
#include "Common.h"
#include "CImage.h"
#include "CSprites.h"
#include "debugspeed.h"

#include "CFont.h"
#include "TitleScreen.h"
#include "SubScoreScreen.h"
#include "GamesShare.h"
#include "Intro.h"

#undef LoadImage
#undef PlaySound

void CGame_LoadMusic()
{
	MusMenu = CAudio_LoadMusic("main/music");
}

void CGame_UnLoadMusic()
{
	CAudio_UnloadMusics();
}

void CGame_UnLoadGraphics()
{
	CImage_UnloadImages();
}

void CGame_LoadSound()
{
	SfxTimeOver = CAudio_LoadSound("common/timeover");
	SfxReadyGo = CAudio_LoadSound("common/readygo");
	SfxOne = CAudio_LoadSound("common/one");
	SfxTwo = CAudio_LoadSound("common/two");
	SfxThree = CAudio_LoadSound("common/three");
	SfxOneMinute = CAudio_LoadSound("common/oneminute");
	SfxConfirm = CAudio_LoadSound("main/confirm");
	SfxBack = CAudio_LoadSound("main/back");
	SfxSelect = CAudio_LoadSound("main/select");
	SfxScore = CAudio_LoadSound("main/score");
}

void CGame_UnLoadSound()
{
	CAudio_UnloadSounds();
}

void CGame_LoadGraphics()
{
	GFXFrameID = CImage_LoadImage("main/frame.png");
	GFXMedal = CImage_LoadImage("main/medal.png");
	GFXPrevewID = CImage_LoadImage("gamepreview/gamepreview.png");
	GFXPreviewID2 = CImage_LoadImage("gamepreview/gamepreview2.png");
}




void CGame_ResetTimer()
{
	Timer = 120;
	if (GameMode == GMRetroCarousel)
	{
		Timer = 2 * 60;
	}
	if (GameMode == GMTimeAttack)
	{
		Timer = 5 * 60;
	}
	TimerTicks = getCurrentTimeMilliseconds();
}

void CGame_UpdateTimer()
{
	if (TimerTicks + 250 < getCurrentTimeMilliseconds())
	{
		TimerTicks = getCurrentTimeMilliseconds();
		if (SubGameState == SGGame)
		{
			if (GameMode == GMGame)
				Timer += 0.25;
			else
			{
				Timer -= 0.25;

				if (Timer == 60)
				 	CAudio_PlaySound(SfxOneMinute, 0);

				if (Timer == 3)
				 	CAudio_PlaySound(SfxThree, 0);

				if (Timer == 2)
				 	CAudio_PlaySound(SfxTwo, 0);

				if (Timer == 1)
				 	CAudio_PlaySound(SfxOne, 0);


				if (Timer <= 0)
				{
					CAudio_PlaySound(SfxTimeOver, 0);
					SubGameState = SGTimeUp;
					SubStateTime = getCurrentTimeMilliseconds() + 750;
					SubStateCounter = 0;
				}
			}
		}
	}
}

void CGame_CreateActiveGame()
{
	switch(ActiveGameGameStateId)
	{
	 	case GSSnake:
	 		CGameSnake_deinit(GameSnake);
	 		Destroy_CGameSnake(GameSnake);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSRamIt:
	 		CGameRamIt_deinit(GameRamIt);
	 		Destroy_CGameRamIt(GameRamIt);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSPang:
	 		CGamePang_deinit(GamePang);
	 		Destroy_CGamePang(GamePang);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSSpaceInvaders:
	 		CGameInvaders_deinit(GameInvaders);
	 		Destroy_CGameInvaders(GameInvaders);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSFrog:
	 		CGameFrog_deinit(GameFrog);
	 		Destroy_CGameFrog(GameFrog);
	 		ActiveGameGameStateId = -1;
	 		break;
		case GSEddy:
	 		CGameFastEddy_deinit(GameFastEddy);
	 		Destroy_CGameFastEddy(GameFastEddy);
	 		ActiveGameGameStateId = -1;
	 		break;
		case GSBreakout:
			CGameBreakOut_deinit(GameBreakOut);
			Destroy_CGameBreakOut(GameBreakOut);
			ActiveGameGameStateId = -1;
			break;
	 	case GSTetris:
	 		CGameBlockStacker_deinit(GameBlockStacker);
	 		Destroy_CGameBlockStacker(GameBlockStacker);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	default:			
	 		ActiveGameGameStateId = -1;
	 		break;
	}

	switch (GameState)
	{
	 	case GSSnakeInit:
	 		GameSnake = Create_CGameSnake();
	 		ActiveGameGameStateId = GSSnake;
	 		break;
	 	case GSTetrisInit:
	 		GameBlockStacker = Create_CGameBlockStacker();
	 		ActiveGameGameStateId = GSTetris;
	 		break;
	 	case GSRamItInit:
	 		GameRamIt = Create_CGameRamIt();
	 		ActiveGameGameStateId = GSRamIt;
	 		break;
	 	case GSEddyInit:
	 		GameFastEddy = Create_CGameFastEddy();
	 		ActiveGameGameStateId = GSEddy;
	 		break;
	 	case GSFrogInit:
	 		GameFrog = Create_CGameFrog();
	 		ActiveGameGameStateId = GSFrog;
	 		break;
	 	case GSBreakoutInit:
			GameBreakOut = Create_CGameBreakOut();
			ActiveGameGameStateId = GSBreakout;
			break;
		case GSPangInit:
	 		GamePang = Create_CGamePang();
	 		ActiveGameGameStateId = GSPang;
	 		break;
	 	case GSSpaceInvadersInit:
	 		GameInvaders = Create_CGameInvaders();
	 		ActiveGameGameStateId = GSSpaceInvaders;
	 		break;
	 	default:
	 		ActiveGameGameStateId = -1;
	 		break;
	}
}
void CGame_DeInit()
{
	switch(ActiveGameGameStateId)
	{
	 	case GSSnake:
	 		CGameSnake_deinit(GameSnake);
	 		Destroy_CGameSnake(GameSnake);
	 		break;
	 	case GSRamIt:
	 		CGameRamIt_deinit(GameRamIt);
	 		Destroy_CGameRamIt(GameRamIt);
	 		break;
	 	case GSPang:
	 		CGamePang_deinit(GamePang);
	 		Destroy_CGamePang(GamePang);
	 		break;
	 	case GSSpaceInvaders:
	 		CGameInvaders_deinit(GameInvaders);
	 		Destroy_CGameInvaders(GameInvaders);
	 		break;
	 	case GSFrog:
	 		CGameFrog_deinit(GameFrog);
	 		Destroy_CGameFrog(GameFrog);
	 		break;
	 	case GSEddy:
	 		CGameFastEddy_deinit(GameFastEddy);
	 		Destroy_CGameFastEddy(GameFastEddy);
	 		break;
	 	case GSBreakout:
	 		CGameBreakOut_deinit(GameBreakOut);
	 		Destroy_CGameBreakOut(GameBreakOut);
	 		break;
	 	case GSTetris:
	 		CGameBlockStacker_deinit(GameBlockStacker);
	 		Destroy_CGameBlockStacker(GameBlockStacker);
	 		break;
	 	default:
	 		break;
	}

	DeInitSubScoreScreen();


	CGame_UnLoadMusic();
	CGame_UnLoadGraphics();
	CGame_UnLoadSound();
	CGame_SaveSettings();
	CGame_SaveHighScores();

	CAudio_DeInit();
	CFont_DeInit();
	CImage_DeInit();
	CSprites_DeInit();
}

void CGame_Init()
{
	//srand(get_time());
	srand(0);
	initDebugSpeed();
	CAudio_Init();
	CFont_Init();
	CImage_Init();
	CSprites_Init();
	CGame_ResetHighScores();
	//CSprites_SetForceShowCollisionShape(debugShowCollisionShapes);

	CGame_LoadSettings();
	CGame_LoadHighScores();
	CGame_LoadGraphics();
	CGame_LoadMusic();
	CGame_LoadSound();

	ResetGlobalsTitleScreen();

	//Main State Variables and such
	CurrentGameMusicID = -1;
	GameState = GSIntroInit;
	Game = 0;
	GameMode = GMGame;
	GameAlpha = MaxAlpha;
	SubStateTime = 0;
	Timer = 0.0;
	SubStateCounter = 0;
	TimerTicks = 0;
	SubGameState = SGNone;
	NextSubState = 0;
	NextSubStateCounter = 0;
	NextSubStateTimeAdd = 0;
	ActiveGameGameStateId = -1;

	//Clear score values
	CGame_ResetScores();

	CSprites_SetForceShowCollisionShape(false);
}

int[1000] DebugTmpText;
int[10] DebugTmpNr = "test";
		

void CGame_MainLoop()
{
	CSprites_SpritesDrawnReset();
	CGame_UpdateTimer();

	switch (GameState)
	{
		case GSIntroInit:
		case GSIntro:
			Intro();
			break;

		case GSSubScoreInit:
		case GSSubScore:
		 	SubScoreScreen();
		 	break;

		case GSTitleScreenInit:
		case GSTitleScreen:
		 	//to clear the game data & set NULL to ActiveGame
		 	CGame_CreateActiveGame();
		 	TitleScreen();
		 	break;

	 	case GSSnakeInit:
	 	case GSRamItInit:
	 	case GSPangInit:
	 	case GSSpaceInvadersInit:
	 	case GSFrogInit:
	 	case GSEddyInit:
	 	case GSBreakoutInit:
	 	case GSTetrisInit:
	 		CGame_CreateActiveGame();
	 		switch (ActiveGameGameStateId)
	 		{
	 			case GSSnake:
	 				CGameSnake_init(GameSnake);
	 				break;
	 			case GSRamIt:
	 				CGameRamIt_init(GameRamIt);
	 				break;
	 			case GSPang:
	 				CGamePang_init(GamePang);
	 				break;
	 			case GSSpaceInvaders:
	 				CGameInvaders_init(GameInvaders);
	 				break;
	 			case GSFrog:
	 				CGameFrog_init(GameFrog);
	 				break;
	 			case GSEddy:
	 				CGameFastEddy_init(GameFastEddy);
	 				break;
	 			case GSBreakout:
	 				CGameBreakOut_init(GameBreakOut);
	 				break;
	 			case GSTetris:
	 				CGameBlockStacker_init(GameBlockStacker);
	 				break;
	 		}
			CGame_ResetTimer();
	 		CGame_StartCrossFade(ActiveGameGameStateId, SGReadyGo, 3, 500);
	 		break;			
	
	 	case GSSnake:
	 	case GSRamIt:
	 	case GSPang:
	 	case GSSpaceInvaders:
	 	case GSFrog:
	 	case GSEddy:
	 	case GSBreakout:
	 	case GSTetris:
	 		switch (ActiveGameGameStateId)
	 		{
	 			case GSSnake:
					StartDebugSpeed(5);
	 				CGameSnake_UpdateLogic(GameSnake);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameSnake_Draw(GameSnake);
					StopDebugSpeed(6);
	 				break;
	 			case GSRamIt:
					StartDebugSpeed(5);
	 				CGameRamIt_UpdateLogic(GameRamIt);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameRamIt_Draw(GameRamIt);
					StopDebugSpeed(6);
	 				break;
	 			case GSPang:
					StartDebugSpeed(5);
	 				CGamePang_UpdateLogic(GamePang);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGamePang_Draw(GamePang);
					StopDebugSpeed(6);
	 				break;
	 			case GSSpaceInvaders:
	 				StartDebugSpeed(5);
					CGameInvaders_UpdateLogic(GameInvaders);
	 				StopDebugSpeed(5);
					StartDebugSpeed(6);
					CGameInvaders_Draw(GameInvaders);
					StopDebugSpeed(6);
	 				break;
	 			case GSFrog:
					StartDebugSpeed(5);
					CGameFrog_UpdateLogic(GameFrog);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
					CGameFrog_Draw(GameFrog);
	 				StopDebugSpeed(6);
					break;
	 			case GSEddy:
					StartDebugSpeed(5);		
	 				CGameFastEddy_UpdateLogic(GameFastEddy);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameFastEddy_Draw(GameFastEddy);
					StopDebugSpeed(6);
	 				break;
	 			case GSBreakout:
					StartDebugSpeed(5);
					CGameBreakOut_UpdateLogic(GameBreakOut);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
					CGameBreakOut_Draw(GameBreakOut);
					StopDebugSpeed(6);
	 				break;
	 			case GSTetris:
					StartDebugSpeed(5);
	 				CGameBlockStacker_UpdateLogic(GameBlockStacker);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameBlockStacker_Draw(GameBlockStacker);
					StopDebugSpeed(6);
	 				break;
	 			default:
	 				break;
	 		}
	 		break;
	 	default:
	 		break;
	}

	// if (AlphaEnabled)
	// {
	// 	if (GameAlpha < MaxAlpha)
	// 	{
	// 		GameAlpha = (int)truncf(MaxAlpha * ((float)(pd->system->getCurrentTimeMilliseconds() - AlphaTimer) / MaxAlphaTime));
	// 		if (GameAlpha >= MaxAlpha)
	// 		{
	// 			GameAlpha = MaxAlpha;
	// 			SubGameState = NextSubState;
	// 			SubStateTime = pd->system->getCurrentTimeMilliseconds() + NextSubStateTimeAdd;
	// 			SubStateCounter = (float)NextSubStateCounter;
	// 		}
	// 		if ((int)floorf((float)(GameAlpha / (MaxAlpha / (GameAlphaPatternLength - 1)))) != GameAlphaPatternIndex)
	// 		{
	// 			GameAlphaPatternIndex = (int)floorf((float)(GameAlpha / (MaxAlpha / (GameAlphaPatternLength-1))));
	// 			pd->graphics->pushContext(TexOffScreenMask);
	// 			pd->graphics->fillRect(0, 0, 0, 0, kColorBlack);
	// 			pd->graphics->fillRect(0, 0, ScreenWidth, ScreenHeight, (LCDColor)FadeInPatterns3[(GameAlphaPatternLength - 1) - GameAlphaPatternIndex]);
	// 			pd->graphics->popContext();
	// 			pd->graphics->setBitmapMask(TexOffScreen, TexOffScreenMask);
	// 		}
	// 		pd->graphics->drawBitmap(TexOffScreen, 0, 0, kBitmapUnflipped);
	// 	}
	// }

// int[21] GFXSlotsMsg = "GFX Slots: 0000/0000";
// 	int[21] SNDSlotsMsg = "SND Slots: 0000/0000";
// 	int[21] MUSSlotsMsg = "MUS Slots: 0000/0000";
// 	int[26] SPRSlotsMsg = "SPR Slots: 0000/0000/0000";
// 	int[17] SPRDRWMsg   = "SPR Draws: 0000"; 
// 	int[11] LOWSPRMsg   = "LOW SPR: 0";
// 	int[13] CPUUSEMsg   = "CPU USE: 000";
// 	if(debugInfoStats)
// 	{
		
// 		GFXSlotsMsg[11] = '0' + (GFX_Max/ 1000);
// 		GFXSlotsMsg[12] = '0' + (GFX_Max % 1000) / 100;
// 		GFXSlotsMsg[13] = '0' + ((GFX_Max % 1000) % 100) / 10;
// 		GFXSlotsMsg[14] = '0' + ((GFX_Max % 1000) % 100) % 10;

// 		GFXSlotsMsg[16] = '0' + (CImage_ImageSlotsUsed / 1000);
// 		GFXSlotsMsg[17] = '0' + (CImage_ImageSlotsUsed % 1000) / 100;
// 		GFXSlotsMsg[18] = '0' + ((CImage_ImageSlotsUsed % 1000) % 100) / 10;
// 		GFXSlotsMsg[19] = '0' + ((CImage_ImageSlotsUsed % 1000) % 100) % 10;


// 		SNDSlotsMsg[11] = '0' + (SND_Max / 1000);
// 		SNDSlotsMsg[12] = '0' + (SND_Max % 1000) / 100;
// 		SNDSlotsMsg[13] = '0' + ((SND_Max % 1000) % 100) / 10;
// 		SNDSlotsMsg[14] = '0' + ((SND_Max % 1000) % 100) % 10;

// 		SNDSlotsMsg[16] = '0' + (CAudio_SoundSlotsUsed / 1000);
// 		SNDSlotsMsg[17] = '0' + (CAudio_SoundSlotsUsed % 1000) / 100;
// 		SNDSlotsMsg[18] = '0' + ((CAudio_SoundSlotsUsed % 1000) % 100) / 10;
// 		SNDSlotsMsg[19] = '0' + ((CAudio_SoundSlotsUsed % 1000) % 100) % 10;

// 		MUSSlotsMsg[11] = '0' + (MUS_Max  / 1000);
// 		MUSSlotsMsg[12] = '0' + (MUS_Max % 1000) / 100;
// 		MUSSlotsMsg[13] = '0' + ((MUS_Max % 1000) % 100) / 10;
// 		MUSSlotsMsg[14] = '0' + ((MUS_Max % 1000) % 100) % 10;

// 		MUSSlotsMsg[16] = '0' + (CAudio_MusicSlotsUsed / 1000);
// 		MUSSlotsMsg[17] = '0' + (CAudio_MusicSlotsUsed % 1000) / 100;
// 		MUSSlotsMsg[18] = '0' + ((CAudio_MusicSlotsUsed % 1000) % 100) / 10;
// 		MUSSlotsMsg[19] = '0' + ((CAudio_MusicSlotsUsed % 1000) % 100) % 10;


// 		SPRSlotsMsg[11] = '0' + (CSprites_spriteMax / 1000);
// 		SPRSlotsMsg[12] = '0' + (CSprites_spriteMax % 1000) / 100;
// 		SPRSlotsMsg[13] = '0' + ((CSprites_spriteMax % 1000) % 100) / 10;
// 		SPRSlotsMsg[14] = '0' + ((CSprites_spriteMax % 1000) % 100) % 10;

// 		SPRSlotsMsg[16] = '0' + (CSprites_MaxSpriteSlotsUsed / 1000);
// 		SPRSlotsMsg[17] = '0' + (CSprites_MaxSpriteSlotsUsed % 1000) / 100;
// 		SPRSlotsMsg[18] = '0' + ((CSprites_MaxSpriteSlotsUsed % 1000) % 100) / 10;
// 		SPRSlotsMsg[19] = '0' + ((CSprites_MaxSpriteSlotsUsed % 1000) % 100) % 10;

// 		SPRSlotsMsg[21] = '0' + (CSprites_SpriteSlotsUsed / 1000);
// 		SPRSlotsMsg[22] = '0' + (CSprites_SpriteSlotsUsed % 1000) / 100;
// 		SPRSlotsMsg[23] = '0' + ((CSprites_SpriteSlotsUsed % 1000) % 100) / 10;
// 		SPRSlotsMsg[24] = '0' + ((CSprites_SpriteSlotsUsed % 1000) % 100) % 10;

		
// 		SPRDRWMsg[11] = '0' + (CSprites_SpritesDrawn / 1000);
// 		SPRDRWMsg[12] = '0' + (CSprites_SpritesDrawn % 1000) / 100;
// 		SPRDRWMsg[13] = '0' + ((CSprites_SpritesDrawn % 1000) % 100) / 10;
// 		SPRDRWMsg[14] = '0' + ((CSprites_SpritesDrawn % 1000) % 100) % 10;

// 		int cpuused = CpuUsed();
// 		CPUUSEMsg[9] = '0' + (cpuused / 100);
// 		CPUUSEMsg[10] = '0' + ((cpuused % 100) / 10);
// 		CPUUSEMsg[11] = '0' + (((cpuused % 100) % 10));

// 		if(CSprites_notEnoughSpots)
// 			LOWSPRMsg[9] = 'T';
// 		else
// 			LOWSPRMsg[9] = 'F';

// 		PDebugText = DebugTmpText;
// 		*PDebugText = 0;
// 		PDebugText = faststrcat(PDebugText, "MEM Use: ");
// 		itoa(MemoryUsed(), DebugTmpNr, 10);
// 		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		
// 		set_multiply_color(make_color_rgba(255,0,255,255));
// 		print_at(0,bios_character_height*1,GFXSlotsMsg);
// 		print_at(0,bios_character_height*2,SNDSlotsMsg);
// 		print_at(0,bios_character_height*3,MUSSlotsMsg);
// 		print_at(0,bios_character_height*4,SPRSlotsMsg);
// 		print_at(0,bios_character_height*5,SPRDRWMsg);
// 		print_at(0,bios_character_height*6,LOWSPRMsg);
// 		print_at(0,bios_character_height*7,CPUUSEMsg);
// 		print_at(0,bios_character_height*8,DebugTmpText);
			
// 		set_multiply_color(color_white);
// 	}

	if(debugInfoStats)
	{
		int* PDebugText = DebugTmpText;
		*PDebugText = 0;
		PDebugText = faststrcat(PDebugText, "GFX Slots: ");
		itoa(GFX_Max, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CImage_ImageSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");

		PDebugText = faststrcat(PDebugText, "SND Slots: ");
		itoa(SND_Max, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CAudio_SoundSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");

		PDebugText = faststrcat(PDebugText, "MUS Slots: ");
		itoa(MUS_Max, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CAudio_MusicSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");
		
		PDebugText = faststrcat(PDebugText, "SPR Slots: ");		
		itoa(CSprites_spriteMax, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CSprites_MaxSpriteSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);		
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CSprites_SpriteSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");
				

		PDebugText = faststrcat(PDebugText, "SPR Draws: ");
		itoa(CSprites_SpritesDrawn, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");

		PDebugText = faststrcat(PDebugText, "LOW SPR: ");
		if(CSprites_notEnoughSpots)
			PDebugText = faststrcat(PDebugText, "T");
		else
			PDebugText = faststrcat(PDebugText, "F");
		PDebugText = faststrcat(PDebugText,"\n");
		
		PDebugText = faststrcat(PDebugText, "MEM USE: ");		
		itoa(MemoryUsed(), DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		
		PDebugText = faststrcat(PDebugText,"\n");
		
		PDebugText = faststrcat(PDebugText, "CPU USE: ");		
		itoa(CpuUsed(), DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);

		PDebugText = faststrcat(PDebugText,"\n");
		
		set_multiply_color(make_color_rgba(255,0,255,255));
		print_at(0,bios_character_height,DebugTmpText);
		set_multiply_color(color_white);
	}
}



#endif