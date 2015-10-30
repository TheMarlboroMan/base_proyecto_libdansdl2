#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_intro.h"
#include "../class/controladores/controlador_ejemplo.h"

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	//Declaraciones de herramientas externas.
	Director_estados DI;

	DLibV::Fuente_TTF f("data/fuentes/sample.ttf", 10);


	const int id_idioma=0;
	Localizador loc("data/localizacion/textos", id_idioma);
	
	/** También podemos ser más explícitos para declarar el localizador.
	* Localizador loc("data/localizacion/textos");
	* loc.inicializar(id_idioma);	
	*/

	//Controladores e interfaces.
	Controlador_intro C_I(DI, loc, f);
	Controlador_ejemplo C_E(DI);

	Interface_controlador * IC=&C_I;

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
			switch(DI.acc_estado_actual())
			{
				case Director_estados::t_estados::INTRO: break;
				case Director_estados::t_estados::EJEMPLO: break;
			}

			switch(DI.acc_estado_deseado())
			{
				case Director_estados::t_estados::INTRO: IC=&C_I; break;
				case Director_estados::t_estados::EJEMPLO: IC=&C_E; break;
			}

			DI.confirmar_cambio_estado();
		}
	};
}
