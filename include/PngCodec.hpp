#pragma once
#include <vector>
#include <string>
#include <cstdint>

class PngCodec {
public:
    struct Image {
        std::vector<uint8_t> data;
        uint32_t width;
        uint32_t height;
        
        Image() : width(0), height(0) {}
        Image(uint32_t w, uint32_t h) : data(w * h * 3), width(w), height(h) {}
        
        uint8_t& r(uint32_t x, uint32_t y) { 
            return data[(y * width + x) * 3 + 0]; 
        }
        uint8_t& g(uint32_t x, uint32_t y) { 
            return data[(y * width + x) * 3 + 1]; 
        }
        uint8_t& b(uint32_t x, uint32_t y) { 
            return data[(y * width + x) * 3 + 2]; 
        }
        
        const uint8_t& r(uint32_t x, uint32_t y) const { 
            return data[(y * width + x) * 3 + 0]; 
        }
        const uint8_t& g(uint32_t x, uint32_t y) const { 
            return data[(y * width + x) * 3 + 1]; 
        }
        const uint8_t& b(uint32_t x, uint32_t y) const { 
            return data[(y * width + x) * 3 + 2]; 
        }
    };

    static bool encode(const std::string& filename, const Image& image);
    static bool decode(const std::string& filename, Image& image);
    static uint64_t compare(const Image& img1, const Image& img2);

private:
    static uint32_t crc32_update(uint32_t crc, const uint8_t* data, size_t len);
    static uint32_t adler32(const uint8_t* data, size_t len);
    static void writeUint32BE(std::vector<uint8_t>& buffer, uint32_t value);
    static void writeChunk(std::vector<uint8_t>& buffer, const char* type, const uint8_t* data, size_t len);
    static bool compressData(const uint8_t* data, size_t len, std::vector<uint8_t>& compressed);
};
