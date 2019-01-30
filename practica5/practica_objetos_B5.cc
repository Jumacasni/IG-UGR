//**************************************************************************
// Práctica 1
//

//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "objetos_B5.h"

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;

int estadoRaton[3], xc, yc, modo[7], cambio=0;

solido *cilindro1, *cilindro2, *base, *cabina, *primer_brazo, *segundo_brazo, *cucharon;

float altura_sustentacion = 0.07 + 0.3;
float altura_cabina = 0.6;
float anchura_cabina = 0.4;
float altura_primer_brazo = 0.8;
float altura_segundo_brazo = 0.6;
float anchura_segundo_brazo = 0.1;
float altura_cucharon = 0.15;
float anchura_cucharon = 0.1;

float giro_cabina = 0.0;
float giro_primer_brazo = 0.0;
float giro_primer_brazo_max = 30;
float giro_primer_brazo_min = 0;
float giro_segundo_brazo = 0.0;
float giro_segundo_brazo_max = 0;
float giro_segundo_brazo_min = -90;
float giro_cucharon = 0.0;
float giro_cucharon_max = 0.0;
float giro_cucharon_min = -90.0;

int vista_multiple=0;
int Ancho=450, Alto=450;
float factor=1.0;
float anterior_xn;

void pick_color(int x, int y);

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
change_projection();
glViewport(0,0,Ancho,Alto);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glLineWidth(1);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	// Excavadora de la práctica 3

	// Sustentación

  	glPushMatrix();
	glTranslatef(-0.3,0.0,0.0);
	glPushMatrix();
	glRotatef(90.0,1,0,0);
	glScalef(0.15,0.5,0.15);
	draw_solido(cilindro1,0.1,0.1,0.1,1);
  	draw_solido(cilindro1,cilindro1->r,cilindro1->g,cilindro1->b,2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6,0.0,0.0);
	glRotatef(90.0,1,0,0);
	glScalef(0.15,0.5,0.15);
	draw_solido(cilindro2,0.1,0.1,0.1,1);
  	draw_solido(cilindro2,cilindro2->r,cilindro2->g,cilindro2->b,2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.3, 0.0);
	glScalef(1.1, 0.3, 1.1);
	draw_solido(base,0.1,0.1,0.1,1);
  	draw_solido(base,base->r,base->g,base->b,2);
	glPopMatrix();

	glPopMatrix();

	// Cabina
	glRotatef(giro_cabina,0,1,0);
	glTranslatef(0.0,(altura_sustentacion+altura_cabina/2),0.0);
	glPushMatrix();
	glScalef(0.4, 0.6, 0.35);
	draw_solido(cabina,0.1,0.1,0.1,1);
  	draw_solido(cabina,cabina->r,cabina->g,cabina->b,2);
	glPopMatrix();

	// Primer brazo

	glTranslatef(anchura_cabina/2,0.0,0.0);	// eje donde tiene que rotar el brazo
	glRotatef(giro_primer_brazo,0,0,1);
	glTranslatef(anchura_cabina,0.0,0.0); // posición del brazo
	glPushMatrix();
	glScalef(0.8, 0.1, 0.1);
	draw_solido(primer_brazo,0.1,0.1,0.1,1);
  	draw_solido(primer_brazo,primer_brazo->r,primer_brazo->g,primer_brazo->b,2);
	glPopMatrix();

	// Segundo brazo

	glTranslatef(altura_primer_brazo/2,0,0);	// eje donde tiene que rotar el brazo
	glRotatef(giro_segundo_brazo,0,0,1);
	glTranslatef(altura_segundo_brazo/2,0,0); // posición del brazo
	glPushMatrix();
	glScalef(0.6, 0.1, 0.1);
	draw_solido(segundo_brazo,0.1,0.1,0.1,1);
  	draw_solido(segundo_brazo,segundo_brazo->r,segundo_brazo->g,segundo_brazo->b,2);
	glPopMatrix();

	// Cucharón

	glPushMatrix();
	glTranslatef(altura_segundo_brazo/2, 0.0, 0.0); // eje donde tiene que rotar el cucharon
	glRotatef(giro_cucharon,0,0,1);
	glTranslatef(anchura_cucharon,-altura_cucharon/2,0.0); // posición del cucharon
	glRotatef(90.0,1,0,0);
	glScalef(0.15,0.1,0.15);
	draw_solido(cucharon,0.1,0.1,0.1,1);
  	draw_solido(cucharon,cucharon->r,cucharon->g,cucharon->b,2);
	glPopMatrix();
}

