# Scatterloom for MPC

Scatterloom is a granular rhythm effect for MPC standalone. It captures audio
into a grain pool and weaves those grains into Euclidean patterns using a Markov
probability matrix. This repository contains the MPC version; the desktop
project and the pairing service are separate.

## Install

Download a release and follow the [MPC installation guide](https://elsewave.pages.dev/mpc/install).
MPC OS 3.10.1 or later and external plugin support are required. A license key
and an internet connection are needed once to pair each MPC. The plugin checks
the resulting license offline afterwards.

## Build

The build currently uses macOS, Python 3, a C++ compiler, Zig, and the
[official MPC Plugin Builder SDK](https://github.com/inmusic-software/mpc-plugin-builder-sdk).
The SDK used for the existing build was revision
`febd2ca5bd9eb16c4a412837196e145566bc981b`. Install the SDK separately and set
`MPC_SDK` to its checkout; the default is `../mpc-plugin-builder-sdk`.

```sh
./build.sh
```

The command builds both MPC architectures and packages the checked-in skin
in `mpc/build/Elsewave - VST - Scatterloom/`. The SDK may install its Zig
compiler if needed. This build has not yet been validated from a clean checkout.

The `mpc/skins` files are generated output checked in for a portable build.
After changes to the interface, regenerate them with `mpc/regenerate-skin.py`;
this currently needs macOS tools, Swift and Python Pillow, and a native build to
produce `mpc/build/params.json`. Do not hand-edit generated engine code.

The MPC-specific engine is preserved in `mpc/generated/Scatterloom.cpp`. It
contains historical MPC changes; the upstream RNBO patch-to-export workflow
has not yet been verified to reproduce those changes. Do not overwrite it with
an export until that workflow is reconciled.

## License

The Elsewave source is available under the restricted terms in [LICENSE](LICENSE).
Third-party code and artwork have their own licenses; see
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
