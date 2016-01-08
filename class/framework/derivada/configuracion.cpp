#include "configuracion.h"

const std::string Configuracion::CLAVE_IDIOMA="idioma";
const std::string Configuracion::ID_IDIOMA="0";

Configuracion::Configuracion(): Configuracion_base(obtener_ruta_archivo(), obtener_separador_archivo(), obtener_comentario_archivo())
{
	configurar(CLAVE_IDIOMA, ID_IDIOMA);
}
