main:
	gcc -O3 -Iheader \
	    src/main/*.c \
	    src/main/util/*.c \
	    src/main/commands/*.c \
	    -o fsh
