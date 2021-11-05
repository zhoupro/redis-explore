server : zmalloc.o server.o
	$(CC)   -o $@   $^

%.o: %.c 
	$(CC) -DREDIS_TEST=1 -MMD -o $@ -c $<


.PHONY: clean
clean:
	rm -rf *.o *.d server
