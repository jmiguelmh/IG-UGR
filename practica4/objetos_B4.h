//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

const float AXIS_SIZE = 5000;
typedef enum
{
	POINTS,
	EDGES,
	SOLID_CHESS,
	SOLID,
	FLAT,
	SMOOTH
} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
	_puntos3D();
	void draw_puntos(float r, float g, float b, int grosor);

	vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D
{
public:
	_triangulos3D();
	void draw_aristas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
	void draw_iluminacion_plana();
	void draw_iluminacion_suave();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	void calcular_normales_caras();
	void calcular_normales_vertices();

	vector<_vertex3i> caras;
	vector<_vertex3f> normales_caras;
	vector<_vertex3f> normales_vertices;

	bool b_normales_caras;
	bool b_normales_vertices;

	_vertex4f ambiente_difusa; //coeficientes ambiente y difuso
	_vertex4f especular;	   //coeficiente especular
	float brillo;			   //exponente del brillo
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
public:
	_cubo(float tam = 0.5);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D
{
public:
	_piramide(float tam = 0.5, float al = 0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply : public _triangulos3D
{
public:
	_objeto_ply();

	int parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion : public _triangulos3D
{
public:
	_rotacion();
	void parametros(vector<_vertex3f> perfil, int num, char eje);

	vector<_vertex3f> perfil;
	int num;
};

//************************************************************************
// clase cono
//************************************************************************

class _cono : public _triangulos3D
{
public:
	_cono(float diametro, float altura, char eje);
};

//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro : public _triangulos3D
{
public:
	_cilindro(float radio = 0.5, float altura = 1.0, char eje = 'y');
};

//************************************************************************
// clase esfera
//************************************************************************

class _esfera : public _triangulos3D
{
public:
	_esfera(float diametro = 1.0);
};

//************************************************************************
// clase modelo articulado
//************************************************************************

class _brazo_izquierdo : public _triangulos3D
{
public:
	_brazo_izquierdo();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_brazo_1;
	float giro_brazo_2;
	float giro_antebrazo;

protected:
	_rotacion rotacion;
};

class _brazo_derecho : public _triangulos3D
{
public:
	_brazo_derecho();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_brazo_1;
	float giro_brazo_2;
	float giro_antebrazo;

protected:
	_rotacion rotacion;
};

class _pierna : public _triangulos3D
{
public:
	_pierna();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_pierna_superior;
	float giro_pierna_inferior;

protected:
	_rotacion rotacion;
};

class _cuerpo : public _triangulos3D
{
public:
	_cuerpo(float tam = 0.5);
};

class _cabeza : public _triangulos3D
{
public:
	_cabeza();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_cabeza;

protected:
	_rotacion rotacion;
	_rotacion cuello;
};

class _monigote : public _triangulos3D
{
public:
	_monigote();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	_brazo_izquierdo brazo_izquierdo;
	_brazo_derecho brazo_derecho;
	_pierna pierna;
	_cuerpo cuerpo;
	_cabeza cabeza;
};