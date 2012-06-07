#include "shared/cryptopp_wrapper.hpp"

#include "shared/Log.hpp"

#include "PacketHandler.hpp"
#include "Session.hpp"

using namespace std;

void PacketHandler::loginHandler(PacketPtr pckt, SessionPtr session)
{
    Log::outDebug("Received login packet");

    string username = pckt->read<string>();
    string passwordHash = pckt->read<string>();
    Log::outDebug("Received Password Hash: %s", passwordHash.c_str());
    Log::outDebug("Received Username: %s", username.c_str());

    stringstream hashInput;

    hashInput << username << ":" <<  passwordHash;

    string hash = BasicCryptoPPWrap::HexEncode(BasicCryptoPPWrap::hashSHA512(hashInput.str()));

    Log::outDebug("SELECT count(id) FROM accounts WHERE username = '%s' AND password = '%s'", username.c_str(), hash.c_str());

    int count;
    m_database->getBackend() << "SELECT count(id) FROM accounts WHERE username = :u AND password = :p", use(username), use(hash), into(count);

    PacketPtr result = Packet::create();
    result->setOpcode(SMSG_LOGIN_RESULT);
    result->add<bool>(count > 0);
    Log::outDebug("Queueing result");
    session->queue(result);
}
