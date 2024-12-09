CC = g++
CFLAGS = -Wall -std=c++11

OBJECTS1 = priorityqueue.o

TARGET1 = priorityqueue.out

.PHONY: run
run:$(TARGET1)

%.o : %.cpp Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET1) : $(OBJECTS1)
	$(CC) $(CFLAGS) $(OBJECTS1) -o $(TARGET1)

	./$(TARGET1)

.PHONY : clean

clean :
	$(RM) *.o *.out core
