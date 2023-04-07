#ifndef PPM_IMAGE_HPP
#define PPM_IMAGE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class pixel {
public:
    pixel() : r(0), g(0), b(0) {}
    pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}
    
    int r, g, b;
};

class ppm_image {
    std::vector<pixel> m_data;
    std::vector<pixel> m_rgb_data;
    int m_width;
    int m_height;

public:
    ppm_image(const std::string& filename);
    // ~ppm_image();

    std::vector<pixel> rgb_data() { return m_rgb_data; }
    int width() const { return m_width; }
    int height() const { return m_height; }
    const pixel& get_pixel(int x, int y) const { return m_data[y * m_width + x]; }

};

void write_ppm_image(const std::string& filename, int width, int height, std::vector<pixel> rgb_data);



#endif // PPM_IMAGE_HPP
