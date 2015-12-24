#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_intro.h"
#include "../class/controladores/controlador_ejemplo.h"

#include <class/dnot_parser.h>
#include <source/string_utilidades.h>

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	//Declaraciones de herramientas externas.

	//Así declaramos una fuente ttf externa...
	DLibV::Fuente_TTF f("data/fuentes/Akashi.ttf", 16);

	//Y así podemos usar el localizador.
	const int id_idioma=0;
	Localizador loc("data/localizacion/textos", id_idioma);
	
	/** También podemos ser más explícitos para declarar el localizador.
	* Localizador loc("data/localizacion/textos");
	* loc.inicializar(id_idioma);	
	*/

	//Un parser de Dnot, que es como JSON, pero en chungo... Vamos a 
	//ver cómo se inicializa y cómo se usa... Un fallo en uso dará como
	//resultado una excepción runtime_error. Por lo demás, es bastante
	//potente (no sé si será lento o no... Ahora mismo no me importa).
	//Algunas de las features...

	const auto tok=Herramientas_proyecto::parsear_dnot("data/recursos/dnot_data.dat");
	auto& p=kernel.acc_pantalla();

	//Autoconversión a string...	
	p.establecer_titulo(tok["prueba_datos"]["nombre"]);

	//Y autoconversión a enteros...
	int w=tok["prueba_datos"]["config_video"]["medidas"][0], 
		h=tok["prueba_datos"]["config_video"]["medidas"][1];

	p.inicializar(w, h); //p.inicializar(w*2, h*2) Hace la pantalla más grande pero mantiene el aspecto :D!.
	p.establecer_medidas_logicas(w, h);
	
	//Puede leer cadenas, enteros, floats y bools. Aún no tenemos los
	//operadores de comparación con const_chars, bools, enteros, floats y
	//strings por lo cual no podemos hacer las comparaciones directamente
	//sin guardar antes el valor o poner un cast.
	std::string tks=tok["string_prueba"];
	bool tkb=tok["bool_prueba"];
	int tki=tok["int_prueba"];
	float tkf=tok["float_prueba"];

	if(tks!="Hola" || tkb || tki!=12 || tkf!=1.0f )
	{
		throw std::runtime_error("Fichero de datos corrupto");
	}

	//Hay overload de ostreams... 
	std::cout<<tok["prueba_datos"]["complejo"]["valor_texto"]<<std::endl;

	//Listas mezclando tipos.
	std::cout<<tok["prueba_datos"]["complejo"]["coleccion"][0]<<" -> "<<
		tok["prueba_datos"]["complejo"]["coleccion"][0]["val"]<<", "<<
		tok["prueba_datos"]["complejo"]["coleccion"][1]["val"]<<", "<<
		tok["prueba_datos"]["complejo"]["coleccion"][2]<<std::endl;

	//No creo que pueda declarar una forma de que se entienda que el
	//valor es un string...
	//std::string cosa("Hola... ");
	//cosa+=tok["prueba_datos"]["complejo"]["coleccion"][3];
	//std::cout<<cosa<<std::endl;

	//Pero podemos hacer esto...
	std::string cosa("Hola... ");
	cosa+=tok["prueba_datos"]["complejo"]["coleccion"][3].acc_string();
	std::cout<<cosa<<std::endl;	

	//Funciones libres para abrir un fichero de tipo "configuración" 
	//y convertirlo en un mapa de claves y valores, que es algo que
	//hacemos bastante a menudo...

	auto mapa_config=Herramientas_proyecto::generar_mapa_pares("data/config/config_alt.dat", ':', '#');
	std::cout<<"Mapa configuración con "<<mapa_config.size()<<" entradas... Para la clave clave1 = "<<mapa_config["clave1"]<<std::endl;

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
