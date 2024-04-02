earth-heightmap-normal-calculator: main.c stb.o
	cc -Wall -Wextra -pedantic -o $@ $^ -lm

test: earth-heightmap-normal-calculator
	./earth-heightmap-normal-calculator .github/gebco_08_rev_elev_540x270.png .github/output_540x270.png

stb.o: stb.c
	cc -c -o $@ $<

