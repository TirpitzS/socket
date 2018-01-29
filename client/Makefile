OBJECTS = err.o client.o
client:$(OBJECTS)
	cc -o client $(OBJECTS)
err.o:err.h err.c
client.o:client.c
.PHONY:clean
clean:
	-rm client $(OBJECTS)**
