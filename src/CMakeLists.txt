

set(ObjectFiles main.cpp Chip8.cpp GFX.cpp Debug.cpp Timer.cpp Keyboard.cpp)


add_executable (ch8emu ${ObjectFiles})
target_link_libraries(ch8emu  ${SDL_LIBRARY} ${CURSES_NCURSES_LIBRARY})
