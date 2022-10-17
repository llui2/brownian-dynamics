set key top left
set title ""
set xlabel "Γ" 
set ylabel "Diffusivity"
 
set xrange [0:]

set style line 1 lc rgb 'red' pt 7 ps 1 lw 2
set style line 2 lc rgb 'pink' pt 7 ps 1 lw 2

set logscale xy

set format x "10^{%T}"
set format y "10^{%T}"

plot "data_4.dat" u 1:2 w linespoints ls 1 title 'D(Γ)'
pause -1