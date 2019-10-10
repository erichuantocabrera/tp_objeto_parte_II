import transportes.*

class Localidad {
	var precio
	var equipajes
	const property nombre
	const property kilometroDeUbicacion  
	
	constructor(unPrecio,equipaje,unNombre,unKilometro) {
		precio = unPrecio
		equipajes = equipaje
		nombre = unNombre
		kilometroDeUbicacion = unKilometro	  }
	
	method darDescuento(descuento){ 
		precio = precio * (1 - (descuento/100))
		equipajes.add("Certificado de descuento")}
	method esDestinoPeligroso() = equipajes.any({equipaje => equipaje.contains('Vacuna')})
	method contieneEquipaje(unaCosa) = equipajes.contains(unaCosa) 
	method esImportante() = precio > 2000
	method distanciaHasta(localidad) = (kilometroDeUbicacion - localidad.kilometroDeUbicacion()).abs()
	//method precio(localidad,transporte) = precio + (self.distanciaHasta(localidad) * transporte.costoPorKilometro())
	method precio() = precio
}

