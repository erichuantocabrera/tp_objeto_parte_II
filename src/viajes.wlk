class Viaje{
	var origen
	var property destino
	var transporte
	constructor (unOrigen,unDestino,unTransporte){
		origen = unOrigen
		destino = unDestino
		transporte =unTransporte
	}
	method distanciaARecorrer() = origen.distanciaHasta(destino)
	method calcularPrecioViaje() = destino.precio(destino,transporte)
}
