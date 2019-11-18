import viajes.*// por el const unViaje 
import barrileteCosmico.*// por la referencia barrileteCosmico

class UserExceptionEstoyPobre inherits Exception {} 

class Usuario{
	var viajesQueRealizo = []
    var property dineroQueCuenta 
    var siguiendo 
    var property localidadDeOrigen 
    var property nombreDeUsuario
    var perfil // ==========  verificar si es debido que sea una variable ========== 
   	
	constructor (dinero,seguidores,origen,usuario,unPerfil){
        dineroQueCuenta = dinero
    	siguiendo = seguidores 
    	localidadDeOrigen = origen
   		nombreDeUsuario	= usuario
   		perfil = unPerfil }
   		
   	method realizarViaje(unDestino) {
   		const unViaje = barrileteCosmico.armaViaje(self,unDestino)
		if(self.puedeViajar(unViaje))  {
			viajesQueRealizo.add(unViaje)
			dineroQueCuenta = dineroQueCuenta - unViaje.calcularPrecioViaje()
			localidadDeOrigen = unViaje.destino()  }
		else  {
			throw new UserExceptionEstoyPobre(message = "viaje demasiado caro eliga otro porfavor")  } }
 	method obtenerKilometros() = viajesQueRealizo.sum({ viaje => viaje.distanciaARecorrer() })
 	method seguirUsuario(usuario) { self.agregarUsuario(usuario)
									usuario.agregarUsuario(self) }  	
	method puedeViajar(unViaje) = dineroQueCuenta >= unViaje.calcularPrecioViaje()	
	method agregarUsuario(usuario) { siguiendo.add(usuario) }
	method cantidadDeViajes() = viajesQueRealizo.size()//agregado para una accion del test
	method cambiarPerfilA(nuevoPerfil) { perfil = nuevoPerfil }
	method perfil() = perfil
   	
   	
   	method elegirTransporte(transportes,destino){
		return perfil.transporte(transportes,localidadDeOrigen.distanciaHasta(destino),dineroQueCuenta)  }

}


object empresarial {
	
	method transporte(transportes,distancia,dineroCuenta) = transportes.min({ transporte => transporte.tiempo() })

}

object estudiantil {

	method transporte(transportes,distancia,dineroCuenta) = (self.quitarTransportesCaros(transportes,distancia,dineroCuenta)).min({ transport => transport.tiempo() })
	method quitarTransportesCaros(transportes,distancia,dinero) = transportes.filter({ transporte => transporte.costoPorDistancia(distancia) < dinero })
}

object familiar {
	
	method transporte(transportes,distancia,dineroCuenta) = transportes.anyOne()

}