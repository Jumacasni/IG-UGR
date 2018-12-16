//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
	b_normales_caras = false;
	b_normales_vertices = false;
	b_textura_coord = false;

	ambiente = _vertex4f(1,1,1,1);
	difusa = _vertex4f(1,1,1,1);
    brillo = 40;
	especular = _vertex4f(1,1,1,1);

	ambiente_oro = _vertex4f(0,0,0,1);
	difusa_oro = _vertex4f(0,0,0,1);
    brillo_oro = 40;
	especular_oro = _vertex4f(0,0,0,1);
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// calcular vectores normales de las caras
//*************************************************************************

void  _triangulos3D::calcular_normales_caras(){

	normales_caras.resize(caras.size());

	// Calcular normales a las caras
	for (int i=0;i<caras.size();i++){
		_vertex3f a = vertices[caras[i]._1] - vertices[caras[i]._0];
		_vertex3f b = vertices[caras[i]._2] - vertices[caras[i]._0];
		_vertex3f normal = a.cross_product(b);

		normales_caras[i] = normal.normalize();
	}	

	b_normales_caras = true;
}

//*************************************************************************
// calcular vectores normales de los vertices
//*************************************************************************

void  _triangulos3D::calcular_normales_vertices(){

	if(!b_normales_vertices){
		if(!b_normales_caras)
			calcular_normales_caras();
	}

	normales_vertices.resize(vertices.size());

	_vertex3f normal;

	for(int i = 0; i < vertices.size(); ++i)
		normales_vertices[i] = _vertex3f(0.0,0.0,0.0);

	for(int i = 0; i < caras.size(); ++i){
		normales_vertices[caras[i]._0] += normales_caras[i];
		normales_vertices[caras[i]._1] += normales_caras[i];
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	for(int i = 0; i < vertices.size(); ++i)
		normales_vertices[i].normalize();

	b_normales_vertices = true;
}

//*************************************************************************
// dibujar con iluminacion plana
//*************************************************************************

void  _triangulos3D::draw_iluminacion_plana(){
	if(!b_normales_caras)
		calcular_normales_caras();	

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	// Si ponemos el material aquí, se aplicará a todas las caras
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i =0; i < caras.size(); ++i){
		// Si por ejemplo queremos que el material se aplique a las caras pares y otro para las impares
		// haríamos:
		// if(i % 2 == 0)
		//	glMaterialfv(...);
		// else
		//	el otro material
		glNormal3fv((GLfloat*) &normales_caras[i]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar con iluminacion suave
//*************************************************************************

void  _triangulos3D::draw_iluminacion_suave(){
	if(!b_normales_vertices)
		calcular_normales_vertices();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i =0; i < caras.size(); ++i){
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar con textura
//*************************************************************************

void  _triangulos3D::draw_textura(){
	draw_textura();
}

void _cubo::draw_textura(){
	_textura textura(1, "dado.jpg");
						// cara 1
	GLfloat caras[] = {vertices[7].x, vertices[7].y, vertices[7].z,
					vertices[3].x, vertices[3].y, vertices[3].z,
					vertices[2].x, vertices[2].y, vertices[2].z,
					vertices[6].x, vertices[6].y, vertices[6].z,
						// cara 2
					vertices[4].x, vertices[4].y, vertices[4].z,
					vertices[7].x, vertices[7].y, vertices[7].z,
					vertices[3].x, vertices[3].y, vertices[3].z,
					vertices[0].x, vertices[0].y, vertices[0].z,
						// cara 3
					vertices[4].x, vertices[4].y, vertices[4].z,
					vertices[0].x, vertices[0].y, vertices[0].z,
					vertices[1].x, vertices[1].y, vertices[1].z,
					vertices[5].x, vertices[5].y, vertices[5].z,
						// cara 4
					vertices[2].x, vertices[2].y, vertices[2].z,
					vertices[1].x, vertices[1].y, vertices[1].z,
					vertices[5].x, vertices[5].y, vertices[5].z,
					vertices[6].x, vertices[6].y, vertices[6].z,
						// cara 5
					vertices[3].x, vertices[3].y, vertices[3].z,
					vertices[0].x, vertices[0].y, vertices[0].z,
					vertices[1].x, vertices[1].y, vertices[1].z,
					vertices[2].x, vertices[2].y, vertices[2].z,
						// cara 6
					vertices[6].x, vertices[6].y, vertices[6].z,
					vertices[7].x, vertices[7].y, vertices[7].z,
					vertices[4].x, vertices[4].y, vertices[4].z,
					vertices[5].x, vertices[5].y, vertices[5].z
				};

	GLfloat vertices_texturas[] = {0.0,0.5,
								 0.0,0.75,
								 0.25,0.75,
								 0.25,0.5,

								 0.5,0.5,
								 0.25,0.5,
								 0.25,0.75,
								 0.5,0.75,

								 0.5,0.5,
								 0.5,0.75,
								 0.75,0.75,
								 0.75,0.5,

								 0.75,0.5,
								 0.75,0.75,
								 1.0,0.75,
								 1.0,0.5,

								 0.5,0.75,
								 0.5,1.0,
								 0.75,1.0,
								 0.75,0.75,

								 0.75,0.25,
								 0.5,0.25,
								 0.5,0.5,
								 0.75,0.5,
								};

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura.ident_textura);

	glVertexPointer(3, GL_FLOAT, 0, caras);
	glTexCoordPointer(2, GL_FLOAT, 0, vertices_texturas);

	glDrawArrays(GL_QUADS, 0, 24);	// 24 porque tiene que dibujar 6 caras por 4 arrays en cada cara

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void  _tablero::draw_textura(){
	_textura textura(1, "logo.jpg");

	GLfloat caras[] = {vertices[0].x, vertices[0].y,
					vertices[4].x, vertices[4].y,
					vertices[5].x, vertices[5].y,
					vertices[1].x, vertices[1].y,

					vertices[1].x, vertices[1].y,
					vertices[5].x, vertices[5].y,
					vertices[6].x, vertices[6].y,
					vertices[2].x, vertices[2].y,

					vertices[2].x, vertices[2].y,
					vertices[6].x, vertices[6].y,
					vertices[7].x, vertices[7].y,
					vertices[3].x, vertices[3].y,

					vertices[4].x, vertices[4].y,
					vertices[8].x, vertices[8].y,
					vertices[9].x, vertices[9].y,
					vertices[5].x, vertices[5].y,

					vertices[5].x, vertices[5].y,
					vertices[9].x, vertices[9].y,
					vertices[10].x, vertices[10].y,
					vertices[6].x, vertices[6].y,

					vertices[6].x, vertices[6].y,
					vertices[10].x, vertices[10].y,
					vertices[11].x, vertices[11].y,
					vertices[7].x, vertices[7].y,

					vertices[8].x, vertices[8].y,
					vertices[12].x, vertices[12].y,
					vertices[13].x, vertices[13].y,
					vertices[9].x, vertices[9].y,

					vertices[9].x, vertices[9].y,
					vertices[13].x, vertices[13].y,
					vertices[14].x, vertices[14].y,
					vertices[10].x, vertices[10].y,

					vertices[10].x, vertices[10].y,
					vertices[14].x, vertices[14].y,
					vertices[15].x, vertices[15].y,
					vertices[11].x, vertices[11].y
					};

	GLfloat vertices_texturas[] = {0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0,

								 0.0,0.0,
								 0.0,1.0,
								 1.0,1.0,
								 1.0,0.0
								};

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura.ident_textura);

	glVertexPointer(2, GL_FLOAT, 0, caras);
	glTexCoordPointer(2, GL_FLOAT, 0, vertices_texturas);

	glDrawArrays(GL_QUADS, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void  _piramide::draw_textura(){ };
void  _objeto_ply::draw_textura(){ };
void  _cilindro::draw_textura(){ };
void  _cono::draw_textura(){ };
void  _esfera::draw_textura(){ };
void  _excavadora::draw_textura(){ };
void  _tanque::draw_textura(){ };
void  _medio_cilindro::draw_textura(){ };

//*************************************************************************

// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
	case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
	case TEXTURE:draw_textura();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=4;caras[10]._1=1;caras[10]._2=0;
caras[11]._0=1;caras[11]._1=4;caras[11]._2=5;  
}

//*************************************************************************
// clase tablero
//*************************************************************************

_tablero::_tablero(int filas, int columnas, float tam, float al)
{

float anchura_cada_cuadrado = tam/columnas;
float altura_cada_cuadrado = al/filas;

_vertex3f vertice_aux;
_vertex3i cara_aux;

//vertices 
vertices.resize((filas+1)*(columnas+1)); 

float vertice_x = -tam/2;
float vertice_y = al/2;

int n_vertice = 0;

for(int i = 0; i < filas+1; ++i){
	for(int j = 0; j < columnas+1; ++j){
		vertice_aux.x = vertice_x;
		vertice_aux.y = vertice_y;
		vertice_aux.z = 0;
		vertices[n_vertice] = vertice_aux;

		n_vertice++;
		vertice_x += anchura_cada_cuadrado;
	}

	vertice_x = -tam/2;
	vertice_y -= altura_cada_cuadrado;
}

caras.resize(filas*columnas*2);

for(int i = 0; i < filas; ++i){
	for(int j = 0; j < columnas; ++j){
		cara_aux._0 = (columnas+1)*i + j;
		cara_aux._1 = (columnas+1)*(i+1) + j;
		cara_aux._2 = (columnas+1)*(i+1) + (j+1);
		caras.push_back(cara_aux);

		cara_aux._0 = (columnas+1)*(i+1) + (j+1);
		cara_aux._1 = (columnas+1)*i + (j+1);
		cara_aux._2 = (columnas+1)*i + j;
		caras.push_back(cara_aux);
	}
}

}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
   
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}

//************************************************************************
// objeto por revolucion CILINDRO
//************************************************************************

_cilindro::_cilindro(float r, float h, int n, int tapas){
	
	num = n;	
	this->tapas = tapas;
	_vertex3f aux;
	
	aux.x=r; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=r; aux.y=-h; aux.z=0.0;
	perfil.push_back(aux);
}

void _cilindro::rotacion()
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();	// número de vértices que tenemos en el perfil inicial
vertices.resize(num_aux*num);

for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)	
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }
     
 // tapa superior
	if (fabs(perfil[0].x)>0.0 && (tapas == 1 || tapas == 3))
	{
		vertice_aux.x=0;
		vertice_aux.y=perfil[0].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=0; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=i;
			cara_aux._2=(i+2)%(vertices.size()-1);
			caras.push_back(cara_aux);
		}
	}
 
 // tapa inferior
	if (fabs(perfil[num_aux-1].x)>0.0 && (tapas == 2 || tapas == 3))
	{
		vertice_aux.x=0;
		vertice_aux.y=perfil[1].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=1; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=(i+2)%(vertices.size()-2);
			cara_aux._2=i;
			caras.push_back(cara_aux);
		}
	}
}

