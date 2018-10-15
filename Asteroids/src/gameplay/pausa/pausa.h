#ifndef PAUSA_H
#define PAUSA_H

namespace Juego
{
	namespace Gameplay
	{
		extern bool pausa;

		void iniciarComponentesPausa();
		void desinicializarPausa();
		void cambiarPausa();
		void chequearInputPausa();
		void dibujarPausa();
	}
}
#endif
