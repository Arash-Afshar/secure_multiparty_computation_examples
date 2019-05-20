#include <array>
#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Network/Session.h>
#include <cryptoTools/Network/IOService.h>
#include <cryptoTools/Crypto/PRNG.h>
#include <libOTe/NChooseOne/Kkrt/KkrtNcoOtReceiver.h>

using namespace osuCrypto;

// The following is a modified version of the example in https://github.com/osu-crypto/libOTe
int main(int argc, char** argv)
{
    u64 numOTs = 1;
    auto numChosenMsgs = 10;

    // get up the networking
    IOService ios;
    Channel recverChl = Session(ios, "localhost:1212", SessionMode::Client).addChannel();
    PRNG prng(sysRandomSeed());

    KkrtNcoOtReceiver recver;

    // all Nco Ot extenders must have configure called first. This determines
    // a variety of parameters such as how many base OTs are required.
    bool maliciousSecure = false;
    bool statSecParam = 40;
    bool inputBitCount = 128;
    recver.configure(maliciousSecure, statSecParam, inputBitCount);

    // Generate new base OTs for the first extender.
    recver.genBaseOts(prng, recverChl);

    std::vector<block>recvMsgs(numOTs);
    std::vector<u64> choices(numOTs);

    // define which messages the receiver should learn.
    for (u64 i = 0; i < numOTs; ++i)
        choices[i] = atoi(argv[1]);

    // the messages that were learned are written to recvMsgs.
    recver.receiveChosen(numChosenMsgs, recvMsgs, choices, prng, recverChl);
    
    std::cout << "Client: chosen city " << choices[0] << ", got temperature " << recvMsgs[0] << std::endl;
}