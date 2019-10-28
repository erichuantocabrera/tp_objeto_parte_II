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
   		
   	method realizarViaje(unDestino) { const unViaje = barrileteCosmico.armaViaje(self,unDestino)
	if(self.puedeViajar(unViaje))
	 {
		viajesQueRealizo.add(unViaje)
		dineroQueCuenta = dineroQueCuenta - unViaje.calcularPrecioViaje()
		localidadDeOrigen = unViaje.destino()		
	}
	 else  {
	throw new UserExceptionEstoyPobre(message = "viaje demasiado caro eliga otro porfavor") 
         }
	}
 	method obtenerKilometros() = viajesQueRealizo.sum({ viaje => viaje.distanciaARecorrer() })
 	method seguirUsuario(usuario) { self.agregarUsuario(usuario)
									usuario.agregarUsuario(self) }  	
	method puedeViajar(unViaje) = dineroQueCuenta >= unViaje.calcularPrecioViaje()	
	method agregarUsuario(usuario) { siguiendo.add(usuario) }
	method cantidadDeViajes() = viajesQueRealizo.size()//agregado para una accion del test
	method cambiarPerfilA(nuevoPerfil) { perfil = nuevoPerfil }
	method perfil() = perfil
   	
}


object empresarial {
	var transportes = []
	
	method transportes(masTransportes) { transportes = masTransportes } 
	method transporte() = transportes.max({ transporte => transporte.tiempo() })
}

object estudiantil {// verificar el de estudiante ==================
	var transportes = []
	var dinero = 10000 //==== revisar este ========== como le asigno el dinero del usuario???
	
	method transportes(masTransportes) { transportes = masTransportes }
	method transporte() = (   transportes.filter({ transporte => transporte.tiempo() < dinero })  ).min({ transport => transport.tiempo() })
}

object familiar {
	var transportes = []
	
	method transportes(masTransportes) { transportes = masTransportes } 
	method transporte() = transportes.anyOne()
}
