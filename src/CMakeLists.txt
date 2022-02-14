add_subdirectory( btree )

add_executable(
  a1
    main.cpp
)

set_target_properties(
  a1
    PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "../lib/"
      LIBRARY_OUTPUT_DIRECTORY "../lib/"
      RUNTIME_OUTPUT_DIRECTORY "../"
)

target_link_libraries(
  a1
    ${Boost_LIBRARIES}
    btree
)
