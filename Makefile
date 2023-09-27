default:
	clang beams.c -o beams -lm
	./beams
	python3 display_data.py
	wslview plot.png
