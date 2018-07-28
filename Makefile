all: comp
comp: ds.c
	gcc ds.c -o ds -lm
