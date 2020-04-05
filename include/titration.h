/*
** EPITECH PROJECT, 2019
** 108trigo
** File description:
** 108trigo functions
*/

#include <vector>

#ifndef TITRATION_H
#define TITRATION_H

struct curve
{
    std::vector <double>vol;
    std::vector <double>ph;
};

int titration(curve c);
int GetCurveFromCSV(char *filename, curve &c);

#endif /*TITRATION_H*/
