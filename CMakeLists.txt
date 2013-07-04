#########################################
## Multi-Variate Interpolation Library ##
#########################################
cmake_minimum_required (VERSION 2.6)
project (muvi)

# Include custom cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Boost components to include
set(BOOST_COMPONENTS system)

# Locate sources
file (GLOB SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/[^.]*.cpp
    src/[^.]*.hpp
    )

# Include basic directories
include_directories (include src)

# Lookup and setup boost
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# Lookup and setup Memcached
find_package(LibMemcached)
include_directories(${LIBMEMCACHED_INCLUDE_DIR})

# Lookup and setup Memcached
find_package(CURL)
include_directories(${CURL_INCLUDE_DIRS})

# Lookup and setup ImageMagick
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
link_directories(${ImageMagick_LIBRARY_DIR})

# Link executable
add_executable (muvi ${SRC_FILES})

# Add provfiler
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -pg")

# Link libraries
target_link_libraries( muvi ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES} ${LIBMEMCACHED_LIBRARY} ${CURL_LIBRARIES} )
