#ifndef JUEGO_H
#define JUEGO_H

namespace Juego
{
	enum Estado
	{
		menu,
		juego,
		gameover,
		creditos,
		juegoPausado
	};

	extern Estado estado;
	extern Estado estadoA;
	extern int screenWidth;
	extern int screenHeight;

	void ejecutarJuego();
}

#endif // !JUEGO_H

