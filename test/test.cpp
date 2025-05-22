#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <complex>
#include <vector>
#include <cmath>

using vector_complex = std::vector<std::complex<double>>;

namespace fft {



vector_complex roots_of_one(size_t, bool=true);
vector_complex compute_fft_slow(const vector_complex&, bool=true);
vector_complex forward_fft_slow(const vector_complex&);
vector_complex backward_fft_slow(const vector_complex&);
vector_complex forward_fft(const vector_complex&);
vector_complex backward_fft(const vector_complex&);


const double EPSILON = 1e-6;

TEST_CASE("Testing roots_of_one function") {
    SUBCASE("Basic cases") {
        auto roots = roots_of_one(1);
        CHECK_EQ(roots.size(), 1);
        CHECK(std::abs(roots[0] - std::complex<double>(1, 0)) < EPSILON);
        
        roots = roots_of_one(2);
        CHECK_EQ(roots.size(), 2);
        CHECK(std::abs(roots[0] - std::complex<double>(1, 0)) < EPSILON);
        CHECK(std::abs(roots[1] - std::complex<double>(-1, 0)) < EPSILON);
    }
}

TEST_CASE("Testing compute_fft_slow function") {
    SUBCASE("Identity transform") {
        vector_complex data{1.0, 0.0, 0.0, 0.0};
        auto result = compute_fft_slow(data);
        
        CHECK_EQ(result.size(), data.size());
        for(const auto& val : result) {
            CHECK(std::abs(val - std::complex<double>(1.0, 0.0)) < EPSILON);
        }
    }

    SUBCASE("Constant signal") {
        const int n = 4;
        vector_complex data(n, 1.0);
        auto result = compute_fft_slow(data);
        
        CHECK_EQ(result.size(), n);
        CHECK(std::abs(result[0] - std::complex<double>(n, 0.0)) < EPSILON);
        for(size_t i = 1; i < n; ++i) {
            CHECK(std::abs(result[i]) < EPSILON);
        }
    }

    SUBCASE("Simple 2-point transform") {
        vector_complex data{1.0, -1.0};
        auto result = compute_fft_slow(data);
        
        CHECK_EQ(result.size(), 2);
        CHECK(std::abs(result[0] - std::complex<double>(0.0, 0.0)) < EPSILON);
        CHECK(std::abs(result[1] - std::complex<double>(2.0, 0.0)) < EPSILON);
    }
}



TEST_CASE("Testing forward_fft_slow backward_fft_slow function") {

    SUBCASE("first test") {
        vector_complex arr = { {3.9, 1.4}, {2.2, -1.0}, {-10.5, 0.5}, {1.5, -0.5}, {0, 1}, {2.4, 5.6} };

        vector_complex fft_arr = forward_fft_slow(arr);
        
        vector_complex _arr = backward_fft_slow(fft_arr);

        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(_arr[i] - arr[i]) < EPSILON);
    }
}


TEST_CASE("Testing forward_fft backward_fft function") {

    SUBCASE("test 1") {
        vector_complex arr = { {1.0, 1.0}, {2.0, -1.0}, {0.5, 0.5}, {1.5, -0.5} };

        vector_complex fft_arr = forward_fft(arr);
        vector_complex fft_arr_slow = forward_fft_slow(arr);

        
        for (size_t i = 0; i < arr.size(); ++i)
            CHECK(std::abs(fft_arr_slow[i] - fft_arr[i]) < EPSILON);
    }

    SUBCASE("test 2") {
        vector_complex arr = { {1.0, 1.0}, {2.0, -1.0}, {0.5, 0.5}, {1.5, -0.5} };

        vector_complex fft_arr = forward_fft(arr);
        vector_complex _arr = backward_fft(fft_arr);

        
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

        vector_complex fft_arr = forward_fft(arr);
        vector_complex fft_arr_slow = forward_fft_slow(arr);

        
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

        vector_complex fft_arr = forward_fft(arr);
        vector_complex _arr = backward_fft(fft_arr);
        
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
    vector_complex fft_arr = forward_fft(arr);
    clock_t time_finish_forward_fft = clock();



    clock_t time_start_backward_fft = clock();
    vector_complex _arr = backward_fft(fft_arr);
    clock_t time_finish_backward_fft = clock();

    
    for (size_t i = 0; i < arr.size(); ++i)
        CHECK(std::abs(_arr[i] - arr[i]) < EPSILON);

    std::cout << "TIME FORWARD FFT: " << (time_finish_forward_fft - time_start_forward_fft) / (double) CLOCKS_PER_SEC << '\n';
    std::cout << "TIME BACKWARD FFT: " << (time_finish_backward_fft - time_start_backward_fft) / (double) CLOCKS_PER_SEC << '\n';

}
















}