//************************************************************************
// objeto por revolucion MEDIO CILINDRO
//************************************************************************

_medio_cilindro::_medio_cilindro(float r, float h, int n, int tapas){
	
	num = n;	
	this->tapas = tapas;
	_vertex3f aux;
	
	aux.x=r; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=r; aux.y=-h; aux.z=0.0;
	perfil.push_back(aux);
}

void _medio_cilindro::rotacion()
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();	// número de vértices que tenemos en el perfil inicial
vertices.resize((num_aux*num));

for (j=0;j<num/2;j++)
  {for (i=0;i<num_aux;i++)	
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

for (j=0;j<num/2;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }
     
 // tapa superior
	if (fabs(perfil[0].x)>0.0 && (tapas == 1 || tapas == 3))
	{
		vertice_aux.x=0;
		vertice_aux.y=perfil[0].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=0; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=i;
			cara_aux._2=(i+2)%(vertices.size()-1);
			caras.push_back(cara_aux);
		}
	}
 
 // tapa inferior
	if (fabs(perfil[num_aux-1].x)>0.0 && (tapas == 2 || tapas == 3))
	{
		vertice_aux.x=0;
		vertice_aux.y=perfil[1].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=1; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=(i+2)%(vertices.size()-2);
			cara_aux._2=i;
			caras.push_back(cara_aux);
		}
	}
}

