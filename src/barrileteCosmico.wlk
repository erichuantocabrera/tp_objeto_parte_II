import usuarios.*//por pabloHari
import viajes.*//por que se crea un viaje

object barrileteCosmico{
	var property destinos = []//[garlicSea,silverSea,lastToninas,goodAirs]
	var property usuarios = [pabloHari]
	var property mediosDeTransporte = []
	
	method destinosImportantes() = destinos.filter({destino => destino.esImportante()})
	method aplicarDescuentosADestinos(descuento){
		destinos.forEach({destino => destino.darDescuento(descuento)}) }
	method esEmpresaExtrema() = destinos.any({destino => destino.esDestinoPeligroso()})
	method cartaDeDestinos() = destinos.map({destino => destino.nombre()})
	method destinosPeligrosos() = destinos.filter({destino => destino.esDestinoPeligroso() })
	method armarViaje(destino) = new Viaje(destino,mediosDeTransporte.anyOne())
	method realizarViaje(usuario,destino) {
		usuario.realizarViaje(self.armarViaje(destino))		}
	
}
