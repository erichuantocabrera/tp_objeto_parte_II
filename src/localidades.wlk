import localidades.*

class Playa inherits Localidad{
//nunca es destino es peligroso

override method esDestinoPeligroso()=false

//es destino destacado si su precio es mayor a 2000
method esDestinoDestacado()= self.esImportante()
} 

class Montania inherits Localidad{
var property altura

	constructor(unPrecio,equipaje,unNombre,unKilometro,alturaDeLaMoontania) = super(unPrecio,equipaje,unNombre,unKilometro) { 
		altura = alturaDeLaMoontania }
//es peligrosa si su altura es mayor a 5000 y mantiene vacuna
override method esDestinoPeligroso()= super() && altura > 5000

//las montañas siempre son destinos destacados
method esDestinoDestacado()=true

}

class CiudadHistorica inherits Localidad{
var property cantidadMuseos
	constructor(unPrecio,equipaje,unNombre,unKilometro,museos) = super(unPrecio,equipaje,unNombre,unKilometro) {
		cantidadMuseos = museos }
//no es peligrosa siempre que se lleve el seguro de asistencia al viajero
override method esDestinoPeligroso()= self.contieneEquipaje("seguro de asistencia al viajero")
//es destino destacado si su precio es mayor a 2000 y tiene al menos 3 museos
method esDestinoDestacado()= self.esImportante() && self.tieneAlMenosTresMuseos()

method tieneAlMenosTresMuseos()= cantidadMuseos >= 3


}

