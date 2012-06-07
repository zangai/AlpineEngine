#include "ObjectAccessor.hpp"

template <typename Type>
char* ObjectAccessor<Type>::add(Type object)
{
    uint32_t value = 0;
    value += rand() + rand() + rand();
    cout << value << endl;
    return (char*)"test";
}
