#include <iostream>
#include <cmath>

struct point {double x;double y;};

point zz, z{ 0.5, 0.5 }, y;

double f( double x, double y) {return x*x + y*y - 10*x - 8*y +3;}

double dfx(double x, double y) {return 2*x - 10;}

double dfy(double x, double y) {return 2*y - 8;}

double norma( double x, double y) {return sqrt(x*x + y*y);}

double phi_fun(point z, point y, double s){
    return(pow((z.x + s*(y.x - z.x)),2) +
           pow((z.y + s*(y.y - z.y)),2) -
           10*(z.x + s*(y.x - z.x)) -
           8*(z.y + s*(y.y - z.y)) + 3);
}

double gold( point z, point y) {
    double eps = 0.0001;
    double a = 0;
    double b = 1;
    double delta = (b-a)*((3-sqrt(5))/2);
    double A = a;
    double B = b;
    double X = A + delta;
    double Y = B - delta;
    double FX = phi_fun(z,y,X);
    double FY = phi_fun(z,y,Y);
    while((B-A) > (2*eps)){
        if(FX>FY){
            A=X; X=Y; FX=FY; Y=A+B-X;
            FY = phi_fun(z,y,Y);
        } else {
            B=Y; Y=X; FY=FX; X=A+B-Y;
            FX = phi_fun(z,y,X);
        }
    }
    double xeps=(A+B)/2;

    return xeps;
}

double fk(point z, point x) {return (dfx(z.x, z.y)*(x.x - z.x) + dfy(z.x, z.y)*(x.y - z.y));}

point argmin() {
    point y1, y2, y3;
    y1.x = 0; y1.y = 0;
    y2.x = 0; y2.y = 1;
    y3.x = 2; y3.y = 0;

    if( fk(z,y1) < fk(z,y2))
        if (fk(z,y1) < fk(z,y3))
            return y1;
        else
            return y2;
    else
    if (fk(z,y2) < fk(z,y3))
        return y2;
    else
        return y3;

}

int main() {
    double n , eps;

    eps = 1e-7;

    int i = 0;

    for (;;i++) {
        y = argmin();

        double s = gold(zz, y);

        zz.x = z.x + s * (y.x - z.x);
        zz.y = z.y + s * (y.y - z.y);

        std::cout << "min: " << z.x << "; " << z.y << std::endl;
        std::cout << "y = (" << y.x << ";" << y.y << ")" << std::endl;
        std::cout << "f(y) = " << f(y.x,y.y) << std::endl;
        std::cout << "iter : " << i << std::endl;
        std::cout << "eps " << eps << std::endl;
        std::cout << "_______________________________" << std::endl << std::endl;


        /// Скалярное произведние градиента в точке z на разность векторов z и y
        n = dfx(z.x, z.y) * (y.x - z.x) + dfy(z.x, z.y) * (y.y - z.y);
        std::cout << "n = " << n << std::endl;
        if (n < -eps)
            z = zz;
        else {
            break;
        }

    }

    return 0;
}
