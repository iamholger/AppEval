# AppEval
Evaluate apprentice approximations in C++

# Requirements
HighFive, libHDF5, eigen3, mpi

# Compilation of library

g++ -O3 -fopenmp  -shared -fPIC -flto  -march=native -mtune=native  -DNDEBUG  -std=c++17  -g -IHighFive/include -I/usr/include/mpich-x86_64 -IEigen3.3.7 -Iinclude/AppEval  -L/usr/lib64/mpich/lib -lhdf5 -o libAppEval.so src/AppEval.cxx

# Compilation of python bindings
g++ -O3 -c pyAppEval.cxx -Dappeval_EXPORTS  -IEigen3.3.7 -I/usr/include/python3.7m -Ipybind11/include -Iinclude/AppEval -fPIC -fvisibility=hidden   -flto -fno-fat-lto-objects -o pyAppEval.o -O3 -fopenmp  -march=native -mtune=native  -DNDEBUG  -std=c++17  -g
g++ -fPIC  -shared  -o appeval.cpython-37m-x86_64-linux-gnu.so pyAppEval.o -flto -lAppEval
