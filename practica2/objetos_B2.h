//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


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

  _esfera(float r=1, int lat=6, int lon=6, int tapas=3);
  void  rotacion();

  vector<_vertex3f> perfil; 
  int num;
  int tapas;
};

