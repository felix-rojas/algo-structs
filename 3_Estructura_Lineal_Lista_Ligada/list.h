#ifndef LIST_H
#define LIST_H
/*
 * list.h
 *
 *  Created on: September 19 2023
 *      Author: felix-rojas

    insertion

    Descripción: Insertar un elemento en la estructura de datos (create) de
 acuerdo a la política de acceso de la estructura Entrada:	Estructura de
 datos y elemento a insertar Salida:	Nada Precondición:	Una estructura
 válida Postcondición: Estructura modificada

    search

    Descripción:Encuentra el elemento en la estructura y devuelve su posición.
    Entrada:	El elemento a buscar (un entero)
    Salida: La posición del elemento a buscar o -1 ( si no existe un elemento
 con esas características) Precondición:	Estructura de datos válida
    Postcondición: Estructura de datos válida

    update

    Descripción:Actualizar un elemento dentro de la estructura de datos (update)
 de acuerdo a la estructura de datos específica Entrada:	posición del
 elemento a actualizar, valor nuevo. Salida:	Nada
    Precondición:	Estructura de datos válida
    Postcondición: Estructura de datos válida con el cambio

    deleteAt

    Descripción: Borrar (eliminar) un elemento dentro de la estructura de datos
 segun su posición. Entrada: La posición del elemento a eliminar. Salida:
 El valor del elemento eliminado. Precondición:	Estructura de datos válida
    Postcondición: Estructura de datos válida con el cambio
*/

#include "node.h"
#include <cstddef>
#include <string>
template <typename T> class List {

private:
  Node<T> head;
  Node<T> tail;

public:
  void insertion();
  int search();
  void update();
  T deleteAt();

  std::string toString();
};
#endif // LIST_H
