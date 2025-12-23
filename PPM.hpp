/**
 * @file   PPM.hpp
 * @author GZ <gaelxarco@icloud.com>
 * @brief  PPM image ADT with implementations
 */

#ifndef PPM_HPP
#define PPM_HPP

#include <cstdint>      // uint8_t, uint16_t
#include <cstddef>      // size_t
#include <vector>
#include <string>
#include <cassert>
#include <stdexcept>
#include <expected>
#include <print>
#include <iostream>

/// @brief PPM image
class PPM {
public:
    static constexpr std::size_t MAX_WIDTH       = 1920;
    static constexpr std::size_t MAX_HEIGHT      = 1080;
    static constexpr std::size_t MAX_COLOR_VALUE = 65'536;

    using data_type = std::uint16_t;            /// Data type for pixels
    using size_type = std::size_t;              /// Size types
    using reference = data_type&;               /// Data type reference
    using pointer = data_type*;                 /// Data type pointer
    using const_pointer = const data_type*;     /// Const data type pointer

    /// @brief PPM error
    struct Error { std::string msg; };
    /// @brief Magic num
    enum class MagicNum { P3, P6 };

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
    size_type max = 0, std::vector<data_type> d = {});

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
    void clear() { m_data.clear(); }
    /**
     * @brief  Reads a PPM image from std::istream and returns expected value of
     *         PPM or PPM::Error
     * @param  is Input stream reference
     * @return expected value of PPM or PPM::Error
     */
    friend std::expected<PPM, PPM::Error> read_ppm(std::istream& is);

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
     * @brief  Inverts color values
     * @return m_max
     */
    void invert(void) { for (auto& i : m_data) { i = get_max() - i; } }

    /**
     * @brief  Returns iterator to m_data
     * @return iterator to m_data
     */
    auto begin(void) noexcept { return m_data.begin(); }
    /**
     * @brief  Returns const iterator to m_data
     * @return const iterator to m_data
     */
    auto begin(void) const noexcept { return m_data.begin(); }
    /**
     * @brief  Returns iterator to el past m_data
     * @return iterator to one el past m_data
     */
    auto end(void) noexcept { return m_data.end(); }
    /**
     * @brief  Returns const iterator to el past m_data
     * @return const iterator to one el past m_data
     */
    auto end(void) const noexcept { return m_data.end(); }
    /**
     * @brief Prints image data as unsigned int
     */
    void out_ppm(std::ostream& os) const;

private:
    MagicNum m_magic;                       /// Magic num
    size_type m_width;                      /// Width
    size_type m_height;                     /// Height
    size_type m_max;                        /// Max color value
    std::vector<data_type> m_data;          /// Vector of color values
};          // PPM

// -----------------------------------------------------------------------------
// MEMBER DEFINITION(S)
// -----------------------------------------------------------------------------

PPM::PPM(PPM::MagicNum m, PPM::size_type w, PPM::size_type h,
PPM::size_type max, std::vector<PPM::data_type> d)
{
    assert(m == PPM::MagicNum::P3 || m == PPM::MagicNum::P6);
    assert(w <= MAX_WIDTH);
    assert(h <= MAX_HEIGHT);
    assert(max <= MAX_COLOR_VALUE);

    if (m != PPM::MagicNum::P3 && m != PPM::MagicNum::P6) {
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
}           // PPM

void PPM::out_ppm(std::ostream& os) const {
    os << (static_cast<int>(get_magic()) == 0 ? "P3" : "P6") << '\n';
    os << get_width() << ' ' << get_height() << '\n';
    os << get_max() << '\n';

    if (get_max() <= 255) {
        for (auto v : m_data) {
            unsigned char b = static_cast<unsigned char>(v);
            os.write(reinterpret_cast<const char*>(&b), 1);
        }
    } else {
        for (auto v : m_data) {
            // big-endian
            unsigned char bytes[2]{
                static_cast<unsigned char>((v >> 8) & 0xFF),
                static_cast<unsigned char>(v & 0xFF)
            };
            os.write(reinterpret_cast<const char*>(bytes), 2);
        }
    }
}           // out_ppm

std::expected<PPM, PPM::Error> read_ppm(std::istream& is) {
    std::string m{};                /// Holds magic num from is
    PPM::size_type w{};             /// Holds width from is
    PPM::size_type h{};             /// Holds height from is
    PPM::size_type max{};           /// Holds max color value from is

    if (!(is >> m) || (m != "P3" && m != "P6"))
        return std::unexpected(PPM::Error{"Invalid magic number from input"});

    if (!(is >> w) || w > PPM::MAX_WIDTH)
        return std::unexpected(PPM::Error{"Invalid width from input"});

    if (!(is >> h) || h > PPM::MAX_HEIGHT)
        return std::unexpected(PPM::Error{"Invalid height from input"});

    if (!(is >> max) || max > PPM::MAX_COLOR_VALUE)
        return std::unexpected(PPM::Error{"Invalid max color val from input"});

    /// Total per-pixel RGB color values
    const PPM::size_type samples = w * h * 3;
    PPM img{};                      /// Holds image
    img.set_magic_num(m == "P3" ? PPM::MagicNum::P3 : PPM::MagicNum::P6);
    img.set_width(w);
    img.set_height(h);
    img.set_max(max);
    img.clear();

    if (m != "P6") {
        int v;                      /// Holds current pixel RGB value

        for (PPM::size_type i{}; i < samples; ++i) {
            if (!(is >> v))
                return std::unexpected(PPM::Error{"Unexpected EOF in P3 data"});
            if (v > max)
                return std::unexpected(PPM::Error{
                    "P3 color value out of range"
                });
            img.push_back(static_cast<PPM::data_type>(v));
        }

        return img;
    }

    // Ignore any whitespace after max before binary data begins
    is.ignore(255, '\n');

    if (max <= 255) {
        // 8-bit samples
        for (PPM::size_type i{}; i < samples; ++i) {
           std::uint8_t b = 0;
            if (!is.read(reinterpret_cast<char*>(&b), 1))
                return std::unexpected(PPM::Error{"Unexpected EOF in P6 data (8-bit)"});
            img.push_back(static_cast<PPM::data_type>(b));
        }
    } 

    if (max > 255) {
        // 16-bit samples
        for (PPM::size_type i{}; i < samples; ++i) {
            std::uint8_t hi = 0;
            std::uint8_t lo = 0;
            if (!is.read(reinterpret_cast<char*>(&hi), 1) ||
                !is.read(reinterpret_cast<char*>(&lo), 1))
                return std::unexpected(PPM::Error{"Unexpected EOF in P6 data (16-bit)"});

            /// Holds current pixel RGB value
            std::uint16_t v =
                (static_cast<std::uint16_t>(hi) << 8) |
                static_cast<std::uint16_t>(lo);

            if (v > max)
                return std::unexpected(PPM::Error{"P6 color value out of range"});

            img.push_back(static_cast<PPM::data_type>(v));
        }
    }

    return img;
}           // read_ppm

#endif      // PPM_HPP

// EOF PPM.hpp
