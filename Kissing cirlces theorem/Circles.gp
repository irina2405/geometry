# To load this script, open gnuplot in this directory and run in gnuplot : load "Circles.gp"

set size ratio 0
set parametric

set xrange [-2:2]
set yrange [0:2]

set xzeroaxis
set yzeroaxis

x(t,r,c)=c+r*cos(t)
y(t,r,c)=c+r*sin(t)

plot x(t,1,1),y(t,1,1),x(t,1,-1),y(t,1,1),x(t,0.25,0),y(t,0.25,0.25),x(t,0.11111,0.33),y(t,0.11111,0.11111)