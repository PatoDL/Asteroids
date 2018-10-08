#include "juego.h"
#include "raylib.h"
#include "menu/menu.h"
#include "gameplay/gameplay.h"
#include "gameover/gameover.h"

namespace Juego 
{
	int screenWidth = 900;
	int screenHeight = 600;

	Estado estado=menu;
	Estado estadoA=menu;
	void ejecutarJuego();
	static void inicializarJuego();
	static void finalizarJuego();
	static void dibujarJuego();
	static void cambiarEstado();
	static void chequearInput();
	static void actualizarJuego();

	int randomizarColor()
	{
		return GetRandomValue(0, 255);
	}

	void chequearInput()
	{
		switch (estado)
		{
		case menu:
			Menu::chequearInputMenu();
			break;
		case juego:
			Gameplay::chequearInputGP();
			break;
		case gameover:
			Gameover::chequearInputGO();
			break;
		}
	}

	void actualizarJuego()
	{
		switch (estado)
		{
		case juego:
			if (estado != estadoA)
			{
				Gameplay::iniciarComponentesGP();
			}
			Gameplay::actualizarGP();
			break;
		}
	}

	void cambiarEstado()
	{
		if (estado != estadoA)
		{
			estadoA = estado;
			switch (estado)
			{
			case menu:
				SetExitKey(KEY_ESCAPE);
				break;
			default:
				SetExitKey(0);
				break;
			}
		}
	}

	void dibujarJuego()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		switch (estado)
		{
		case menu:
			Menu::dibujarMenu();
			break;
		case juego:
			Gameplay::dibujarGameplay();
			break;
		}
		EndDrawing();
	}

	void ejecutarJuego()
	{
		inicializarJuego();
		while (!WindowShouldClose())
		{
			cambiarEstado();
			//input
			chequearInput();
			//actualizacion
			actualizarJuego();
			//dibujo
			dibujarJuego();
		}
		finalizarJuego();
	}

	void inicializarJuego()
	{
		//init game
		InitWindow(screenWidth, screenHeight, "Asteroids");
		SetTargetFPS(60);
		Menu::inicializarMenu();
	}

	void finalizarJuego()
	{
		//close game
		Menu::desinicializarMenu();
		CloseWindow();
	}
}