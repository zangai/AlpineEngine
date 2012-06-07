#include <sstream>

#include "shared/Log.hpp"

#include "Database.hpp"

void Database::connect()
{
    std::stringstream connString;
    connString << "mysql://user=" << m_user << " password='" << m_password << "' host=" << m_host << " port=" << m_port << " db=" << m_database;

    m_conn.open(connString.str());
}

session& Database::getBackend()
{
    return m_conn;
}

rowset<row> Database::query(string query)
{
    return m_conn.prepare << query;
}
rowset<row> Database::pQuery(const char* str, ...)
{
    char* query = new char[300];

    va_list ap;
    va_start(ap, str);
    vsprintf(query, str, ap);
    va_end(ap);

    Log::outDebug("[SQL] %s", query);
    return m_conn.prepare << query;
}

void Database::execute(string query)
{
    m_conn << query;
}

void Database::save(Saveable* object)
{
    object->save(this);
}