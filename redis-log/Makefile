all: server
	@echo "anet demo"

server :  server.o localtime.o
	$(CC)   -o $@   $^


.PHONY: clean
clean:
	rm -rf *.o *.d server client
