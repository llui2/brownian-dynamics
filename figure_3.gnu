set size ratio -1

set key outside
set title ""
set xlabel ""
set ylabel "" 

L = 60
set xrange [-L:L]
set yrange [-L:L]

set style line 1 lc rgb 'green' pt 7 ps 0.2
set style line 2 lc rgb 'dark-green' pt 7 ps 0.2

plot "data_3.dat" index 0 u 1:2 w points ls 1 title 'initial', "data_3.dat" index 1 u 1:2 w points ls 2 title 'final'
pause -1