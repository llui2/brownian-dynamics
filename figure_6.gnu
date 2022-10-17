set key outside
set title ""
set xlabel ""
set ylabel "" 

f = '1 0.1 0.01 0.001'

set xrange [0:100]
set yrange [0:100]

set style line 1 lc rgb 'red' pt 7 ps 1 lw 2
set style line 2 lc rgb 'orange' pt 7 ps 1 lw 2
set style line 3 lc rgb 'dark-yellow' pt 7 ps 1 lw 2
set style line 4 lc rgb 'gold' pt 7 ps 1 lw 2

plot  for [n=0:5] "data_6.dat" index n using 1:2 w lines ls n+1 title sprintf("f = ".word(f,n+1))
pause -1