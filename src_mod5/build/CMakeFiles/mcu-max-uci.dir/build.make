# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\b0318\chess2\mcu-max\src_mod5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\b0318\chess2\mcu-max\src_mod5\build

# Include any dependencies generated for this target.
include CMakeFiles/mcu-max-uci.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mcu-max-uci.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mcu-max-uci.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mcu-max-uci.dir/flags.make

CMakeFiles/mcu-max-uci.dir/codegen:
.PHONY : CMakeFiles/mcu-max-uci.dir/codegen

CMakeFiles/mcu-max-uci.dir/main.c.obj: CMakeFiles/mcu-max-uci.dir/flags.make
CMakeFiles/mcu-max-uci.dir/main.c.obj: CMakeFiles/mcu-max-uci.dir/includes_C.rsp
CMakeFiles/mcu-max-uci.dir/main.c.obj: C:/Users/b0318/chess2/mcu-max/src_mod5/main.c
CMakeFiles/mcu-max-uci.dir/main.c.obj: CMakeFiles/mcu-max-uci.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\b0318\chess2\mcu-max\src_mod5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mcu-max-uci.dir/main.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcu-max-uci.dir/main.c.obj -MF CMakeFiles\mcu-max-uci.dir\main.c.obj.d -o CMakeFiles\mcu-max-uci.dir\main.c.obj -c C:\Users\b0318\chess2\mcu-max\src_mod5\main.c

CMakeFiles/mcu-max-uci.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mcu-max-uci.dir/main.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\b0318\chess2\mcu-max\src_mod5\main.c > CMakeFiles\mcu-max-uci.dir\main.c.i

CMakeFiles/mcu-max-uci.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mcu-max-uci.dir/main.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\b0318\chess2\mcu-max\src_mod5\main.c -o CMakeFiles\mcu-max-uci.dir\main.c.s

CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj: CMakeFiles/mcu-max-uci.dir/flags.make
CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj: CMakeFiles/mcu-max-uci.dir/includes_C.rsp
CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj: C:/Users/b0318/chess2/mcu-max/src_mod5/mcu-max.c
CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj: CMakeFiles/mcu-max-uci.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\b0318\chess2\mcu-max\src_mod5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj -MF CMakeFiles\mcu-max-uci.dir\mcu-max.c.obj.d -o CMakeFiles\mcu-max-uci.dir\mcu-max.c.obj -c C:\Users\b0318\chess2\mcu-max\src_mod5\mcu-max.c

CMakeFiles/mcu-max-uci.dir/mcu-max.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mcu-max-uci.dir/mcu-max.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\b0318\chess2\mcu-max\src_mod5\mcu-max.c > CMakeFiles\mcu-max-uci.dir\mcu-max.c.i

CMakeFiles/mcu-max-uci.dir/mcu-max.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mcu-max-uci.dir/mcu-max.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\b0318\chess2\mcu-max\src_mod5\mcu-max.c -o CMakeFiles\mcu-max-uci.dir\mcu-max.c.s

# Object files for target mcu-max-uci
mcu__max__uci_OBJECTS = \
"CMakeFiles/mcu-max-uci.dir/main.c.obj" \
"CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj"

# External object files for target mcu-max-uci
mcu__max__uci_EXTERNAL_OBJECTS =

mcu-max-uci.exe: CMakeFiles/mcu-max-uci.dir/main.c.obj
mcu-max-uci.exe: CMakeFiles/mcu-max-uci.dir/mcu-max.c.obj
mcu-max-uci.exe: CMakeFiles/mcu-max-uci.dir/build.make
mcu-max-uci.exe: CMakeFiles/mcu-max-uci.dir/linkLibs.rsp
mcu-max-uci.exe: CMakeFiles/mcu-max-uci.dir/objects1.rsp
mcu-max-uci.exe: CMakeFiles/mcu-max-uci.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\b0318\chess2\mcu-max\src_mod5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable mcu-max-uci.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mcu-max-uci.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mcu-max-uci.dir/build: mcu-max-uci.exe
.PHONY : CMakeFiles/mcu-max-uci.dir/build

CMakeFiles/mcu-max-uci.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mcu-max-uci.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mcu-max-uci.dir/clean

CMakeFiles/mcu-max-uci.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\b0318\chess2\mcu-max\src_mod5 C:\Users\b0318\chess2\mcu-max\src_mod5 C:\Users\b0318\chess2\mcu-max\src_mod5\build C:\Users\b0318\chess2\mcu-max\src_mod5\build C:\Users\b0318\chess2\mcu-max\src_mod5\build\CMakeFiles\mcu-max-uci.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/mcu-max-uci.dir/depend

