class Personaje {
	//var energia pero en javaSript no va;
	constructor(unaEnergia) {
		this.energia = unaEnergia;
	}

	felicidad() {}
	
	rebeldia() { 
		return 1 / this.felicidad(); }
	
	consecuenciasDeConocerEscenario(escenario) {}
	
	conocer(escenario) {
		this.energia -= escenario.fama();
		this.consecuenciasDeConocerEscenario(escenario);
		escenario.aumentarVisitas();
	}
	/*
	esRebelde() { return self.rebeldia() > 10 }
	
	interactuarConMuchos(personajes) {	personajes.foreach(personaje => self.interactuar(personaje)) }

	interactuar(personaje) {  energia /=2 }
	*/
}

class Anfitrion extends Personaje {
	//var valocidadProcesamiento;
	//var recuerdos;
	constructor(unaEnergia,unaVelocidadProcesamiento,unosRecuerdos) {
		super(unaEnergia);
		this.velocidadProcesamiento = unaVelocidadProcesamiento;
		this.recuerdos = unosRecuerdos;
	}

	felicidad() { 
		return this.energia / this.velocidadProcesamiento; }

	consecuenciasDeConocerEscenario(escenario) {
		this.recuerdos.push(new Recuerdo("Conoci un escenario", escenario)); }

}

class Huesped extends Personaje {
	//var minutosRestantes
	//var amigos
	constructor(unaEnergia,tiempos,mejoresAmigos) {
		super(unaEnergia);
		this.minutosRestantes = tiempos;
		this.amigos = mejoresAmigos;
	}

	felicidad() { 
		return this.minutosRestantes * this.felicidadAmigos();  }

	felicidadAmigos() {
		return this.amigos.map(function(amigo) {return amigo.felicidad()}).reduce(function(anterior,actual) {return anterior + actual});  }

	consecuenciasDeConocerEscenario(escenario) { 
		this.minutosRestantes -= 10;  }

}


class Recuerdo {
	//var descripcion;
	//var escenario;
	
	constructor(unaDescripcion, unEscenario) {
		this.descripcion = unaDescripcion;
		this.escenario = unEscenario;
	}

	emotividad() {
		return this.descripcion.length * this.escenario.fama();  }

}

class Escenario {
	//var property nombre
	//var property categoria
	constructor(unNombre, unaCategoria) {
		this.nombre = unNombre;
		this.categoria = unaCategoria;
	}
	
	fama() {
		return 100 + this.categoria.extra();  }

	aumentarVisitas() {
		this.categoria.aumentarVisitas();  }

	evolucionar() {
		this.categoria.evolucionar(this); }

}


class BajoCoste {
	//var property zona
	constructor(unaZona) {
		this.zona = unaZona;  }

	extra() {
	 	return this.zona.length;  }

	aumentarVisitas() {}

	evolucionar(escenario) {
		escenario.categoria = new Estandar();  }

}


class Estandar {
   
   extra() { 
		return 10;  }

   aumentarVisitas() {}

   evolucionar(escenario) {
		escenario.categoria = new DeLujo(50);/*DECISION MIA LA DE 50*/  }
	
}


class DeLujo {
	//var property visitas
	constructor(unasVisitas) {
		this.visitas = unasVisitas;  }

	extra() { 
		return this.visitas;  }

	aumentarVisitas() { 
		this.visitas++; }

	evolucionar(escenario) {
		return console.log("esta categoria no puede evolucionar");  }

}

/*===========            PRUEBAS PARTE 1          =====================================================================================*/


/* cosas nencesarias para agregarle un recuerdo a dolores*/
const cafeteria = new Escenario( "cafe de mou ",new BajoCoste("achachicala") );
const amor = new Recuerdo("el dia que conoci el amor de mi vida",cafeteria);/*

/* 
1.) Modelar los personajes
		dolores y william
*/

const dolores = new Anfitrion(90,0.8,[amor]);
const william = new Huesped(70,3600,[dolores]);

console.log(dolores);
console.log(william);

/*
2.) preguntarle a una persona su nivel de felicidad
*/
console.log("la felicidad de dolores es: ");
console.log(dolores.felicidad());
console.log("la felicidad de william es: ");
console.log(william.felicidad());

