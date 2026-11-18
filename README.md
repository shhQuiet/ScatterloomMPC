# Scatterloom for MPC

Scatterloom is a granular rhythm effect for MPC standalone. It captures audio
into a grain pool and weaves those grains into Euclidean patterns using a Markov
probability matrix. This repository contains the MPC version; the desktop
project is separate.

## Install

Download a release and follow the [MPC installation guide](https://elsewave.pages.dev/mpc/install).
MPC OS 3.10.1 or later and external plugin support are required. No license key or internet connection is required.

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
compiler if needed. Both architectures and the native host simulator have been tested from a clean source snapshot of this repository.

The `mpc/skins` files are generated output checked in for a portable build.
After changes to the interface, regenerate them with `mpc/regenerate-skin.py`;
this currently needs macOS tools, Swift and Python Pillow, and a native build to
produce `mpc/build/params.json`. The checked-in skin is generated; edit its generators instead of the output.

The MPC-specific engine in `mpc/generated/Scatterloom.cpp` is a maintained C++
fork of the original RNBO export. Its MPC changes are not reproduced by the
older RNBO source; do not overwrite this fork with a fresh export. Preserve
the Cycling '74 copyright and license notice when modifying it.

## License

Elsewave-authored source is available under the MIT license in [LICENSE](LICENSE).
The combined plugin is distributed under [GPL version 3](licenses/GPL-3.0-only.txt),
using the GPL option for the Cycling 74-generated engine.
Third-party code and artwork have their own licenses; see
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
