CFLAGS += -I../include/
LDFLAGS += -L../build/lib/ -l:libexparser.a -lm

all: \
  exparser_tests \
  exparser_example_1 \
  exparser_example_2

exparser_tests: exparser_tests.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

exparser_example_1: exparser_example_1.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

exparser_example_2: exparser_example_2.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) exparser_tests exparser_example_1 exparser_example_2
