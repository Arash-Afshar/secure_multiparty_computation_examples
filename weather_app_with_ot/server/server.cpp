#include <array>
#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Network/Session.h>
#include <cryptoTools/Network/IOService.h>
#include <cryptoTools/Crypto/PRNG.h>
#include <libOTe/NChooseOne/Kkrt/KkrtNcoOtSender.h>

using namespace osuCrypto;

// The following is a modified version of the example in https://github.com/osu-crypto/libOTe
int main(int argc, char** argv)
{

    u64 numOTs = 1;
    auto numChosenMsgs = 10;

    // get up the networking
    IOService ios;
    Channel senderChl = Session(ios, "localhost:1212", SessionMode::Server).addChannel();
    PRNG prng(sysRandomSeed());

    KkrtNcoOtSender sender;

    // all Nco Ot extenders must have configure called first. This determines
    // a variety of parameters such as how many base OTs are required.
    bool maliciousSecure = false;
    bool statSecParam = 40;
    bool inputBitCount = 128;
    sender.configure(maliciousSecure, statSecParam, inputBitCount);

    // Generate new base OTs for the first extender.
    sender.genBaseOts(prng, senderChl);


    // populate this with the messages that you want to send.
    Matrix<block> sendMessages(numOTs, numChosenMsgs);
    for (int i = 0; i < numChosenMsgs; i++) {
        sendMessages[0][i] = toBlock(15+i);
    }
    std::cout << "Server - the temperatures are:" << std::endl;
    for (int i = 0; i < numChosenMsgs; i++) {
        std::cout << "City" << i << ": " << sendMessages[0][i] << std::endl;
    }
    std::cout << std::endl;

    // perform the OTs with the given messages.
    sender.sendChosen(sendMessages, prng, senderChl);
}