# Makefile DEMAC GeMM
PROGRAM = main.c
PRG_EXE = main.o
GCC = mpicc
CRSC = arm-linux-gnueabi-gcc
NFS_DIR = /home/parallella/DEMAC_nfs
LOCAL_NSF = /home/darptolus/CAPSL/DEMAC/nfs
N_NODES?= 48
N_SIZE?= 10
N_OPR?= 48
N_ITER?= 1

${PRG_EXE}: copy_file 
	ssh parallella@NOPA01 'cd ${NFS_DIR}; ${GCC} -std=c99 -o ${PRG_EXE} -DN_SIZE=${N_SIZE} -DN_OPR=${N_OPR} -DN_ITER=${N_ITER} ${PROGRAM}'
	
copy_file: ${PROGRAM}
	cp ${PROGRAM} ${LOCAL_NSF}/
	
run: ${LOCAL_NSF}/${PRG_EXE}
	ssh parallella@NOPA01 'cd ${NFS_DIR}; mpiexec -machinefile mpiNodeList -n ${N_NODES} ./${PRG_EXE}'
	
init:
	./DEMAC_sshfsEnable.sh

clean:
	rm -f ${LOCAL_NSF}/${PRG_EXE} ${LOCAL_NSF}/${PROGRAM} ${LOCAL_NSF}/M_*
