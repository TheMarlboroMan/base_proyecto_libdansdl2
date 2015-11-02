#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_intro.h"
#include "../class/controladores/controlador_ejemplo.h"

#include <dnot_parser.h>

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	//Declaraciones de herramientas externas.

	//Así declaramos una fuente ttf externa...
	DLibV::Fuente_TTF f("data/fuentes/sample.ttf", 16);

	//Y así podemos usar el localizador.
	const int id_idioma=0;
	Localizador loc("data/localizacion/textos", id_idioma);
	
	/** También podemos ser más explícitos para declarar el localizador.
	* Localizador loc("data/localizacion/textos");
	* loc.inicializar(id_idioma);	
	*/

	//Un parser de Dnot, que es como JSON, pero en chungo... Vamos a 
	//ver cómo se inicializa y cómo se usa... Un fallo en uso dará como
	//resultado una excepción runtime_error.

	const auto tok=Herramientas_proyecto::parsear_dnot("data/recursos/dnot_data.dat");
	auto& p=kernel.acc_pantalla();

	//Autoconversión a string...	
	p.establecer_titulo(tok["prueba_datos"]["nombre"]);

	//Y autoconversión a enteros!.
	int w=tok["prueba_datos"]["config_video"]["medidas"][0], 
		h=tok["prueba_datos"]["config_video"]["medidas"][1];

	p.inicializar(w, h);
	p.establecer_medidas_logicas(w, h);
	
	//Puede leer cadenas, enteros, floats y bools. Aún no
	//podemos hacar la comparación directamente sin hacer cast.
	std::string tks=tok["string_prueba"];
	bool tkb=tok["bool_prueba"];
	int tki=tok["int_prueba"];
	float tkf=tok["float_prueba"];

	if(tks!="Hola" || tkb || tki!=12 || tkf!=1.0f )
	{
		throw std::runtime_error("Fichero de datos corrupto");
	}

	//Controladores e interfaces.
	Director_estados DI;
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
