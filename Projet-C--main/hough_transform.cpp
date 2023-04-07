#include "hough_transform.hpp"
#include <sstream>
using namespace std;

HoughTransform::HoughTransform(int num_theta_bins, int num_rho_bins, int threshold)
    : num_theta_bins_(num_theta_bins), num_rho_bins_(num_rho_bins), threshold_(threshold)
{}

void HoughTransform::transform(ppm_image& image) {
    initialize_accumulator(image);
    perform_transform(image);

    // Accumulateur
    ofstream acc("accumulator.ppm", ios::binary);
    if (!acc) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << "accumulator.ppm" << endl;
        return;
    }

    acc << "P3\n" << accumulator_.size() << " " << accumulator_[0].size() << "\n255\n";

   for (unsigned int i = 0; i < accumulator_.size(); ++i) {
        for (unsigned int j = 0; j < accumulator_[i].size(); ++j) {
            if (accumulator_[i][j] > 0) {
                acc << "255" << "\n"
                    << "255" << "\n"
                    << "255" << "\n";
        
            } else {
                acc << "0" << "\n"
                    << "0" << "\n"
                    << "0" << "\n";
            }
        }   
    }

    // (theta, rho) des droites
    lines_.clear();

    for (unsigned int i = 0; i < accumulator_.size(); ++i) {
        for (unsigned int j = 0; j < accumulator_[i].size(); ++j) {
            if (accumulator_[i][j] > threshold_) {
                /*double theta = static_cast<double>(i *M_PI/ num_theta_bins_ );*/
                /*double rho = x * cos(theta) + y * sin(theta);*/
                /*double rho = static_cast<double>(j) / num_rho_bins_ * sqrt(image.width() * image.width() + image.height() * image.height());*/
                /*double rho = j-num_rho_bins_*/
                lines_.push_back({i, j});
            }
        }
    }

    // Lignes à part
    for( int k = 0; k < image.width()*image.height();++k){
        image.rgb_data()[k] = {0,0,0};
        cout<<image.rgb_data()[k].r<<endl;
    }

    for(unsigned int i =0; i < lines_.size();++i){
        for(int x = 0; x < image.width(); ++x) {
            int y = (lines_[i].second -x*cos(lines_[i].first))/sin(lines_[i].first);
            image.rgb_data()[int(y*image.width() +x)] = {255,0,0};
        }
    }
}

std::vector<std::pair<double, double>> HoughTransform::detect_lines() const {
    return lines_;
}

void HoughTransform::initialize_accumulator(const ppm_image& image) {
    accumulator_.resize(num_theta_bins_);
    for (int i = 0; i < num_theta_bins_; ++i) {
        accumulator_[i].resize(2*num_rho_bins_);
    }
}

void HoughTransform::perform_transform(const ppm_image& image) {
    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            if (image.get_pixel(x, y).r == 255 || image.get_pixel(x, y).g == 255 || image.get_pixel(x, y).b == 255) {
                for (int i = 0; i < num_theta_bins_; ++i) {
                    double theta = static_cast<double>(i*M_PI / num_theta_bins_) ;
                    double rho = x * cos(theta) + y * sin(theta);
                    accumulator_[i][int(rho) + num_rho_bins_]+=1; 
                }
            }
        }
    }
}