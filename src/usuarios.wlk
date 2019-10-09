import viajes.*// por el const unViaje 
import barrileteCosmico.*// por la referencia barrileteCosmico

class UserExceptionEstoyPobre inherits Exception {} 

class Usuario{
	var viajesQueRealizo = []// todos los usuarios deben empezar con 0 viajes
    var property dineroQueCuenta 
    var siguiendo 
    var property localidadDeOrigen 
    var property nombreDeUsuario
    //var kilometrosRecorridos// es algo redundante se puede realizar un metodo
   	
	constructor (dinero,seguidores,origen,usuario){
        dineroQueCuenta =dinero
    	siguiendo = seguidores 
    	localidadDeOrigen = origen
   		nombreDeUsuario	= usuario }
   		
   	method puedeViajar(unViaje) = dineroQueCuenta >=  unViaje.calcularPrecioViaje()
	method realizarViaje(unDestino) {
		const unViaje = barrileteCosmico.armaViaje(self,unDestino)
		if(self.puedeViajar(unViaje)){
			viajesQueRealizo.add(unViaje)
			dineroQueCuenta = dineroQueCuenta - unViaje.calcularPrecioViaje()
			//kilometrosRecorridos += kilometrosRecorridos + unViaje.distanciaARecorrer(localidadDeOrigen)
            // realizar un metodo que calcule el recorrido de viajes usando lista de viajes que realiza
			localidadDeOrigen = unViaje.destino()		}
		else {
			throw new UserExceptionEstoyPobre(message = "viaje demasiado caro eliga otro porfavor")
		}
	}
 	//method obtenerKilometros() = kilometrosRecorridos
 	method agregarUsuario(usuario) {siguiendo.add(usuario) }
	method seguirUsuario(usuario) {
		self.agregarUsuario(usuario)
		usuario.agregarUsuario(self) }  	
		
	
	method cantidadDeViajes() = viajesQueRealizo.size()//agregado para una accion del test
   	
}



