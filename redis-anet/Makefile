all: server client
	@echo "anet demo"

server : anet.o zmalloc.o server.o
	$(CC)   -o $@   $^

client : anet.o zmalloc.o client.o
	$(CC)   -o $@   $^

%.o: %.c 
	$(CC) -O0 -DREDIS_TEST=1 -MMD -o $@ -c $<


.PHONY: clean
clean:
	rm -rf *.o *.d server client
