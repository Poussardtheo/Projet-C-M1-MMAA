#include <iostream>
#include <vector>
#include <utility>
#include "ppm_image.hpp"
#include "hough_transform.hpp"

using namespace std;

int main() {
string filename = "input.ppm";
ppm_image image(filename);

HoughTransform hough(360, sqrt(image.width()*image.width() + image.height()*image.height()), 150);
hough.transform(image);

vector<pair<double, double>> lines = hough.detect_lines();
for (unsigned int i = 0; i < lines.size(); ++i) {
    cout << "Ligne detectee : theta = " << lines[i].first << ", rho = " << lines[i].second << endl;
}

write_ppm_image("output.ppm", image.width(), image.height(), image.rgb_data());

return 0;
}
