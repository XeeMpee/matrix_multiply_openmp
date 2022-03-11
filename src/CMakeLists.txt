file(GLOB_RECURSE CPP_FILES *.cpp)
set (SRCS ${CPP_FILES} ${H_FILES})

# add WITH_EIGEN, if specified
# if(WITH_EIGEN)
#   add_definitions("-DWITH_EIGEN")
# endif()

# find_package(Eigen3)
# if (${EIGEN3_FOUND})
#   include_directories(${EIGEN3_INCLUDE_DIR})
# else()
#   message(STATUS "Eigen3 not found")
# endif()

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
if (${PYTHON3_FOUND})
  include_directories(
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS})
else()
  message(STATUS "Python not found")
endif()
  

add_executable( ${PROJECT_NAME}
    ${SRCS}
)

target_link_libraries( ${PROJECT_NAME} 
    PUBLIC OpenMP::OpenMP_CXX
    PUBLIC matplotlibcpp
    ${Python3_LIBRARIES}
)
