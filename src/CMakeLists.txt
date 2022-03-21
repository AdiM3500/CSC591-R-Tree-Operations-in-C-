add_subdirectory( rtree )

add_executable(
  a2
    main.cpp
)

set_target_properties(
  a2
    PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "../lib/"
      LIBRARY_OUTPUT_DIRECTORY "../lib/"
      RUNTIME_OUTPUT_DIRECTORY "../"
)

target_link_libraries(
  a2
    ${Boost_LIBRARIES}
    rtree
)
