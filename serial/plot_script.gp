set terminal pngcairo size 800,600
set output 'n_body_simulation.png'
set title 'N-Body Simulation'
set xlabel 'X Position'
set ylabel 'Y Position'
set grid

set xrange [-5000:5000]
set yrange [-5000:5000]

# Plot each body with a different color
plot 'output.dat' using ($3==0 ? $4 : 1/0):($3==0 ? $5 : 1/0) with linespoints linecolor rgb "red" title 'Body 0', \
     'output.dat' using ($3==1 ? $4 : 1/0):($3==1 ? $5 : 1/0) with linespoints linecolor rgb "green" title 'Body 1', \
     'output.dat' using ($3==2 ? $4 : 1/0):($3==2 ? $5 : 1/0) with linespoints linecolor rgb "blue" title 'Body 2'

