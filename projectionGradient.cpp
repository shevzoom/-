#include <iostream>
#include <cmath>
#include <ctime>

inline double f(double x,double y) {return pow(x,2) + pow(y,2) - 10*x - 8*y + 3;}

inline double gk1(double x, double y) {return 2*x - 10;}

inline double gk2(double x, double y) {return 2*y - 8;}

const double n(const double x, const double y) {return sqrt(x*x + y*y);}

// |z-P(z)| = inf|z-x|
inline double Px(double x, double y) {
    if ( x + 2*y <= 2 && x >= 0 && y >= 0)
        return x;
    if ( x + 2*y > 2 && x < 0 && y >= 0)
        return 2 - (y - 2*x + 4)*2/5;
    if ( x + 2*y > 2 && x >= 2 && y >= 0)
        return 2;
    if ( x + 2*y <= 2 && x >= 2 && y < 0)
        return 2;
    if ( x + 2*y <= 2 && x >= 0 && y < 0)
        return x;
    if ( x + 2*y <= 2 && x < 0 && y < 0)
        return 0;
    if ( x + 2*y <= 2 && x < 0 && y >= 0)
        return 0;
    if ( x + 2*y <= 2 && x < 0 && y >= 1)
        return 0;
    if ( x + 2*y > 2 && x >= 0 && y >= 1)
        return 0;
}

inline double Py(double x, double y) {
    if ( x + 2*y <= 2 && x >= 0 && y >= 0)
        return y;
    if ( x + 2*y <= 2 && x < 0 && y >= 0)
        return (y - 2*x + 4)/5;
    if ( x + 2*y > 2 && x >= 2 && y >= 0)
        return 0;
    if ( x + 2*y <= 2 && x >= 2 && y < 0)
        return 0;
    if ( x + 2*y <= 2 && x >= 0 && y < 0)
        return 0;
    if ( x + 2*y <= 2 && x < 0 && y < 0)
        return 0;
    if ( x + 2*y <= 2 && x < 0 && y >= 0)
        return y;
    if ( x + 2*y <= 2 && x < 0 && y >= 1)
        return 1;
    if ( x + 2*y > 2 && x >= 0 && y >= 1)
        return 1;
}

int main() {
    double start = clock();
    double x = 4, y = 1;

    double  S = 10, eps = 0.00001, sigma = 0.1, alpha = 0.1;

    double z1 = Px(x - S * gk1(x,y), y - S * gk2(x,y));
    double z2 = Py(x - S * gk1(x,y), y - S * gk2(x,y));

    int i = 0;
    while ((n((z1 - x), (z2 - y)) > eps) && (n(gk1(z1,z2), gk2(z1,z2)) > eps)) {
        i++;
        x = z1; y = z2;

        while ( (f(x,y) - f(z1,z2)) < sigma * pow(n((x - z1), (y - z2)),2)) {
            S *= alpha;
        }
        x = z1; y = z2;

        z1 = Px(x - S * gk1(x,y), y - S * gk2(x,y));
        z2 = Py(x - S * gk1(x,y), y - S * gk2(x,y));

        std::cout << std::endl << "iter:"<<i;
        std::cout << std::endl << "z = " << "(" << z1 << ";" << z2 << ")";
        std::cout << std::endl << "f(x,y) = " << f(x,y);
        std::cout << std::endl << "f'(x,y) = " << "(" << gk1(x, y) << ";" << gk2(x, y) << ")";
        std::cout << std::endl << "|x-z| = " << n((x - z1), (y - z2));
    }
    std::cout<< "\n" <<"time"<< (clock() - start)/ CLOCKS_PER_SEC;
    return 0;
}

