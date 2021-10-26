#include <iostream>

#include <boost>

#include "utils.h"
#include "math.h"

int main(int argc, char* argv) {
    VecType b({1.0/3.0, 1.0/3.0, 1.0/3.0});
    VecType a({1.0});
    Filter my_filt(b, a);

    VecType tt = arange(0, 10, 0.01);
    VecType x;
    VecType y;
    x.resize(tt.size());
    y.resize(tt.size());

    double f1 = 10;
    double f2 = 1.5;

    for (int i(0); i < tt.size(); i++) {
        x[i] = sin(TWOPI*f1*tt[i]) + sin(TWOPI*f2*tt[i]);
    }
    for (int i(0); i < tt.size(); i++) {
        y[i] = my_filt.run(x[i]);
    }

    std::cout << "test_app!" << std::endl;
    std::vector<VecType> vecs({tt,x,y});
    std::vector<std::string> headers({"tt", "x", "y"});
    to_csv(vecs, headers, "data.csv");
    
    return 0;
}