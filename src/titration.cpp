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

double getPreciseSummit(curve c, int roughtID)
{
	double preciseID = 0;
	double pID_data = c.ph[roughtID - 1];

	cout << fixed << setprecision(1) << c.vol[roughtID - 1] << " ml -> " << setprecision(2) << c.ph[roughtID - 1] << endl;
	for (int i = (int)(c.vol[roughtID - 1] * 10) + 1; i < (int)(c.vol[roughtID] * 10); i++) {
		double coef = (c.ph[roughtID] - c.ph[roughtID - 1]) / ((int)(c.vol[roughtID] * 10) - (int)(c.vol[roughtID - 1] * 10));
		int iter = i - (int)(c.vol[roughtID - 1] * 10);
		float result = c.ph[roughtID - 1] + coef * iter;
		cout << fixed << setprecision(1) << i / 10.0 << " ml -> " << setprecision(2) << result << endl;
		if (pID_data > abs(result)) {
			preciseID = i / 10.0;
			pID_data = abs(result);
		}
	}
	cout << fixed << setprecision(1) << c.vol[roughtID] << " ml -> " << setprecision(2) << c.ph[roughtID] << endl;
	if (pID_data > abs(c.ph[roughtID])) {
		preciseID = c.vol[roughtID];
		pID_data = abs(c.ph[roughtID]);
	}
	for (int i = (int)(c.vol[roughtID] * 10) + 1; i < (int)(c.vol[roughtID + 1] * 10); i++) {
		double coef = (c.ph[roughtID + 1] - c.ph[roughtID]) / ((int)(c.vol[roughtID + 1] * 10) - (int)(c.vol[roughtID] * 10));
		int iter = i - (int)(c.vol[roughtID] * 10);
		float result = c.ph[roughtID] + coef * iter + 0.001;
		cout << fixed << setprecision(1) << i / 10.0 << " ml -> " << setprecision(2) << result << endl;
		if (pID_data > abs(result)) {
			preciseID = i / 10.0;
			pID_data = abs(result);
		}
	}
	cout << fixed << setprecision(1) << c.vol[roughtID + 1] << " ml -> " << setprecision(2) << c.ph[roughtID + 1] << endl;
	return preciseID;
}

int titration(curve c)
{

	cout << "Derivative:" << endl;
	curve dc = derive(c);

	int summitID = GetSummit(dc);
	cout << endl << "Equivalence point at " << fixed << setprecision(1) << dc.vol[summitID] << " ml" << endl << endl;

	cout << "Second derivative:" << endl;
	curve fc = derive(dc);

	cout << endl << "Second derivative estimated:" << endl;
	double preciseID = getPreciseSummit(fc, summitID - 1);
	cout << endl << "Equivalence point at " << fixed << setprecision(1) << preciseID << " ml" << endl << endl;
	return 0;
}
