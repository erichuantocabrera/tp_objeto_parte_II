import localidades.*//por la casa de Hari

class UserException inherits Exception {} 

class Usuario{
	var viajesQueRealizo 
    var property dineroQueCuenta 
    var siguiendo 
    var localidadDeOrigen 
    var property nombreDeUsuario
    var kilometrosRecorridos
    
    constructor (_viajesQueRealizo,_dineroQueCuenta,_siguiendo,_localidadDeOrigen,_nombreDeUsuario,_kilometrosRecorridos){
        viajesQueRealizo =_viajesQueRealizo 
    	dineroQueCuenta =_dineroQueCuenta 
    	siguiendo = _siguiendo 
    	localidadDeOrigen = _localidadDeOrigen
   		nombreDeUsuario	= _nombreDeUsuario
   		kilometrosRecorridos = _kilometrosRecorridos		}
   		
   	method puedeViajar(unViaje) = dineroQueCuenta >=  unViaje.calcularPrecioViaje(localidadDeOrigen)
	method realizarViaje(unViaje){
		if(self.puedeViajar(unViaje)){
			viajesQueRealizo.add(unViaje)
			dineroQueCuenta = dineroQueCuenta - unViaje.calcularPrecioViaje(localidadDeOrigen)
			kilometrosRecorridos = kilometrosRecorridos + unViaje.distanciaARecorrer(localidadDeOrigen)
			localidadDeOrigen = unViaje.destino()		}
		else {
			throw new UserException(message = "viaje demasiado caro eliga otro porfavor")}	}
 	method obtenerKilometros() = kilometrosRecorridos
 	method agregarUsuario(usuario) {siguiendo.add(usuario) }
	method seguirUsuario(usuario) {
		self.agregarUsuario(usuario)
		usuario.agregarUsuario(self) }  	
		
	
	method cantidadDeViajes() = viajesQueRealizo.size()//agregado para una accion del test
   	
}

const pabloHari = new Usuario([],1500,[],casaDeHari,"PHari",0)// agregado_casaDeHari_para_su_correcta_inicializacion.


