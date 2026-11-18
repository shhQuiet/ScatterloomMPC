#!/bin/sh
# Build both standalone MPC architectures using the official MPC SDK.
set -eu
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
MPC_SDK=${MPC_SDK:-"$ROOT/../mpc-plugin-builder-sdk"}
export MPC_SDK
if [ ! -f "$MPC_SDK/tools/build.py" ]; then
  echo 'Set MPC_SDK to the official MPC Plugin Builder SDK checkout.' >&2
  exit 1
fi
export CPLUS_INCLUDE_PATH="$ROOT/generated/rnbo/rnbo:$ROOT/generated/rnbo/rnbo/common:$ROOT/generated/rnbo/rnbo/src:$ROOT/mpc/src${CPLUS_INCLUDE_PATH:+:$CPLUS_INCLUDE_PATH}"
python3 "$MPC_SDK/tools/build.py" "$ROOT/mpc" --target all --toolchain zig --define RNBO_USE_FLOAT32 --no-ui

python3 "$ROOT/mpc/package_notices.py"
