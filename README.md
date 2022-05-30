# Informática Gráfica
Repositorio en el que se encuentran las prácticas de la asignatura Informática Gráfica de la Universidad de Granada. Las prácticas están realizadas en C++ con la librería gráfica OpenGL.

## Práctica 1 - Primitivas básicas
La práctica contiene el código para representar una pirámide y un cubo. También permite los distintos tipos de representación de las primitivas. Las teclas asignadas son:
- Salir (tecla Q)
- Seleccionar visión de puntos (tecla P)
- Seleccionar visión de líneas (tecla L)
- Seleccionar visión de sólido (tecla F)
- Seleccionar visión de ajedrez (tecla C)
- Seleccionar pirámide (tecla 1)
- Seleccionar cubo (tecla 2)

## Práctica 2 - Cuerpos de revolución y modelos PLY
La práctica contiene el código para representar objetos de revolución, con los que se han creado las primitivas cono, cilindro y esfera. Además permite crear cualquier cuerpo de revolución a partir del prefil de dicho objeto. También se ha implementado una función que permite cargar modelos PLY para poder ser representados en OpenGL.
El programa hay que ejecutarlo con un modelo PLY pasado por parámetro, por ejemplo:<br />
*./practica_objetos_B2 beethoven*<br />

Las teclas asignadas son:
- Salir (tecla Q)
- Seleccionar visión de puntos (tecla P)
- Seleccionar visión de líneas (tecla L)
- Seleccionar visión de sólido (tecla F)
- Seleccionar visión de ajedrez (tecla C)
- Seleccionar pirámide (tecla 1)
- Seleccionar cubo (tecla 2)
- Seleccionar cono (tecla 3)
- Seleccionar cilindro (tecla 4)
- Seleccionar esfera (tecla 5)
- Seleccionar modelo PLY (tecla 6)
- Seleccionar cuerpo de revolución (tecla 7)

## Práctica 3 - Modelos jerárquicos
Esta práctica consiste en representar un modelo jerárquico funcional en OpenGL. Las restricciones del modelo es que tenga 3 articulaciones como mínimo y que alguna de estás tenga dos o más grados de libertad (que tenga mas de una transformación asociada). Para la práctica se ha decidido implemetar un monigote que tiene articulaciones en hombros con dos grados de libertad (rotaciones en ejes X y Z), codos, cintura, rodillas y cuello. En el directorio de la práctica 2 se adjunta un PDF que contiene el grafo de escena del modelo jerárquico. El modelo jerárquico se puede controlar mediante ciertas teclas y dispone de una animación básica.
El programa hay que ejecutarlo con un modelo PLY pasado por parámetro, por ejemplo:<br />
*./practica_objetos_B2 beethoven*<br />

Las teclas asignadas son:
- Salir (tecla Q)
- Seleccionar visión de puntos (tecla P)
- Seleccionar visión de líneas (tecla L)
- Seleccionar visión de sólido (tecla F)
- Seleccionar visión de ajedrez (tecla C)
- Seleccionar pirámide (tecla 1)
- Seleccionar cubo (tecla 2)
- Seleccionar cono (tecla 3)
- Seleccionar cilindro (tecla 4)
- Seleccionar esfera (tecla 5)
- Seleccionar modelo PLY (tecla 6)
- Seleccionar cuerpo de revolución (tecla 7)
- Seleccionar modelo jerárquico (tecla 8)

Las teclas para controlar el movimiento del modelo jerárquico son:
- Aumentar el giro de los brazos en el eje X (tecla F1)
- Disminuir el giro de los brazos en el eje X (tecla F2)
- Aumentar el giro de los brazos en el eje Z (tecla F3)
- Disminuir el giro de los brazos en el eje Z (tecla F4)
- Aumentar el giro de los antebrazos (tecla F5)
- Disminuir el giro de los antebrazos (tecla F6)
- Aumentar el giro de toda la pierna (tecla F7)
- Disminuir el giro de toda la pierna (tecla F8)
- Aumentar el giro de la parte inferior de la pierna (tecla F9)
- Disminuir el giro de la parte inferior de la pierna (tecla F10)
- Aumentar el giro de la cabeza (tecla F11)
- Disminuir el giro de la cabeza (tecla F12)
- Activar/Desactivar animación (Barra Espaciadora)
- Aumentar velocidad de animación (tecla +)
- Disminuir velocidad de animación (tecla -)

## Práctica 4 - Luces y materiales
La práctica contiene el código para añadir dos luces a la escena (una estática y otra que se mueve), materiales a las primitivas y dos modos de visión nuevos (flat y smooth). Se ha eliminado la necesidad de pasar por parámetro un fichero con un modelo PLY. Para ejecutar el programa se hace sin argumentos.

Las teclas asignadas son:
- Salir (tecla Q)
- Seleccionar visión de puntos (tecla P)
- Seleccionar visión de líneas (tecla L)
- Seleccionar visión de sólido (tecla R)
- Seleccionar visión de ajedrez (tecla C)
- Seleccionar visión flat (tecla F)
- Seleccionar visión smooth (tecla S) 
- Seleccionar pirámide (tecla 1)
- Seleccionar cubo (tecla 2)
- Seleccionar cono (tecla 3)
- Seleccionar cilindro (tecla 4)
- Seleccionar esfera (tecla 5)
- Seleccionar modelo PLY (tecla 6)
- Seleccionar cuerpo de revolución (tecla 7)
- Seleccionar modelo jerárquico (tecla 8)
- Activar/Desactivar animación de luces (Barra Espaciadora)

Las teclas para controlar el movimiento del modelo jerárquico son las mismas de la práctica 3 salvo que la Barra Espaciadora se utiliza para animar las luces de la escena y las teclas + y - se ha desactivado.

## Práctica 5 - Interacción y cámara
La práctica contiene el código para las funciones de picking y movimiento de cámara. El picking permite detectar que polígono de un modelo se le hice clic con el ratón y se cambia el color. Las funciones de movimiento de cámara permiten mover la cámara de la escena haciendo clic y arrastrando con el ratón. Las teclas asignadas no han cambiado con respecto a la práctica 4.
