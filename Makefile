CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
TARGET = bank_teller

SRCS = src/Utils.cpp \
       src/QueueManager.cpp \
       src/CustomerInterface.cpp \
       src/TellerInterface.cpp \
       src/Statistics.cpp \
       src/AppController.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): main.o

clean:
	rm -f $(OBJS) main.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
