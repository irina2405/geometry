#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void gnuplot(int n, int x, int y);
float rn(float r);
float newX(float xn1, float rn, float yn1);

int main() {
    printf("Kissing Circles Theorem\n");

///Set initial datas
    int n = 5,
        x = -1,
        y = 1;

///Draw the result
    gnuplot(n,x,y);

    return 0;
}

/// @brief To draw in gnuplot
/// @param n number of iteration
/// @param x x of the initial circle
/// @param y y of the initial circle
void gnuplot(int n, int x, int y) {
    float   xn = -x,
            yn = y,
            yn1 = y;

    FILE* gp = _popen("gnuplot -persist","w");

    printf("Open a pipe to gnuplot \n");

    if (gp)
    {
///Initialization of gnuplot
        fprintf(gp,"set size ratio 0\n");
        fprintf(gp,"set parametric\n");
        fprintf(gp,"set xrange [-2:2]\n");
        fprintf(gp,"set yrange [0:2]\n");
        fprintf(gp,"set xzeroaxis\n");
        fprintf(gp,"set yzeroaxis\n");

///Function x and y to draw a circle
        fprintf(gp,"x(t,r,c)=c+r*cos(t)\n");
        fprintf(gp,"y(t,r,c)=c+r*sin(t)\n");

///Draw the first circle as the reference circle
        fprintf(gp,"plot x(t,%i,%i),y(t,%i,%i)\n",y,x,y,y);

///Draw the second circle which will change
        fprintf(gp,"replot x(t,%.5f,%.5f),y(t,%.5f,%.5f)\n",yn,xn,yn,yn);
        
///Loop which find the next circles
        for (int i = 0; i < n; i++)
        {
///Search the radius and the x of the new cirlce
            yn = rn(yn);
            xn = newX(xn,yn,yn1);

///Draw the circle
            fprintf(gp,"replot x(t,%.5f,%.5f),y(t,%.5f,%.5f)\n",yn,xn,yn,yn);

///Remember the radius for the next circle
            yn1 = yn;
        }
        
        fflush(gp);
        _pclose(gp);

    } else
    {
        printf("gnuplot not found...\n");
    }
    
}

/// @brief To find the radius of the new cirlce
/// @param r the radius of the previous circle
/// @return radius of the new circle
float rn(float r) {
    return pow((1/((1+sqrt(r))/sqrt(r))),2);
}

/// @brief To find the x of the new circle
/// @param xn1 x of the previous circle
/// @param rn the radius of the new circle
/// @param yn1 the radius of the previous circle
/// @return x of new circle
float newX(float xn1, float rn, float yn1) {
    return xn1-(2*(sqrt(rn*yn1)));
}