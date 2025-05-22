#pragma once
#include <vector>
#include <complex>
#include <cmath>


namespace fft {

using vector_complex = std::vector<std::complex<double>>;


vector_complex roots_of_minuse_one(size_t n) {
    vector_complex roots;
    const double pi = 3.14159265358979323846;

    for (size_t i = 0; i < n; ++i) {
        double ang = pi * i / n;
        roots.push_back(exp(std::complex<double>(0, ang)));
    }

    return roots;
}

vector_complex compute_easy_fft(
    vector_complex _data
) {
    size_t n = _data.size();
    vector_complex roots = roots_of_minuse_one(n);

    vector_complex result(n);

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            result[i] += roots[(i * j) % n] * _data[j];
 
    return result;
}

vector_complex forward_fft(
    vector_complex _data
);
vector_complex backward_fft(
    vector_complex _data
);


vector_complex compute_recursion_fft(
    vector_complex _data,
    size_t n1,
    size_t n2
) {
    size_t n = _data.size();
    if (n != n1 * n2)
        throw std::runtime_error("error compute_recursion_fft arguments");

    vector_complex roots = roots_of_minuse_one(n);

}

}