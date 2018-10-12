#include "gameover.h"

#include <iostream>
#include "raylib.h"
#include "gameplay/gameplay.h"
#include "juego.h"

using namespace std;

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
			jugarB = volverAJ;
			volverMB = Gameplay::botonMenu;
			resultado = perdiste;
		}

		void desinicializarGO()
		{
			UnloadTexture(fondo);
			UnloadTexture(felicidades);
			UnloadTexture(perdiste);
			UnloadTexture(volverAJ);
			UnloadTexture(volverAJP);
			UnloadTexture(jugarB);
			UnloadTexture(volverMB);
			UnloadTexture(resultado);
		}

		void chequearMouse()
		{
				if (GetMouseX() >= (screenWidth - jugarB.width) / 2 &&
					GetMouseX() <= (screenWidth - jugarB.width) / 2 + jugarB.width)
				{
					if (GetMouseY() >= screenHeight - (jugarB.height * 2 + jugarB.height) && GetMouseY() <= (screenHeight - (jugarB.height * 2 + jugarB.height)) + jugarB.height)
					{
						jugarB = volverAJP;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = juego;
						}
					}
					else if (GetMouseY() >= screenHeight - (volverMB.height + volverMB.height / 2) && GetMouseY()<=(screenHeight - (volverMB.height + volverMB.height / 2))+volverMB.height)
					{
						volverMB = Gameplay::botonMenuP;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = menu;
						}
					}
					else
					{
						jugarB = volverAJ;
						volverMB = Gameplay::botonMenu;
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