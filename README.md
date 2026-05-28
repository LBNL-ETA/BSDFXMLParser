# BSDFXMLParser

A C++20 library for parsing **BSDF** (Bidirectional Scattering Distribution Function) XML files used in LBNL window/shading optical simulations. Built on top of [FileParse](https://github.com/LBNL-ETA/FileParse) for the XML/JSON serialization machinery, this library defines the schema-specific node bindings for the BSDF XML format.

## Requirements

- C++20 compatible compiler (`g++` 11+, `clang++` 14+, MSVC 19.30+)
- CMake 3.8+ (3.21+ if you want to use the shipped CMake presets)
- [FileParse](https://github.com/LBNL-ETA/FileParse) (fetched automatically)

## Consuming BSDFXMLParser

### Using FetchContent in CMake (recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
    BSDFXMLParser
    GIT_REPOSITORY https://github.com/LBNL-ETA/BSDFXMLParser.git
    GIT_TAG Version_0.0.11
)
FetchContent_MakeAvailable(BSDFXMLParser)

target_link_libraries(MyTarget PRIVATE BSDFXMLParser)
```

Update `GIT_TAG` to the desired release tag.

## Building (developers)

`FileParse` (and its transitive deps `xmlParser`, `nlohmann_json`) is downloaded automatically via CMake FetchContent on first configure. Tests are built by default (`-DBUILD_BSDFXMLParser_Tests=OFF` to disable).

### Presets

`CMakePresets.json` ships four visible configure presets, plus two hidden inheritance bases:

| Preset | When to use it |
|---|---|
| `default-debug` / `default-release` | Standard configure on any platform; CI. Fetches all dependencies from declared remotes. Picks the system default compiler (MSVC on Windows, system `cc`/`c++` on Linux/macOS). |
| `local-debug` / `local-release` | Consume sibling working copies of dependencies instead of fetching them. |

Examples:

```
cmake --preset default-release
cmake --build build/default-release --parallel
ctest --test-dir build/default-release -C Release --output-on-failure
```

`local` expects a sibling directory layout — e.g. `../FileParse` next to `../BSDFXMLParser`. Currently overridden:

| Dependency | Expected sibling path |
|------------|----------------------|
| FileParse | `../FileParse` |

Missing siblings fall back to the declared remote automatically, so `local-*` is safe to invoke even if you don't have the sibling checked out.

#### Per-machine compiler presets (`CMakeUserPresets.json`)

To use a specific compiler (`vs2022-release`, `gcc-13-debug`, `clang-18-release`, etc.), each developer maintains their own `CMakeUserPresets.json` next to `CMakePresets.json`. It is gitignored, read automatically by CMake (and CLion, VS Code, etc.), and stays on the developer's machine.

Personal presets `inherit` from one of the shipped presets (usually `local`, which gives you sibling-repo overrides for free) and override whatever they want. A complete realistic example — building with WSL Clang on a Windows machine, with CLion 2023.2+ routed through the WSL toolchain automatically:

```json
{
    "version": 6,
    "configurePresets": [
        {
            "name": "clang-release",
            "displayName": "clang (Release)",
            "inherits": "local",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build/clang-release",
            "cacheVariables": {
                "CMAKE_C_COMPILER":   "clang",
                "CMAKE_CXX_COMPILER": "clang++",
                "CMAKE_BUILD_TYPE":   "Release"
            },
            "vendor": {
                "jetbrains.com/clion": {
                    "toolchain": "WSL"
                }
            }
        }
    ]
}
```

A few things going on in that one preset:

- `"inherits": "local"` → picks up sibling-repo overrides (when present) and the rest of the framework setup.
- Bare compiler names (`clang`, `clang++`) rather than `/usr/bin/clang` → portable to any machine that has that toolchain on `PATH`. Use absolute paths only if the compiler isn't on `PATH` (e.g. `C:/Program Files/LLVM/bin/clang.exe` — forward slashes work in JSON, no escaping needed).
- `"vendor.jetbrains.com/clion.toolchain"` → tells CLion (2023.2+) which configured toolchain to route this preset through. Standard names are `WSL`, `Visual Studio`, `MinGW`; whatever you see in `Settings → Build, Execution, Deployment → Toolchains`. The hint is silently ignored if the name doesn't match — no configure-time error.

Add as many of those blocks as you have toolchains you want explicit presets for (one per compiler × build type). Each gets its own `binaryDir` so Debug and Release artifacts don't clobber each other.

Alternative if you don't want a personal preset at all: set `CC` and `CXX` environment variables in your shell rc (`~/.bashrc`, PowerShell profile) before invoking `cmake --preset default-release`. CMake picks them up.

### Manual configure (without presets)

```
cmake -B build
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

### Clean rebuild

Delete the `build/` directory and re-run the configure and build commands above.

## License

See the [LICENSE](LICENSE) file.