//************************************************************************
// objeto por revolucion CONO
//************************************************************************

_cono::_cono(float r, float h, int n, bool tapas){
	
	num = n;	
	this->tapas = tapas;
	_vertex3f aux;
	
	aux.x=0.0; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=r; aux.y=0.0; aux.z=0.0;
	perfil.push_back(aux);
}

void _cono::rotacion()
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=1;	
vertices.resize(num_aux+num); 

	vertices[0] = perfil[0];

	for (j=0;j<num;j++){
		vertice_aux.x=perfil[num_aux].x*cos(2.0*M_PI*j/(1.0*num))+
				                perfil[num_aux].z*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-perfil[num_aux].x*sin(2.0*M_PI*j/(1.0*num))+
				                perfil[num_aux].z*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=perfil[num_aux].y;
		vertices[num_aux+j]=vertice_aux;
	}

// tratamiento de las caras 

	for (i=0;i<num-1;i++){
		cara_aux._0=0;
		cara_aux._1=i+1;
		cara_aux._2=(i+2)%(num+num_aux);
		caras.push_back(cara_aux);
	}

	cara_aux._0=0;
	cara_aux._1=num;
	cara_aux._2=1;
	caras.push_back(cara_aux);

 // tapa inferior
if (fabs(perfil[1].x)>0.0 && tapas)
  {
	vertice_aux.x=0;
    vertice_aux.y=perfil[1].y;
    vertice_aux.z=0;
    vertices.push_back(vertice_aux);
	
	for(i=0; i<num-1; i++){
		cara_aux._0=vertices.size()-1;
      	cara_aux._1=i+2;
      	cara_aux._2=i+1;
      	caras.push_back(cara_aux);
	}
	
	cara_aux._0=vertices.size()-1;
    cara_aux._1=1;
    cara_aux._2=vertices.size()-2;
    caras.push_back(cara_aux);
  }
}

