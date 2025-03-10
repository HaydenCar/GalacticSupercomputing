set terminal pngcairo size 800,600
set output 'n_body_simulation.png'
set title 'N-Body Simulation'
set xlabel 'X Position'
set ylabel 'Y Position'
set grid

set xrange [-1.596e11:1.596e11]  
set yrange [-1.596e11:1.596e11]

# Plot each body with a different color
plot 'output.dat' using ($2==0 ? $3 : 1/0):($2==0 ? $4 : 1/0) with linespoints linecolor rgb "red" title 'Sun', \
     'output.dat' using ($2==1 ? $3 : 1/0):($2==1 ? $4 : 1/0) with linespoints linecolor rgb "green" title 'Earth', \
     'output.dat' using ($2==2 ? $3 : 1/0):($2==2 ? $4 : 1/0) with linespoints linecolor rgb "blue" title 'Moon'
