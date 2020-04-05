/*
** EPITECH PROJECT, 2020
** 109titration
** File description:
** main
*/

//libC
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

//perso
#include "titration.h"

//namespaces
using namespace std;

int GetCurveFromCSV(char *filename, curve &c)
{
	ifstream file(filename);
    string line;
    double old_vol = 0;

    if (!file.is_open()) {
        perror("csv file not found, exit program\n");
        return 84;
    }
    while (getline(file,line) ) {
        double vol = 0;
        double ph = 0;
        try {
            string str_vol = line.substr(0, line.find(";"));
            string str_ph = line.substr(line.find(";") + 1, line.length() - 1);
            vol = stod(str_vol);
            ph = stod(str_ph);
            if (vol < 0 || vol < old_vol) {
                perror("volume can't be negative, exit program\n");
                return 84;
            }
            if (ph < 0 || ph > 12) {
                perror("ph can't be negative or superior to 12, exit program\n");
                return 84;
            }
            old_vol = vol;
        } catch (invalid_argument const &e) {
            perror("csv file invalid, exit program\n");
        	return 84;
    	} catch ( out_of_range const &e) {
            perror("overflow error, exit program\n");
        	return 84;
    	}
        c.ph.push_back(ph);
        c.vol.push_back(vol);
    }
    file.close();
    if (c.ph.empty()) {
        perror("empty file, exit program\n");
    }
    return 0;
}