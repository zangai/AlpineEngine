#ifndef _OPCODE_HPP_
#define _OPCODE_HPP_

enum opcodes
{
    SMSG_PING           = 0x0001,
    CMSG_PONG           = 0x0001,

    CMSG_SEND_LOGIN     = 0x0002,
    SMSG_LOGIN_RESULT   = 0x0002,

    MSG_NULL            = 0x0003,
};

#endif //_OPCODE_HPP_
