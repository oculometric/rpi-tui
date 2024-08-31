C_IN	= $(wildcard *.cpp)
EXE 	= rpi-tui

$(EXE):
	g++ $(C_IN) -o $(EXE) -I stui/inc

build: $(EXE)

clean:
	rm -f $(EXE)

execute: $(EXE)
	./$(EXE)
