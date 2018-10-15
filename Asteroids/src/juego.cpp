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
	Music musicaJuego;

	static void inicializarJuego();
	static void finalizarJuego();
	static void dibujarJuego();
	static void cambiarEstado();
	static void chequearInput();
	static void actualizarJuego();
	static void dibujarVersion();

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
				if (estadoA == juegoPausado)
				{
					Gameplay::desinicializarGP();
					ResumeMusicStream(musicaJuego);
					ShowCursor();
				}
			}
			UpdateMusicStream(musicaJuego);
			break;
		case juego:
			if (estado != estadoA)
			{
				if (estadoA != juegoPausado)
				{
					Gameplay::iniciarComponentesGP();
					PauseMusicStream(musicaJuego);
					HideCursor();
				}
				if(estadoA==juegoPausado)
				{
					Gameplay::desinicializarPausa();
					HideCursor();
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
				StopMusicStream(musicaJuego);
				estadoA = gameover; //la unica solucion que le encontré al problema
				PlayMusicStream(musicaJuego);
			}
			ShowCursor();
			UpdateMusicStream(musicaJuego);
			break;
		case juegoPausado:
			if (estado != estadoA)
			{
				Gameplay::iniciarComponentesPausa();
			}
			UpdateMusicStream(Gameplay::musicaFondo);
			ShowCursor();
			break;
		case creditos:
			if (estado != estadoA)
			{
				Creditos::inicializarCreditos();
				Menu::desinicializarMenu();
			}
			UpdateMusicStream(musicaJuego);
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

	void dibujarVersion()
	{
		DrawText("v0.8", screenWidth - screenWidth/10, screenHeight/20, screenHeight*screenWidth/27000, WHITE);
	}

	void dibujarJuego()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		switch (estado)
		{
		case menu:
			Menu::dibujarMenu();
			dibujarVersion();
			break;
		case creditos:
			Creditos::dibujarCreditos();
			dibujarVersion();
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
			if (estado != gameover) //unica solucion que le encontré al problema
			{
				cambiarEstado();
			}
			//input
			chequearInput();
			//actualizacion
			actualizarJuego();
			//dibujo
			dibujarJuego();

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
		InitAudioDevice();
		musicaJuego = LoadMusicStream("res/sonidos/titulo.ogg");
		PlayMusicStream(musicaJuego);
		SetExitKey(0);
		Menu::inicializarMenu();
	}

	void finalizarJuego()
	{
		//close game
		Menu::desinicializarMenu();
		UnloadMusicStream(musicaJuego);
		CloseAudioDevice();
		CloseWindow();
	}
}