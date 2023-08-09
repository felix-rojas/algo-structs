/*
 * sorts.h
 *
 *  Created on: 09/08/2023
 *      Author: felix-rojas
 */

#ifndef SORTS_H_
#define SORTS_H_
template <typename T>
class Sorts
{

public:
    void ordenaSeleccion(std::vector<T> &vec)
    {
        for (int i = 0; i < vec.size() - 1; i++)
        {
            int min = i;
            for (int j = i + 1; j < vec.size(); j++)
            {
                if (vec.at(j) < vec.at(min))
                    min = j;
            }
            std::swap(vec.at(i), vec.at(min));
        }
    }
    void ordenaBurbuja(std::vector<T> &vec)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            for (int i = 0; i < vec.size() - (j + 1); i++)
            {
                if (vec.at(i) > vec.at(i + 1))
                {
                    std::swap(vec.at(i), vec.at(i + 1));
                }
            }
        }
    }

    void ordenaMerge(std::vector<int> &vec)
    {
    }

    int busqSecuencial(std::vector<int> vec, int item)
    {
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (item == vec.at(i))
            {
                return i;
            }
        }
        return -1;
    }
    int busqBinaria(std::vector<int>, int item) { return 0; }
};

#endif /* SORTS_H_ */
