//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"


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
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
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
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
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
	altura = (0.15/2)+0.3;
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
	altura = 1.0;
};

void _primer_brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0, 0.1, 0.1);
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
glTranslatef(primer_brazo.altura/2,0.0,0.0); // posición del brazo
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