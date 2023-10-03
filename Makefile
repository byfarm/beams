default:
	clang -c beams.c 
	clang -c calc.c 
	clang -c fileio.c
	clang -o beams beams.o calc.o fileio.o
	./beams
	python3 analyze_data.py
	python3 display_data.py
	wslview plot.png
