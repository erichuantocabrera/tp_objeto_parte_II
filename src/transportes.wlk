class Transporte {
	var tiempo 
	constructor(unTiempo) {
		tiempo = unTiempo}

	method costoPorDistancia(distancia) = distancia * self.costoPorKilometro()
	method costoPorKilometro() // ==== verificar este ========
	method tiempo() = tiempo
}

class Avion inherits Transporte {
	var cantidadDeTurbinas 
	var turbina
	
	constructor(unTiempo,unaCantidad,unaTurbina) = super(unTiempo) {
		cantidadDeTurbinas = unaCantidad
		turbina = unaTurbina	}
	
	override method costoPorKilometro() = cantidadDeTurbinas * turbina.nivelDeImpuslo()
}

class Micro inherits Transporte {
	override method costoPorKilometro() = 5000
}

class Tren inherits Transporte {
	var costoPorMilla = 2300 //======== verificar este =============
	
	override method costoPorKilometro() = costoPorMilla * (1/0.62137)
}

class Barco inherits Transporte {
	var probabilidadDeChocarse
	
	constructor(unTiempo,probabilidad) = super(unTiempo) {
		probabilidadDeChocarse = probabilidad	}
	
	override method costoPorKilometro() = 1000 * probabilidadDeChocarse
}

class Turbina {
	var nivelDeImpulso
	
	constructor(impulso) {
		nivelDeImpulso = impulso }
	
	method nivelDeImpulso() = nivelDeImpulso // ==========    verificar este   ===========
}
