//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B5.h"
#include "file_ply_stl.hpp"

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
	int i;
	glPointSize(grosor);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	for (i = 0; i < vertices.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[i]);
	}
	glEnd();
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
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int Vertex_1, Vertex_2, Vertex_3;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	glColor3f(r, g, b);
	for (int i = 0; i < caras.size(); i++)
	{
		Vertex_1 = caras[i]._0;
		Vertex_2 = caras[i]._1;
		Vertex_3 = caras[i]._2;
		glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);
		glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);
		glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		if (i % 2 == 0)
			glColor3f(r1, g1, b1);
		else
			glColor3f(r2, g2, b2);

		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

void _triangulos3D::draw_iluminacion_plana()
{
	glEnable(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ambiente_difusa);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *)&normales_caras[i]);

		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_FLAT);
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
}

void _triangulos3D::draw_iluminacion_suave()
{
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ambiente_difusa);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
}

void _triangulos3D::draw_seleccion(int r, int g, int b)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(r, g, b);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	switch (modo)
	{
	case POINTS:
		draw_puntos(r1, g1, b1, grosor);
		break;
	case EDGES:
		draw_aristas(r1, g1, b1, grosor);
		break;
	case SOLID_CHESS:
		draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);
		break;
	case SOLID:
		draw_solido(r1, g1, b1);
		break;
	case FLAT:
		draw_iluminacion_plana();
		break;
	case SMOOTH:
		draw_iluminacion_suave();
		break;
	case SELECT:
		draw_seleccion(r1, g1, b1);
		break;
	}
}

void _triangulos3D::calcular_normales_caras()
{
	if (caras.size() > 0)
	{
		_vertex3f a, b, normal;
		normales_caras.resize(caras.size());

		for (int i = 0; i < caras.size(); i++)
		{
			a = vertices[caras[i]._1] - vertices[caras[i]._0];
			b = vertices[caras[i]._2] - vertices[caras[i]._0];
			normal = a.cross_product(b);
			normales_caras[i] = normal.normalize();
		}
	}
}

