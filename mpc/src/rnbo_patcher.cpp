// Force the MPC bridge into the generated engine before any same-named header.
#include "./StatusBridge.h"
static_assert(ScatterloomStatusBridge::mpcBridgeAbi == 4, "Wrong MPC status bridge");
#define SCATTERLOOM_MPC_CAPTURE_GUARD 1
#include "../generated/Scatterloom.cpp"
// The wrapper must link against the waveform-aware engine translation unit.
extern "C" __attribute__((visibility("hidden"))) int scatterloom_mpc_bridge_abi_v4() noexcept { return 4; }
