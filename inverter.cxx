/**
 * @file   inverter.cxx
 * @author GZ <gaelxarco@icloud.com>
 * @brief  Inverts colors from .ppm images
 */

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

// -----------------------------------------------------------------------------
// GLOBAL CONSTANT(S)
// -----------------------------------------------------------------------------

const std::size_t MAX_WIDTH       = 1920;           /// Max ppm width
const std::size_t MAX_HEIGHT      = 1080;           /// Max ppm height
const std::size_t MAX_COLOR_VALUE = 65'536;         /// Max ppm color value

// -----------------------------------------------------------------------------
// DATA TYPE(S)
// -----------------------------------------------------------------------------

/// @brief PPM image struct
struct PPM {
    using data_type = int;
    using size_type = std::size_t;

    /// @brief Enum for magic num
    enum class MagicNum {
        P3,
        P6
    };

    /**
     * @brief     Default constructor
     * @param     m Magic num
     * @param     w Width
     * @param     h Height
     * @param     d Pixel color values vector
     * @exception std::runtime_error If magic num is not P3 or P6
     * @exception std::overflow_error If w, h, or max are too large
     */
    PPM(MagicNum m = MagicNum::P3, size_type w = 0, size_type h = 0,
    size_type max = 0, std::vector<data_type> d = {0}) {
        assert(m == MagicNum::P3 || m == MagicNum::P6);
        assert(w <= MAX_WIDTH);
        assert(h <= MAX_HEIGHT);
        assert(max <= MAX_COLOR_VALUE);

        if (m != MagicNum::P3 && m != MagicNum::P6) {
            throw std::invalid_argument("PPM magic num is not P3 or P6");
        }
        if (w > MAX_WIDTH) {
            throw std::overflow_error("PPM width too large (MAX 1920)");
        }
        if (h > MAX_HEIGHT) {
            throw std::overflow_error("PPM height too large (MAX 1080)");
        }
        if (max > MAX_COLOR_VALUE) {
            throw std::overflow_error("PPM max color value over 65536");
        }

        m_magic = m;
        m_width = w;
        m_height = h;
        m_max = max;
        m_data = d;
    }

    MagicNum m_magic;                       /// Magic num
    size_type m_width;                      /// Width
    size_type m_height;                     /// Height
    size_type m_max;                        /// Max color value
    std::vector<data_type> m_data;          /// Vector of color values
};          // PPM

// -----------------------------------------------------------------------------
// PROTOTYPE(S)
// -----------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, PPM& img);

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main(int argc, char** argv) {
    PPM ppm;

    try {
        std::cin >> ppm;
    } catch (std::exception& e) {
        std::cout << "[ERR] " << e.what() << '\n';
    }

    std::cout << static_cast<int>(ppm.m_magic) << '\n';
    std::cout << ppm.m_width << '\n';
    std::cout << ppm.m_height << '\n';
    std::cout << ppm.m_max << '\n';

    for (PPM::data_type& i : ppm.m_data) {
        std::cout << i << '\n';
    }
}           // main

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

/**
 * @brief     Overloaded >> op for populating a PPM image
 * @param     is Input stream reference
 * @param     img PPM object
 * @exception std::runtime_error If magic num, width, or height are invalid
 * @return    input stream reference
 */
std::istream& operator>>(std::istream& is, PPM& img) {
    std::string m;              /// Holds magic num from is
    PPM::size_type w;           /// Holds width from is
    PPM::size_type h;           /// Holds height from is
    PPM::size_type max;         /// Holds max color value from is
    PPM::data_type c;           /// Holds color value from is

    is >> m;

    if (m == "P3") {
        img.m_magic = PPM::MagicNum::P3;
    } else if (m == "P6") {
        img.m_magic = PPM::MagicNum::P6;
    } else {
        throw std::runtime_error("Invalid magic number from input");
    }

    if (!(is >> w) || w > MAX_WIDTH) {
        throw std::runtime_error("Invalid width from input");
    }

    img.m_width = w;

    if (!(is >> h) || h > MAX_HEIGHT) {
        throw std::runtime_error("Invalid height from input");
    }

    img.m_height = h;

    if (!(is >> max) || max > MAX_COLOR_VALUE) {
        throw std::runtime_error("Invalid max color value from input");
    }

    img.m_max = max;

    while (is >> c) {
        img.m_data.push_back(c);
    }

    return is;
}           // operator>>

// EOF inverter.cxx
