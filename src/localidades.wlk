class Localidad {
	var property precio
	var equipajes
	const property nombre
	const property kilometroUbicacion  
	
	constructor(_precio,_equipajes,_nombre,_kilometro) {
		precio = _precio
		equipajes = _equipajes
		nombre = _nombre
		kilometroUbicacion = _kilometro	  }
	
	method darDescuento(descuento){ 
		precio = precio * (1 - (descuento/100))
		equipajes.add("Certificado de descuento")}
	method esDestinoPeligroso(){return equipajes.any({equipaje => equipaje.take(6) =="Vacuna"})}//modificar este
	method contieneEquipaje(unaCosa) = equipajes.contains(unaCosa) 
	method esImportante() = precio > 2000
	method distanciaHasta(localidad) = absoluto.apply(kilometroUbicacion - localidad.kilometroUbicacion())
	//method precio(unDestino,transporte) = precio + (self.distanciaHasta(unDestino) * transporte.costoPorKilometro())

}

const garlicSea = new Localidad(2500,["Caña de Pescar","Piloto"],"Garlic's Sea",2)
const silverSea = new Localidad(1350,["Protector Solar","Equipo de Buceo"],"Silver's Sea",5)
const lastToninas = new Localidad(3500,["Vacuna Gripal","Vacuna B","Necronomicon"],"Last Toninas",10)
const goodAirs = new Localidad(1500,["Cerveza","Protector Solar"],"Good Airs",20)
const casaDeHari = new Localidad(0,[],"casa",0)// para que pablo tenga un lugar de casa y o me tire error al declararlo

const absoluto = {numero => numero.abs()}

