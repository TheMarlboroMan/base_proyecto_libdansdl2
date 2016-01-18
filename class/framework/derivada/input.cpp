#include "input.h"

void Input::configurar()
{
	//El input I_ESCAPE es la tecla SDLK_ESCAPE. Simple.
	configurar_teclado(I_ESCAPE, SDL_SCANCODE_ESCAPE);
	configurar_teclado(I_ESPACIO, SDL_SCANCODE_SPACE);
	configurar_teclado(I_ENTER, SDL_SCANCODE_RETURN);

	configurar_teclado(I_IZQUIERDA, SDL_SCANCODE_LEFT);
	configurar_teclado(I_DERECHA, SDL_SCANCODE_RIGHT);
	configurar_teclado(I_ARRIBA, SDL_SCANCODE_UP);
	configurar_teclado(I_ABAJO, SDL_SCANCODE_DOWN);

	configurar_raton(I_CLICK_I, SDL_BUTTON_LEFT);
	configurar_raton(I_CLICK_I, SDL_BUTTON_RIGHT);
}
