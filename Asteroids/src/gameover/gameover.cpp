#include "gameover.h"

#include "raylib.h"
#include "gameplay/gameplay.h"
#include "juego.h"

namespace Juego
{
	namespace Gameover
	{
		Texture2D fondo;
		Texture2D resultado;
		Texture2D felicidades;
		Texture2D perdiste;
		Texture2D volverAJ;
		Texture2D volverAJP;
		Texture2D volverAM;
		Texture2D volverAMP;
		Texture2D jugarB;
		Texture2D volverMB;

		static void chequearMouse();

		void inicializarGO()
		{
			fondo = LoadTexture("res/fondo portada.png");
			felicidades = LoadTexture("res/gameover/felicidades.png");
			perdiste = LoadTexture("res/gameover/perdiste0.png");
			volverAJ = LoadTexture("res/gameover/volver a jugar.png");
			volverAJP = LoadTexture("res/gameover/volver a jugarP.png");
			volverAM = LoadTexture("res/pausa/volver al menu.png");
			volverAMP = LoadTexture("res/pausa/volver al menuP.png");
			jugarB = volverAJ;
			volverMB = volverAM;
			resultado = perdiste;
		}

		void desinicializarGO()
		{
			UnloadTexture(fondo);
			UnloadTexture(felicidades);
			UnloadTexture(perdiste);
			UnloadTexture(volverAJ);
			UnloadTexture(volverAJP);
			UnloadTexture(volverAM);
			UnloadTexture(volverAMP);
			UnloadTexture(jugarB);
			UnloadTexture(volverMB);
			UnloadTexture(resultado);
		}

		void chequearMouse()
		{
				if (GetMouseX() >= (screenWidth - jugarB.width) / 2 &&
					GetMouseX() <= (screenWidth - jugarB.width) / 2 + jugarB.width)
				{
					if (GetMouseY() >= screenHeight - (jugarB.height * 2 + jugarB.height) &&
						GetMouseY() <= (screenHeight - (jugarB.height * 2 + jugarB.height)) + jugarB.height)
					{
						jugarB = volverAJP;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = juego;
						}
					}
					else if (GetMouseY() >= screenHeight - (volverMB.height + volverMB.height / 2) &&
						GetMouseY()<=(screenHeight - (volverMB.height + volverMB.height / 2))+volverMB.height)
					{
						volverMB = volverAMP;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = menu;
						}
					}
					else
					{
						jugarB = volverAJ;
						volverMB = volverAM;
					}
				
				}
				if (Gameplay::gano)
				{
					resultado = felicidades;
				}
				else
				{
					resultado = perdiste;
				}
		}

		void chequearInputGO()
		{
			chequearMouse();
		}

		void dibujarGO()
		{
			DrawTexture(fondo, screenWidth / 2 - fondo.width / 2, screenHeight / 2 - fondo.height / 2, WHITE);
			DrawTexture(resultado, (screenWidth - resultado.width) / 2, resultado.height * 2, WHITE);
			DrawTexture(jugarB, (screenWidth - jugarB.width) / 2, screenHeight - (jugarB.height * 2 + jugarB.height), WHITE);
			DrawTexture(volverMB, (screenWidth - volverMB.width) / 2, screenHeight - (volverMB.height + volverMB.height / 2), WHITE);
		}
	}
}