/* 
 * File:   Saveable.hpp
 * Author: xeross
 *
 * Created on October 11, 2010, 11:09 AM
 */

#ifndef _SAVEABLE_HPP_
#define	_SAVEABLE_HPP_

class Database;

class Saveable
{
    public:
        virtual void save(Database* db);
};

#endif	/* _SAVEABLE_HPP_ */

