#ifndef UGINE_MATH_H
#define UGINE_MATH_H

template <typename T> T min(T a, T b) { return (a < b) ? a : b; }
template <typename T> T max(T a, T b) { return (a > b) ? a : b; }

double Log2(double x);
double DegSin(double degrees);
double DegCos(double degrees);
double DegTan(double degrees);
double DegASin(double sin);
double DegACos(double cos);
double DegATan(double tan);
double DegATan2(double y, double x);
double WrapValue(double val, double mod);		//ajusta el valor que se pase al modulo. 720 lo pasa a 360
double Angle(double x1, double y1, double x2, double y2);
double Distance(double x1, double y1, double x2, double y2);
bool ValueInRange(double value, double min, double max);
bool PointInRect(double x, double y, double rectx, double recty, double width, double height);
void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy);
bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2);
void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight);
void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY);

#endif
