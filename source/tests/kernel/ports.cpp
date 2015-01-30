#include <memory>
#include <cstring>
#include <3ds.h>

#include "common/scope_exit.h"
#include "tests/test.h"

namespace Kernel {
namespace Ports {

static bool Test_ConnectToPort() {
    const Result ERR_NOT_FOUND = 0xD88007FA;
    const Result ERR_PORT_NAME_TOO_LONG = 0xE0E0181E;
    Handle handle;

    // Test for correct Result codes in various situations
    // NULL port name
    TestEquals(svcConnectToPort(&handle, nullptr), ERR_UNKNOWN_PORT);
    // empty port name
    TestEquals(svcConnectToPort(&handle, ""), ERR_UNKNOWN_PORT);
    // port name too long
    TestEquals(svcConnectToPort(&handle, "SuperExtremelyUltraMegaVeryLongString"), ERR_PORT_NAME_TOO_LONG);
    TestEquals(svcConnectToPort(&handle, "0123456789A"), ERR_UNKNOWN_PORT); // Just right (11 characters)
    TestEquals(svcConnectToPort(&handle, "0123456789AB"), ERR_PORT_NAME_TOO_LONG); // too long
    // non-registered port name
    TestEquals(svcConnectToPort(&handle, "xyz:"), ERR_UNKNOWN_PORT);
    // connecting to srv services using ConnectToPort should fail
    TestEquals(svcConnectToPort(&handle, "APT:U"), ERR_UNKNOWN_PORT);

    // Connecting to "srv:" should succeed
    TestEquals(svcConnectToPort(&handle, "srv:"), 0);

    return true;
}

void TestAll() {
    Test("Kernel::Ports", "ConnectToPort", Test_ConnectToPort(), true);
}

} // namespace
} // namespace
