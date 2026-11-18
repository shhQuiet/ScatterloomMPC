#!/usr/bin/env python3
"""Include third-party license texts with the built plugin folder."""
from pathlib import Path
import shutil

root = Path(__file__).resolve().parent.parent
out = root / 'mpc/build/Elsewave - VST - Scatterloom/Licenses'
out.mkdir(parents=True, exist_ok=True)
files = {
    'Elsewave-MIT.txt': 'LICENSE',
    'README-third-party.md': 'THIRD_PARTY_NOTICES.md',
    'RNBO-runtime-MIT.txt': 'generated/rnbo/rnbo/LICENSE',
    'inMusic-MPC-SDK-MIT.txt': 'licenses/MPC-Plugin-Builder-SDK.txt',
    'concurrentqueue-BSD.txt': 'generated/rnbo/rnbo/src/3rdparty/concurrentqueue/LICENSE.md',
    'readerwriterqueue-BSD.txt': 'generated/rnbo/rnbo/src/3rdparty/readerwriterqueue/LICENSE.md',
}
for name, source in files.items():
    shutil.copyfile(root / source, out / name)
for name, source in {
    'Cycling74-generated-code.txt': 'mpc/generated/Scatterloom.cpp',
    'nlohmann-json-MIT.txt': 'generated/rnbo/rnbo/src/3rdparty/json/json.hpp',
}.items():
    text = (root / source).read_text()
    (out / name).write_text(text[:text.index('*/') + 2] + '\n')
text = (root / 'generated/rnbo/rnbo/src/3rdparty/readerwriterqueue/atomicops.h').read_text()
start = text.index('// LICENSE:', text.index('Jeff Preshing'))
end = text.index('\n\tnamespace spsc_sema', start)
(out / 'Jeff-Preshing-zlib.txt').write_text(text[start:end] + '\n')
