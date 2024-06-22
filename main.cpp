#include <iostream>
#include <Python.h>
#include <sys/time.h>

/**
results of test (10 000 000 iterations)
time python 1.35321 sec
time c++ 0.0153279 sec
 */

double microtime() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec)/1000000.0;
}

float minx = 0;

void a_test_method(float x, float y, float z, float a, float b, float c, float u, float v, float w) {
    if (minx<x) minx = x;
}

void call_with_python() {
    float x = 1.0, y = 2.0, z = 3.0, a, b, c, u, v, w;
    PyObject *args = Py_BuildValue( "fffffffff",
                            x, y, z, a, b, c, u, v, w);
    if(args == NULL) {
        std::cerr << "could not buildValue";
        return;
    }

    a_test_method(x,y,z,a,b,c,u,v,w);

    if (!PyArg_ParseTuple(args, "fffffffff",
                  &x, &y, &z, &a, &b, &c, &u, &v, &w)) {
        std::cerr << "could not Py_ParseTuple";
        return;

    }

    Py_XDECREF(args);

}


int main() {

    Py_Initialize();

    // testing with python build/parse
     double tm = microtime();

     for (int i = 0; i < 10000000; i++) {
         call_with_python();
     }

     std::cout << "time python " << microtime() - tm << std::endl;

    // c++ calls without this
     tm = microtime();

     for (int i = 0; i < 10000000; i++) {
         a_test_method(1,2,3,0,0,0, 1,2,3);
     }

     std::cout << "time c++ " << microtime() - tm << std::endl;

     return 0;
}

