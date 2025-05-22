#include "fft.hpp"
#include <iostream>


int main() {
    fft::vector_complex arr;

    int n = 3000000;

    std::cout << "array size: " << n << '\n';

    for (int i = 0; i < n; ++i) {
        double R = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double I = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

        arr.push_back( {R, I} );
    }

    clock_t time_start_forward_fft = clock();
    fft::vector_complex fft_arr = fft::forward_fft(arr);
    clock_t time_finish_forward_fft = clock();


    clock_t time_start_backward_fft = clock();
    fft::vector_complex _arr = fft::backward_fft(fft_arr);
    clock_t time_finish_backward_fft = clock();

    double MAX_DEV = 0;
    double MID_DEV = 0;
    
    for (size_t i = 0; i < arr.size(); ++i) {
        double dev = std::abs(_arr[i] - arr[i]);
        MAX_DEV = std::max(dev, MAX_DEV);
        MID_DEV += dev;
    }

    MID_DEV /= arr.size();

    std::cout << "TIME FORWARD FFT: " << (time_finish_forward_fft - time_start_forward_fft) / (double) CLOCKS_PER_SEC << '\n';
    std::cout << "TIME BACKWARD FFT: " << (time_finish_backward_fft - time_start_backward_fft) / (double) CLOCKS_PER_SEC << '\n';
    std::cout << "\n";

    std::cout << "maximum deviation: " << MAX_DEV << "\n";
    std::cout << "middle deviation: " << MID_DEV << "\n";

}