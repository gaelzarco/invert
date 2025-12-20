/**
 * @file   PPM.hpp
 * @author GZ <gaelxarco@icloud.com>
 * @brief  PPM image ADT with implementations
 */

#ifndef PPM_HPP
#define PPM_HPP

#include <cstdint>      // uint16_t
#include <cstddef>      // size_t
#include <vector>
#include <string>
#include <cassert>
#include <stdexcept>

/// @brief PPM image
class PPM {
public:
    inline static constexpr std::size_t MAX_WIDTH       = 1920;
    inline static constexpr std::size_t MAX_HEIGHT      = 1080;
    inline static constexpr std::size_t MAX_COLOR_VALUE = 65'536;

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

#endif      // PPM_HPP

// EOF PPM.hpp
