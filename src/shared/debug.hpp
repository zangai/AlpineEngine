#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

template <typename Type>
void printVector(Type &vector)
{
    for(uint16_t i=0; i<vector.size(); ++i)
        printf("%04i = %04x = %c\n", i, vector[i], vector[i]);
}

#endif // _DEBUG_HPP_
