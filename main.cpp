#include <iostream>

using namespace std;

enum Direccion {Norte, Sur, Este, Oeste};

class LugarDelMapa
{
    public:
        virtual void Entrar()=0;
};

class Habitacion : public LugarDelMapa
{
    private:
        LugarDelMapa*    _lados[4];
        int                _numeroHabitacion;

    public:
        Habitacion(int numHabitacion){}
        LugarDelMapa* ObtenerLado(Direccion) const{}
        void EstablecerLado(Direccion, LugarDelMapa*){}
        virtual void Entrar(){}
};

class Pared : public LugarDelMapa
{
    public:
        Pared(){}
        virtual void Entrar(){}

};

class Puerta : public LugarDelMapa
{
    private:
        Habitacion* _habitacion1;
        Habitacion* _habitacion2;
        bool        _estaAbierta;

    public:
        Puerta(Habitacion* =0, Habitacion* =0){}
        virtual void Entrar(){}
        Habitacion* OtroLadoDe(Habitacion*){}
};

class Laberinto
{
    private:
        //...

    public:
        Laberinto(){}
        void AnadirHabitacion(Habitacion*){}
        //Hago esto nada más para que devuelva algo!
        Habitacion* NumeroDeHabitacion(int) const{return NULL;}
};

/*
ConstructorLaberinto no crea el laberinto en sí; su principal propósito es simplemetne definir una interfaz
para crear laberintos. Define implementaciones vacías más que nada por comodiad. Son las subclases
de ConstructorLaberinto las qe hacen el trabajo real.
*/
class ConstructorLaberinto
{
    protected:
        ConstructorLaberinto(){}

    public:
        virtual void ConstruirLaberinto(){}
        virtual void ConstruirHabitacion(int habitacion){}
        virtual void ConstruirPuerta(int habitacionDesde, int habitacionHasta){}
        virtual Laberinto* ObtenerLaberinto(){return 0;}
};

/*
La subclase ConstructorLaberintoEstandar es una implementación que construye laberintos simples. Sabe
qué laberinto está siendo creado gracias a la variable _laberintoActual.
*/
class ConstructorLaberintoEstandar : public ConstructorLaberinto
{
    private:
        //Hago esto nada más para que devuelva algo!
        Direccion ParedNormal(Habitacion*, Habitacion*){return Este;}
        Laberinto* _laberintoActual;

    public:
        ConstructorLaberintoEstandar(){_laberintoActual = 0;cout<<"Uso el ConstructorLaberintoEstandar\n";}

        virtual void ConstruirLaberinto(){_laberintoActual = new Laberinto;}
        virtual void ConstruirHabitacion(int);
        virtual void ConstruirPuerta(int, int);

        virtual Laberinto* ObtenerLaberinto(){return _laberintoActual;}
};

void ConstructorLaberintoEstandar::ConstruirHabitacion(int n)
{
    if(!_laberintoActual->NumeroDeHabitacion(n))
    {
        Habitacion* habitacion = new Habitacion(n);
        _laberintoActual->AnadirHabitacion(habitacion);

        habitacion->EstablecerLado(Norte,new Pared);
        habitacion->EstablecerLado(Sur,new Pared);
        habitacion->EstablecerLado(Este,new Pared);
        habitacion->EstablecerLado(Oeste,new Pared);
    }
}

void ConstructorLaberintoEstandar::ConstruirPuerta(int n1, int n2)
{
    Habitacion* h1 = _laberintoActual->NumeroDeHabitacion(n1);
    Habitacion* h2 = _laberintoActual->NumeroDeHabitacion(n2);
    Puerta* p = new Puerta(h1,h2);

    h1->EstablecerLado(ParedNormal(h1,h2),p);
    h2->EstablecerLado(ParedNormal(h1,h2),p);
}

class JuegoDelLaberinto
{
    public:
        Laberinto* CrearLaberinto(ConstructorLaberinto& constructor);
};

Laberinto* JuegoDelLaberinto::CrearLaberinto(ConstructorLaberinto &constructor)
{
    constructor.ConstruirLaberinto();

    constructor.ConstruirHabitacion(1);
    constructor.ConstruirHabitacion(2);
    constructor.ConstruirPuerta(1,2);

    return constructor.ObtenerLaberinto();
}

void main()
{
    Laberinto* laberinto;
    JuegoDelLaberinto juego;
    ConstructorLaberintoEstandar constructor;

    juego.CrearLaberinto(constructor);
    laberinto = constructor.ObtenerLaberinto();
    cin.get();
}
