# PPM Inverter (inverter.cxx)

## Overview
`inverter.cxx` defines a small C++ program and a `PPM` image container for
reading PPM images (`P3` or `P6`) from standard input and printing the parsed
header and pixel values to standard output. The code enforces bounds on image
dimensions and color depth.

## Features
- Parses and emits valid PPM images (`P3` ASCII and `P6` binary).
- Implements a `PPM` image abstraction with bounds checking.
- Inverts pixel color values while preserving image metadata.
- Supports 8-bit and 16-bit color depths.
- Enforces maximum width, height, and color value constraints.
- Performs I/O via `std::istream` / `std::ostream`.
- Modern error handling using `std::expected`.
- Utilizes C++ modules.

## Build
```sh
make
```

## Clean
```sh
make clean
```

## Usage
```sh
build/inverter < assets/cat.ppm > assets/out.ppm
display assets/out.ppm    // LINUX
```
