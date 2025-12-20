/**
 * @file   inverter.cxx
 * @author GZ <gaelxarco@icloud.com>
 * @brief  Inverts colors from .ppm images
 */

#include "PPM.hxx"
#include <cassert>
#include <expected>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <print>

// -----------------------------------------------------------------------------
// FUNCTION PROTOTYPE(S)
// -----------------------------------------------------------------------------

std::expected<PPM, PPM::Error> read_ppm(std::istream& is);
std::istream& operator>>(std::istream& is, PPM& img);

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

    const PPM& img = *ppm;          /// Validated PPM image
    std::println("{}", static_cast<int>(img.get_magic()));
    std::println("{}", img.get_width());
    std::println("{}", img.get_height());
    std::println("{}", img.get_max());

    for (const PPM::data_type& i : img) std::print("{}", i);
    std::println("");

    return 0;
}           // main

// -----------------------------------------------------------------------------
// FUNCTION DEFINITION(S)
// -----------------------------------------------------------------------------

/**
 * @brief  Reads a PPM image from std::istream and returns expected value of PPM
 *         or PPM::Error
 * @param  is Input stream reference
 * @return expected value of PPM or PPM::Error
 */
std::expected<PPM, PPM::Error> read_ppm(std::istream& is) {
    std::string m{};                /// Holds magic num from is
    PPM::size_type w{};             /// Holds width from is
    PPM::size_type h{};             /// Holds height from is
    PPM::size_type max{};           /// Holds max color value from is
    PPM::data_type c{};             /// Holds color value from is

    if (!(is >> m) || (m != "P3" && m != "P6"))
        return std::unexpected(PPM::Error{"Invalid magic number from input"});

    if (!(is >> w) || w > PPM::MAX_WIDTH)
        return std::unexpected(PPM::Error{"Invalid width from input"});

    if (!(is >> h) || h > PPM::MAX_HEIGHT)
        return std::unexpected(PPM::Error{"Invalid height from input"});

    if (!(is >> max) || max > PPM::MAX_COLOR_VALUE)
        return std::unexpected(PPM::Error{"Invalid max color val from input"});

    PPM img{};                      /// Holds image
    img.set_magic_num(m == "P3" ? PPM::MagicNum::P3 : PPM::MagicNum::P6);
    img.set_width(w);
    img.set_height(h);
    img.set_max(max);
    img.clear();

    while (is >> c) img.push_back(c);

    return img;
}           // read_ppm

/**
 * @brief     Overloaded >> op for populating a PPM image
 * @param     is Input stream reference
 * @param     img PPM object
 * @exception std::runtime_error If magic num, width, or height are invalid
 * @return    input stream reference
 * 
 * @note      DEPRECATED!!!
 * 
 */
std::istream& operator>>(std::istream& is, PPM& img) {
    std::string m{};              /// Holds magic num from is
    PPM::size_type w{};           /// Holds width from is
    PPM::size_type h{};           /// Holds height from is
    PPM::size_type max{};         /// Holds max color value from is
    PPM::data_type c{};           /// Holds color value from is

    if (!(is >> m) || (m != "P3" && m != "P6"))
        throw std::runtime_error("Invalid magic number from input");
    if (!(is >> w) || w > PPM::MAX_WIDTH)
        throw std::runtime_error("Invalid width from input");
    if (!(is >> h) || h > PPM::MAX_HEIGHT)
        throw std::runtime_error("Invalid height from input");
    if (!(is >> max) || max > PPM::MAX_COLOR_VALUE)
        throw std::runtime_error("Invalid max color val from input");

    img.set_magic_num(m == "P3" ? PPM::MagicNum::P3 : PPM::MagicNum::P6);
    img.set_width(w);
    img.set_height(h);
    img.set_max(max);
    img.clear();

    while (is >> c) img.push_back(c);

    return is;
}           // operator>>

// EOF inverter.cxx
