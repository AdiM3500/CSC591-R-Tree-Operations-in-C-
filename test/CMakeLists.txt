add_executable(
  unit_tests
    unitTests.cpp
    rtree/rtree-lookup-tests.cpp
    rtree/rtree-range-tests.cpp
    rtree/rtree-tests.cpp

 
)

target_link_libraries(
  unit_tests
    rtree
    gcov
)

target_compile_options(
  unit_tests
    PRIVATE --coverage
)
