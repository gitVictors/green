# Имя исполняемого файла
TARGET = main


# Компилятор и флаги
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -O0 
LDFLAGS = 
#-ljsoncpp -lws2_32 -lcrypto

# Список исходных файлов
SRCS = main.cpp tv_control.cpp tv.cpp 

# Объектные файлы (меняем .cpp на .o)
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET) $(TARGET_2)

# Правило сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Правило сборки объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило очистки
clean:
	rm -f $(OBJS) $(TARGET) 

# Фиктивные цели
.PHONY: all clean
