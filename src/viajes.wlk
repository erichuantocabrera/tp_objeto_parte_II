class Viaje{
	var property destino
	var transporte
	constructor (_destino,_transporte){
		destino = _destino
		transporte = _transporte
	}
	method distanciaARecorrer(origen) = destino.distanciaHasta(origen)
	method calcularPrecioViaje(origen) =  destino.precio() + (self.distanciaARecorrer(origen) * transporte.costoPorKilometro())
}