//**************************************************************************
// Funcion que dibuja los objetos en el buffer trasero
//***************************************************************************

void draw_objects_seleccion()
{
	// Excavadora de la práctica 3

	// Sustentación
	int inc = 0;
  	glPushMatrix();
	glTranslatef(-0.3,0.0,0.0);

	glPushMatrix();
	glRotatef(90.0,1,0,0);
	glScalef(0.15,0.5,0.15);
  	draw_seleccion_color(cilindro1,100,100,100);
	glPopMatrix();
	inc+=20;

	glPushMatrix();
	glTranslatef(0.6,0.0,0.0);
	glRotatef(90.0,1,0,0);
	glScalef(0.15,0.5,0.15);
  	draw_seleccion_color(cilindro2,100+inc,100+inc,100+inc);
	glPopMatrix();
	inc+=20;

	glPushMatrix();
	glTranslatef(0.3, 0.3, 0.0);
	glScalef(1.1, 0.3, 1.1);
	draw_seleccion_color(base,100+inc,100+inc,100+inc);
	glPopMatrix();
	inc+=20;

	glPopMatrix();

	// Cabina
	glRotatef(giro_cabina,0,1,0);
	glTranslatef(0.0,(altura_sustentacion+altura_cabina/2),0.0);
	glPushMatrix();
	glScalef(0.4, 0.6, 0.35);
	draw_seleccion_color(cabina,100+inc,100+inc,100+inc);
	glPopMatrix();
	inc+=20;

	// Primer brazo

	glTranslatef(anchura_cabina/2,0.0,0.0);	// eje donde tiene que rotar el brazo
	glRotatef(giro_primer_brazo,0,0,1);
	glTranslatef(anchura_cabina,0.0,0.0); // posición del brazo
	glPushMatrix();
	glScalef(0.8, 0.1, 0.1);
	draw_seleccion_color(primer_brazo,100+inc,100+inc,100+inc);
	glPopMatrix();
	inc+=20;

	// Segundo brazo

	glTranslatef(altura_primer_brazo/2,0,0);	// eje donde tiene que rotar el brazo
	glRotatef(giro_segundo_brazo,0,0,1);
	glTranslatef(altura_segundo_brazo/2,0,0); // posición del brazo
	glPushMatrix();
	glScalef(0.6, 0.1, 0.1);
	draw_seleccion_color(segundo_brazo,100+inc,100+inc,100+inc);
	glPopMatrix();
	inc+=20;

	// Cucharón

	glPushMatrix();
	glTranslatef(altura_segundo_brazo/2, 0.0, 0.0); // eje donde tiene que rotar el cucharon
	glRotatef(giro_cucharon,0,0,1);
	glTranslatef(anchura_cucharon,-altura_cucharon/2,0.0); // posición del cucharon
	glRotatef(90.0,1,0,0);
	glScalef(0.15,0.1,0.15);
	draw_seleccion_color(cucharon,100+inc,100+inc,100+inc);
	glPopMatrix();
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

if (vista_multiple==0)
  {
    clear_window();
   change_observer();
   draw_axis();
   draw_objects();

   glDrawBuffer(GL_BACK);
   clear_window();
   change_observer();
   draw_objects_seleccion();
   glDrawBuffer(GL_FRONT);

   glFlush();

  }

else
{
  //vista alzado
  clear_window();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(Observer_distance*-1.0,Observer_distance*1.0,Observer_distance*-1.0,Observer_distance*1.0,-100.0,100.0);
  glViewport(0,0,Ancho,Alto);
  glRotatef(90,1,0,0);
  glScalef(factor,factor,1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  draw_axis();
  draw_objects();
  
  glFlush();
  }
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
Ancho=Ancho1;
Alto=Alto1;
draw_scene();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (Tecla1=='+') 
   {factor*=0.9;
    glutPostRedisplay();}
if (Tecla1=='-') 
   {factor*=1.1;
    glutPostRedisplay();}
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    case GLUT_KEY_F1:vista_multiple=1;break;
    case GLUT_KEY_F2:vista_multiple=0;break;
    case GLUT_KEY_F5:giro_cabina+=5;break;
    case GLUT_KEY_F6:giro_cabina-=5;break;
    case GLUT_KEY_F7:giro_primer_brazo+=1;
                    if (giro_primer_brazo>giro_primer_brazo_max) giro_primer_brazo=giro_primer_brazo_max;
                    break;
    case GLUT_KEY_F8:giro_primer_brazo-=1;
                    if (giro_primer_brazo<giro_primer_brazo_min) giro_primer_brazo=giro_primer_brazo_min;
                    break;break;
    case GLUT_KEY_F9:giro_segundo_brazo+=1;
                    if (giro_segundo_brazo>giro_segundo_brazo_max) giro_segundo_brazo=giro_segundo_brazo_max;
                    break;
    case GLUT_KEY_F10:giro_segundo_brazo-=1;
                    if (giro_segundo_brazo<giro_segundo_brazo_min) giro_segundo_brazo=giro_segundo_brazo_min;
                    break;break;
    case GLUT_KEY_F11:giro_cucharon+=1;
                    if (giro_cucharon>giro_cucharon_max) giro_cucharon=giro_cucharon_max;
                    break;
    case GLUT_KEY_F12:giro_cucharon-=1;
                    if (giro_cucharon<giro_cucharon_min) giro_cucharon=giro_cucharon_min;
                    break;break;
	}
glutPostRedisplay();
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_y;
*y=Observer_angle_x;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=y;
Observer_angle_y=x;
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
      float x0, y0;
      getCamara(&x0,&y0);
      anterior_xn=x0-(x-xc);    // se usa para hacer zoom en la vista en planta
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      if(vista_multiple==0)
        pick_color(xc, yc);
    } 
  }

  // Hacer zoom con la rueda del ratón
  if(boton == 3 || boton == 4){
    if(estado == GLUT_DOWN){
      if(boton == 3)
        Observer_distance-=0.5;

      if(boton == 4)
        Observer_distance+=0.5;

      glutPostRedisplay();
    }
  }
}

