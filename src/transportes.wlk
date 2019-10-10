class Transporte {
	var tiempo 
	var costoPorKilometro
	constructor(unTiempo,unCosto) {
		tiempo = unTiempo
		costoPorKilometro = unCosto	}

	method costoPorDistancia(distancia) = distancia * costoPorKilometro
}

