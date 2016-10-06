.PHONY: all clean

all: tapencode

tapencode: tapencode.c
	gcc -o $@ $<

clean:
	rm -f tapencode
