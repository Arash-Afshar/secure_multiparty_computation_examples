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
    Channel recverChl = Session(ios, "localhost:1212", SessionMode::Client).addChannel();

    // The number of OTs.
    int n = 1;

    // The code to be run by the OT receiver.
    auto recverThread = std::thread([&]() {
        PRNG prng(sysRandomSeed());
        IknpOtExtReceiver recver;
        recver.genBaseOts(prng, recverChl);

        // Choose which messages should be received.
        BitVector choices(n);
        choices[0] = atoi(argv[1]);

        // Receive the messages
        std::vector<block> messages(n);
        recver.receiveChosen(choices, messages, prng, recverChl);

        std::cout << "User: Chose city " << choices[0] << " and got " << messages[0] << std::endl;
    });

    recverThread.join();
    return 0;
}
