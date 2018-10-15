#ifndef ASTEROIDES_H
#define ASTEROIDES_H

namespace Juego
{
	namespace Gameplay
	{
		extern const int cantAsteroidesG;
		extern const int cantAsteroidesM;
		extern const int cantAsteroidesP;

		void iniciarAsteroides();
		void desinicializarAsteroides();
		void moverAsteroides();
		void chequearColisionConAsteroide();
		void dibujarAsteroides();
	}
}

#endif // !ASTEROIDES_
