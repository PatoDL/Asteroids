#ifndef GAMEPLAY_H
#define GAMEPLAY_H
namespace Juego
{
	namespace Gameplay
	{
		struct Nave
		{
			Vector2 posPunta;
			Vector2 posIzq;
			Vector2 posDer;
		};

		void iniciarNave();
		void moverNave();
		void dibujarNave();
	}
}
#endif // !GAMEPLAY_H

