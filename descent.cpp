#include<iostream>
#include<math>

using namespace std;

double f(double x1, double x2) {
    return pow(x1,2)+4*pow(x2,2)+sin(x1-x2);
}

double dfx(double x1,double x2) {
    return 2*x1+cos(x1-x2);
}

double dfy(double x1,double x2) {
    return 8*x2-cos(x1-x2);
}

double gk1(double x1, double x2) { return dfx(x1,x2); }
double gk2(double x1, double x2) { return dfy(x1,x2); }

double xk1(double x1, double x2,double s) {
    return x1 - s*gk1(x1,x2);
}

double xk2(double x1, double x2,double s) {
    return x2 - s*gk2(x1,x2);
}

double fs(double x1,double x2,double s) {
    return pow(x1-s*gk1(x1,x2),2)+4*pow(x2-s*gk2(x1,x2),2)+sin(x1-s*gk1(x1,x2)-x2+s*gk2(x1,x2));
}

double n(double x1,double x2) {
    return sqrt(pow(gk1(x1,x2),2)+pow(gk2(x1,x2),2));
}

double section(double x1,double x2,double h) {
    int a = 0;
    double fa = fs(x1,x2,a);
    double fh = fs(x1,x2,h);

    while(fa > fh) {
        h *= 2;
        fh = fs(x1,x2,h);
    }
    return h;
}

double min(double x1,double x2, double B) {
    double A = 0, eps = 0.000001;
    double l = (1 + pow(5,0.5)) / 2;
    double delta = (B - A) / (l*l);

    double Y = B - delta;
    double X = A + delta;

    double FX = fs(x1,x2,X);
    double FY = fs(x1,x2,Y);

    while(B - A > 2*eps) {
        if (FX > FY) { A=X; X=Y; FX=FY; Y=A+B-X; FY=fs(x1,x2,Y);
        } else {
            B=Y; Y=X; FY=FX; X=A+B-Y; FX=fs(x1,x2,X);
        }
    }
    double Xeps=(A+B)/2;

    return Xeps;
}

int main() {
    double x0 = 0, y0 = 0;
    double eps = 0.0000001;
    double x, y, x1min, x2min, s0;
    int i=0;

    double h = 0.01;
    double b = section(x0,y0,h);

    if(n(x0,y0) < eps) {
        x1min = x0; x2min = y0;
    } else {
        while(n(x0,y0) > eps) {
            i++;

            s0 = min(x0,y0,b);
            x = xk1(x0,y0,s0);
            y = xk2(x0,y0,s0);

            x0 = x; y0 = y;
            cout << i <<" z=("<< x0 <<";"<< y0 <<")"<<" f(z)="<< f(x0,y0) <<" ||f'(z)||="<< n(x0,y0) <<")\n";
        }
    }

    x1min = x; x2min = y;
    cout <<"min=("<< x1min <<";"<< x2min <<")";

    return 0;
}
