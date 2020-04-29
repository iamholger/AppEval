# AppEval
Evaluate apprentice approximations in C++

# Requirements
HighFive, libHDF5, eigen3, mpi

# Compilation
g++ -O3 -fopenmp -shared -fPIC  -march=native -mtune=native  -DNDEBUG  -std=c++17  -g -I/home/hschulz/scidac/HighFive/include -I/usr/include/mpich-x86_64 -I/usr/include/eigen3 -IAppEval -L/usr/lib64/mpich/lib -lhdf5 -o AppEval AppEval.cxx