void _triangulos3D::calcular_normales_vertices()
{
	if (normales_caras.size() > 0)
	{

		normales_vertices.resize(vertices.size());

		for (int i = 0; i < vertices.size(); ++i)
		{
			normales_vertices[i].x = 0;
			normales_vertices[i].y = 0;
			normales_vertices[i].z = 0;

			for (int j = 0; j < caras.size(); ++j)
			{
				if (caras[j]._0 == i ||
					caras[j]._1 == i ||
					caras[j]._2 == i)
				{
					normales_vertices[i] += normales_caras[j];
				}
			}

			normales_vertices[i] = normales_vertices[i].normalize();
		}
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
	vertices.resize(8);

	vertices[0].x = -tam;
	vertices[0].y = 0;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = 0;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = 0;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = -tam;
	vertices[4].y = 2 * tam;
	vertices[4].z = tam;
	vertices[5].x = tam;
	vertices[5].y = 2 * tam;
	vertices[5].z = tam;
	vertices[6].x = tam;
	vertices[6].y = 2 * tam;
	vertices[6].z = -tam;
	vertices[7].x = -tam;
	vertices[7].y = 2 * tam;
	vertices[7].z = -tam;

	// triangulos
	caras.resize(12);

	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 5;
	caras[1]._0 = 0;
	caras[1]._1 = 4;
	caras[1]._2 = 5;
	caras[2]._0 = 1;
	caras[2]._1 = 2;
	caras[2]._2 = 6;
	caras[3]._0 = 1;
	caras[3]._1 = 5;
	caras[3]._2 = 6;
	caras[4]._0 = 2;
	caras[4]._1 = 3;
	caras[4]._2 = 7;
	caras[5]._0 = 2;
	caras[5]._1 = 6;
	caras[5]._2 = 7;
	caras[6]._0 = 3;
	caras[6]._1 = 0;
	caras[6]._2 = 4;
	caras[7]._0 = 3;
	caras[7]._1 = 4;
	caras[7]._2 = 7;
	caras[8]._0 = 0;
	caras[8]._1 = 1;
	caras[8]._2 = 3;
	caras[9]._0 = 1;
	caras[9]._1 = 2;
	caras[9]._2 = 3;
	caras[10]._0 = 4;
	caras[10]._1 = 5;
	caras[10]._2 = 6;
	caras[11]._0 = 4;
	caras[11]._1 = 6;
	caras[11]._2 = 7;

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(0.4, 0.8, 0.9, 1.0);
	especular = _vertex4f(0.5, 0.0, 0.5, 1.0);
	brillo = 20;
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

	//vertices
	vertices.resize(5);
	vertices[0].x = -tam;
	vertices[0].y = 0;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = 0;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = 0;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = 0;
	vertices[4].y = al;
	vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 4;
	caras[1]._0 = 1;
	caras[1]._1 = 2;
	caras[1]._2 = 4;
	caras[2]._0 = 2;
	caras[2]._1 = 3;
	caras[2]._2 = 4;
	caras[3]._0 = 3;
	caras[3]._1 = 0;
	caras[3]._2 = 4;
	caras[4]._0 = 3;
	caras[4]._1 = 1;
	caras[4]._2 = 0;
	caras[5]._0 = 3;
	caras[5]._1 = 2;
	caras[5]._2 = 1;

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(0.9, 0.5, 0.1, 1.0);
	especular = _vertex4f(0.0, 0.0, 0.0, 1.0);
	brillo = 5;
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
	int n_ver, n_car;

	vector<float> ver_ply; //Puntos consecutivos (x1,y1,z1,x2,y2...)
	vector<int> car_ply;

	_file_ply::read(archivo, ver_ply, car_ply);

	n_ver = ver_ply.size() / 3;
	n_car = car_ply.size() / 3;

	vertices.resize(n_ver);

	for (int i = 0; i < n_ver; i++)
	{
		vertices[i].x = ver_ply[3 * i];
		vertices[i].y = ver_ply[3 * i + 1];
		vertices[i].z = ver_ply[3 * i + 2];
	}

	caras.resize(n_car);

	for (int i = 0; i < n_car; i++)
	{
		caras[i]._0 = car_ply[3 * i];
		caras[i]._1 = car_ply[3 * i + 1];
		caras[i]._2 = car_ply[3 * i + 2];
	}

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(0.7, 0.7, 0.7, 1.0);
	especular = _vertex4f(0.0, 0.0, 0.0, 1.0);
	brillo = 30;

	return (0);
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, char eje)
{

	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	_vertex3f vertice_inferior;
	_vertex3f vertice_superior;
	int num_aux, num_vertices;
	int modo;

	// tratamiento de los vértices iniciales
	if ((eje == 'y' && perfil[0].x != 0 && perfil[perfil.size() - 1].x != 0) ||
		(eje == 'x' && perfil[0].z != 0 && perfil[perfil.size() - 1].z != 0) ||
		(eje == 'z' && perfil[0].y != 0 && perfil[perfil.size() - 1].y != 0))
		modo = 0; // vertices de eje no creados

	else if ((eje == 'y' && perfil[0].x == 0 && perfil[perfil.size() - 1].x != 0) ||
			 (eje == 'x' && perfil[0].z == 0 && perfil[perfil.size() - 1].z != 0) ||
			 (eje == 'z' && perfil[0].y == 0 && perfil[perfil.size() - 1].y != 0))
		modo = 1; // solo primer vertice en eje(inferior)

	else if ((eje == 'y' && perfil[0].x != 0 && perfil[perfil.size() - 1].x == 0) ||
			 (eje == 'x' && perfil[0].z != 0 && perfil[perfil.size() - 1].z == 0) ||
			 (eje == 'z' && perfil[0].y != 0 && perfil[perfil.size() - 1].y == 0))
		modo = 2; // solo ultimo vertice en eje(superior)

	else
		modo = 3; //ambos vertices en eje

	switch (modo)
	{
	case 0:
		num_aux = perfil.size();	  //Vertices del perfil sin contar extremos
		num_vertices = num_aux * num; //Vertices totales sin extremos
		vertices.resize(num_vertices);
		//Calculamos vertice inferior
		vertice_inferior.x = (eje == 'x') ? perfil[0].x : 0;
		vertice_inferior.y = (eje == 'y') ? perfil[0].y : 0;
		vertice_inferior.z = (eje == 'z') ? perfil[0].z : 0;
		//Calculamos vertice superior
		vertice_superior.x = (eje == 'x') ? perfil[num_aux - 1].x : 0;
		vertice_superior.y = (eje == 'y') ? perfil[num_aux - 1].y : 0;
		vertice_superior.z = (eje == 'z') ? perfil[num_aux - 1].z : 0;
		break;

	case 1:
		num_aux = perfil.size() - 1;
		num_vertices = num_aux * num;
		vertices.resize(num_vertices);
		//Extraemos vertice inferior
		vertice_inferior = perfil[0];
		//Calculamos vertice superior
		vertice_superior.x = (eje == 'x') ? perfil[num_aux].x : 0;
		vertice_superior.y = (eje == 'y') ? perfil[num_aux].y : 0;
		vertice_superior.z = (eje == 'z') ? perfil[num_aux].z : 0;
		//desplazar para eliminar del vector el vertice extremo basura
		for (int i = 1; i < perfil.size(); i++)
			perfil[i - 1] = perfil[i];
		perfil.pop_back();
		break;

	case 2:
		num_aux = perfil.size() - 1;
		num_vertices = num_aux * num;
		vertices.resize(num_vertices);
		//Extraemos vertice inferior
		vertice_superior = perfil[num_aux];
		//Calculamos vertice superior
		vertice_inferior.x = (eje == 'x') ? perfil[0].x : 0;
		vertice_inferior.y = (eje == 'y') ? perfil[0].y : 0;
		vertice_inferior.z = (eje == 'z') ? perfil[0].z : 0;
		//eliminar del vector el vertice extremo basura
		perfil.pop_back();

		break;

	case 3:							  //ambos vertices incluidos
		num_aux = perfil.size() - 2;  //Vertices del perfil sin contar extremos
		num_vertices = num_aux * num; //Vertices totales sin extremos
		vertices.resize(num_vertices);
		vertice_inferior = perfil[0];
		vertice_superior = perfil[perfil.size() - 1];
		//desplazar para eliminar del vector los dos vertices extremos basura
		for (int i = 1; i < (perfil.size() - 1); i++)
			perfil[i - 1] = perfil[i];
		perfil.pop_back();
		perfil.pop_back();
		break;
	}

	//Creacion de rotacion de vertices
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux; i++)
		{
			if (eje == 'y')
			{
				vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
								perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
								perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.y = perfil[i].y;
			}
			else if (eje == 'x')
			{
				vertice_aux.y = perfil[i].y * cos(2.0 * M_PI * j / (1.0 * num)) -
								perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.z = perfil[i].y * sin(2.0 * M_PI * j / (1.0 * num)) +
								perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.x = perfil[i].x;
			}
			else
			{
				vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) -
								perfil[i].y * sin(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.y = perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
								perfil[i].y * cos(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.z = perfil[i].z;
			}
			vertices[i + j * num_aux] = vertice_aux;
		}
	}

	//Inserccion de los vertices extremos de los ejes
	vertices.push_back(vertice_inferior);
	vertices.push_back(vertice_superior);

	//Genereacion de caras
	for (int i = 0; i < num_vertices - 1; i++)
	{
		//Salto a siguiente columna si he llegado arriba
		if (i % num_aux == (num_aux - 1))
			i++;

		// tringulo inferior
		cara_aux._0 = i;
		cara_aux._1 = (i + num_aux) % num_vertices;
		cara_aux._2 = i + 1;
		caras.push_back(cara_aux);

		// triangulo superior
		cara_aux._0 = i + 1;
		cara_aux._1 = (i + num_aux) % num_vertices;
		cara_aux._2 = (i + num_aux + 1) % num_vertices;
		caras.push_back(cara_aux);
	}

	// tapa inferior
	for (int i = 0; i < num; i++)
	{
		cara_aux._0 = i * num_aux;
		cara_aux._1 = (i * num_aux + num_aux) % num_vertices;
		cara_aux._2 = num_vertices; //tapa inferior
		caras.push_back(cara_aux);
	}

	// tapa superior
	for (int i = 0; i < num; i++)
	{
		cara_aux._0 = num_aux - 1 + i * num_aux;
		cara_aux._1 = (num_aux - 1 + (i + 1) * num_aux) % num_vertices;
		cara_aux._2 = num_vertices + 1; //tapa superior
		caras.push_back(cara_aux);
	}

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(1.0, 0.0, 0.0, 1.0);
	especular = _vertex4f(0.0, 0.0, 0.0, 1.0);
	brillo = 20;
}

