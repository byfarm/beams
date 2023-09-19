default:
	clang beams.c -o beams
	./beams
	python3 display_data.py
	wslview plot.png
