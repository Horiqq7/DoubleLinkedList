EXEC = tema1

build:
	gcc -o $(EXEC) main.c
	
run:
	./$(EXEC)

clean:
	rm -f $(EXEC)