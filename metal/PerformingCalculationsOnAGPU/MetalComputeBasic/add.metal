#include <metal_stdlib>
using namespace metal;

template<typename T> kernel void
add_arrays_T(device const T* inA, device const T* inB, device T* result, uint index [[thread_position_in_grid]]) {
    result[index] = inA[index] + inB[index];
}

template [[ host_name("add_arrays_float" )]] kernel void
add_arrays_T<float>(device const float*, device const float*, device float*, uint);
