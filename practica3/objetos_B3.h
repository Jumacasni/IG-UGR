//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

/*//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil; 
int num;
};*/

//*************************************************************************
// clase objeto cilindro
//*************************************************************************

class _cilindro: public _triangulos3D
{
public:

  // if{
  //    tapas == 1 -> tapa superior
  //    tapas == 2 -> tapa inferior
  //    tapas == 3 -> ambas tapas
  // }
  // else{
  //    no hay tapas
  // }

  _cilindro(float r=1, float h=1, int n=20, int tapas=3);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  int tapas;
};

//*************************************************************************
// clase objeto medio cilindro
//*************************************************************************

class _medio_cilindro: public _triangulos3D
{
public:

  // if{
  //    tapas == 1 -> tapa superior
  //    tapas == 2 -> tapa inferior
  //    tapas == 3 -> ambas tapas
  // }
  // else{
  //    no hay tapas
  // }

  _medio_cilindro(float r=1, float h=1, int n=20, int tapas=3);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  int tapas;
};

//*************************************************************************
// clase objeto cono
//*************************************************************************

class _cono: public _triangulos3D
{
public:

  // tapas = true -> tapa activada
  // tapas = false -> tapa desactivada

  _cono(float r=1.0, float h=1, int n=20, bool tapas=true);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  bool tapas;
};

//************************************************************************
// clase objeto esfera
//************************************************************************

class _esfera: public _triangulos3D
{
public:
  
  // if{
  //    tapas == 1 -> tapa superior
  //    tapas == 2 -> tapa inferior
  //    tapas == 3 -> ambas tapas
  // }
  // else{
  //    no hay tapas
  // }

  _esfera(float r=1, int lat=10, int lon=10, int tapas=3);
  void  rotacion();

  vector<_vertex3f> perfil; 
  int num;
  int tapas;
};

//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_cilindro  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cilindro tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};

//************************************************************************
// objeto articulado: excavadora
//************************************************************************

class _sustentacion: public _triangulos3D
{
public:
       _sustentacion();
       float altura;

void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cilindro  rodamiento;
_cubo base;
};

class _cabina: public _triangulos3D
{
public:
       _cabina();
       float altura;
       float anchura;

void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo base;
};

class _primer_brazo: public _triangulos3D
{
public:
       _primer_brazo();
       float altura;

void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo brazo;
};

class _segundo_brazo: public _triangulos3D
{
public:
       _segundo_brazo();
       float altura;
       float anchura;

void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo brazo;
};

class _cucharon: public _triangulos3D
{
public:
       _cucharon();
       float altura;
       float anchura;

void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_medio_cilindro cucharon;
};

class _excavadora: public _triangulos3D
{
public:
       _excavadora();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_cabina;
float giro_primer_brazo;
float giro_segundo_brazo;
float giro_cucharon;

float giro_primer_brazo_max;
float giro_primer_brazo_min;
float giro_segundo_brazo_max;
float giro_segundo_brazo_min;
float giro_cucharon_max;
float giro_cucharon_min;

protected:
_sustentacion  sustentacion;
_cabina cabina;
_primer_brazo primer_brazo;
_segundo_brazo segundo_brazo;
_cucharon cucharon;
};