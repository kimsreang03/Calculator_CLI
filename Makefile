execute = cal
sources = ${wildcard src/*.c}
objects = ${sources:.c=.o}
flags = -g -Wall -lm -ldl -fPIC -rdynamic

$(execute): $(objects)
	cc $(objects) $(flags) -o $(execute)

%.o: %.c include/%.h
	cc -c $(flags) $< -o $@


clean:
	-rm $(execute)
	-rm src/*.o
