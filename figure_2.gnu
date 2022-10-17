set size ratio -1

set key top right 
set title ""
set xlabel ""
set ylabel "" 

L = 10
set xrange [-L:L]
set yrange [-L:L]

plot "data_2.dat" u 1:2 w lines notitle
pause -1