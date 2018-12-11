CXX=g++
CXXFLAGS += -g -pthread -Wall 
# CPPFLAGS += -isystem src -std=c++14

MKDIR_P = mkdir -p
OBJ_DIR = obj

# TARGET = main server

main : main.o server.o
	$(CXX) $(CXXFLAGS) -o main main.o server.o

main.o : main.cpp server.h
	$(CXX) $(CXXFLAGS) -c main.cpp

server.o : server.cpp user.cpp chat.cpp server.h user.h chat.h
	$(CXX) $(CXXFLAGS) -c server.cpp user.cpp chat.cpp -o server.h user.h chat.h

# ${OBJ_DIR}:
# 	${MKDIR_P} ${OBJ_DIR}

# $(TARGET) : $(TARGET).c
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).c

# obj/%.o: src/%.cpp ${OBJ_DIR}
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# main: obj/main.o obj/my_malloc.o
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# obj/malloc_tests.o: test/malloc_tests.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# malloc_tests : obj/my_malloc.o obj/malloc_tests.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	# rm -f main malloc_tests test_detail.xml
	# rm -rf obj
	# rm -f *~ obj/*.o obj/*.a *.zip
	rm main *.o