//************************************************************************
// objeto por revolucion ESFERA
//************************************************************************

_esfera::_esfera(float r, int lat, int lon, int tapas){

	num = lon;
	this->tapas = tapas;
	_vertex3f aux;
	
	float increRad = M_PI/lat;
	float angulo = 0;

	aux.x=0.0; aux.y=r; aux.z=0.0;
	perfil.push_back(aux);

	for(int i=0; i < lat-1; ++i){
		angulo += increRad;

		aux.x = r*sin(angulo);
		aux.y = r*cos(angulo);
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	aux.x=0.0; aux.y=-r; aux.z=0.0;
	perfil.push_back(aux);
}

void _esfera::rotacion()
{
int i,j,k;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();	// número de vértices que tenemos en el perfil inicial
vertices.resize((perfil.size()-2)*num+2); 

vertices[vertices.size()-2] = perfil[0];
vertices[vertices.size()-1] = perfil[perfil.size()-1];

k = 0;
for (j=0;j<num;j++)
  {for (i=1;i<num_aux-1;i++)	
     {
		vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=perfil[i].y;
		vertices[k]=vertice_aux;
		++k;
     }
  }

// tratamiento de las caras 

	for (j=0;j<num;j++)
		{for (i=0;i<num_aux-3;i++)
			{cara_aux._0=i+((j+1)%num)*(num_aux-2);
			cara_aux._1=i+1+j*(num_aux-2);
			cara_aux._2=i+1+((j+1)%num)*(num_aux-2);
			caras.push_back(cara_aux);

			cara_aux._0=i+1+j*(num_aux-2);
			cara_aux._1=i+((j+1)%num)*(num_aux-2);
			cara_aux._2=i+j*(num_aux-2);
			caras.push_back(cara_aux);
		}
	}

 // tapa superior
	if (fabs(perfil[0].x)==0.0 && (tapas == 1 || tapas == 3))
	{
	cara_aux._0=vertices.size()-2;
	cara_aux._1=0;
	cara_aux._2=perfil.size()-2;
	caras.push_back(cara_aux);
	auto cara_aux_anterior = cara_aux;

	k = perfil.size()-2;
	for(int i=0; i<num-2; i++){
		cara_aux._0 = vertices.size()-2;
		cara_aux._1 = cara_aux_anterior._1 + k;
		cara_aux._2 = cara_aux_anterior._2 + k;
		caras.push_back(cara_aux);
		cara_aux_anterior = cara_aux;
	}

	cara_aux._0=vertices.size()-2;
	cara_aux._1=cara_aux_anterior._1 + k;
	cara_aux._2=0;
	caras.push_back(cara_aux);

	}
 
 //tapa inferior
if (fabs(perfil[num_aux-1].x)==0.0 && (tapas == 2 || tapas == 3))
{	
	cara_aux._0=vertices.size()-1;
	cara_aux._1=perfil.size()-3+perfil.size()-2;
	cara_aux._2=perfil.size()-3;
	caras.push_back(cara_aux);
	auto cara_aux_anterior = cara_aux;

	k = perfil.size()-2;
	for(int i=0; i<num-2; i++){
		cara_aux._0 = vertices.size()-1;
		cara_aux._1 = cara_aux_anterior._1 + k;
		cara_aux._2 = cara_aux_anterior._2 + k;
		caras.push_back(cara_aux);
		cara_aux_anterior = cara_aux;
	}

	cara_aux._0=vertices.size()-1;
	cara_aux._1=perfil.size()-3;
	cara_aux._2=cara_aux_anterior._2 + k;
	caras.push_back(cara_aux);
}
}

//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
	_cilindro cilindro(0.107,0.5,20,3);
	rodamiento = cilindro;
	rodamiento.rotacion();
	altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
	_cilindro cilindro(0.04, 0.4, 12, 3);
	tubo_abierto = cilindro;
	tubo_abierto.rotacion();
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};

