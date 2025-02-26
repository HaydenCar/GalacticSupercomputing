#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    // initializes MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    printf("Hello from rank %d out of %d processes\n", rank, size);

    MPI_Finalize();
    // end MPI
    return 0;
}

/*to install openmpi,
download tarball folder
extract into serial folder
./configure
make all
make install
(takes a long time)



set environmental variables:

make sure include folder is present in openmpi folder, if not extract it again
using the commandline (normal extraction excluded the include folder for somereason)
"tar -xvf openmpi-5.0.7.tar.gz"

place openmpi folder in serial

(setting enviromental variables)
nano ~/.bashrc


place these 2 at the end of the file (replace the path to whichever mpi file is)

export PATH=/home/ramazan/Documents/GitHub/GalacticSupercomputing/serial/openmpi-5.0.7/bin:$PATH
export LD_LIBRARY_PATH=/home/ramazan/Documents/GitHub/GalacticSupercomputing/serial/openmpi-5.0.7/lib:$LD_LIBRARY_PATH

save (ctrl + X) , Y, Enter

(to apply it, use this)
source ~/.bashrc


now in visual studio code,

ctrl+shift+p

search up "C/C++:Edit Config UI"
now in the settings, find the part called "include path"

put this into "include path" (change to whatever your path is)
/home/ramazan/Documents/GitHub/GalacticSupercomputing/serial/openmpi-5.0.7/include

save file and restart.



to run with openmpi

mpicc -o mpiTest mpiTest.c

mpirun -np 4 ./mpiTest

(-np 4 = will run with 4 processes)
*/