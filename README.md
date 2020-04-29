# AppEval
Evaluate apprentice approximations in C++

# Requirements
HighFive, libHDF5, eigen3, mpi

# Compilation of library

g++ -O3 -fopenmp  -shared -fPIC -flto  -march=native -mtune=native  -DNDEBUG  -std=c++17  -g -IHighFive/include -I/usr/include/mpich-x86_64 -IEigen3.3.7 -Iinclude/AppEval  -L/usr/lib64/mpich/lib -lhdf5 -o libAppEval.so src/AppEval.cxx
