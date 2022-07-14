### Set cmake minimum version
cmake_minimum_required(VERSION 3.1.0)
### Set project name
project(CProject)
### Set verbose setting
set(CMAKE_VERBOSE_MAKEFILE OFF)
### gcc/g++ property setting
#set(CMAKE_CXX_FLAGS "-std=c++20")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")
#set(CMAKE_C_FLAGS "-std=c++20")
set(CMAKE_C_COMPILER "/usr/bin/gcc")

#### set project folder path
SET(BASE_PATH ${PROJECT_SOURCE_DIR})
SET(SOURCE_LOCATION ${BASE_PATH}/source)

### Collect all cpp source from SOURCE_LOCATION and append them into FILE_LIST_CPP and C
### NOTE all file will be recursiverly find c/cpp file.


file(GLOB_RECURSE FILE_LOC ${SOURCE_LOCATION}/*.cpp)
list(APPEND FILE_LISTS_SRC ${FILE_LOC})
SET(CPP_SRC_FILES ${FILE_LISTS_SRC})

file(GLOB_RECURSE FILE_LOC ${SOURCE_LOCATION}/*.c)
list(APPEND FILE_LISTS_SRC ${FILE_LOC})
SET(C_SRC_FILES ${FILE_LISTS_SRC})

#### set additional package and link include/lib path
#set(TensorRT_DIR "/usr/local/TensorRT")
#find_package(OpenCV REQUIRED)
#find_package(CUDA REQUIRED)
#find_package(TensorRT REQUIRED)

### below command find header file where you write in the INCLUDE_DRIECTORIS
### for example if you make header file in the include you must add in here to use.
INCLUDE_DIRECTORIES(
                        ${SOURCE_LOCATION}/
                        ${SOURCE_LOCATION}/header
                        #example.
                        #${SOURCE_LOCATION}/include
                        #${OpenCV_INCLUDE_DIR}
                        #${CUDA_INCLUDE_DIRS}
                        #${TensorRT_INCLUDE_DIRS}
                        #"-I/usr/local/TensorRT/include/"
)
### link library by adding option below command
LINK_LIBRARIES(
            ### OPENCV
            #${OpenCV_LIBRARIES}
            ### CUDA
            #${CUDA_LIBRARIES}
            ### TensorRT
            #${TensorRT_LIBRARIES}

            ###
            #-L/usr/local/cuda/lib64
            #-lcuda
            # etc...
)

### Add compiler option
add_compile_options(-w -g) #-fno-elide-constructors)
### Add definition( macro )
add_definitions(-DPROJECT_ROOT="${BASE_PATH}" 
                            -DTARGET_OS="LINUX" 
                            -DUSE_OPENCV=false)

### set executable option
SET(OUTPUT_ELF "CProj.out")
add_executable(${OUTPUT_ELF} ${CPP_SRC_FILES} ${C_SRC_FILES})
message("${CPP_SRC_FILES}")