//************************************************************************
// objeto articulado: excavadora
//************************************************************************

_sustentacion::_sustentacion()
{
	rodamiento.rotacion();
	altura = 0.07+0.3;
};

void _sustentacion::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glTranslatef(-0.3,0.0,0.0);

glPushMatrix();
glRotatef(90.0,1,0,0);
glScalef(0.15,0.5,0.15);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.6,0.0,0.0);
glRotatef(90.0,1,0,0);
glScalef(0.15,0.5,0.15);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.3, 0.3, 0.0);
glScalef(1.1, 0.3, 1.1);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPopMatrix();
}

_cabina::_cabina()
{
	altura = 0.6;
	anchura = 0.4;
};

void _cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.4, 0.6, 0.35);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

_primer_brazo::_primer_brazo()
{
	altura = 0.8;
};

void _primer_brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.8, 0.1, 0.1);
brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

_segundo_brazo::_segundo_brazo()
{
	altura = 0.6;
	anchura = 0.1;
};

void _segundo_brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.6, 0.1, 0.1);
brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

_cucharon::_cucharon()
{
	cucharon.rotacion();
	altura = 0.15;
	anchura = 0.1;
};

void _cucharon::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.15,0.1,0.15);
cucharon.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

_excavadora::_excavadora()
{
	giro_cabina = 0.0;
	giro_primer_brazo = 0.0;
	giro_primer_brazo_max = 30;
	giro_primer_brazo_min = 0;
	giro_segundo_brazo = 0.0;
	giro_segundo_brazo_max = 0;
	giro_segundo_brazo_min = -90;
	giro_cucharon = 0.0;
	giro_cucharon_max = 0.0;
	giro_cucharon_min = -90.0;
};

