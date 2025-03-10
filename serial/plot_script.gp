set terminal pngcairo size 800,600
set output 'n_body_simulation.png'
set title 'N-Body Simulation'
set xlabel 'X Position'
set ylabel 'Y Position'
set grid

set xrange [-1.596e11:1.596e11]  
set yrange [-1.596e11:1.596e11]

# Plot each body with a different color
plot 'output.dat' using ($3==0 ? $4 : 1/0):($3==0 ? $5 : 1/0) with linespoints linecolor rgb "red" title 'Sun', \
     'output.dat' using ($3==1 ? $4 : 1/0):($3==1 ? $5 : 1/0) with linespoints linecolor rgb "green" title 'Earth', \
     'output.dat' using ($3==2 ? $4 : 1/0):($3==2 ? $5 : 1/0) with linespoints linecolor rgb "blue" title 'Moon'
