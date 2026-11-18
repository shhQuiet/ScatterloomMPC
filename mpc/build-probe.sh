#!/bin/sh
set -eu
: "${MPC_SDK:?Set MPC_SDK to the official MPC Plugin SDK directory}"
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
export CPLUS_INCLUDE_PATH="$ROOT/generated/rnbo/rnbo:$ROOT/generated/rnbo/rnbo/common:$ROOT/generated/rnbo/rnbo/src:$ROOT/mpc/src:$ROOT/vst${CPLUS_INCLUDE_PATH:+:$CPLUS_INCLUDE_PATH}"
python3 "$MPC_SDK/tools/build.py" "$ROOT/mpc" --target native --toolchain gcc --define RNBO_USE_FLOAT32
