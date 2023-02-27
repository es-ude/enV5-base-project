# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/maxi/Desktop/ENv5_Base_Project/extern/elastic-ai.runtime.enV5/extern/pico-sdk/tools/pioasm"
  "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pioasm"
  "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
