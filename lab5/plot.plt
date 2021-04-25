
set term png
# ZALOZENIE: w pliku lambda.dat znajduja sie dane w formie dwoch kolumn oddzielonych spacja lub tabulatorem:
#       numer_iteracji aktualna_lambda
# Po zmianie k (numeru wartosci wlasnej) w pliku powinny znajdowac sie dwie puste linie.

l_width = 1
p_size = 1.5
set style line 1 lt rgb "red" lw l_width pt 7 ps p_size
set style line 2 lt rgb "black" lw l_width pt 7 ps p_size
set style line 3 lt rgb "dark-spring-green" lw l_width pt 7 ps p_size
set style line 4 lt rgb "goldenrod" lw l_width*2 pt 7 ps p_size*1.2
set style line 5 lt rgb "turquoise" lw l_width pt 7 ps p_size
set style line 6 lt rgb "royalblue" lw l_width pt 7 ps p_size
#set style line 7 lt rgb "brown" lw l_width pt 7 ps p_size


set output "lambda_300.png"

set xlabel "Numer iteracji"
set ylabel "λ_{k}"
set yrange [0:0.6]
plot for [i=1:6] "wyn_l.dat" i i u 1:2 w lp ls (i+1) t "{/Symbol l}_".i."" 


set output "lambda2_300.png"
set yrange [3.589:3.596]
plot "wyn_l.dat" i 0 u 1:2 w lp ls 1 t "{/Symbol l}_0"

