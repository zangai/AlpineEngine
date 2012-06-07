#ifndef _DATABASE_HPP_
#define	_DATABASE_HPP_

#include <cstdarg>
#include <cstdio>

#include <boost/cstdint.hpp>
#include <boost/thread/detail/singleton.hpp>

#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"

#include "Saveable.hpp"

using namespace boost;
using namespace std;
using namespace soci;

class Database
{
    private:
        string m_host;
        string m_user;
        string m_password;
        string m_database;
        uint16_t m_port;

        session m_conn;

    public:
        /**
         * @param Saveable object Object that will be saved to the database
         */
        void save(Saveable* object);
        /**
         * @param string host The database host
         * @param string user Database username
         * @param string password Database password
         * @param string database Database name
         * @param uint16_t port Database port
         */
        Database(string host, string user, string password, string database, uint16_t port = 3306)
            : m_host(host), m_user(user), m_password(password), m_database(database), m_port(port) {}

        session& getBackend();

        void connect();
        rowset<row> query(string query);
        rowset<row> pQuery(const char* str, ...);
        void execute(string query);
};


#endif // _DATABASE_HPP_

