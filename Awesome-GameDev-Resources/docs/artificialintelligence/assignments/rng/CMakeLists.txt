add_executable(ai-rng rng.cpp)

file(GLOB TEST_INPUT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.in)
file(GLOB TEST_OUTPUT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.out)

#add_custom_test(ai-rng-test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ai-rng "${TEST_INPUT_FILES}" "${TEST_OUTPUT_FILES}")

