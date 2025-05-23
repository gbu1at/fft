#include "ComputeFFT.hpp"
#include <iostream>


namespace fft
{


vector_complex ComputeFFT::compute_recursion_fft(const vector_complex& _data, bool is_forward) {
    int p;
    int n = _data.size();

    if (n == 2 || n == 3 || n == 5)
        return compute_fft_slow(_data, is_forward);

    if (n % 2 == 0) p = 2;
    else if (n % 3 == 0) p = 3;
    else if (n % 5 == 0) p = 5;
    else throw std::runtime_error("N not equal 0 mod 2 or mod 3 or mod 5");
    
    return compute_recursion_fft(_data, n / p, p, is_forward);
}

vector_complex ComputeFFT::compute_recursion_fft(const vector_complex& _data, size_t n1, size_t n2, bool is_forward) {
    size_t n = _data.size();
    if (n != n1 * n2)
        throw std::runtime_error("error compute_recursion_fft arguments");

    vector_complex roots = roots_of_one(n, is_forward);

    std::vector<vector_complex> separation(n1, vector_complex(n2));

    std::vector<vector_complex> compute_sep(n1, vector_complex(n2));


    for (size_t i = 0; i < n1; ++i) {
        for (size_t j = 0; j < n2; ++j)
            separation[i][j] = _data[i + j * n1];
    
        compute_sep[i] = compute_recursion_fft(separation[i], is_forward);
    }

    std::vector<vector_complex> compute_group(n2, vector_complex(n1));

    for (size_t group = 0; group < n2; ++group) {
        vector_complex A(n1);
        std::complex<double> w = 1;
        for (size_t i = 0; i < n1; ++i) {
            A[i] = compute_sep[i][group] * w;
            w *= roots[group];
        }
        
        compute_group[group] = compute_recursion_fft(A, is_forward);
    }

    vector_complex result(n);

    for (size_t i = 0; i < n; ++i)
        result[i] = compute_group[i % n2][i / n2];

    return result;
}


vector_complex ComputeFFT::compute_fft_slow(
    const vector_complex& _data,
    bool is_forward
) {
    size_t n = _data.size();

    if (n == 2)
        return { _data[0] + _data[1], _data[0] - _data[1] };

    vector_complex roots;
    
    roots = roots_of_one(n, is_forward);

    vector_complex result(n);

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            result[i] += roots[(i * j) % n] * _data[j];
 
    return result;
}

vector_complex ComputeFFT::forward_fft_slow(
    const vector_complex& _data
) {
    return compute_fft_slow(_data, true);
}


vector_complex ComputeFFT::normalized_backward_result(vector_complex _data) {
    for (auto& x : _data)
        x /= _data.size();
    return _data;
}

vector_complex ComputeFFT::backward_fft_slow(
    const vector_complex& _data
) {
    return normalized_backward_result(compute_fft_slow(_data, false));
}



vector_complex ComputeFFT::roots_of_one(size_t n, bool is_forward) {
    vector_complex roots;
    roots.reserve(n);

    const double pi = 3.14159265358979323846;

    for (size_t i = 0; i < n; ++i) {
        double ang = ((is_forward) ? 1 : -1) * 2 * pi * i / n;
        roots.push_back(exp(std::complex<double>(0, ang)));
    }

    return roots;
}

vector_complex ComputeFFT::forward_fft(const vector_complex& _data) {
    return compute_recursion_fft(_data);
}

vector_complex ComputeFFT::backward_fft(const vector_complex& _data) {
    return normalized_backward_result(compute_recursion_fft(_data, false));
}


}
