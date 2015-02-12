#include "kernel.h"

namespace Kernel {

namespace Ports { void TestAll(); }
namespace WaitSynch { void TestAll(); }

void TestAll() {
    Ports::TestAll();
    WaitSynch::TestAll();
}

} // namespace
