#include "controlador_intro.h"
#include "../app/recursos.h"

Controlador_intro::Controlador_intro(Director_estados &DI, const Localizador& loc, const DLibV::Fuente_TTF& fuente)
	:Controlador_base(DI),
	loc(loc),
	texto_actual(uno),
	camara(0, 0, 400, 400),
	rep_txt(DLibV::Gestor_superficies::obtener(App::Recursos_graficos::RS_FUENTE_BASE), loc.obtener(texto_actual)),
	rep_ttf(fuente, 255, 255, 255, 255, loc.obtener(texto_actual))
	//,rep_tiles(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RT_TILES))
{
	rep_txt.establecer_posicion(16, 400);
	rep_ttf.establecer_posicion(16, 300);

//	rep_tiles.establecer_posicion(0, 128, 64, 64);
//	rep_tiles.establecer_recorte(32, 0, 32, 32);
//	rep_tiles.establecer_pincel(SDL_Rect{8, 8, 16, 16});

	rep_txt.hacer_estatica();
	rep_ttf.hacer_estatica();

	//TODO: En caso de excepción estamos tirando dentro de un constructor.
	escena.mapear_textura("sprites", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RT_SPRITES));
	escena.mapear_textura("tiles", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RT_TILES));
	escena.mapear_superficie("fuente", DLibV::Gestor_superficies::obtener(App::Recursos_graficos::RS_FUENTE_BASE));
	escena.mapear_fuente("fuente", &fuente);
	escena.parsear("data/recursos/escena.dat", "escena_prueba");
}

Controlador_intro::~Controlador_intro()
{

}

void Controlador_intro::preloop(Input_base& input, float delta)
{

}

void Controlador_intro::postloop(Input_base& input, float delta)
{

}

void Controlador_intro::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else
	{
		if(input.es_input_down(Input::I_ENTER))
		{
			++texto_actual;
			if(texto_actual==fin) texto_actual=uno;

			rep_txt.asignar(loc.obtener(texto_actual));
			rep_ttf.asignar(loc.obtener(texto_actual));
		}
		else if(input.es_input_down(Input::I_ESPACIO))
		{
			solicitar_cambio_estado(Director_estados::t_estados::EJEMPLO);
		}

		if(input.es_input_pulsado(Input::I_IZQUIERDA)) camara.movimiento_relativo(-1, 0);
		else if(input.es_input_pulsado(Input::I_DERECHA)) camara.movimiento_relativo(1, 0);

		if(input.es_input_pulsado(Input::I_ARRIBA)) camara.movimiento_relativo(0, -1);
		else if(input.es_input_pulsado(Input::I_ABAJO)) camara.movimiento_relativo(0, 1);
	}
}

void Controlador_intro::dibujar(DLibV::Pantalla& pantalla)
{
//	escena.obtener_por_id("mi_caja")->establecer_alpha(64);
	escena.volcar(pantalla, camara);
	rep_txt.volcar(pantalla);
	rep_ttf.volcar(pantalla);
//	rep_tiles.volcar(pantalla, camara);
}

