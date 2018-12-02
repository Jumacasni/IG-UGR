#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);		// Color rojo
       glVertex3f(-1.0,0.0,0.0);	// Desde el vértice -1.0, 0.0, 0.0
       glVertex3f(1.0,0.0,0.0);		// Al vértica 1.0, 0.0, 0.0

       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);

       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
 
// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);			// Lo que mide el cuadrado
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Lo que rellena el perímetro GL_LINE
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 
   
// hacer un triángulo

   glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.1,0.0,0.0);			// Lo que mide el triángulo
      glVertex3f(0.1,0.0,0.0);			// Definimos 3 vértices, los 3 del triángulo
      glVertex3f(0.0,0.2,0.0);
   glEnd(); 
}


static void Init( )
{

   glShadeModel( GL_FLAT);		// Todos los polígonos de un solo color
					// GL_SMOOTH para un degradado
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);	// Así el sistema de coordenadas
						// no cambia y la figura no se 
						// deforma
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );	// Trabajar con RGB

   glutInitWindowPosition( 20, 100 );	// x = 20, y = 100
   glutInitWindowSize(500, 500 );	// Tamaño 500x500
   glutCreateWindow("Practica 0 IG");	// Se crea la ventana


   Init();				

   glutReshapeFunc(Reshape);		// Para poder redimensionar la ventana			
   glutDisplayFunc(Display);		// Si la ventana está tapada por otra, 
					// si se pincha encima se vuelve a ver
   glutKeyboardFunc(Keyboard);		// En función de la tecla que se pulse,
					// se hará una cosa u otra
  
   glutMainLoop( );			// Espera a que los eventos vayan 
					// sucediendo

   return 0;
}

