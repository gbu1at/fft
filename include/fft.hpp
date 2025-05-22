#pragma once
#include <vector>
#include <complex>
#include <cmath>


namespace fft {

using vector_complex = std::vector<std::complex<double>>;

class ComputeFFT {
public:

    ComputeFFT() = delete;

    static vector_complex forward_fft(const vector_complex&);

    static vector_complex backward_fft(const vector_complex&);

    static vector_complex forward_fft_slow(const vector_complex&);

    static vector_complex backward_fft_slow(const vector_complex&);

private:

    static vector_complex roots_of_one(size_t, bool=true);

    static vector_complex compute_fft_slow(const vector_complex&,bool=true);

    static vector_complex compute_recursion_fft(const vector_complex&, size_t, size_t, bool=true);

    static vector_complex compute_recursion_fft(const vector_complex&, bool=true);

    static vector_complex normalized_backward_result(vector_complex);
};

}