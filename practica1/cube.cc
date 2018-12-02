/*
* Practicas de IG
* Domingo Martin Perandres© 2014-2018
* dmartin@ugr.es
*
* GPL 3
*/

#include "cube.h"

/**
*
*@param
*@returns
*/

_cube::_cube(float Size)
{
  Vertices.resize(8);

	// Los vértices

  Vertices[0]=_vertex3f(0,0,Size/2);
  Vertices[1]=_vertex3f(Size/2,0,Size/2);
  Vertices[2]=_vertex3f(Size/2,0,0);
  Vertices[3]=_vertex3f(0,0,0);
	Vertices[4]=_vertex3f(0,Size/2,Size/2);
  Vertices[5]=_vertex3f(Size/2,Size/2,Size/2);
  Vertices[6]=_vertex3f(Size/2,Size/2,0);
  Vertices[7]=_vertex3f(0,Size/2,0);
	
	// Las caras

  Triangles.resize(12);

  Triangles[0]=_vertex3ui(0,1,4);
  Triangles[1]=_vertex3ui(1,5,4);
  Triangles[2]=_vertex3ui(1,2,5);
  Triangles[3]=_vertex3ui(2,6,5);
	Triangles[4]=_vertex3ui(2,3,6);
  Triangles[5]=_vertex3ui(3,7,6);
  Triangles[6]=_vertex3ui(3,0,7);
  Triangles[7]=_vertex3ui(0,4,7);
	Triangles[8]=_vertex3ui(4,5,6);
  Triangles[9]=_vertex3ui(4,6,7);
  Triangles[10]=_vertex3ui(0,1,3);
  Triangles[11]=_vertex3ui(1,2,3);
}