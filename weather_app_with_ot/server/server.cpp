#include <array>
#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Network/Session.h>
#include <cryptoTools/Network/IOService.h>
#include <cryptoTools/Crypto/PRNG.h>
#include <libOTe/TwoChooseOne/IknpOtExtReceiver.h>
#include <libOTe/TwoChooseOne/IknpOtExtSender.h>

using namespace osuCrypto;

// The following is a modified version of the example in https://github.com/osu-crypto/libOTe
int main(int argc, char** argv)
{
    // Setup networking. See cryptoTools\frontend_cryptoTools\Tutorials\Network.cpp
    IOService ios;
    Channel senderChl = Session(ios, "localhost:1212", SessionMode::Server).addChannel();

    // The number of OTs.
    int n = 1;
    PRNG prng(sysRandomSeed());
    IknpOtExtSender sender;
    sender.genBaseOts(prng, senderChl);

    // Choose which messages should be sent.
    std::vector<std::array<block, 2>> sendMessages(n);
    sendMessages[0] = { toBlock(54), toBlock(33) };
    std::cout << "Server: the two city temperatures are: " << sendMessages[0][0] << ", and " << sendMessages[0][1] << std::endl;

    // Send the messages.
    sender.sendChosen(sendMessages, prng, senderChl);
    return 0;
}
