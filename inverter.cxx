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
class PPM {
public:
    using data_type = int;
    using size_type = std::size_t;
    using reference = data_type&;
    using size_reference = size_type&;
    using pointer = data_type*;
    using const_pointer = const data_type*;

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
    explicit PPM(MagicNum m = MagicNum::P3, size_type w = 0, size_type h = 0,
    size_type max = 0, std::vector<data_type> d = {}) {
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

    /**
     * @brief Sets magic number
     * @param value data
     */
    void set_magic_num(MagicNum value) noexcept { m_magic = value; }
    /**
     * @brief Sets image width
     * @param value num
     */
    void set_width(size_type value) noexcept { m_width = value; }
    /**
     * @brief Sets image height
     * @param value width
     */
    void set_height(size_type value) noexcept { m_height = value; }
    /**
     * @brief Sets max color value
     * @param value height
     */
    void set_max(size_type value) noexcept { m_max = value; }
    /**
     * @brief Pushes value into m_data
     * @param value value to push
     */
    void push_back(data_type value) { m_data.push_back(value); }
    /**
     * @brief Clears m_data
     */
    void clear_data() { m_data.clear(); }

    /**
     * @brief  Gets m_magic
     * @return m_magic
     */
    MagicNum get_magic(void) const noexcept { return m_magic; }
    /**
     * @brief  Gets width
     * @return m_width
     */
    size_type get_width(void) const noexcept { return m_width; }
    /**
     * @brief  Gets height
     * @return m_height
     */
    size_type get_height(void) const noexcept { return m_height; }
    /**
     * @brief  Gets max color value
     * @return m_max
     */
    size_type get_max(void) const noexcept { return m_max; }

    /**
     * @brief  Returns iterator to m_data
     * @return iterator to m_data
     */
    auto begin(void) noexcept { return m_data.begin(); }
    /**
     * @brief  Returns const iterator to m_data
     * @return const iterator to m_data
     */
    auto cbegin(void) const noexcept { return m_data.cbegin(); }
    /**
     * @brief  Returns iterator to el past m_data
     * @return iterator to one el past m_data
     */
    auto end(void) noexcept { return m_data.end(); }
    /**
     * @brief  Returns const iterator to el past m_data
     * @return const iterator to one el past m_data
     */
    auto cend(void) const noexcept { return m_data.cend(); }

private:
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

    std::cout << static_cast<int>(ppm.get_magic()) << '\n';
    std::cout << ppm.get_width() << '\n';
    std::cout << ppm.get_height() << '\n';
    std::cout << ppm.get_max() << '\n';

    for (const PPM::data_type& i : ppm) {
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

    if (!(is >> m) && (m != "P3" && m != "P6")) {
        throw std::runtime_error("Invalid magic number from input")
    }

    if (!(is >> w) || w > MAX_WIDTH) {
        throw std::runtime_error("Invalid width from input");
    }

    if (!(is >> h) || h > MAX_HEIGHT) {
        throw std::runtime_error("Invalid height from input");
    }

    if (!(is >> max) || max > MAX_COLOR_VALUE) {
        throw std::runtime_error("Invalid max color value from input");
    }


    if (m == "P3") {
        img.set_magic_num(PPM::MagicNum::P3);
    } else if (m == "P6") {
        img.set_magic_num(PPM::MagicNum::P6);
    }

    img.set_width(w);
    img.set_height(h);
    img.set_max(max);
    img.clear_data();

    while (is >> c) {
        img.push_back(c);
    }

    return is;
}           // operator>>

// EOF inverter.cxx
