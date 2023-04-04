#include "hough_transform.hpp"

HoughTransform::HoughTransform(int num_theta_bins, int num_rho_bins, int threshold)
    : num_theta_bins_(num_theta_bins), num_rho_bins_(num_rho_bins), threshold_(threshold)
{}

void HoughTransform::transform(const ppm_image& image) {
    initialize_accumulator(image);
    perform_transform(image);
    
    lines_.clear();
    for (unsigned int i = 0; i < accumulator_.size(); ++i) {
        for (unsigned int j = 0; j < accumulator_[i].size(); ++j) {
            if (accumulator_[i][j] > threshold_) {
                double theta = static_cast<double>(i) / num_theta_bins_ * M_PI;
                double rho = static_cast<double>(j) / num_rho_bins_ * sqrt(image.width() * image.width() + image.height() * image.height());
                lines_.push_back({theta, rho});
            }
        }
    }
}

std::vector<std::pair<double, double>> HoughTransform::detect_lines() const {
    return lines_;
}

void HoughTransform::initialize_accumulator(const ppm_image& image) {
    accumulator_.resize(num_theta_bins_);
    for (int i = 0; i < num_theta_bins_; ++i) {
        accumulator_[i].resize(num_rho_bins_);
    }
}

void HoughTransform::perform_transform(const ppm_image& image) {
    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            if (image.get_pixel(x, y).r == 255) {
                for (int i = 0; i < num_theta_bins_; ++i) {
                    double theta = static_cast<double>(i) / num_theta_bins_ * M_PI;
                    double rho = x * cos(theta) + y * sin(theta);
                    int j = static_cast<int>(rho / (sqrt(image.width() * image.width() + image.height() * image.height()) / num_rho_bins_)) + num_rho_bins_ / 2;
                    if (j >= 0 && j < num_rho_bins_) {
                        ++accumulator_[i][j];
                    }
                }
            }
        }
    }
}
