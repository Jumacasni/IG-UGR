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
       glVertex3f(-1.0,0.0,0.0);		
       glVertex3f(1.0,0.0,0.0);		

       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);

       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();     
}

void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo) 
{
	int i;

	if(modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if(modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glBegin(GL_POLYGON);
		for(i=0;i<n;i++)
			glVertex2f(cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
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
   
// nariz

   glLineWidth(1);
   glColor3f(1.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.07,0.2,0.0);			// Lo que mide el triángulo
      glVertex3f(0.07,0.2,0.0);			// Definimos 3 vértices, los 3 del triángulo
      glVertex3f(0.0,0.3,0.0);
   glEnd(); 

// oreja izquierda

   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.12,0.0);			
      glVertex3f(-0.2,0.12,0.0);			
	   glVertex3f(-0.2,0.4,0.0);
		glVertex3f(-0.3,0.4,0.0);
   glEnd(); 

	glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Lo que rellena el perímetro GL_LINE
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.12,0.0);			
      glVertex3f(-0.2,0.12,0.0);			
	   glVertex3f(-0.2,0.4,0.0);
		glVertex3f(-0.3,0.4,0.0);
   glEnd(); 

// oreja derecha

   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(0.3,0.12,0.0);			
      glVertex3f(0.2,0.12,0.0);			
	   glVertex3f(0.2,0.4,0.0);
		glVertex3f(0.3,0.4,0.0);
   glEnd(); 

	glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Lo que rellena el perímetro GL_LINE
   glBegin(GL_POLYGON);
      glVertex3f(0.3,0.12,0.0);			
      glVertex3f(0.2,0.12,0.0);			
	   glVertex3f(0.2,0.4,0.0);
		glVertex3f(0.3,0.4,0.0);
   glEnd(); 

// ojo izquierdo

	glColor3f(0.0,0.0,0.0);
	Circle(0.05,-0.1,0.40,20,GL_FILL);

// ojo derecho

	glColor3f(0.0,0.0,0.0);
	Circle(0.05,0.1,0.40,20,GL_FILL);

// boca

   glLineWidth(1);
   glColor3f(1.0,0.62,0.62);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.1,0.05,0.0);			
      glVertex3f(0.1,0.05,0.0);			
	   glVertex3f(0.1,0.12,0.0);
		glVertex3f(-0.1,0.12,0.0);
   glEnd(); 

	glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Lo que rellena el perímetro GL_LINE
   glBegin(GL_POLYGON);
      glVertex3f(-0.1,0.05,0.0);			
      glVertex3f(0.1,0.05,0.0);			
	   glVertex3f(0.1,0.12,0.0);
		glVertex3f(-0.1,0.12,0.0);
   glEnd(); 

// sombrero

   glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.55,0.0);			
      glVertex3f(0.3,0.55,0.0);			
	   glVertex3f(0.3,0.65,0.0);
		glVertex3f(-0.3,0.65,0.0);
   glEnd(); 

// copa sombrero

   glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.65,0.0);			
      glVertex3f(0.2,0.65,0.0);			
	   glVertex3f(0.2,0.95,0.0);
		glVertex3f(-0.2,0.95,0.0);
   glEnd(); 

// pendiente izquierdo

   glLineWidth(1);
   glColor3f(1.0,0.62,0.89);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.24,0.15,0.0);			
      glVertex3f(-0.26,0.15,0.0);			
	   glVertex3f(-0.26,0.05,0.0);
		glVertex3f(-0.24,0.05,0.0);
   glEnd(); 

	glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(-0.24,0.15,0.0);			
      glVertex3f(-0.26,0.15,0.0);			
	   glVertex3f(-0.26,0.05,0.0);
		glVertex3f(-0.24,0.05,0.0);
   glEnd();

// pendiente derecho

   glLineWidth(1);
   glColor3f(1.0,0.62,0.89);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(0.24,0.15,0.0);			
      glVertex3f(0.26,0.15,0.0);			
	   glVertex3f(0.26,0.05,0.0);
		glVertex3f(0.24,0.05,0.0);
   glEnd(); 

	glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Esto rellena lo de dentro GL_FILL
   glBegin(GL_POLYGON);
      glVertex3f(0.24,0.15,0.0);			
      glVertex3f(0.26,0.15,0.0);			
	   glVertex3f(0.26,0.05,0.0);
		glVertex3f(0.24,0.05,0.0);
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
