# Informática Gráfica
Repositorio en el que se encuentran las prácticas de la asignatura Informática Gráfica de la Universidad de Granada. Las prácticas están realizadas en C++ con la librería gráfica OpenGL.

## Práctica 1 - Primitivas básicas
La práctica contiene el código para representar una pirámide y un cubo. También permite los distintos tipos de representación de las primitivas. Las teclas asignadas son:
- Visión de puntos (tecla P)
- Visión de líneas (tecla L)
- Visión de sólido (tecla F)
- Visión de ajedrez (tecla C)
- Cambiar a pirámide (tecla 1)
- Cambiar a cubo (tecla 2)

## Práctica 2 - Cuerpos de revolución y modelos PLY
La práctica contiene el código para representar objetos de revolución, con los que se han creado las primitivas cono, cilindro y esfera. Además permite crear cualquier cuerpo de revolución a partir del prefil de dicho objeto. También se ha implementado una función que permite cargar modelos PLY para poder ser representados en OpenGL.
El programa hay que ejecutarlo con un modelo PLY pasado por parámetro, por ejemplo:<br />
*./practica_objetos_B2 beethoven*<br />

Las teclas asignadas son:
- Visión de puntos (tecla P)
- Visión de líneas (tecla L)
- Visión de sólido (tecla F)
- Visión de ajedrez (tecla C)
- Cambiar a pirámide (tecla 1)
- Cambiar a cubo (tecla 2)
- Cambiar a cono (tecla 3)
- Cambiar a cilindro (tecla 4)
- Cambiar a esfera (tecla 5)
- Cambiar a modelo PLY (tecla 6)
- Cambiar a cuerpo de revolución (tecla 7)

## Práctica 3- Modelos jerárquicos
Esta práctica consiste en representar un modelo jerárquico funcional en OpenGL. Las restricciones del modelo es que tenga 3 articulaciones como mínimo y que alguna de estás tenga dos o más grados de libertad (que tenga mas de una transformación asociada). Para la práctica se ha decidido implemetar un monigote que tiene articulaciones en hombros con dos grados de libertad (rotaciones en ejes X y Z), codos, cintura, rodillas y cuello. En el directorio de la práctica 2 se adjunta un PDF que contiene el grafo de escena del modelo jerárquico. El modelo jerárquico se puede controlar con las siguientes teclas
