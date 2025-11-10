
# test for test formatting
add_executable(test_format test_format.cc)
target_link_libraries(test_format PRIVATE
    QFString
    Catch2WithMain
)

# # general use case test
# add_executable(test_general test_general.cc)
# target_link_libraries(test_general
#     PRIVATE
#     QFString
#     catch2::catch2
# )

add_test(NAME FormatTest COMMAND test_format)
# add_test(NAME GeneralTest COMMAND test_general)