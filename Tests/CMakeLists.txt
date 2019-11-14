project(kek-lang)

find_package(GTest REQUIRED)

add_executable(kek_lang_test
        LexerTests.cpp
        TestUtils.h)

target_include_directories(kek_lang_test PRIVATE ../Source)
target_link_libraries(kek_lang_test GTest::GTest GTest::Main)
target_link_libraries(kek_lang_test kek_lang_lib)

add_test(NAME test COMMAND kek_lang_test)
