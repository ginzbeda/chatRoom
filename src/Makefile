CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++14

MKDIR_P = mkdir -p
OBJ_DIR = obj

all: create_fs fs fs_tests submission

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

# submission:
# 	zip -r fs-submission.zip src

obj/%.o: src/%.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

create_fs: obj/create_fs.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

fs: obj/main.o obj/fs.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

obj/fs_tests.o: test/fs_tests.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

fs_tests : obj/fs.o obj/fs_tests.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	rm -f create_fs fs fs_tests disk0 disk1
	rm -rf obj
	rm -f *~ obj/*.o obj/*.a *.zip