/*************************************************************************/

void RatonMovido( int x, int y )
{
  float x0, y0, xn, yn; 
  if(estadoRaton[2]==1) 
      {

        // Mover los ángulos de la cámara con el click derecho del ratón
        if(vista_multiple==0){      // si está en perspectiva
          getCamara(&x0,&y0);
          yn=y0+(y-yc);
          xn=x0-(x-xc);
          setCamara(xn,yn);
          xc=x;
          yc=y;
          glutPostRedisplay();
        }

        // Hacer zoom con el click derecho del ratón 
        else{                     // si está en vista en planta
          getCamara(&x0,&y0);
          xn=x0-(x-xc);
          
          if(anterior_xn >= xn)
            Observer_distance+=0.05;
          else
            Observer_distance-=0.05;

          anterior_xn = xn;
          glutPostRedisplay();
        }
  }
}


//***************************************************************************
// Funciones para la seleccion
//***************************************************************************


void procesar_hits(GLint hits, GLuint *names)
 {
 	int i;
        solido *obj;

        obj=new solido[sizeof(solido)];
 
 	/*
 		For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected 
 									beacuse when we draw each object
 									we use glLoadName, so we replace the
 									prevous name in the stack)
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName)
 	*/
 
 	cout << "hits: " << hits << endl;
 
 	for (i = 0; i < hits; i++){
 		cout << "Número: " << names[i * 4] << endl;
 		cout << "Min Z: " << names[i * 4 + 1]/(pow(2,32)-1) << endl;
 		cout << "Max Z: " << names[i * 4 + 2]/(pow(2,32)-1) << endl;
 		cout << "Nombre en la pila: " << names[i * 4 + 3] << endl;
 	}

	cout << endl;

        switch (names[0+3])
              {case 1: obj=cilindro1;
                       if (modo[0]==0) 
                               {modo[0]=1;
                                cambio=1;
                               }
                          else 
                              {modo[0]=0;
                               cambio=0;
                              }
                       break; 
               case 2: obj=cilindro2;
                       if (modo[1]==0) 
                               {modo[1]=1;
                                cambio=1;
                               }
                          else 
                              {modo[1]=0;
                               cambio=0;
                              } 
                       break;
               case 3: obj=base;
                       if (modo[2]==0) 
                               {modo[2]=1;
                                cambio=1;
                               }
                          else 
                              {modo[2]=0;
                               cambio=0;
                              }
                       break; 
               case 4: obj=cabina;
                       if (modo[3]==0) 
                               {modo[3]=1;
                                cambio=1;
                               }
                          else 
                              {modo[3]=0;
                               cambio=0;
                              }
                       break;
               case 5: obj=primer_brazo;
                       if (modo[4]==0) 
                               {modo[4]=1;
                                cambio=1;
                               }
                          else 
                              {modo[4]=0;
                               cambio=0;
                              }
                       break;
                case 6: obj=segundo_brazo;
                       if (modo[5]==0) 
                               {modo[5]=1;
                                cambio=1;
                               }
                          else 
                              {modo[5]=0;
                               cambio=0;
                              }
                       break;
                case 7: obj=cucharon;
                       if (modo[6]==0) 
                               {modo[6]=1;
                                cambio=1;
                               }
                          else 
                              {modo[6]=0;
                               cambio=0;
                              }
                       break;
                }        
               
        if (cambio==1) 
                  {obj->r=0.3;
                   obj->g=0.9;
                   obj->b=0.3;
                  }
        if (cambio==0)
                  {obj->r=0.9;
                   obj->g=0.6;
                   obj->b=0.2;
                  }
                 
 }

 void procesar_color(unsigned char color[3])
 {
 	int i;
        solido *obj;

        obj=new solido[sizeof(solido)];

        switch (color[0])
              {case 100: obj=cilindro1;
                       if (modo[0]==0) 
                               {modo[0]=1;
                                cambio=1;
                               }
                          else 
                              {modo[0]=0;
                               cambio=0;
                              }
                       break; 
               case 120: obj=cilindro2;
                       if (modo[1]==0) 
                               {modo[1]=1;
                                cambio=1;
                               }
                          else 
                              {modo[1]=0;
                               cambio=0;
                              } 
                       break;
               case 140: obj=base;
                       if (modo[2]==0) 
                               {modo[2]=1;
                                cambio=1;
                               }
                          else 
                              {modo[2]=0;
                               cambio=0;
                              }
                       break; 
               case 160: obj=cabina;
                       if (modo[3]==0) 
                               {modo[3]=1;
                                cambio=1;
                               }
                          else 
                              {modo[3]=0;
                               cambio=0;
                              }
                       break;
               case 180: obj=primer_brazo;
                       if (modo[4]==0) 
                               {modo[4]=1;
                                cambio=1;
                               }
                          else 
                              {modo[4]=0;
                               cambio=0;
                              }
                       break;
                case 200: obj=segundo_brazo;
                       if (modo[5]==0) 
                               {modo[5]=1;
                                cambio=1;
                               }
                          else 
                              {modo[5]=0;
                               cambio=0;
                              }
                       break;
                case 220: obj=cucharon;
                       if (modo[6]==0) 
                               {modo[6]=1;
                                cambio=1;
                               }
                          else 
                              {modo[6]=0;
                               cambio=0;
                              }
                       break;
                }        
               
        if (cambio==1) 
                  {obj->r=0.3;
                   obj->g=0.9;
                   obj->b=0.3;
                  }
        if (cambio==0)
                  {obj->r=0.9;
                   obj->g=0.6;
                   obj->b=0.2;
                  }
                 
 }

