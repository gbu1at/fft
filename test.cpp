#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <complex>
#include <vector>
#include <cmath>

using vector_complex = std::vector<std::complex<double>>;

// Тестируемые функции объявлены здесь
vector_complex roots_of_minuse_one(int n);
vector_complex compute_easy_fft(vector_complex _data);

const double EPSILON = 1e-6;

TEST_CASE("Testing roots_of_minuse_one function") {
    SUBCASE("Basic cases") {
        auto roots = roots_of_minuse_one(1);
        CHECK_EQ(roots.size(), 1);
        CHECK(std::abs(roots[0] - std::complex<double>(-1, 0)) < EPSILON);
        
        roots = roots_of_minuse_one(2);
        CHECK_EQ(roots.size(), 2);
        CHECK(std::abs(roots[0] - std::complex<double>(0, 1)) < EPSILON);
        CHECK(std::abs(roots[1] - std::complex<double>(0, -1)) < EPSILON);
    }

    SUBCASE("Roots properties") {
        const int n = 4;
        auto roots = roots_of_minuse_one(n);
        
        CHECK_EQ(roots.size(), n);
        for(const auto& root : roots) {
            // Проверка что root^n ≈ -1
            auto powered = std::pow(root, n);
            CHECK(std::abs(powered.real() - (-1)) < EPSILON);
            CHECK(std::abs(powered.imag()) < EPSILON);
        }
    }
}

TEST_CASE("Testing compute_easy_fft function") {
    SUBCASE("Identity transform") {
        vector_complex data{1.0, 0.0, 0.0, 0.0};
        auto result = compute_easy_fft(data);
        
        CHECK_EQ(result.size(), data.size());
        for(const auto& val : result) {
            CHECK(std::abs(val - std::complex<double>(1.0, 0.0)) < EPSILON);
        }
    }

    SUBCASE("Constant signal") {
        const int n = 4;
        vector_complex data(n, 1.0);
        auto result = compute_easy_fft(data);
        
        CHECK_EQ(result.size(), n);
        CHECK(std::abs(result[0] - std::complex<double>(n, 0.0)) < EPSILON);
        for(size_t i = 1; i < n; ++i) {
            CHECK(std::abs(result[i]) < EPSILON);
        }
    }

    SUBCASE("Simple 2-point transform") {
        vector_complex data{1.0, -1.0};
        auto result = compute_easy_fft(data);
        
        CHECK_EQ(result.size(), 2);
        CHECK(std::abs(result[0] - std::complex<double>(0.0, 0.0)) < EPSILON);
        CHECK(std::abs(result[1] - std::complex<double>(2.0, 0.0)) < EPSILON);
    }
}