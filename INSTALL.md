# Installation Guide

## Building and Installing binancecpp

### Basic Installation

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
sudo cmake --install .
```

### Installation with Examples

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBINANCECPP_BUILD_EXAMPLES=ON -DBINANCECPP_INSTALL_EXAMPLES=ON
cmake --build .
sudo cmake --install .
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

### Building the Installed Examples

If you installed with examples, you can build them separately:

```bash
# Navigate to the examples directory (usually /usr/local/share/binancecpp/examples)
cd /usr/local/share/binancecpp/examples

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run an example
./example
```

## CMake Options

- `BINANCECPP_BUILD_EXAMPLES=ON/OFF`: Build examples during the main build (default: OFF)
- `BINANCECPP_INSTALL_EXAMPLES=ON/OFF`: Install example source files (default: OFF)
- `CMAKE_INSTALL_PREFIX`: Installation directory (default: /usr/local)

## Installation Locations

- **Library**: `${CMAKE_INSTALL_PREFIX}/lib/`
- **Headers**: `${CMAKE_INSTALL_PREFIX}/include/binancecpp/`
- **CMake files**: `${CMAKE_INSTALL_PREFIX}/lib/cmake/binancecpp/`
- **Examples**: `${CMAKE_INSTALL_PREFIX}/share/binancecpp/examples/` (if enabled)
