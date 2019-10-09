import transportes.*

class Localidad {
	var precio
	var equipajes
	const property nombre
	const property kilometroDeUbicacion  
	
	constructor(_precio,_equipajes,_nombre,_kilometro) {
		precio = _precio
		equipajes = _equipajes
		nombre = _nombre
		kilometroDeUbicacion = _kilometro	  }
	
	method darDescuento(descuento){ 
		precio = precio * (1 - (descuento/100))
		equipajes.add("Certificado de descuento")}
	method esDestinoPeligroso() = equipajes.any({equipaje => equipaje.contains('Vacuna')})
	method contieneEquipaje(unaCosa) = equipajes.contains(unaCosa) 
	method esImportante() = precio > 2000
	method distanciaHasta(destino) = (kilometroDeUbicacion - destino.kilometroDeUbicacion()).abs()
	method precio(destino,transporte) = precio + (self.distanciaHasta(destino) * transporte.costoPorKilometro())

}

