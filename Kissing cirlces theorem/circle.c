#include <stdio.h>
#include <math.h>
#include <string.h>
void draw (int n,int x,int y);
void gp_initialise (FILE* gp);
int main (){
   printf("cercle tangente\n");
//data
    int n = 5 , x = 1, y = 1 ;
    float xn = -1, yn = 1;  
//result

}
void draw (int n,int x,int y) {
    printf("open pipe to gnuplot\n");
	FILE * gp=_popen("gnuplot -persist","w");

	if (gp){//found and stay
		gp_initialise (gp);
        float * rn = malloc (n* sizeof(float));
        getRays(&rn,n);
        float * xn = malloc (n* sizeof(float));
        getXn(&xn,n,rn);

        char * rep ="";
        int k=0;
        for (int i = 0; i < n; i++)
        {
            char * temp = "x(t,%.5f,%.5f),y(t,%.5f,%.5f)";
            sprintf(temp, temp , rn[i] , xn[i] ,rn[i]  , xn[i] );
            if (k!=0)
            {
                char* concat = strcat(",", temp) ;
            }
            
            rep= strcat(rep,) ;
        }
        
	}
	else{
		printf("gnuplot not found\n");
	}
}
void getRays (float** rnaddr,int n){
    float * rn = malloc (n* sizeof(float));
    rn[0] = 1;
    rn[1] = 1/4 ;
    for (int i = 2; i < n; i++)
    {
        rn[i] = 1 / (((1/rn[i-1])+1)*((1/rn[i-1])+1)); 
    }
    rnaddr[0]=rn;
}
void getXn (float** xnaddr,int n,float * rn){
    float * xn = malloc (n* sizeof(float));
    xn[0] = -1;
    xn[1] = 0 ;
    for (int i = 2; i < n; i++)
    {
        xn[i] = xn[i-1] - 2 * sqrt (rn[0]-rn[i]) ; 
    }
    xnaddr[0]=xn;
}
void gp_initialise (FILE* gp){
	fprintf(gp, "set term wxt size 640,480\n");
	fprintf(gp, "set title 'result de mesures vs sin(x)' \n");
	fprintf(gp, "set xlabel 'Temps(s)'\n");
	fprintf(gp, "set ylabel 'Valeurs'\n");
	fprintf(gp, "set style data linespoints\n");
	fprintf(gp, "set size ratio 0\n");
	fprintf(gp, "set parametric \n");
	fprintf(gp, "x(t,r,c)=c+r*cos(t)\n");
	fprintf(gp, "y(t,r,c)=c+r*sin(t)\n");
	//fprintf(gp, "plot 'curve.txt' ,sin (x)\n");
	
}