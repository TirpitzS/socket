OBJECTS = err.o server.o
server:$(OBJECTS)
	cc -o server $(OBJECTS) -lpthread
err.o:err.h err.c
server.o:server.c
.PHONY:clean
clean:
	-rm server $(OBJECTS)**
