//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"

using namespace std;

// tipos
typedef enum
{
	CUBO,
	PIRAMIDE,
	CONO,
	CILINDRO,
	ESFERA,
	OBJETO_PLY,
	ROTACION,
	ARTICULADO
} _tipo_objeto;
_tipo_objeto t_objeto = CUBO;
_modo modo = POINTS;
bool animacion = false;
double animacion_cabeza = 1.0;
double animacion_brazo_izquierdo = 1.0;
double animacion_brazo_derecho = 1.0;
double animacion_antebrazo_izquierdo = 1.0;
double animacion_antebrazo_derecho = 1.0;
double animacion_pierna_superior = 1.0;
double animacion_pierna_inferior = 1.0;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 450, Window_high = 450;

// objetos
_cubo cubo;
_piramide piramide(0.85, 1.3);
_objeto_ply ply;
_rotacion rotacion;
_cono cono(1, 1.0, 'y');
_cilindro cilindro(0.5, 1.0, 'y');
_esfera esfera(2);
_monigote articulado;

// _objeto_ply *ply1;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -Observer_distance);
	glRotatef(Observer_angle_x, 1, 0, 0);
	glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1, 0, 0);
	glVertex3f(-AXIS_SIZE, 0, 0);
	glVertex3f(AXIS_SIZE, 0, 0);
	// eje Y, color verde
	glColor3f(0, 1, 0);
	glVertex3f(0, -AXIS_SIZE, 0);
	glVertex3f(0, AXIS_SIZE, 0);
	// eje Z, color azul
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -AXIS_SIZE);
	glVertex3f(0, 0, AXIS_SIZE);
	glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//**************************************************************************

