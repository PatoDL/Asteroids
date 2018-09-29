#include "gameplay.h"
#include "juego.h"
#include <cmath>

namespace Juego
{
	namespace Gameplay
	{
		Nave nave;
		Asteroide asteroides[20];
		
		static void iniciarNave();
		static void dibujarNave();
		static void iniciarAsteroides();
		static void dibujarAsteroides();
		void moverNave();
		void dibujarGameplay();
		void iniciarComponentesGP();

		void iniciarAsteroides()
		{
			for (int i = 0; i < 20; i++)
			{
				asteroides[i].pos = { (float)GetRandomValue(0,screenWidth),(float)GetRandomValue(0,screenHeight) };
				asteroides[i].radio = GetRandomValue(20, 30);
			}
		}

		void iniciarNave()
		{
			nave.posPunta = { (float)screenWidth/2,(float)screenHeight/2-15};
			nave.posIzq = { (float)screenWidth / 2-15,(float)screenHeight / 2+15 };
			nave.posDer = { (float)screenWidth / 2+15,(float)screenHeight / 2+15 };
			nave.radioColision = (nave.posDer.y-nave.posPunta.y)/2+10;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarAsteroides();
		}

		void moverNave()
		{
			if (IsKeyDown(KEY_UP))
			{
				nave.posPunta.y--;
				nave.posDer.y--;
				nave.posIzq.y--;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				nave.posPunta.y++;
				nave.posDer.y++;
				nave.posIzq.y++;
			}
			if (IsKeyDown(KEY_LEFT))
			{
				nave.posPunta.x--;
				nave.posDer.x--;
				nave.posIzq.x--;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				nave.posPunta.x++;
				nave.posDer.x++;
				nave.posIzq.x++;
			}
		}

		void dibujarNave()
		{
			if (IsKeyDown(KEY_SPACE)) { DrawCircle(nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2, nave.radioColision, GREEN); }
			DrawTriangle(nave.posIzq, nave.posDer, nave.posPunta, WHITE);
		}

		void dibujarAsteroides()
		{
			for (int i = 0; i < 20; i++)
			{
				DrawCircle(asteroides[i].pos.x, asteroides[i].pos.y, asteroides[i].radio, RED);
			}
		}

		void dibujarGameplay()
		{
			dibujarNave();
			dibujarAsteroides();
		}

	}
}