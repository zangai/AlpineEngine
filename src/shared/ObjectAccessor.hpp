#ifndef _OBJECTACCESSOR_HPP_
#define _OBJECTACCESSOR_HPP_

#include <map>
#include <cstdlib>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/cstdint.hpp>

using namespace std;

/**
 * Draft for an object accessing class
 */
template <typename Type>
class ObjectAccessor
    : public boost::enable_shared_from_this< ObjectAccessor<Type> >
{
    public:
        typedef boost::shared_ptr< ObjectAccessor<Type> > pointer;
        pointer create()
        {
            return pointer(new ObjectAccessor<Type>());
        }

        char* add(Type object);
    private:
        std::map<char[40], Type> _objects;
};

#endif //_OBJECTACCESSOR_HPP_