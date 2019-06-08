# Makefile DEMAC GeMM
PROGRAM = main
GCC = mpicc
NPP?= 4
N_SIZE?= 5
N_OPR?= 48
N_ITER?= 1

${PROGRAM}: ${PROGRAM}.cpp
	${GCC} -o ${PROGRAM}.o -DN_SIZE=${N_SIZE} -DN_OPR=${N_OPR} -DN_ITER=${N_ITER} ${PROGRAM}.cpp

run: ${PROGRAM}.o
	mpiexec -np ${NPP} ./${PROGRAM}.o

clean:
	rm -f ${PROGRAM}.o M_gen_* M_out_*