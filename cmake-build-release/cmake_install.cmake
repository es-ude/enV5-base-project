# Install script for directory: /Users/maxi/Desktop/ENv5_Base_Project

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/local/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/extern/elastic-ai.runtime.c/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/pico-sdk/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/extern/freeRTOS/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/src/freeRtos/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/src/esp/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/src/atCommands/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/src/uart/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/src/gpio/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/extern/elastic-ai.runtime.enV5/src/network/cmake_install.cmake")
  include("/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/test/hardware/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/maxi/Desktop/ENv5_Base_Project/cmake-build-release/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
