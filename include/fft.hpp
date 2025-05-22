#pragma once
#include <vector>
#include <complex>
#include <cmath>


namespace fft {

using vector_complex = std::vector<std::complex<double>>;


vector_complex roots_of_one(size_t, bool=true);

vector_complex compute_fft_slow(const vector_complex&,bool=true);

vector_complex forward_fft(const vector_complex&);

vector_complex backward_fft(const vector_complex&);

vector_complex forward_fft_slow(const vector_complex&);

vector_complex backward_fft_slow(const vector_complex&);

vector_complex compute_recursion_fft(const vector_complex&, size_t, size_t, bool=true);

vector_complex compute_recursion_fft(const vector_complex&, bool=true);

vector_complex normalized_backward_result(vector_complex&);

}