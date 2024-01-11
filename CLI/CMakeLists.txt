add_executable(SoftView-CLI)

target_sources(SoftView-CLI
PRIVATE
    main.c
)

target_link_libraries(SoftView-CLI
PUBLIC
    SoftView-lib
)