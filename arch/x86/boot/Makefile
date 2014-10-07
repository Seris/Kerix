C_FILES := $()

all:
	@ # Creating init file
	${AS} ${ASFLAGS} init.s -o ${virtualtree}/${DIR}/${INIT_OBJ_NAME}
	${CC} ${CFLAGS} -c main.c -o export-main.o