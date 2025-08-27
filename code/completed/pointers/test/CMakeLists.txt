add_executable("pointers_test")

target_sources("pointers_test" PRIVATE
    "pointers_test.cpp"
)

target_link_libraries("pointers_test"
    "Catch2WithMain"
	"pointers_lib"
)