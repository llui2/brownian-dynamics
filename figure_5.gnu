set key top right 
set title ""
set xlabel "x"
set ylabel "P(x)" 

set xrange [-40:40]
set yrange [0:0.5]

set xtics -40,10,40
set ytics 0,0.1,0.5

width=1 
hist(x,width)=width*floor(x/width) + width/2.0
set boxwidth width*0.9
set style fill solid 0.5 

set style line 6 lc rgb '#479023' pt 7 ps 1 lw 2
set style line 5 lc rgb '#769E25' pt 7 ps 1 lw 2
set style line 4 lc rgb '#ACAD28' pt 7 ps 1 lw 2
set style line 3 lc rgb '#BB8B2B' pt 7 ps 1 lw 2
set style line 2 lc rgb '#CA612D' pt 7 ps 1 lw 2
set style line 1 lc rgb '#D93030' pt 7 ps 1 lw 2

times = '1 3 10 30 100 1000'
M = 1000

plot for [n=0:5] "data_5.dat" i n u (hist($1,width)):(1.0/M) smooth freq w boxes ls n+1 t sprintf("time = ".word(times,n+1))
pause -1