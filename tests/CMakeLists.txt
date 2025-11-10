
# test for indexable arg parser
add_executable(test_Format test_format.cc)
target_link_libraries(test_Format PRIVATE
    QFString
    Catch2WithMain
)

add_test(NAME FormatTest COMMAND test_Format)