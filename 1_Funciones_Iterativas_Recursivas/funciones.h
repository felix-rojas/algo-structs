/*
 * funciones.h
 *
 *  Created on: 07/10/2020
 *      Author: Félix Javier Rojas Gallardo
 */

#include <iostream>

class Funciones
{
public:
    int sumaRecursiva(int number)
    {
        if (number == 0)
        {
            return number;
        } 
        else 
        {
            return number + sumaRecursiva(number-1);
        }
    };
    int sumaIterativa(int number)
    {
        int res = 0;
        for (int i = 0; i <= number; i++)
        {
            res += i;
        }
        return res;
    };
    int sumaDirecta(int number)
    {
        return static_cast<int>(number * (number + 1) * 0.5);
    };
};