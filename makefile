# https://stackoverflow.com/questions/3774568/makefile-issue-smart-way-to-scan-directory-tree-for-c-files

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# How to recursively find all files with the same name in a given folder
# ALL_INDEX_HTMLS := $(call rwildcard,foo/,index.html)

# How to recursively find all files that match a pattern
# ALL_HTMLS := $(call rwildcard,foo/,*.html)

SRC := $(call rwildcard,src/,*.cpp)
OBJ = $(subst src,obj,$(subst .cpp,.o,$(SRC)))
MY_SRC := $(call rwildcard,src/my/,*.cpp)
MY_OBJ = $(subst src,obj,$(subst .cpp,.o,$(MY_SRC)))

.PHONY : all

all : $(OBJ)

bin/%.exe : obj/%.o $(MY_OBJ)
	g++ -o "$@" $^ -L"lib\x64" -lfreeglut -lopengl32 -lglu32 -std=c++14

obj/%.o : src/%.cpp include/%.hpp
	if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	g++ -c -o "$@" "$<" -I"include" -std=c++14

obj/%.o : src/%.cpp # include/%.hpp
	if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	g++ -c -o "$@" "$<" -I"include" -std=c++14
