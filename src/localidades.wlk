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
	method esDestinoPeligroso() = equipajes.any({ equipaje => equipaje.contains('Vacuna') })
	method contieneEquipaje(unaCosa) = equipajes.contains(unaCosa) 
	method esImportante() = precio > 2000
	method distanciaHasta(localidad) = (kilometroDeUbicacion - localidad.kilometroDeUbicacion()).abs()
	method precio() = precio
}

class Playa inherits Localidad {
	override method esDestinoPeligroso() = false
}

class Montania inherits Localidad {
	var alturaDeMontania
	
	constructor(unPrecio,equipaje,unNombre,unKilometro,alturaDeLaMoontania) = super(unPrecio,equipaje,unNombre,unKilometro) { 
		alturaDeMontania = alturaDeLaMoontania }
		
	override method esDestinoPeligroso() = super() && (self.siEsMontaniaAlta())
	method siEsMontaniaAlta() = alturaDeMontania > 5000
	override method esImportante() = true
}

class CiudadHistorica inherits Localidad {
	var cantidadDeMuseos
	
	constructor(unPrecio,equipaje,unNombre,unKilometro,museos) = super(unPrecio,equipaje,unNombre,unKilometro) {
		cantidadDeMuseos = museos }
	
	override method esDestinoPeligroso() = equipajes.any({ equipaje => equipaje.contains("seguro de asistencia") })//============    verificar este    ==============
	override method esImportante() = super() && self.tieneMuchosMuseos()
	method tieneMuchosMuseos() = cantidadDeMuseos > 3
}

