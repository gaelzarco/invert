# PPM Inverter (inverter.cxx)

## Overview
`inverter.cxx` defines a small C++ program and a `PPM` image container for
reading PPM images (`P3` or `P6`) from standard input and printing the parsed
header and pixel values to standard output. The code enforces bounds on image
dimensions and color depth.

## Features
- Supports PPM magic numbers `P3` (ASCII) and `P6` (binary)
- Enforces limits on width, height, and maximum color value
- Stream extraction operator (`operator>>`) for loading PPM data
- Outputs image metadata and pixel values line by line

## Build
```cpp
g++ -std=c++17 -O2 -Wall -Wextra -pedantic inverter.cxx -o inverter
```

## Usage
```cpp
./inverter < input.ppm > output.txt
```

## Notes
- The program currently does not perform color inversion despite the filename.
- Binary `P6` data is not correctly handled due to formatted stream extraction.
- The magic number is printed as an enum value, not as `P3` or `P6`.- The magic number is printed as an enum value, not as `P3` or `P6`.# PPM Inverter (inverter.cxx)
