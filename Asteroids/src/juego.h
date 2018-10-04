#ifndef JUEGO_H
#define JUEGO_H
namespace Juego
{
	enum Estado
	{
		menu,
		juego,
		gameover
	};
	extern Estado estado;
	extern Estado estadoA;
	extern int screenWidth;
	extern int screenHeight;
	void ejecutarJuego();
	int randomizarColor();
}
#endif // !JUEGO_H

