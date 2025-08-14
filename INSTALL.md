# Installation Guide

## Building and Installing# Platform-specific builds
cmake --preset=macos-debug      # macOS debug with examples
cmake --preset=macos-release    # macOS release with examples
cmake --preset=linux-debug      # Linux debug with examples
cmake --preset=linux-release    # Linux release with examples
cmake --preset=windows-debug    # Windows debug with examples
cmake --preset=windows-release  # Windows release with examples

# Platform-specific deployment builds (no examples)
cmake --preset=macos-deploy     # macOS production deployment
cmake --preset=linux-deploy     # Linux production deployment
cmake --preset=windows-deploy   # Windows production deploymentecpp

### Development Build (with examples)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
# or use preset: cmake --preset=dev
cmake --build .
sudo cmake --install .
```

### Production/Deployment Build (without examples)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBINANCECPP_DEPLOY_MODE=ON
# or use preset: cmake --preset=deploy
cmake --build .
sudo cmake --install .
```

### Custom Build Options

```bash
# Build without examples (override default)
cmake .. -DBINANCECPP_BUILD_EXAMPLES=OFF

# Force deployment mode (disables examples regardless of BUILD_EXAMPLES)
cmake .. -DBINANCECPP_DEPLOY_MODE=ON
```

### Using CMake Presets (Recommended)

```bash
# List available presets
```bash
# List available presets
cmake --list-presets=all

# Development build with examples
cmake --preset=dev
cmake --build --preset=dev

# Production deployment without examples
cmake --preset=deploy
cmake --build --preset=deploy

# Platform-specific builds
cmake --preset=macos-debug      # macOS debug with examples
cmake --preset=macos-release    # macOS release with examples
cmake --preset=linux-debug      # Linux debug with examples
cmake --preset=linux-release    # Linux release with examples
cmake --preset=windows-debug    # Windows debug with examples
cmake --preset=windows-release  # Windows release with examples

# Platform-specific deployment builds (no examples)
cmake --preset=macos-deploy     # macOS production deployment
cmake --preset=linux-deploy     # Linux production deployment
cmake --preset=windows-deploy   # Windows production deployment
```

### Custom Installation Prefix

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/binancecpp
cmake --build .
sudo cmake --install .
```

## Using the Installed Library

### In Your CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)
project(my_project)

set(CMAKE_CXX_STANDARD 20)

find_package(binancecpp REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE binancecpp::binancecpp)
```

### Running the Installed Examples

If you installed with examples, the example binaries are installed and ready to run:

```bash
# Example binaries are installed to /usr/local/bin/examples/ (or your install prefix)
# Run examples directly
/usr/local/bin/examples/example
/usr/local/bin/examples/example_aggTrades
/usr/local/bin/examples/example_klines

# Or if you add the examples directory to your PATH
export PATH="$PATH:/usr/local/bin/examples"
example
example_aggTrades
example_klines
```

## CMake Options

- `BINANCECPP_BUILD_EXAMPLES=ON/OFF`: Build and install examples (default: ON)
- `BINANCECPP_DEPLOY_MODE=ON/OFF`: Enable deployment mode, disables examples (default: OFF)
- `CMAKE_INSTALL_PREFIX`: Installation directory (default: /usr/local)

## Build Behavior

- **Default**: Examples are built and installed
- **Debug builds**: Always include examples (unless deploy mode is enabled)
- **Release builds with deploy mode**: Examples are disabled
- **Deploy mode overrides**: When `BINANCECPP_DEPLOY_MODE=ON`, examples are always disabled regardless of `BINANCECPP_BUILD_EXAMPLES`

## Installation Locations

- **Library**: `${CMAKE_INSTALL_PREFIX}/lib/`
- **Headers**: `${CMAKE_INSTALL_PREFIX}/include/binancecpp/`
- **CMake files**: `${CMAKE_INSTALL_PREFIX}/lib/cmake/binancecpp/`
- **Example binaries**: `${CMAKE_INSTALL_PREFIX}/bin/examples/` (if examples are enabled)
