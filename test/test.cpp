#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <complex>
#include <vector>
#include <cmath>
#include "ComputeFFT.hpp"

using vector_complex = std::vector<std::complex<double>>;

namespace fft {

const double EPSILON = 1e-6;


TEST_CASE("Testing forward_fft_slow backward_fft_slow function") {

    SUBCASE("first test") {
        vector_complex arr = { {3.9, 1.4}, {2.2, -1.0}, {-10.5, 0.5}, {1.5, -0.5}, {0, 1}, {2.4, 5.6} };

        vector_complex fft_arr = ComputeFFT::forward_fft_slow(arr);
        
        vector_complex _arr = ComputeFFT::backward_fft_slow(fft_arr);

        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(_arr[i] - arr[i]) < EPSILON);
    }
}


TEST_CASE("Testing forward_fft backward_fft function") {

    SUBCASE("test 1") {
        vector_complex arr = { {1.0, 1.0}, {2.0, -1.0}, {0.5, 0.5}, {1.5, -0.5} };

        vector_complex fft_arr = ComputeFFT::forward_fft(arr);
        vector_complex fft_arr_slow = ComputeFFT::forward_fft_slow(arr);

        
        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(fft_arr_slow[i] - fft_arr[i]) < EPSILON);
    }

    SUBCASE("test 2") {
        vector_complex arr = { {1.0, 1.0}, {2.0, -1.0}, {0.5, 0.5}, {1.5, -0.5} };

        vector_complex fft_arr = ComputeFFT::forward_fft(arr);
        vector_complex _arr = ComputeFFT::backward_fft(fft_arr);

        
        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(_arr[i] - arr[i]) < EPSILON);
    }
    SUBCASE("test 3") {

        vector_complex arr;

        int n = 100;

        for (int i = 0; i < n; ++i) {
            double R = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double I = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

            arr.push_back( {R, I} );
        }

        vector_complex fft_arr = ComputeFFT::forward_fft(arr);
        vector_complex fft_arr_slow = ComputeFFT::forward_fft_slow(arr);

        
        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(fft_arr[i] - fft_arr_slow[i]) < EPSILON);
    }

    SUBCASE("test 4") {

        vector_complex arr;

        int n = 100;

        for (int i = 0; i < n; ++i) {
            double R = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double I = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

            arr.push_back( {R, I} );
        }

        vector_complex fft_arr = ComputeFFT::forward_fft(arr);
        vector_complex _arr = ComputeFFT::backward_fft(fft_arr);
        
        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(_arr[i] - arr[i]) < EPSILON);
    }
}


TEST_CASE("TEST TIME") {

    vector_complex arr;

    int n = 3000000;

    std::cout << "array size: " << n << '\n';

    for (int i = 0; i < n; ++i) {
        double R = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        double I = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

        arr.push_back( {R, I} );
    }

    clock_t time_start_forward_fft = clock();
    vector_complex fft_arr = ComputeFFT::forward_fft(arr);
    clock_t time_finish_forward_fft = clock();



    clock_t time_start_backward_fft = clock();
    vector_complex _arr = ComputeFFT::backward_fft(fft_arr);
    clock_t time_finish_backward_fft = clock();

    
    for (size_t i = 0; i < arr.size(); ++i)
        CHECK(std::abs(_arr[i] - arr[i]) < EPSILON);

    std::cout << "TIME FORWARD FFT: " << (time_finish_forward_fft - time_start_forward_fft) / (double) CLOCKS_PER_SEC << '\n';
    std::cout << "TIME BACKWARD FFT: " << (time_finish_backward_fft - time_start_backward_fft) / (double) CLOCKS_PER_SEC << '\n';

}












}