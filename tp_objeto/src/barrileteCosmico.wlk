import viajes.*//por que se crea un viaje

object barrileteCosmico{
	var property destinos = []
	var property usuarios = []
	var property mediosDeTransporte = []
	
	method destinosImportantes() = destinos.filter({destino => destino.esDestacado()})
	method aplicarDescuentosADestinos(descuento){
		destinos.forEach({destino => destino.darDescuento(descuento)}) }
	method esEmpresaExtrema() = destinos.any({destino => destino.esDestinoPeligroso()})
	method cartaDeDestinos() = destinos.map({destino => destino.nombre()})
	method destinosPeligrosos() = destinos.filter({destino => destino.esDestinoPeligroso() })
	
	method armaViaje(usuario, destino) = new Viaje(usuario.localidadDeOrigen(), destino,  usuario.elegirTransporte(mediosDeTransporte,destino) )
	
}

