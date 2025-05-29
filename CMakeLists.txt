cmake_minimum_required(VERSION 3.15)
project(exam)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF) # Stick with statically linked libraries

include(sanitizers.cmake)

#add_executable(exam_test exam_test.cpp)
#target_link_libraries(exam_test PRIVATE doctest_with_main)

#add_executable(terms_test terms_test.cpp terms.cpp evaluate.cpp print.cpp)
#target_link_libraries(terms_test PRIVATE doctest_with_main)

#add_executable(expressions_test expressions_test.cpp expressions.cpp terms.cpp evaluate.cpp print.cpp)
#target_link_libraries(expressions_test PRIVATE doctest_with_main)

#add_executable(print_test print_test.cpp print.cpp terms.cpp)
#target_link_libraries(print_test PRIVATE doctest_with_main)

add_executable(main src/main.cpp include/SymbolTable.h)
#target_link_libraries(main_test PRIVATE doctest_with_main)


#enable_testing()
#add_test(NAME main_test COMMAND main_test)

#add_test(NAME exam_test COMMAND exam_test)
#add_test(NAME terms_test COMMAND terms_test)
#add_test(NAME expressions_test COMMAND expressions_test)
#add_test(NAME print_test COMMAND print_test)
