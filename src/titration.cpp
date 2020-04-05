/*
** EPITECH PROJECT, 2020
** 109titration
** File description:
** 109titration
*/

//libC
#include <iostream>
#include <iomanip>

//mylibs
#include "titration.h"

//namespaces
using namespace std;


curve derive(curve c)
{
	curve dc = {vector<double>(), vector<double>()};
	int len = c.ph.size();

	for (int i = 1; i < len - 1; i++) {

		double ph0 = c.ph[i - 1], ph1 = c.ph[i], ph2 = c.ph[i + 1];
		double vol0 = c.vol[i - 1], vol1 = c.vol[i], vol2 = c.vol[i + 1];
		double w0 = (vol2 - vol1) / (vol2 - vol0), w1 = 1.0 - w0;
		double r0 = (ph2 - ph1) / (vol2 - vol1);
		double r1 = (ph1 - ph0) / (vol1 - vol0);
		double result = w1 * r0 + w0 * r1;

		dc.ph.push_back(result);
        dc.vol.push_back(vol1);
		cout << fixed << setprecision(1) << c.vol[i] << " ml -> " << setprecision(2) << result << endl;
	}

	return dc;
}

int GetSummit(curve c)
{
	double summit = c.ph[0];
	int summitID = 0;
	int size = c.ph.size();

	for (int i = 0; i < size; i++)
		if (summit < c.ph[i]) {
			summit = c.ph[i];
			summitID = i;
		}
	return summitID;
}

int titration(curve c)
{

	cout << "Derivative:" << endl;
	curve dc = derive(c);

	cout << endl << "Equivalence point at " << fixed << setprecision(1) << dc.vol[GetSummit(dc)] << " ml" << endl << endl;

	cout << "Second derivative:" << endl;
	curve fc = derive(dc);

	return 0;
}
