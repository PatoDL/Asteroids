#include "nave.h"

#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "gameplay/gameplay.h"
#include "gameplay/pausa/pausa.h"

namespace Juego
{
	namespace Gameplay
	{		
			Nave nave;

			
			static Vector2 vNormalizador;

			static Vector2 posNave;
			static Vector2 posMouse;
			static Vector2 vecDirector;
			static float angulo;

			void iniciarNave()
			{
				nave.base = screenWidth/30;
				nave.altura = (nave.base / 2) / tanf(25 * DEG2RAD);
				nave.rotacion = 0;
				nave.pos = { (float)screenWidth / 2,(float)screenHeight / 2 };
				nave.colision = { nave.pos.x + sin(nave.rotacion*DEG2RAD),
					nave.pos.y - cos(nave.rotacion*DEG2RAD) };
				nave.radioColision = nave.altura * 2 / 3 + 10;
				nave.color = WHITE;
				nave.sprite = LoadTexture("res/nave.png");
				nave.velocidad = (float)screenWidth/2;
				nave.aceleracion = {10.0f,10.0f };
				nave.angleFixer = 90.0f;
				nave.detenida = true;
				nave.puntaje = 0;
			}

			void moverNave()
			{

				if (!pausa)
				{
					if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
					{	
						vNormalizador.x = vecDirector.x / sqrt(pow(vecDirector.x, 2.0f) + pow(vecDirector.y, 2.0f));
						vNormalizador.y = vecDirector.y / sqrt(pow(vecDirector.x, 2.0f) + pow(vecDirector.y, 2.0f));

						nave.aceleracion.x += vNormalizador.x * nave.velocidad * GetFrameTime();
						nave.aceleracion.y += vNormalizador.y * nave.velocidad * GetFrameTime();
					}
				}
			}

			void actualizarPosNave()
			{
				posNave = nave.pos;
				posMouse = { GetMousePosition() };
				vecDirector = { posMouse.x - posNave.x, posMouse.y - posNave.y };
				angulo = atan2(vecDirector.y , vecDirector.x);
				nave.rotacion = angulo;

				nave.pos.x = nave.pos.x + nave.aceleracion.x*GetFrameTime();
				nave.pos.y = nave.pos.y + nave.aceleracion.y*GetFrameTime();
			}

			void chequearColisionConBordes()
			{
				if (nave.pos.x < bordes[izquierda])
				{
					nave.pos.x = bordes[derecha];
				}
				if (nave.pos.x > bordes[derecha])
				{
					nave.pos.x = bordes[izquierda];
				}
				if (nave.pos.y < bordes[arriba])
				{
					nave.pos.y = bordes[abajo];
				}
				if (nave.pos.y > bordes[abajo])
				{
					nave.pos.y = bordes[arriba];
				}
			}

			void dibujarNave()
			{
				DrawTexturePro(nave.sprite, { 0.0f,0.0f,(float)nave.sprite.width,(float)nave.sprite.height },
					{ nave.pos.x , nave.pos.y, (float)nave.sprite.width / 8 , (float)nave.sprite.height / 8 },
					{ (float)nave.sprite.width / 16,(float)nave.sprite.height / 16 }, nave.rotacion*RAD2DEG+nave.angleFixer, WHITE);
			}
	}
}