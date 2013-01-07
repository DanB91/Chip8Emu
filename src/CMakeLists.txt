

set(ObjectFiles main.cpp )


add_executable (ch8emu ${ObjectFiles})
target_link_libraries(ch8emu  ${SDL_LIBRARY})
