#ifndef CONTROLADOR_INTRO
#define CONTROLADOR_INTRO

#include "controlador_base.h"
#include "../framework/derivada/localizador.h"
#include <string>

class Controlador_intro:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
	
	Controlador_intro(Director_estados &DI, const Localizador& loc);
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
	int						texto_actual;
	DLibV::Representacion_texto_auto_estatica 	rep_txt;

	///////////////
	//Métodos internos.


};

#endif
