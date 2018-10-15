#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace Juego
{
	namespace Gameplay
	{
		enum Bordes
		{
			arriba,
			izquierda,
			derecha,
			abajo
		};

		extern float bordes[4];

		extern bool gano;
		extern bool gameOver;

		void iniciarComponentesGP();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
		void desinicializarGP();
	}
}

#endif // !GAMEPLAY_H