void _excavadora::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
sustentacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_cabina,0,1,0);
glTranslatef(0.0,(sustentacion.altura+cabina.altura/2),0.0);
glPushMatrix();
cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glTranslatef(cabina.anchura/2,0.0,0.0);	// eje donde tiene que rotar el brazo
glRotatef(giro_primer_brazo,0,0,1);
glTranslatef(cabina.anchura,0.0,0.0); // posición del brazo
glPushMatrix();
primer_brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glTranslatef(primer_brazo.altura/2,0,0);	// eje donde tiene que rotar el brazo
glRotatef(giro_segundo_brazo,0,0,1);
glTranslatef(segundo_brazo.altura/2,0,0); // posición del brazo
glPushMatrix();
segundo_brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(segundo_brazo.altura/2, 0.0, 0.0); // eje donde tiene que rotar el cucharon
glRotatef(giro_cucharon,0,0,1);
glTranslatef(cucharon.anchura,-cucharon.altura/2,0.0); // posición del cucharon
glRotatef(90.0,1,0,0);
cucharon.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPopMatrix();
};

//************************************************************************
// Objeto luz
//************************************************************************

_luz::_luz(GLenum indice_luz, _vertex4f punto_luz, _vertex4f luz_ambiente, _vertex4f luz_difusa, _vertex4f luz_especular){
	this->indice_luz = indice_luz;
	this->punto_luz = punto_luz;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;

	pos_x = punto_luz[0];
	pos_y = punto_luz[1];
	pos_z = punto_luz[2];
	angx = 0;
	angy = 0;
	angz = 0;
	a = 0;
	b = 0;
	c = 0;
}

void _luz::activar(){
	glEnable(GL_LIGHTING);
	glEnable(indice_luz);
	
	glLightfv(indice_luz, GL_AMBIENT, (GLfloat*) &luz_ambiente);
	glLightfv(indice_luz, GL_DIFFUSE, (GLfloat*) &luz_difusa);
	glLightfv(indice_luz, GL_SPECULAR, (GLfloat*) &luz_especular);
	glLightfv(indice_luz, GL_POSITION, (GLfloat*) &punto_luz);
}

void _luz::desactivar(){
	glDisable(indice_luz);
	glDisable(GL_LIGHTING);	
}

void _luz::transformar(GLenum indice_luz, int a, int b, int c, float ang, float x, float y, float z){
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(ang,a,b,c);
	glLightfv(indice_luz, GL_POSITION, (GLfloat*) &punto_luz);
	glPopMatrix();

	cout << "Posición actual de la luz: " << "(" << x << "," << y << "," << z << ")" << endl;
	cout << "Rotación actual de la luz eje x: " << angx << endl;
	cout << "Rotación actual de la luz eje y: " << angy << endl;
	cout << "Rotación actual de la luz eje z: " << angz << endl;
	cout << endl;
}

_textura::_textura(GLuint textura_id, char const *archivoJPG){
	std::vector<unsigned char> data;
	ident_textura = textura_id;
   imagen.load(archivoJPG);	// Imagen que se va a leer

   // empaquetamos bien los datos
   for (long y = 0; y < imagen.height(); y ++)
      for (long x = 0; x < imagen.width(); x ++)
      {
	 unsigned char *r = imagen.data(x, y, 0, 0);
	 unsigned char *g = imagen.data(x, y, 0, 1);
	 unsigned char *b = imagen.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, &ident_textura);
   glBindTexture(GL_TEXTURE_2D, ident_textura);

   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

// IMPORTANTE EXAMEN:
// crear un objeto tablero para aplicar textura, porque en el examen podemos aplicar la textura tanto al cubo 
// como al tablero

// también se podría pedir calcular las normales a los vértices sin haber calculado previamente las normales