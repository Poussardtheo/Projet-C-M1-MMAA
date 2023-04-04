#ifndef PPM_IMAGE_HPP
#define PPM_IMAGE_HPP

#include <string>

class ppm_image {
    unsigned char *m_rgb_data;
    int m_width;
    int m_height;

public:
    ppm_image(const std::string& filename);
    ~ppm_image();

    const unsigned char* rgb_data() const { return m_rgb_data; }
    int width() const { return m_width; }
    int height() const { return m_height; }
};

void write_ppm_image(const std::string& filename, int width, int height, const unsigned char *rgb_data);

#endif // PPM_IMAGE_HPP
