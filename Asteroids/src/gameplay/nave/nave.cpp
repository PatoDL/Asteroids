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

			//variables para calcular la rotacion
			Vector2 v1;
			Vector2 v2;

			float prodPunto;
			float moduloV1;
			float moduloV2;
			float prodModulo; 
			//--------------------------------------

			static void calcularAnguloRotacion();
			static void normalizarDireccion();

			void iniciarNave()
			{
				nave.base = screenWidth/30;
				nave.altura = (nave.base / 2) / tanf(25 * DEG2RAD);
				nave.rotacion = 0;
				nave.pos = { (float)screenWidth / 2,(float)screenHeight / 2 };
				nave.colision = { nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
					nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) };
				nave.radioColision = nave.altura * 2 / 3 + 10;
				nave.color = WHITE;
				nave.sprite = LoadTexture("res/cohete.png");
				nave.velocidad = (float)screenWidth/3;
				nave.aceleracion = 0.0f;
				nave.anguloAceler = 0.0f;
				nave.detenida = true;
				nave.puntaje = 0;
			}

			void calcularAnguloRotacion()
			{
				v1.x = 0;
				v1.y = -nave.pos.y;

				v2.x = GetMouseX() - nave.pos.x;
				v2.y = GetMouseY() - nave.pos.y;

				prodPunto = v1.x*v2.x + v1.y*v2.y;
				moduloV1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
				moduloV2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
				prodModulo = moduloV1 * moduloV2;
				nave.rotacion = acosf(prodPunto / (prodModulo));

				nave.rotacion *= RAD2DEG;

				if (GetMouseX() < nave.pos.x)
				{
					nave.rotacion = 360 - nave.rotacion;
				}

				/*v1 = { GetMouseX() - nave.pos.x,GetMouseY() - nave.pos.y };
				float angulo = atanf(v1.y / v1.x)*RAD2DEG;
				if (GetMouseX() < nave.pos.x)
				{
				angulo = 360 - angulo;
				}
				nave.rotacion = angulo;*/
			}

			float direccionNormalizada;
			Vector2 vectorNorm;

			void normalizarDireccion()
			{
				vectorNorm = { v2.x / moduloV2, v2.y / moduloV2 };
				direccionNormalizada = sqrtf(pow(vectorNorm.x, 2) + pow(vectorNorm.y, 2));
			}

			void moverNave()
			{
				calcularAnguloRotacion();
				normalizarDireccion();

				if (!pausa)
				{
					if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
					{
						if (nave.detenida)
						{
							nave.detenida = false;
						}
						nave.anguloAceler = nave.rotacion;
						nave.aceleracion = 0.8 + direccionNormalizada;
					}
					if (IsMouseButtonUp(MOUSE_RIGHT_BUTTON) && nave.aceleracion != 0)
					{
						nave.aceleracion -= 0.05;
					}
				}
			}

			void actualizarPosNave()
			{
				nave.pos.y -= cos(nave.anguloAceler*DEG2RAD) * nave.velocidad*nave.aceleracion * GetFrameTime();
				nave.pos.x += sin(nave.anguloAceler*DEG2RAD) * nave.velocidad*nave.aceleracion * GetFrameTime();
				if (nave.aceleracion < 0.2 && !nave.detenida)
				{
					nave.aceleracion = 0.2;
				}
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
				if (IsKeyDown(KEY_C))
				{
					DrawCircle(nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						nave.radioColision,
						GREEN);
				}

				DrawTexturePro(nave.sprite, { 0.0f,0.0f,(float)nave.sprite.width,(float)nave.sprite.height },
					{ nave.pos.x , nave.pos.y , (float)nave.sprite.width / 8 , (float)nave.sprite.height / 8 },
					{ (float)nave.sprite.width / 16,(float)nave.sprite.height / 16 }, nave.rotacion, WHITE);
			}
	}
}