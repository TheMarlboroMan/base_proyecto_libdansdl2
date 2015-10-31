#include "controlador_intro.h"
#include "../app/recursos.h"

Controlador_intro::Controlador_intro(Director_estados &DI, const Localizador& loc, const DLibV::Fuente_TTF& fuente)
	:Controlador_base(DI),
	loc(loc),
	texto_actual(uno),
	rep_txt(DLibV::Gestor_superficies::obtener(Recursos_graficos::RS_FUENTE_BASE), loc.obtener(texto_actual)),
	rep_ttf(fuente, 255, 255, 255, 255, loc.obtener(texto_actual))
{
	rep_txt.establecer_posicion(16, 400);
	rep_ttf.establecer_posicion(16, 300);
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
	}
}

void Controlador_intro::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(128, 128, 128, 255);
	rep_txt.volcar(pantalla);
	rep_ttf.volcar(pantalla);
}
