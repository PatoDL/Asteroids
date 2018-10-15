#include "juego.h"

#include "raylib.h"
#include "menu/menu.h"
#include "gameplay/gameplay.h"
#include "gameover/gameover.h"
#include "creditos/creditos.h"
#include "gameplay/pausa/pausa.h"

namespace Juego 
{
	int screenWidth = 900;
	int screenHeight = 600;

	Estado estado=menu;
	Estado estadoA=menu;
	static bool enjuego = true;

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
		case juegoPausado:
			Gameplay::chequearInputGP();
			break;
		case gameover:
			Gameover::chequearInputGO();
			break;
		case creditos:
			Creditos::chequearInputCreditos();
			break;
		}
	}

	void actualizarJuego()
	{
		switch (estado)
		{
		case menu:
			if (estado != estadoA)
			{
				Menu::inicializarMenu();
				Creditos::desinicializarCreditos();
				if (estadoA == juego)
				{
					Gameplay::desinicializarGP();
					ShowCursor();
				}
			}
			break;
		case juego:
			if (estado != estadoA)
			{
				if (estadoA != juegoPausado)
				{
					Gameplay::iniciarComponentesGP();
					HideCursor();
				}
				if(estadoA==juegoPausado)
				{
					Gameplay::desinicializarPausa();
				}
				if (estadoA == menu)
				{
					Menu::desinicializarMenu();
				}
				else if (estadoA == gameover)
				{
					Gameover::desinicializarGO();
				}
			}
			Gameplay::actualizarGP();
			break;
		case gameover:
			if (estado!=estadoA)
			{
				Gameover::inicializarGO();
				Gameplay::desinicializarGP();
			}
			ShowCursor();
			break;
		case juegoPausado:
			if (estado != estadoA)
			{
				Gameplay::iniciarComponentesPausa();
			}
			ShowCursor();
			break;
		case creditos:
			if (estado != estadoA)
			{
				Creditos::inicializarCreditos();
				Menu::desinicializarMenu();
			}
			break;
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
		case creditos:
			Creditos::dibujarCreditos();
			break;
		case juego:
			Gameplay::dibujarGameplay();
			break;
		case gameover:
			Gameover::dibujarGO();
			break;
		case juegoPausado:
			Gameplay::dibujarGameplay();
			break;
		}
		EndDrawing();
	}

	void ejecutarJuego()
	{
		inicializarJuego();
		while (enjuego)
		{
			//input
			chequearInput();
			//actualizacion
			actualizarJuego();
			//dibujo
			dibujarJuego();

			if (estado != gameover)
			{
				cambiarEstado();
			}

			//-------------
			if (Menu::salir)
			{
				enjuego=false;
			}
		}
		finalizarJuego();
	}

	void inicializarJuego()
	{
		//init game
		InitWindow(screenWidth, screenHeight, "Asteroids");
		SetExitKey(0);
		Menu::inicializarMenu();
	}

	void finalizarJuego()
	{
		//close game
		Menu::desinicializarMenu();
		CloseWindow();
	}
}