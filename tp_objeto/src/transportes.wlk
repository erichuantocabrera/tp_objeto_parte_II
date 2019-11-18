class Transporte {
	var tiempo 
	
	constructor(unTiempo) {
		tiempo = unTiempo}

	method costoPorDistancia(distancia) = distancia * self.costoPorKilometro()
	method costoPorKilometro()
	method tiempo() = tiempo
}

class Avion inherits Transporte {
	var turbinas
	
	constructor(unTiempo,unasTurbina) = super(unTiempo) {
		turbinas = unasTurbina	}
		
	override method costoPorKilometro() = turbinas.sum({turbina => turbina.nivelDeImpulso()})
	
	method agregarTurbina(unaTurbina) {turbinas.add(unaTurbina)}
	
}

class Micro inherits Transporte {
	override method costoPorKilometro() = 5000
}

class Tren inherits Transporte {
	
	override method costoPorKilometro() = 0.621*2300// se hizo una conversion de millas a kilometros
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
	
	method nivelDeImpulso() = nivelDeImpulso
}
