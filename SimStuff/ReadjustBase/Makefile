OBJS = main.o Matrix.o Molecule.o SimulatorSetup.o
Readjust.exe : ${OBJS}
	g++ -O2 -o $@ $^
%.o : %.cxx
	g++ -O2 -c $<
${OBJS} : Matrix.h

clean :
	rm -f .*~ *~ Readjust.exe *.o
