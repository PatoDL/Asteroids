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

			Vector2 vDireccion;  //vector que va de la nave a la pos del mouse, sirve para calcular la rotacion
			Vector2 vNormalizador;
			static void calcularAnguloRotacion();
			static void normalizarDireccion();

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
				nave.velocidad = (float)screenWidth/3;
				nave.aceleracionBase = { 0.8f };
				nave.aceleracion = { 0.0f,0.0f };
				nave.anguloAceler = 0.0f;
				nave.detenida = true;
				nave.puntaje = 0;
			}

			void calcularAnguloRotacion()
			{
				vDireccion.x = GetMouseX() - nave.pos.x;
				vDireccion.y = GetMouseY() - nave.pos.y;
				
				nave.rotacion = atan2(vDireccion.y , vDireccion.x)*RAD2DEG+90.0f;

				/*if (IsKeyReleased(KEY_F))
				{
					cout << nave.rotacion << endl;
					cout << "x:" << GetMouseX() << ",y:" << GetMouseY() << endl;
					cout << "navex:" << nave.pos.x << ", navey:" << nave.pos.y << endl;
				}*/
			}

			void normalizarDireccion()
			{
				/*vNormalizador.x = vDireccion.x / sqrtf(powf(vDireccion.x, 2) + powf(vDireccion.y, 2));
				vNormalizador.y = vDireccion.y / sqrtf(powf(vDireccion.x, 2) + powf(vDireccion.y, 2));*/
			}

			void moverNave()
			{
				calcularAnguloRotacion();
				//normalizarDireccion();
				
				if (!pausa)
				{
					if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
					{
						if (nave.detenida)
						{
							nave.detenida = false;
						}
						
						nave.anguloAceler = nave.rotacion;
					}

					nave.aceleracion = { nave.aceleracionBase //* vNormalizador.x 
										,nave.aceleracionBase //* vNormalizador.y
									   };
				}
			}

			void actualizarPosNave()
			{
				if (!nave.detenida)
				{
					nave.pos.y -= cos(nave.anguloAceler*DEG2RAD) * nave.velocidad * nave.aceleracion.x * GetFrameTime();
					nave.pos.x += sin(nave.anguloAceler*DEG2RAD) * nave.velocidad * nave.aceleracion.y * GetFrameTime();
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
				DrawTexturePro(nave.sprite, { 0.0f,0.0f,(float)nave.sprite.width,(float)nave.sprite.height },
					{ nave.pos.x , nave.pos.y, (float)nave.sprite.width / 8 , (float)nave.sprite.height / 8 },
					{ (float)nave.sprite.width / 16,(float)nave.sprite.height / 16 }, nave.rotacion, WHITE);
			}
	}
}