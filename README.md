# PPM Inverter (inverter.cxx)

## Overview
`inverter.cxx` defines a small C++ program and a `PPM` image container for
reading PPM images (`P3` or `P6`) from standard input and printing the parsed
header and pixel values to standard output. The code enforces bounds on image
dimensions and color depth.

## Features
- Supports PPM magic numbers `P3` (ASCII) and `P6` (binary)
- Enforces limits on width, height, and maximum color value
- Outputs image metadata and pixel values

## Build
```cpp
g++ -std=c++23 -O2 -Wall -Wextra -pedantic inverter.cxx -o inverter
```

## Usage
```cpp
./inverter < cat.ppm > out.ppm
