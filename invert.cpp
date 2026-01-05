/**
 * @file   inverter.cxx
 * @author GZ <gaelxarco@icloud.com>
 * @brief  Inverts colors from .ppm images
 */

#include <iostream>
#include <print>
#include <expected>

import ppm;

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main() {
    /// PPM image
    std::expected<PPM, PPM::Error> ppm = read_ppm(std::cin);

    if (!ppm) {
        std::println("[ERR] {}", ppm.error().msg);
        return 1;
    }

    PPM& img = *ppm;          /// Validated PPM image
    img.invert();
    img.out_ppm(std::cout);

    return 0;
}           // main

// EOF inverter.cxx
