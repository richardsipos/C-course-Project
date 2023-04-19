# C-course-Project
My project for C++ University course. 

Tasks:
Write a .h file that is included in the Main program.
The code should not generate any Warnings or Errors.

g++ -fsanitize=address,leak,undefined -O3 -Wall -Wextra -Werror main.cpp
clang-tidy-12 -header-filter='.*' main.cpp --
