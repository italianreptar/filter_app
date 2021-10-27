# How to build:

``` bash
mkdir -p build
cd build
cmake ..
cmake --build . --target filter_app
```

## Current Functionality:

Allows user to create and use an LIT IIR filter to filter data. This filter must be ran repeatedly at a constant rate with using coefficients generated using any existing method.  The filter adjusts the order and buffer size automatically, making utilizing the filter as easy as the MATLAB filter function, but this code is not yet optimized.

## TODO:

- Make a python app to *write* filter coefficients to a json
- Wrap the filter class with an actuator class which works as a linear filter

## Potential Project ideas:

- actuator control loop
- Unicycle problem controls with linear actuators
    - Dubins path planning, and control using the path for guidance
- Create a longitudinal autopilot loop in cpp and python, using an RC planes aero model
