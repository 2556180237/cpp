#pragma once
#include <vector>
#include <string>
#include <cstdint>

/**
 * Embedded PNG encoder/decoder with no external runtime dependencies.
 * Supports RGB24 input (8 bits per channel). RGBA input is accepted and
 * converted to RGB by dropping the alpha during decoding.
 */
class PngCodec {
public:
    // Image container
    struct Image {
        std::vector<uint8_t> data;  // RGB bytes (R,G,B,R,G,B,...)
        uint32_t width;
        uint32_t height;
        
        Image() : width(0), height(0) {}
        Image(uint32_t w, uint32_t h) : data(w * h * 3), width(w), height(h) {}
        
        // Access pixel components by coordinates
        uint8_t& r(uint32_t x, uint32_t y) { return data[(y * width + x) * 3 + 0]; }
        uint8_t& g(uint32_t x, uint32_t y) { return data[(y * width + x) * 3 + 1]; }
        uint8_t& b(uint32_t x, uint32_t y) { return data[(y * width + x) * 3 + 2]; }
        
        const uint8_t& r(uint32_t x, uint32_t y) const { return data[(y * width + x) * 3 + 0]; }
        const uint8_t& g(uint32_t x, uint32_t y) const { return data[(y * width + x) * 3 + 1]; }
        const uint8_t& b(uint32_t x, uint32_t y) const { return data[(y * width + x) * 3 + 2]; }
    };

    /**
     * Save image to a PNG file.
     * @param filename output path
     * @param image image data (RGB)
     * @return true on success, false on failure
     */
    static bool encode(const std::string& filename, const Image& image);
    
    /**
     * Load image from a PNG file.
     * @param filename input path
     * @param image output image data (RGB)
     * @return true on success, false on failure
     */
    static bool decode(const std::string& filename, Image& image);
    
    /**
     * Compare two images pixel-by-pixel.
     * @return number of differing pixels (0 if identical), or UINT64_MAX on size mismatch
     */
    static uint64_t compare(const Image& img1, const Image& img2);

private:
    // PNG helpers
    static uint32_t crc32_update(uint32_t crc, const uint8_t* data, size_t len);
    static uint32_t adler32(const uint8_t* data, size_t len);
    static void writeUint32BE(std::vector<uint8_t>& buffer, uint32_t value);
    static void writeChunk(std::vector<uint8_t>& buffer, const char* type, const uint8_t* data, size_t len);
    static bool compressData(const uint8_t* data, size_t len, std::vector<uint8_t>& compressed);
};
