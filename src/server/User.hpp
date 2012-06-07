#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>

class User
{
    public:
        User() {}
        ~User() {}

        void setNickname(std::string nickname) { _nickname = nickname; }
        std::string getNickname() { return _nickname; }
    private:
        std::string _nickname;

};

#endif //_USER_HPP_
