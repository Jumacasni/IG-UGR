//**************************************************************************
// Práctica IG usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include <string>

// ----------------------------------------------------------------------
// NECESARIO PARA CARGAR LAS IMÁGENES DE DISCO
#include "./CImg.h"
using namespace cimg_library;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD,TEXTURE} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
  _puntos3D();
void  draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//************************************************************************
// Clase textura
//************************************************************************

class _textura{
public:
  _textura(GLuint textura_id, char const *archivoJPG); // lee una imagen del fichero

  GLuint ident_textura; // entero que asigna OPENGL a la textura
  CImg<unsigned char> imagen; // imagen a leer
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

  _triangulos3D();
void  draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void  draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void  draw_iluminacion_plana();
void  draw_iluminacion_suave();
virtual void draw_textura();

void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void  calcular_normales_caras();
void  calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;
bool b_textura_coord;

GLfloat plano_s[4], plano_t[4];
vector<_vertex2f> textura_coord;
bool modo_text;

_vertex4f ambiente;       //coeficientes ambiente y difuso
_vertex4f difusa;
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 

// material oro
_vertex4f ambiente_oro;       //coeficientes ambiente y difuso
_vertex4f difusa_oro;
_vertex4f especular_oro;           //coeficiente especular
float brillo_oro;                  //exponente del brillo 

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

  _cubo(float tam=0.5);

  void draw_textura();
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _tablero: public _triangulos3D
{
public:

  _tablero(int filas=3, int columnas=3, float tam=2.0, float al=2.0);

  void draw_textura();
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

  _piramide(float tam=0.5, float al=0.75);

  void draw_textura();
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);

void draw_textura();
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
  void draw_textura();

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
  void draw_textura();
  
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
  void draw_textura();

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
  void draw_textura();

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
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

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
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

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
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cilindro tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
void draw_textura();

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
void draw_textura();

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


//************************************************************************
// Clase luz
//************************************************************************

class _luz
{
public:

  float pos_x, pos_y, pos_z, angx, angy, angz;
  int a, b, c;
  GLenum indice_luz;

  _luz(GLenum indice_luz, _vertex4f punto_luz, _vertex4f luz_ambiente, _vertex4f luz_difusa, _vertex4f luz_especular);

  void activar();
  void transformar(GLenum indice_luz, int a, int b, int c, float ang, float x, float y, float z);
  void desactivar();

protected:
  
  _vertex4f punto_luz;
  _vertex4f luz_ambiente;
  _vertex4f luz_difusa;
  _vertex4f luz_especular;
};