add_executable(
  unit_tests
    unitTests.cpp
    btree/btree-tests.cpp
)

target_link_libraries( 
  unit_tests
    btree
    gcov
)

target_compile_options(
  unit_tests
    PRIVATE --coverage
)