void draw_objects()
{
	switch (t_objeto)
	{
	case CUBO:
		cubo.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case PIRAMIDE:
		piramide.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case OBJETO_PLY:
		ply.draw(modo, 1.0, 0.6, 0.0, 0.0, 1.0, 0.3, 2);
		break;
	case ROTACION:
		rotacion.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case CONO:
		cono.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case CILINDRO:
		cilindro.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case ESFERA:
		esfera.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case ARTICULADO:
		articulado.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	}
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{

	clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
	float Aspect_ratio;

	Aspect_ratio = (float)Alto1 / (float)Ancho1;
	Size_y = Size_x * Aspect_ratio;
	change_projection();
	glViewport(0, 0, Ancho1, Alto1);
	glutPostRedisplay();
}

// Animacion

void movimiento()
{
	if (animacion)
	{
		articulado.cabeza.giro_cabeza += animacion_cabeza;
		if (articulado.cabeza.giro_cabeza < -90.0 || articulado.cabeza.giro_cabeza > 90.0)
			animacion_cabeza = -animacion_cabeza;

		articulado.brazo_izquierdo.giro_brazo_1 += 0.3 * animacion_brazo_izquierdo;
		if (articulado.brazo_izquierdo.giro_brazo_1 > 0.0 || articulado.brazo_izquierdo.giro_brazo_1 < -180.0)
			animacion_brazo_izquierdo = -animacion_brazo_izquierdo;

		articulado.brazo_izquierdo.giro_brazo_2 += animacion_brazo_izquierdo;
		if (articulado.brazo_izquierdo.giro_brazo_2 > 90.0 || articulado.brazo_izquierdo.giro_brazo_2 < 0.0)
			animacion_brazo_izquierdo = -animacion_brazo_izquierdo;

		articulado.brazo_izquierdo.giro_antebrazo += 0.5 * animacion_antebrazo_izquierdo;
		if (articulado.brazo_izquierdo.giro_antebrazo > 0.0 || articulado.brazo_izquierdo.giro_antebrazo < -90.0)
			animacion_antebrazo_izquierdo = -animacion_antebrazo_izquierdo;

		articulado.brazo_derecho.giro_brazo_1 += 0.3 * animacion_brazo_derecho;
		if (articulado.brazo_derecho.giro_brazo_1 > 0.0 || articulado.brazo_derecho.giro_brazo_1 < -180.0)
			animacion_brazo_derecho = -animacion_brazo_derecho;

		articulado.brazo_derecho.giro_brazo_2 += animacion_brazo_derecho;
		if (articulado.brazo_derecho.giro_brazo_2 > 90.0 || articulado.brazo_derecho.giro_brazo_2 < 0.0)
			animacion_brazo_derecho = -animacion_brazo_derecho;

		articulado.brazo_derecho.giro_antebrazo += 0.5 * animacion_antebrazo_derecho;
		if (articulado.brazo_derecho.giro_antebrazo > 0.0 || articulado.brazo_derecho.giro_antebrazo < -90.0)
			animacion_antebrazo_derecho = -animacion_antebrazo_derecho;

		articulado.pierna.giro_pierna_superior += animacion_pierna_superior;
		if (articulado.pierna.giro_pierna_superior < -90.0 || articulado.pierna.giro_pierna_superior > 0.0)
			animacion_pierna_superior = -animacion_pierna_superior;

		articulado.pierna.giro_pierna_inferior += animacion_pierna_inferior;
		if (articulado.pierna.giro_pierna_inferior < 0.0 || articulado.pierna.giro_pierna_inferior > 90.0)
			animacion_pierna_inferior = -animacion_pierna_inferior;

		glutPostRedisplay();
	}
}

// Luces

float angulo = 0.0;
GLfloat posicion[] = {3.0, 3.0, 0.0, 1.0};

void Luces()
{
	GLfloat luz_posicion[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat luz_ambiente[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat luz_difusa[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat luz_especular[] = {1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);

	glEnable(GL_LIGHT0);

}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y)
{
	switch (toupper(Tecla1))
	{
	case 'Q':
		exit(0);
	case 'P':
		modo = POINTS;
		break;
	case 'L':
		modo = EDGES;
		break;
	case 'R':
		modo = SOLID;
		break;
	case 'C':
		modo = SOLID_CHESS;
		break;
	case 'F':
		modo = FLAT;
		break;
	case 'S':
		modo = SMOOTH;
		break;
	case '1':
		t_objeto = PIRAMIDE;
		break;
	case '2':
		t_objeto = CUBO;
		break;
	case '3':
		t_objeto = CONO;
		break;
	case '4':
		t_objeto = CILINDRO;
		break;
	case '5':
		t_objeto = ESFERA;
		break;
	case '6':
		t_objeto = OBJETO_PLY;
		break;
	case '7':
		t_objeto = ROTACION;
		break;
	case '8':
		t_objeto = ARTICULADO;
		break;
	case ' ':
		animacion = !animacion;
		articulado.brazo_izquierdo.giro_brazo_1 = -90.0;
		articulado.brazo_izquierdo.giro_brazo_2 = 45.0;
		articulado.brazo_izquierdo.giro_antebrazo = -45.0;
		articulado.brazo_derecho.giro_brazo_1 = -90.0;
		articulado.brazo_derecho.giro_brazo_2 = 45.0;
		articulado.brazo_derecho.giro_antebrazo = -45.0;
		articulado.pierna.giro_pierna_superior = -45.0;
		articulado.pierna.giro_pierna_inferior = 45.0;
		articulado.cabeza.giro_cabeza = 0.0;
		break;
	case '+':
		if (animacion_cabeza < 2.0 && animacion_cabeza > -2.0)
		{
			animacion_cabeza *= 1.1;
			animacion_brazo_izquierdo *= 1.1;
			animacion_antebrazo_izquierdo *= 1.1;
			animacion_brazo_derecho *= 1.1;
			animacion_antebrazo_derecho *= 1.1;
			animacion_pierna_superior *= 1.1;
			animacion_pierna_inferior *= 1.1;
		}
		cout << "animacion cabeza: " << animacion_cabeza << endl;
		break;
	case '-':
		if (animacion_cabeza > 0.5 || animacion_cabeza < -0.5)
		{
			animacion_cabeza *= 0.9;
			animacion_brazo_izquierdo *= 0.9;
			animacion_antebrazo_izquierdo *= 0.9;
			animacion_brazo_derecho *= 0.9;
			animacion_antebrazo_derecho *= 0.9;
			animacion_pierna_superior *= 0.9;
			animacion_pierna_inferior *= 0.9;
		}
		cout << "animacion cabeza: " << animacion_cabeza << endl;
		break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

	switch (Tecla1)
	{
	case GLUT_KEY_LEFT:
		Observer_angle_y--;
		break;
	case GLUT_KEY_RIGHT:
		Observer_angle_y++;
		break;
	case GLUT_KEY_UP:
		Observer_angle_x--;
		break;
	case GLUT_KEY_DOWN:
		Observer_angle_x++;
		break;
	case GLUT_KEY_PAGE_UP:
		Observer_distance *= 1.2;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Observer_distance /= 1.2;
		break;
	case GLUT_KEY_F1:
		if (articulado.brazo_izquierdo.giro_brazo_1 < 0.0)
		{
			articulado.brazo_izquierdo.giro_brazo_1++;
			articulado.brazo_derecho.giro_brazo_1++;
		}
		break;
	case GLUT_KEY_F2:
		if (articulado.brazo_izquierdo.giro_brazo_1 > -180.0)
		{
			articulado.brazo_izquierdo.giro_brazo_1--;
			articulado.brazo_derecho.giro_brazo_1--;
		}
		break;
	case GLUT_KEY_F3:
		if (articulado.brazo_izquierdo.giro_brazo_2 < 90.0)
		{
			articulado.brazo_izquierdo.giro_brazo_2++;
			articulado.brazo_derecho.giro_brazo_2++;
		}
		break;
	case GLUT_KEY_F4:
		if (articulado.brazo_izquierdo.giro_brazo_2 > 0.0)
		{
			articulado.brazo_izquierdo.giro_brazo_2--;
			articulado.brazo_derecho.giro_brazo_2--;
		}
		break;
	case GLUT_KEY_F5:
		if (articulado.brazo_izquierdo.giro_antebrazo < 0.0)
		{
			articulado.brazo_izquierdo.giro_antebrazo++;
			articulado.brazo_derecho.giro_antebrazo++;
		}
		break;
	case GLUT_KEY_F6:
		if (articulado.brazo_izquierdo.giro_antebrazo > -90.0)
		{
			articulado.brazo_izquierdo.giro_antebrazo--;
			articulado.brazo_derecho.giro_antebrazo--;
		}
		break;
	case GLUT_KEY_F7:
		if (articulado.pierna.giro_pierna_superior < 0.0)
			articulado.pierna.giro_pierna_superior++;
		break;
	case GLUT_KEY_F8:
		if (articulado.pierna.giro_pierna_superior > -90.0)
			articulado.pierna.giro_pierna_superior--;
		break;
	case GLUT_KEY_F9:
		if (articulado.pierna.giro_pierna_inferior < 90.0)
			articulado.pierna.giro_pierna_inferior++;
		break;
	case GLUT_KEY_F10:
		if (articulado.pierna.giro_pierna_inferior > 0.0)
			articulado.pierna.giro_pierna_inferior--;
		break;
	case GLUT_KEY_F11:
		if (articulado.cabeza.giro_cabeza < 90.0)
			articulado.cabeza.giro_cabeza++;
		break;
	case GLUT_KEY_F12:
		if (articulado.cabeza.giro_cabeza > -90.0)
			articulado.cabeza.giro_cabeza--;
		break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

	// se inicalizan la ventana y los planos de corte
	Size_x = 0.5;
	Size_y = 0.5;
	Front_plane = 1;
	Back_plane = 1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance = 4 * Front_plane;
	Observer_angle_x = 0;
	Observer_angle_y = 0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1, 1, 1, 1);

	Luces();
	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{

	_objeto_ply objeto_rotado;
	objeto_rotado.parametros(argv[1]);
	rotacion.parametros(objeto_rotado.vertices, 10, 'y');

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x, Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width, Window_high);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 4");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	glutIdleFunc(movimiento);

	// funcion de inicialización
	initialize();

	// creación del objeto ply
	ply.parametros(argv[1]);

	//ply1 = new _objeto_ply(argv[1]);

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
