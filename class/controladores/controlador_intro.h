#ifndef CONTROLADOR_INTRO
#define CONTROLADOR_INTRO

#include "controlador_base.h"
#include "../framework/derivada/localizador.h"
#include <string>
#include <video/representacion/representacion_grafica/representacion_ttf/representacion_ttf.h>
#include <compositor_vista.h>

class Controlador_intro:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
	
	Controlador_intro(Director_estados &DI, const Localizador& loc, const DLibV::Fuente_TTF& fuente);
	~Controlador_intro();

	virtual void preloop(Input_base& input, float delta);
	virtual void postloop(Input_base& input, float delta);
	virtual void loop(Input_base& input, float delta);
	virtual void dibujar(DLibV::Pantalla& pantalla);

	//////////////
	//Propiedades
	private:

	enum textos{uno=1, dos=2, tres=3, cuatro=4, fin};
	const Localizador&				loc;
	Herramientas_proyecto::Compositor_vista		escena;

	int						texto_actual;
	DLibV::Representacion_texto_auto	 	rep_txt;
	DLibV::Representacion_TTF			rep_ttf;

	///////////////
	//Métodos internos.


};

#endif