_cono::_cono(float diametro, float altura, char eje)
{
	vector<_vertex3f> perfil;
	_vertex3f punto;
	_rotacion cono;

	//formar perfil
	punto.x = (eje == 'y') ? diametro : 0;
	punto.y = (eje == 'z') ? diametro : 0;
	punto.z = (eje == 'x') ? diametro : 0;
	perfil.push_back(punto);

	punto.x = (eje == 'x') ? altura : 0;
	punto.y = (eje == 'y') ? altura : 0;
	punto.z = (eje == 'z') ? altura : 0;
	perfil.push_back(punto);

	//formar revolucion
	cono.parametros(perfil, 15, eje);
	vertices = cono.vertices;
	caras = cono.caras;

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(0.2, 0.6, 0.1, 1.0);
	especular = _vertex4f(1.0, 1.0, 1.0, 1.0);
	brillo = 50;
}

_esfera::_esfera(float diametro)
{
	vector<_vertex3f> perfil;
	_vertex3f punto;
	_rotacion esfera;
	punto.x = 0;
	punto.y = -diametro / 2;
	punto.z = 0;
	perfil.push_back(punto);

	esfera.parametros(perfil, 100, 'z');
	perfil = esfera.vertices;

	for (int i = 0; i < 51; i++)
		perfil.pop_back(); //me quedo con media esfera
	esfera.caras.clear();
	vector<_vertex3f>::iterator it = perfil.end();
	it--;
	it->x = 0;

	esfera.parametros(perfil, 100, 'y');
	vertices = esfera.vertices;
	caras = esfera.caras;

	calcular_normales_caras();
	//calcular_normales_vertices();

	normales_vertices.resize(vertices.size());
	for (int i = 0; i < vertices.size(); i++)
	{
		normales_vertices[i] = vertices[i].normalize();
	}

	ambiente_difusa = _vertex4f(1.0, 0.5, 0.5, 1.0);
	especular = _vertex4f(1.0, 1.0, 1.0, 1.0);
	brillo = 10;
}

