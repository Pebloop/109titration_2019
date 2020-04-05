/*
** EPITECH PROJECT, 2020
** 109titration
** File description:
** main
*/

//libC
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h> 

//mylibs
#include "titration.h"

//namespaces
using namespace std;

//functions

int display_usage()
{
	cout << "USAGE" << endl;
	cout << "    ./109titration file" << endl << endl;
	cout << "DESCRIPTION" << endl;
	cout << "	file    a csv file containing \"vol;ph\" lines"  << endl;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		perror("wrong number of arguments, exit program\n");
		return 84;
	}
	if (argc == 2 && !strcmp(argv[1], "-h"))
		return display_usage();
	curve c = {vector<double>(), vector<double>()};
	if (GetCurveFromCSV(argv[1], c))
		return 84;
	return titration(c);
}
