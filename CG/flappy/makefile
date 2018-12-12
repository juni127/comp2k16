compilar:
	gcc main.c -o a -lglut -lGL -lGLU -lIL

make: main.c
	gcc main.c -o a -lglut -lGL -lGLU -lIL -lmpg123 -lao -pthread

dependencias:
	sudo apt install libao-dev
	sudo apt install libmpg123-dev
	sudo apt install libdevil-dev

clean:
	rm a