_cilindro::_cilindro(float radio, float altura, char eje)
{
	vector<_vertex3f> perfil;
	_vertex3f punto;
	_rotacion cilindro;

	punto.x = (eje == 'x') ? -altura / 2 : (eje == 'y') ? radio
														: 0;
	punto.y = (eje == 'y') ? -altura / 2 : (eje == 'z') ? radio
														: 0;
	punto.z = (eje == 'z') ? -altura / 2 : (eje == 'x') ? radio
														: 0;
	perfil.push_back(punto);
	punto.x = (eje == 'x') ? altura / 2 : (eje == 'y') ? radio
													   : 0;
	punto.y = (eje == 'y') ? altura / 2 : (eje == 'z') ? radio
													   : 0;
	punto.z = (eje == 'z') ? altura / 2 : (eje == 'x') ? radio
													   : 0;
	perfil.push_back(punto);

	cilindro.parametros(perfil, 16, eje);
	vertices = cilindro.vertices;
	caras = cilindro.caras;

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(0.4, 0.1, 0.6, 1.0);
	especular = _vertex4f(1.0, 1.0, 1.0, 1.0);
	brillo = 100;
}

// Modelo articulado monigote

_brazo_izquierdo::_brazo_izquierdo()
{
	giro_brazo_1 = 0.0;
	giro_brazo_2 = 90.0;
	giro_antebrazo = 0.0;

	vector<_vertex3f> perfil;
	_vertex3f punto;

	for (double i = -M_PI / 2; i <= 0.0; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 - 0.7;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	for (double i = 0.0; i <= M_PI / 2; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 + 0.7;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	rotacion.parametros(perfil, 10, 'y');
	vertices = rotacion.vertices;
	caras = rotacion.caras;

	calcular_normales_caras();
	calcular_normales_vertices();
};

void _brazo_izquierdo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(giro_brazo_1, 1.0, 0.0, 0.0);
	glRotatef(giro_brazo_2, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(giro_antebrazo, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();
};

_brazo_derecho::_brazo_derecho()
{
	giro_brazo_1 = 0.0;
	giro_brazo_2 = 90.0;
	giro_antebrazo = 0.0;

	vector<_vertex3f> perfil;
	_vertex3f punto;

	for (double i = -M_PI / 2; i <= 0.0; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 - 0.7;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	for (double i = 0.0; i <= M_PI / 2; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 + 0.7;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	rotacion.parametros(perfil, 10, 'y');
	vertices = rotacion.vertices;
	caras = rotacion.caras;

	calcular_normales_caras();
	calcular_normales_vertices();
};

void _brazo_derecho::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(giro_brazo_1, 1.0, 0.0, 0.0);
	glRotatef(-giro_brazo_2, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(giro_antebrazo, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();
};

_pierna::_pierna()
{
	giro_pierna_superior = 0.0;
	giro_pierna_inferior = 0.0;

	vector<_vertex3f> perfil;
	_vertex3f punto;

	for (double i = -M_PI / 2; i <= 0.0; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 - 0.7;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	for (double i = 0.0; i <= M_PI / 2; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 + 0.7;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	rotacion.parametros(perfil, 10, 'y');
	vertices = rotacion.vertices;
	caras = rotacion.caras;

	calcular_normales_caras();
	calcular_normales_vertices();
};

void _pierna::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(giro_pierna_superior, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(giro_pierna_inferior, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();
};

_cuerpo::_cuerpo(float tam)
{
	//vertices
	vertices.resize(8);

	vertices[0].x = -tam * 0.75;
	vertices[0].y = 0;
	vertices[0].z = tam * 0.75;
	vertices[1].x = tam * 0.75;
	vertices[1].y = 0;
	vertices[1].z = tam * 0.75;
	vertices[2].x = tam * 0.75;
	vertices[2].y = 0;
	vertices[2].z = -tam * 0.75;
	vertices[3].x = -tam * 0.75;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = -tam;
	vertices[4].y = 2 * tam;
	vertices[4].z = tam;
	vertices[5].x = tam;
	vertices[5].y = 2 * tam;
	vertices[5].z = tam;
	vertices[6].x = tam;
	vertices[6].y = 2 * tam;
	vertices[6].z = -tam;
	vertices[7].x = -tam;
	vertices[7].y = 2 * tam;
	vertices[7].z = -tam;

	// triangulos
	caras.resize(12);

	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 5;
	caras[1]._0 = 0;
	caras[1]._1 = 4;
	caras[1]._2 = 5;
	caras[2]._0 = 1;
	caras[2]._1 = 2;
	caras[2]._2 = 6;
	caras[3]._0 = 1;
	caras[3]._1 = 5;
	caras[3]._2 = 6;
	caras[4]._0 = 2;
	caras[4]._1 = 3;
	caras[4]._2 = 7;
	caras[5]._0 = 2;
	caras[5]._1 = 6;
	caras[5]._2 = 7;
	caras[6]._0 = 3;
	caras[6]._1 = 0;
	caras[6]._2 = 4;
	caras[7]._0 = 3;
	caras[7]._1 = 4;
	caras[7]._2 = 7;
	caras[8]._0 = 0;
	caras[8]._1 = 1;
	caras[8]._2 = 3;
	caras[9]._0 = 1;
	caras[9]._1 = 2;
	caras[9]._2 = 3;
	caras[10]._0 = 4;
	caras[10]._1 = 5;
	caras[10]._2 = 6;
	caras[11]._0 = 4;
	caras[11]._1 = 6;
	caras[11]._2 = 7;

	calcular_normales_caras();
	calcular_normales_vertices();

	ambiente_difusa = _vertex4f(1.0, 0.0, 0.0, 1.0);
	especular = _vertex4f(0.0, 0.0, 0.0, 1.0);
	brillo = 20;
}

_cabeza::_cabeza()
{
	giro_cabeza = 0.0;

	vector<_vertex3f> perfil;
	_vertex3f punto;

	for (double i = -M_PI / 2; i <= M_PI / 2; i += M_PI / 18)
	{
		punto.x = cos(i) * 0.3;
		punto.y = sin(i) * 0.3 + 0.15;
		punto.z = 0.0;
		perfil.push_back(punto);
	}

	rotacion.parametros(perfil, 10, 'y');
	vertices = rotacion.vertices;
	caras = rotacion.caras;

	perfil.clear();
	punto.x = 0.1;
	punto.y = 0.0;
	punto.z = 0.0;
	perfil.push_back(punto);

	punto.x = 0.1;
	punto.y = 0.15;
	punto.z = 0.0;
	perfil.push_back(punto);

	cuello.parametros(perfil, 10, 'y');
	vertices = cuello.vertices;
	caras = cuello.caras;

	calcular_normales_caras();
	calcular_normales_vertices();
};

void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(giro_cabeza, 0.0, 1.0, 0.0);
	glPushMatrix();
	cuello.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glTranslatef(0.0, 0.25, 0.0);
	rotacion.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();
};

_monigote::_monigote()
{
	calcular_normales_caras();
	calcular_normales_vertices();

	int c = 100;
	piezas = 6;
	color_pick[0] = 1.0;
	color_pick[1] = 0.0;
	color_pick[2] = 0.0;
	for (int i = 0; i < piezas; i++)
	{
		activo[i] = 0;
		color_selec[0][i] = color_selec[1][i] = color_selec[2][i] = c;
		c = c + 20;
	}
};

void _monigote::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	float r_p, g_p, b_p;

	r_p = color_pick[0];
	g_p = color_pick[1];
	b_p = color_pick[2];

	// Cuerpo
	glPushMatrix();
	glScalef(1.0, 1.25, 0.5);
	if (activo[0] == 1)
		cuerpo.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor);
	else
		cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	// Brazo izquierdo
	glPushMatrix();
	glTranslatef(0.5, 1.15, 0.0);
	glScalef(0.5, 0.5, 0.5);
	if (activo[1] == 1)
		brazo_izquierdo.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor);
	else
		brazo_izquierdo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	// Brazo derecha
	glPushMatrix();
	glTranslatef(-0.5, 1.15, 0.0);
	glScalef(0.5, 0.5, 0.5);
	if (activo[2] == 1)
		brazo_derecho.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor);
	else
		brazo_derecho.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	// Pierna izquierda
	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	if (activo[3] == 1)
		pierna.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor);
	else
		pierna.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	// Pierna derecha
	glPushMatrix();
	glTranslatef(-0.2, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	if (activo[4] == 1)
		pierna.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor);
	else
		pierna.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	// Cabeza
	glPushMatrix();
	glTranslatef(0.0, 1.25, 0.0);
	if (activo[5] == 1)
		cabeza.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor);
	else
		cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
};

void _monigote::seleccion()
{
	int c;

	c = color_selec[0][0];
	glPushMatrix();
	glScalef(1.0, 1.25, 0.5);
	cuerpo.draw(SELECT, c, c, c, c, c, c, 1);
	glPopMatrix();

	// Brazo izquierdo
	c = color_selec[0][1];
	glPushMatrix();
	glTranslatef(0.5, 1.15, 0.0);
	glScalef(0.5, 0.5, 0.5);
	brazo_izquierdo.draw(SELECT, c, c, c, c, c, c, 1);
	glPopMatrix();

	// Brazo derecha
	c = color_selec[0][2];
	glPushMatrix();
	glTranslatef(-0.5, 1.15, 0.0);
	glScalef(0.5, 0.5, 0.5);
	brazo_derecho.draw(SELECT, c, c, c, c, c, c, 1);
	glPopMatrix();

	// Pierna izquierda
	c = color_selec[0][3];
	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	pierna.draw(SELECT, c, c, c, c, c, c, 1);
	glPopMatrix();

	// Pierna derecha
	c = color_selec[0][4];
	glPushMatrix();
	glTranslatef(-0.2, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	pierna.draw(SELECT, c, c, c, c, c, c, 1);
	glPopMatrix();

	// Cabeza
	c = color_selec[0][5];
	glPushMatrix();
	glTranslatef(0.0, 1.25, 0.0);
	cabeza.draw(SELECT, c, c, c, c, c, c, 1);
	glPopMatrix();
}