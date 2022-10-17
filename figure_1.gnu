set key top right 
set title ""
set xlabel ""
set ylabel "" 

set xrange [-5:5]
set xtics -5,1,5

set logscale y
set yrange [1e-06:]
set format y "10^{%T}"

set style line 1 lc rgb 'purple' lw 1
set style line 2 lc rgb 'magenta' lw 2
set style fill solid 0.5

pi = 3.1415
g(x) = exp(-(x**2)/2)/sqrt(2*pi)

plot "data_1.dat" u 1:2 smooth freq w boxes ls 1 t 'data', g(x) w lines ls 2 t 'N(0,1)'
pause -1