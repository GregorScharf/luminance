#ifndef COPY_HPP
#define COPY_HPP

namespace engine{

// ! use only if you understand what this really does
// note: this can be faster than std::copy but only when compiled with -O3 and for large datasets such as >1_000_000 elements
// when you have a heap allocated array this may differ on different mashines and you still have to delete the original array manually
template <typename InputIterator, typename OutputIterator>
void copy(InputIterator first, InputIterator last, OutputIterator d_first)
{
    while (first != last)
    {
        *d_first = *first;
        ++d_first;
        ++first;
    }
}

}
#endif