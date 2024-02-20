#include <iostream>
#include "olcConsoleGameEngine.h"

using namespace std;

class HalloweenGame : public olcConsoleGameEngine
{
private:
	float fPlayerX = 2.0f;
	float fPlayerY = 16.0f;
	float fPlayerA = 0.0f;
	float fFOV = 3.14159f / 4.0f;
	float fDepth = 16.0f;

	int nMapHeight = 32;
	int nMapWidth = 32;
	float* fDepthBuffer;

	wstring map;
	bool bMap = true;

	olcSprite* spriteWall;
	olcSprite* spriteGhost;
	olcSprite* spriteBullet;
	olcSprite* spritePumpkin;
	struct Thing
	{
		float x;
		float y;
		float vx;
		float vy;
		float sx;
		float sy;
		olcSprite* sprite;
		bool show;
		
	};

	list<Thing> listThings;

public:
	HalloweenGame()
	{
		m_sAppName = L"HalloweenGame";
		
	}
	bool OnUserCreate() 
	{

		map += L"################################";
		map += L"#..............................#";
		map += L"#..............................#";
		map += L"#.....####.....................#";
		map += L"#.....####.....................#";
		map += L"#.....####..........######.....#";
		map += L"#.....####..........######.....#";
		map += L"#.....####.....................#";
		map += L"#.....####.....................#";
		map += L"#.....####.....................#";
		map += L"#.....####.....................#";
		map += L"#..............................#";
		map += L"#..............................#";
		map += L"#............##############....#";
		map += L"#............##############....#";
		map += L"#..............................#";
		map += L"#..............................#";
		map += L"#..............................#";
		map += L"#..............................#";
		map += L"#..................###.........#";
		map += L"#.....###..........###.........#";
		map += L"#.....###..........###.........#";
		map += L"#.....###..........###.........#";
		map += L"#.....###......................#";
		map += L"#.....###......................#";
		map += L"#.....###......................#";
		map += L"#.....###......................#";
		map += L"#.....###......................#";
		map += L"#..............................#";
		map += L"#...........##############.....#";
		map += L"#..............................#";
		map += L"################################";

		spriteWall = new olcSprite(L"..\\Halloween_Game\\wall2.spr");
		spriteGhost = new olcSprite(L"..\\Halloween_Game\\ghost.spr");
		spriteBullet = new olcSprite(L"..\\Halloween_Game\\bullet.spr");
		spritePumpkin = new olcSprite(L"..\\Halloween_Game\\Pumpkin.spr");
		fDepthBuffer = new float[ScreenWidth()];

		listThings = {
			
			{13.5f, 1.5f, 1.0f, 1.0f, 13.5f, 1.5f, spriteGhost,1},
			{13.5f, 31.5f, 1.0f, 1.0f, 13.5f, 31.5f, spriteGhost,1},
			{17.5f, 1.5f, 1.0f, 1.0f, 17.5f, 1.5f, spriteGhost,1},
			{17.5f, 31.5f, 1.0f, 1.0f, 17.5f, 31.5f, spriteGhost,1},
			{22.5f, 9.5f, 1.0f, 1.0f, 22.5f, 9.5f, spriteGhost,1},
			{24.5f, 24.5f, 1.0f, 1.0f, 24.5f, 24.5f, spriteGhost,1},
			{29.5f, 6.5f, 1.0f, 1.0f, 29.5f, 6.5f, spriteGhost,1},
			{30.5f, 22.5f, 1.0f, 1.0f, 30.5f, 22.5f, spriteGhost,1},


			{3.5f, 3.5f, 1.0f, 1.0f, 3.5f, 3.5f, spritePumpkin,1},
			{2.5f, 14.5f, 1.0f, 1.0f,2.5f, 14.5f, spritePumpkin,1},
			{6.5f, 11.5f, 1.0f, 1.0f, 6.5f, 11.5f, spritePumpkin,1},
			{8.5f, 25.5f, 1.0f, 1.0f, 8.5f, 25.5f, spritePumpkin,1},
			{10.5f, 13.5f, 1.0f, 1.0f, 10.5f, 13.5f, spritePumpkin,1},
			{13.5f, 4.5f, 1.0f, 1.0f, 13.5f, 4.5f, spritePumpkin,1},
			{17.5f, 22.5f, 1.0f, 1.0f,17.5f, 22.5f, spritePumpkin,1},
			{18.5f, 5.5f, 1.0f, 1.0f, 18.5f, 5.5f, spritePumpkin,1},
			{22.5f, 12.5f, 1.0f, 1.0f, 22.5f, 12.5f, spritePumpkin,1},
			{23.5f, 27.5f, 1.0f, 1.0f, 23.5f, 27.5f, spritePumpkin,1},
			{24.5f, 1.5f, 1.0f, 1.0f, 24.5f, 1.5f, spritePumpkin,1},
			{26.5f, 15.5f, 1.0f, 1.0f, 26.5f, 15.5f, spritePumpkin,1},
			{28.5f, 5.5f, 1.0f, 1.0f, 28.5f, 5.5f, spritePumpkin,1},
			{28.5f, 29.5f, 1.0f, 1.0f, 28.5f, 29.5f, spritePumpkin,1},
			
			
			
			};

		return true;
	}
	bool OnUserUpdate(float fElapsedTime)
	{
		if (m_keys[VK_LEFT].bHeld && m_keys[VK_SHIFT].bHeld)
			fPlayerA -= (2.0f) * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld && m_keys[VK_SHIFT].bHeld)
			fPlayerA += (2.0f) * fElapsedTime;
		if (m_keys[VK_LEFT].bHeld && !m_keys[VK_SHIFT].bHeld)
			fPlayerA -= (0.5f) * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld && !m_keys[VK_SHIFT].bHeld)
			fPlayerA += (0.5f) * fElapsedTime;
		if (m_keys[L'W'].bHeld)
		{
			fPlayerX += sinf(fPlayerA) * 3.0f * fElapsedTime;
			fPlayerY += cosf(fPlayerA) * 3.0f * fElapsedTime;

			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * 3.0f * fElapsedTime;
				fPlayerY -= cosf(fPlayerA) * 3.0f * fElapsedTime;
			}

		}
		if (m_keys[L'S'].bHeld)
		{
			fPlayerX -= sinf(fPlayerA) * 3.0f * fElapsedTime;
			fPlayerY -= cosf(fPlayerA) * 3.0f * fElapsedTime;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX += sinf(fPlayerA) * 3.0f * fElapsedTime;
				fPlayerY += cosf(fPlayerA) * 3.0f * fElapsedTime;
			}

		}
		if (m_keys[L'D'].bHeld)
		{
			fPlayerX += cosf(fPlayerA) * 3.0f * fElapsedTime;
			fPlayerY -= sinf(fPlayerA) * 3.0f * fElapsedTime;

			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= cosf(fPlayerA) * 3.0f * fElapsedTime;
				fPlayerY += sinf(fPlayerA) * 3.0f * fElapsedTime;
			}

		}
		if (m_keys[L'A'].bHeld)
		{
			fPlayerX -= cosf(fPlayerA) * 3.0f * fElapsedTime;
			fPlayerY += sinf(fPlayerA) * 3.0f * fElapsedTime;

			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX += cosf(fPlayerA) * 3.0f * fElapsedTime;
				fPlayerY -= sinf(fPlayerA) * 3.0f * fElapsedTime;
			}

		}


		if (m_keys[L'M'].bHeld)
			bMap = true;
		if (m_keys[L'N'].bHeld)
			bMap = false;

		if (m_keys[L' '].bPressed)
		{
			Thing bullet;
			bullet.x = fPlayerX;
			bullet.y = fPlayerY;

			bullet.vx = sinf(fPlayerA) * 8.0f;
			bullet.vy = cosf(fPlayerA) * 8.0f;

			bullet.sprite = spriteBullet;
			bullet.show = true;
			listThings.push_back(bullet);
		}

		for (int x = 0; x < ScreenWidth(); x++)
		{
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)ScreenWidth()) * fFOV;
			float fDistancetoWall = 0.01f;
			bool bHitWall = 0;

			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);

			float fSampleX = 0.0f;
			
			while (!bHitWall && fDistancetoWall < fDepth)
			{
				fDistancetoWall += 0.01f;
				int nTestX = (int)(fPlayerX + fEyeX * fDistancetoWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistancetoWall);

				if (nTestX < 0 || nTestX >= nMapWidth || nTestY >= nMapHeight || nTestY < 0)
				{
					bHitWall = true;
					fDistancetoWall = fDepth;
				}
				else
				{
					if (map.c_str()[nTestX * nMapWidth + nTestY] == '#')
					{
						bHitWall = true;
						float fBlockMidX = (float)nTestX + 0.5f;
						float fBlockMidY = (float)nTestY + 0.5f;

						float fTestPointX = fPlayerX + fEyeX * fDistancetoWall;
						float fTestPointY = fPlayerY + fEyeY * fDistancetoWall;

						float fTestAngle = atan2f((fTestPointY - fBlockMidY), (fTestPointX - fBlockMidX));

						if (fTestAngle >= -3.14159f * 0.25f && fTestAngle < 3.14159f * 0.25f)
							fSampleX = fTestPointY - (float)nTestY;
						if (fTestAngle >= 3.14159f * 0.25f && fTestAngle < 3.14159f * 0.75f)
							fSampleX = fTestPointX - (float)nTestX;
						if (fTestAngle < -3.14159f * 0.25f && fTestAngle >= -3.14159f * 0.75f)
							fSampleX = fTestPointX - (float)nTestX;
						if (fTestAngle >= 3.14159f * 0.75f || fTestAngle < -3.14159f * 0.75f)
							fSampleX = fTestPointY - (float)nTestY;
					}
					
				}

			}
			int nCeiling = (float)(ScreenHeight() / 2.0) - ScreenHeight() / ((float)fDistancetoWall);
			int nFloor = ScreenHeight() - nCeiling;

			fDepthBuffer[x] = fDistancetoWall;
		

			for (int y = 0; y < ScreenHeight(); y++)
			{
				if (y <= nCeiling)
					Draw(x, y, L' ');
				else if (y > nCeiling && y <= nFloor)
				{
					if (fDistancetoWall < fDepth)
					{
						float fSampleY = ((float)y - (float)nCeiling) / ((float)nFloor - (float)nCeiling);
						Draw(x, y, spriteWall->SampleGlyph(fSampleX, fSampleY), spriteWall->SampleColour(fSampleX, fSampleY));

					}
					else
						Draw(x, y, PIXEL_SOLID, 0);
				}
				else
				{
					Draw(x, y, PIXEL_SOLID, FG_DARK_GREEN);

				}
			}
			

		}
		for (auto& thing : listThings)
		{


			if (thing.sprite == spriteBullet)
			{
			
			thing.x += thing.vx * fElapsedTime;
			thing.y += thing.vy * fElapsedTime;

			for (auto& thing2 : listThings)
			{
				if (thing2.sprite == spriteGhost)
				{
					if (thing2.x >= thing.x - 0.2f && thing2.x <= thing.x + 0.2 && thing2.y >= thing.y - 0.2f && thing2.y <= thing.y + 0.2)
					{
						//thing2.x = thing2.sx;
						//thing2.y = thing2.sy;
						thing2.show = false;
						thing.show = false;
					}

				}
			}

			}
			if (map.c_str()[(int)thing.x * nMapWidth + (int)thing.y] == '#' && thing.sprite==spriteBullet)
				thing.show = false;
			

			float fVecX = thing.x - fPlayerX;
			float fVecY = thing.y - fPlayerY;
			float fDistanceFromPlayer = sqrtf(fVecX * fVecX + fVecY * fVecY);

			float fEyeX = sinf(fPlayerA);
			float fEyeY = cosf(fPlayerA);

			float fThingAngle = atan2f(fEyeY, fEyeX) - atan2f(fVecY, fVecX);

			if (fThingAngle < -3.14159)
				fThingAngle += 2.0f * 3.14159;
			if (fThingAngle > 3.14159)
				fThingAngle -= 2.0f * 3.14159;

			bool bInSight = fabs(fThingAngle) < fFOV / 2.0f;

			if (fDistanceFromPlayer < fDepth && thing.sprite==spriteGhost)
			{
				thing.x -= sinf(atan2f(fVecX,fVecY)) * thing.vx * fElapsedTime;
				thing.y -= cosf(atan2f(fVecX,fVecY)) * thing.vy * fElapsedTime;
			}
			if (fDistanceFromPlayer < 0.1 && thing.sprite == spriteGhost)
			{
				wstring msg = L"You Died! A ghost was probably behind you. Press any key and try again";
				MessageBox(NULL, (msg).c_str(), L"Msg title", MB_OK | MB_ICONQUESTION);
				exit(0);
			}
			if (bInSight && fDistanceFromPlayer >= 0.5f && fDistanceFromPlayer < fDepth)
			{
				float fThingCeiling = (float)(ScreenHeight() / 2.0) - ScreenHeight() / ((float)fDistanceFromPlayer);
				float fThingFloor = ScreenHeight() - fThingCeiling;
				float fThingHeight = fThingFloor - fThingCeiling;
				float fThingAspectRatio = (float)thing.sprite->nHeight / (float)thing.sprite->nWidth;
				float fThingWidth = fThingHeight / fThingAspectRatio;

				float fMiddleOfThing = (0.5f * (fThingAngle / (fFOV / 2.0f)) + 0.5f) * (float)ScreenWidth();
			
			for (float tx = 0; tx < fThingWidth; tx++)
			{
				for (float ty = 0; ty < fThingHeight; ty++)
				{
					float fSampleX = tx / fThingWidth;
					float fSampleY = ty / fThingHeight;
					wchar_t c = thing.sprite->SampleGlyph(fSampleX, fSampleY);
					int nThingColumn = (int)(fMiddleOfThing + tx - (fThingWidth / 2.0f));
					if (nThingColumn > 0 && nThingColumn < ScreenWidth())
						if (c != L' ' && fDepthBuffer[nThingColumn] >= fDistanceFromPlayer) ///
						{
							Draw(nThingColumn, fThingCeiling + ty, c, thing.sprite->SampleColour(fSampleX, fSampleY));
							fDepthBuffer[nThingColumn] = fDistanceFromPlayer;
						}
				}
			}
			}
		}
		bool bWin = true;
		for (auto& ghost : listThings)
		{
			if (ghost.sprite == spriteGhost)
				bWin = false;
		}
		if (bWin)
		{
			wstring msg = L"You Won!";
			MessageBox(NULL, (msg).c_str(), L"Msg title", MB_OK | MB_ICONQUESTION);
			exit(0);
		}
		listThings.remove_if([](Thing& t) { return !t.show; });

		// Display Map
		if (bMap == true)
		{
			for (int nx = 0; nx < nMapWidth; nx++)
				for (int ny = 0; ny < nMapWidth; ny++)
				{
					Draw(nx + 1, ny + 1, map[ny * nMapWidth + nx]);
				}
			Draw(1 + (int)fPlayerY, 1 + (int)fPlayerX, L'P');
		}
		
		wchar_t s[256];
		swprintf_s(s, 256, L"Halloween Game - %s - FPS: %3.2f - %3.2f ", m_sAppName.c_str(), 1.0f / fElapsedTime, fPlayerA);
		SetConsoleTitle(s);
		return true;
	}
};

int main()
{
	HalloweenGame game;
	game.ConstructConsole(360,240,4,4);
	game.Start();
	

	return 0;
}