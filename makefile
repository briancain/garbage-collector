CC = gcc
OBJECTS = garbageCollector.o gcLogger.o main.o list.o heapList.o

gc: $(OBJECTS)
	        $(CC) $(OBJECTS) -o gc

clean:
	        rm *.o gc
