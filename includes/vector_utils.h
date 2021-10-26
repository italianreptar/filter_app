#ifndef __CNAP_UTILS_H_
#define __CNAP_UTILS_H_

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/chrono.hpp>

#define _USE_MATH_DEFINES
#define TWOPI M_PI*2

typedef std::vector<double> VecType;

void to_csv(std::vector<VecType> vecs_to_print, std::vector<std::string> headers, std::string fname) {
    if (vecs_to_print.size() != headers.size()) {
        throw std::exception("Must be the same number of headers as vectors!");
    }
    int num_cols = vecs_to_print.size();

    size_t max_vec_len = 0;
    for (int col = 0; col < num_cols; col++) {
        max_vec_len = ( vecs_to_print[col].size() > max_vec_len ) ? vecs_to_print[col].size() : max_vec_len;
    }

    // Open File
    std::ofstream fh;
    fh.open(fname);

    // Print headers
    for (int col = 0; col < num_cols; col++) {
        if (col != num_cols-1) {
            fh << headers[col] + ",";
        } else {
            fh << headers[col];
        }
    }
    fh << "\n";

    // Print body
    for (int row = 0; row < max_vec_len; row++) {
        for (int col = 0; col < num_cols; col++) {
            if ( col != num_cols - 1 ) {
                if ( row < vecs_to_print[col].size() ) {
                    fh << std::setprecision(9);
                    fh << vecs_to_print[col][row] << ",";
                } else {
                    fh << ",";
                }
            } else {
                if ( row < vecs_to_print[col].size() ) {
                    fh << std::setprecision(9);
                    fh << vecs_to_print[col][row];
                }
            }
        }
        fh << "\n";
    }
    fh.close();
}

VecType arange(double start, double end, double step) {
    if ( step == 0 ) {
        throw std::exception("Step must be non-zero.");
    } else if ( step > 0 ) {
        if ( start > end ) {
            throw std::exception("Start must be less than end with step > 0.");
        }
    } else {
        if ( end < start ) {
            throw std::exception("End must be less than start with step < 0.");
        }
    }
    size_t vec_size = std::floor((end - start) / step) + 1;
    VecType out;
    out.resize(vec_size);

    for (int i(0); i < vec_size; i++) {
        out[i] = start + i*step;
    }
    return out;
}

VecType linspace(double start, double end, size_t num_steps) {
    if ( num_steps <= 0 ) {
        throw std::exception("num_steps must be positive definite.");
    } 

    VecType out;
    out.reserve(num_steps);
    double step_size = (end - start) / num_steps;
    for (int i(0); i < num_steps; i++) {
        out[i] = start + step_size*i;
    }
    return out;
}


#endif  // __CNAP_UTILS_H_