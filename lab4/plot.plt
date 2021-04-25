set term png
set xlabel 'alfa'
set ylabel 'ω' 
set yrange [0:1.80]
set xrange [0:100]
set out 'w.png'

plot 	'w.dat' u 1:2 w l t 'ω 1',\
		'w.dat' u 1:3 w l t 'ω 2',\
		'w.dat' u 1:4 w l t 'ω 3',\
		'w.dat' u 1:5 w l t 'ω 4',\
		'w.dat' u 1:6 w l t 'ω 5',\
		'w.dat' u 1:7 w l t 'ω 6',\

set term png
set xlabel 'x'
set ylabel 'u(x)'
set yrange [-0.1:0.1]
set xrange [-5 : 5]
set out 'a_0.png'

plot 	'a_0.dat' u 1:2 w l t 'u 1',\
		'a_0.dat' u 1:3 w l t 'u 2',\
		'a_0.dat' u 1:4 w l t 'u 3',\
		'a_0.dat' u 1:5 w l t 'u 4',\
		'a_0.dat' u 1:6 w l t 'u 5',\
		'a_0.dat' u 1:7 w l t 'u 6',\


set out 'a_100.png'
set yrange [-0.15:0.15]
set xrange [-5 : 5]
plot 	'a_100.dat' u 1:2 w l t 'u 1',\
		'a_100.dat' u 1:3 w l t 'u 2',\
		'a_100.dat' u 1:4 w l t 'u 3',\
		'a_100.dat' u 1:5 w l t 'u 4',\
		'a_100.dat' u 1:6 w l t 'u 5',\
		'a_100.dat' u 1:7 w l t 'u 6',\