/*
3.) conocer el nivel de rebeldia de un personaje
*/
console.log("la rebeldia de dolores es: ");
console.log(dolores.rebeldia());
console.log("la rebeldia de william es: ");
console.log(william.rebeldia());
/*
4.) conocer la emotividad de un recuerdo 
*/
console.log("la emotividad del recuerdo amor es: ");
console.log(amor.emotividad());

/*===================        PRUEBAS PARTE 2          ==================================================================================*/
/*
1.) modelar los escanarios
*/
const casa = new Escenario("casa",new BajoCoste("flores"));
const edificio = new Escenario("edificio",new Estandar());
const teatro = new Escenario("teatro",new DeLujo(24));
//console.log(casa);
//console.log(edificio);
//console.log(teatro);
/*
2.) poder conocer el nivel de fama de un escenario
*/
console.log("el nivel de fama de \"casa\", un escenario de bajoCoste es:");
console.log(casa.fama());
console.log("el nivel de fama de \"edificio\", un escenario estandar es:");
console.log(edificio.fama());
console.log("el nivel de fama de \"teatro\", un escenario de lujo es:");
console.log(teatro.fama());
/*
3.) hacer que un persona pueda conocer un escenario
*/
console.log("informacion de dolores y william 2 personajes");
console.log(dolores);
console.log(william);
/*dolores y william conocen un scenario*/
dolores.conocer(teatro);
william.conocer(teatro);
console.log("informacion de dolores y william despues de conocer el escenario");
console.log(dolores);
console.log(william);
console.log("informacion del teatro despues de que dos personas lo conocieron");
console.log(teatro);
console.log("el nivel de fama de \"teatro\", un escenario de lujo es:");
console.log(teatro.fama());
/*
4.) la evolucion de un scenario
*/
console.log("fama de \"casa\" un scenario de bajoCoste");
console.log(casa.fama());
/*el escenario casa se vuelve tan famosa que que pasa de BajoCoste a Estandar*/
casa.evolucionar();
console.log("fama de \"casa\" despues de evolucionar");
console.log(casa.fama());

console.log("fama de \"edificio\" un scenario standard");
console.log(edificio.fama());
/*el escenario casa se vuelve tan famosa que que pasa de BajoCoste a Estandar*/
edificio.evolucionar();
console.log("fama de \"edificio\" despues de evolucionar");
console.log(edificio.fama());

console.log("fama de \"teatro\" un scenario deLujo");
console.log(teatro.fama());
/*el escenario casa se vuelve tan famosa que que pasa de BajoCoste a Estandar*/
teatro.evolucionar();
console.log("fama de \"teatro\" despues de evolucionar");
console.log(teatro.fama());
/* ===========================          PRUEBAS PARTE 3        ======================================================================*/






/*

class Persona {

	constructor(unNombre,unApellido,unaEdad) {
		this.nombre = unNombre;
		this.apellido = unApellido;
		this.edad = unaEdad;
	}

	nombreCompleto() {
		return this.nombre + this.apellido + this.edad;
	}
	cumplirAnio() {
		return this.edad + 1;
	}

	objetivo() {
		return this.nombre + "ser mejor el anio que viene " + this.cumplirAnio();
	}
}

const eric = new Persona("eric","huanto",20);
const jose = new Persona("jose","cabrera",15);
const piter = new Persona("piter","huanto",30);

console.log(eric.cumplirAnio());
console.log(eric.objetivo());

class Lugar {

	constructor(muchosAmigos) {
		this.amigos = muchosAmigos;
	}

	cantidadAmigos() {
		return this.amigos.length;
	}

	aniosEnTotal() {
		//return sumar(this.amigos.map(function(amigo) {return amigo.edad}));
		return this.amigos.map(function(amigo) {return amigo.edad}).reduce(function(anterior,actual) {return anterior + actual} );
		//return sumarEdad(this.amigos);
	}

	dato() {
		return this.amigos[0].edad;
	}

} 


const plaza = new Lugar([eric,jose,piter]);

console.log(plaza.cantidadAmigos());
console.log(plaza.aniosEnTotal());
console.log(plaza.dato());
*/
document.write("<h1> estamos con el tp <br> finalize correctamente js</h1>");