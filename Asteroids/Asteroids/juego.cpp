#include "juego.h"
#include "raylib.h"
#include "menu.h"
#include "gameplay.h"

namespace Juego 
{
	int screenWidth = 900;
	int screenHeight = 600;

	Estado estado=menu;
	Estado estadoA=menu;
	static void inicializarJuego();
	void ejecutarJuego();
	static void finalizarJuego();
	static void dibujarJuego();
	static void cambiarEstado();
	static void chequearInput();
	static void actualizarJuego();

	void chequearInput()
	{
		switch (estado)
		{
		case menu:
			Menu::chequearInputMenu();
			break;
		case juego:
			Gameplay::moverNave();
			break;
		}
	}

	void actualizarJuego()
	{
		if (estado == juego)
		{
			if (estado != estadoA)
			{
				Gameplay::iniciarNave();
			}
		}
	}

	void cambiarEstado()
	{
		if (estado != estadoA)
		{
			estadoA = estado;
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
			Gameplay::dibujarNave();
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
	}

	void finalizarJuego()
	{
		//close game
		CloseWindow();
	}
}