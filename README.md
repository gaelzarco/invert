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
make
```

## Clean
```cpp
make clean
```

## Usage
```cpp
./build/inverter < ./assets/cat.ppm > ./assets/out.ppm
display ./assets/out,ppm    // LINUX
```
