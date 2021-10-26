#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "filter.h"
#include "vector_utils.h"
#include "math.h"

using boost::property_tree::ptree;

int main(int argc, char* argv) {
    VecType b({1.0/3.0, 1.0/3.0, 1.0/3.0});
    VecType a({1.0});
    Filter filt1(b, a);

    ptree pt;

    read_json("filter_coeffs.json", pt);
    ptree fc1 = pt.get_child("LowPassFilter");
    Filter filt2(fc1);

    VecType tt = arange(0, 10, 0.01);
    VecType x;
    VecType y;
    VecType y2;
    x.resize(tt.size());
    y.resize(tt.size());
    y2.resize(tt.size());

    double f1 = 10;
    double f2 = 1.5;

    for (int i(0); i < tt.size(); i++) {
        x[i] = sin(TWOPI*f1*tt[i]) + sin(TWOPI*f2*tt[i]);
    }
    for (int i(0); i < tt.size(); i++) {
        y[i] = filt1.run(x[i]);
        y2[i] = filt2.run(x[i]);
    }

    std::cout << "Running filter_app::main()!" << std::endl;
    std::vector<VecType> vecs({tt,x,y,y2});
    std::vector<std::string> headers({"tt", "x", "y", "y2"});
    to_csv(vecs, headers, "data.csv");
    
    return 0;
}