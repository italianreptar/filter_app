# How to build:

``` bash
cd build
cmake ..
cmake --build . --target filter_app
```

## Current Functionality:

Allows user to create and use a filter to filter data.

## TODO:

- Get boost working to be able to use property tree input
- Make a python app to write filter coefficients to a json
- Wrap the filter class with an actuator class which works as a linear filter

## Potential Project ideas:

- Update overall framework be more package-like
- vector-utils, filter, actuator, io
- Unicycle problem controls with linear actuators
- Do some dubins path planning, and control based off the path
- Create a longitudinal autopilot loop in cpp and python, using an RC planes aero model
