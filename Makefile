test: earth-heightmap-normal-calculator
	./earth-heightmap-normal-calculator gebco_08_rev_elev_21600x10800.png output.png

stb.o: stb.c
	cc -c -o $@ $<

earth-heightmap-normal-calculator: main.c stb.o
	cc -o $@ $^ -lm
