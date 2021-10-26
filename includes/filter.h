#ifndef __CNAP_FILTER_H_
#define __CNAP_FILTER_H_

#include "vector_utils.h"

#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

class Filter {
 public:
    Filter() {
        _a = {1};
        _b = {1};
        _check_coeffs();

        std::cout << "Default Constructor Called!" << std::endl;
    }

    Filter(VecType& b, VecType& a) {
        _a = a;
        _b = b;
        _check_coeffs();

        std::cout << "Constructor Called!" << std::endl;
    }

    Filter(ptree& pt) {
        for (auto& item : pt.get_child("a")) {
            _a.push_back(item.second.get_value<double>());
        }

        for (auto& item : pt.get_child("b")) {
            _b.push_back(item.second.get_value<double>());
        }

        _check_coeffs();
        std::cout << "PTree Constructor Called!" << std::endl;
    }

    double run(double x) {
        if ( _fb_order > 0 ) {
            // Rotate the buffer one space to the right in prep to use it
            std::rotate(_ybuffer.rbegin(), _ybuffer.rbegin()+1, _ybuffer.rend());
        }
        _ybuffer[0] = 0.0;

        if ( _ff_order > 0 ) {
            // Rotate the buffer one space to the right in prep to use it
            std::rotate(_xbuffer.rbegin(), _xbuffer.rbegin()+1, _xbuffer.rend());
        }
        _xbuffer[0] = x;

        for (int i = 0; i < _ff_order; i++ ) {
            _ybuffer[0] += _b[i]*_xbuffer[i];
        }

        for (int i = 1; i < _fb_order+1; i++ ) {
            _ybuffer[0] -= _a[i]*_ybuffer[i];
        }

        return _ybuffer[0];
    }

    std::vector<double> a() {
        return _a;
    }

    std::vector<double> b() {
        return _b;
    }

 private:
    /*
    ** Class Members:
    */
    size_t _fb_order;
    size_t _ff_order;

    VecType _b;
    VecType _a;
    VecType _xbuffer;
    VecType _ybuffer;
    // std::vector<double> _state;

 private:
    /*
    ** Class Private Functions
    */
    void _check_coeffs(void) {
        if ( _a.size() > 0 ) {
            if ( _a[0] != 0 ) {
                for (int i = 0; i < _a.size(); i++) {
                    _a[i] = _a[i] / _a[0];
                    if ( i < _b.size() ) {
                        _b[i] = _b[i] / _a[0];
                    }
                }
            } else {
                throw std::exception("a[0] cannot be 0.");
            }
        }
        _fb_order = _a.size() - 1;
        _ff_order = _b.size();
        _xbuffer.resize(_ff_order);
        _ybuffer.resize(_fb_order + 1);

        // Initialize a null buffer
        for (int i(0); i < _ybuffer.size(); i++) {
            _ybuffer[i] = 0;
        }

        for (int i(0); i < _xbuffer.size(); i++) {
            _xbuffer[i] = 0;
        }
    }
};

#endif  // __CNAP_FILTER_H_