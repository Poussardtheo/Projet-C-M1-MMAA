#ifndef HOUGH_TRANSFORM_HPP
#define HOUGH_TRANSFORM_HPP

#include <vector>
#include <cmath>

#include "ppm_image.hpp"

class HoughTransform {
public:
    HoughTransform(int num_theta_bins, int num_rho_bins, int threshold);
    
    void transform(ppm_image& image);
    std::vector<std::pair<double, double>> detect_lines() const;
    
private:
    int num_theta_bins_;
    int num_rho_bins_;
    int threshold_;
    
    std::vector<std::vector<int>> accumulator_;
    std::vector<std::pair<double, double>> lines_;
    
    void initialize_accumulator(const ppm_image& image);
    void perform_transform(const ppm_image& image);
};

#endif // HOUGH_TRANSFORM_HPP