void pick_color(int x, int y){
	GLint viewport[4];
	unsigned char pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
  int r = pixel[0];
  int g = pixel[1];
  int b = pixel[2];
	cout << "valor x " << x << " valor y " << y << " color " << r << " " << g << " " << b << endl;

	procesar_color(pixel);
	glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

for (int i=0;i<7;i++) modo[i]=0;
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    

    cilindro1=new solido[sizeof(solido)];
    construir_cilindro(1,1,20,3,cilindro1);

    cilindro2=new solido[sizeof(solido)];
    construir_cilindro(1,1,20,3,cilindro2);

    base=new solido[sizeof(solido)];
    construir_cubo(0.5,base);

    cabina=new solido[sizeof(solido)];
    construir_cubo(0.5,cabina);

    primer_brazo=new solido[sizeof(solido)];
    construir_cubo(0.5,primer_brazo);

    segundo_brazo=new solido[sizeof(solido)];
    construir_cubo(0.5,segundo_brazo);

    cucharon=new solido[sizeof(solido)];
    construir_medio_cilindro(1,1,20,3,cucharon);
    
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 5");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // eventos ratón
    glutMouseFunc( clickRaton );
    glutMotionFunc( RatonMovido );


    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}


// EXAMEN se pedira un objeto y hacer la selección por caras
// seleccionar un objeto y cuando se seleccione el objeto se pinta arriba una esfera
// a nivel de camara se puede pedir hacer una cámara en primera persona // pero no, está explicado en el tema 4 pagina 31 utilizar glLookAt
// por ejemplo que también se pueda hacer el zoom con el ratón
// por una vista en paralelo

// PRACTICA:
// se pide que se mueva la cámara en perspectiva con el ratón
// cuando se ponga la escena en perspectiva en planta, el ratón solo debe hacer zoom, no debe girar los angulos
