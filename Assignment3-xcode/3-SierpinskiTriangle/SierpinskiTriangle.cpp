/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the Sierpinski Triangle problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

/* Main program */
void DrawFractal (double x, double y, double w, double h);
void DrawTriangle (double x, double y, double w, double h);

int main() {
   GWindow gw(600, 500);

   // Fill in the necessary code here
   return 0;
}

void DrawFractal (double x, double y, double w, double h) {
    DrawTriangle(x, y, w, h);
    if (w < .2 || h < .2) return;
    double halfH = h/2;
    double halfW = w/2;
    DrawFractal(x, y, halfW, halfH); // left
    DrawFractal(x + halfW/2, y + halfH, halfW, halfH); // top
    DrawFractal(x + halfW, y, halfW, halfH); // right
}

void DrawTriangle (double x, double y, double w, double h) {

}
