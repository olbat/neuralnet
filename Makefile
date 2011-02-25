CFLAGS= -Wall -ansi -pedantic -O3 -g
LFLAGS= `ls /usr/lib/libboost_*.so | grep "libboost_[^-]*\.so" | grep -v python`
CC= g++ ${CFLAGS}
SNAME= neuralnet
SRC= data.cc example.cc example_list.cc af_identity.cc af_sigmoid.cc neuralnet.cc neuron.cc perceptron.cc layer.cc layer_perceptron.cc layer_list.cc multi_layer_network.cc multi_perceptron_layer_network.cc main.cc
OBJ=$(SRC:.cc=.o)

all : ${SNAME} clean
	@echo success making ${SNAME}
dev : ${SNAME}
	@echo success making ${SNAME}
shared : ${OBJ}
	@${CC} -shared -fPIC -o ${SNAME}.so ${OBJ} ${LFLAGS}
	@echo success making ${SNAME}.so
${SNAME} : ${OBJ}
	@echo making ${SNAME}
	@${CC} -o $@ ${OBJ} ${LFLAGS}
%.o : %.cc
	@echo -n 'compiling $< ... '
	@${CC} -g -o $@ -c $<
	@echo done
clean :
	@echo cleaning object files
	@rm -f ${OBJ} ${SNAME}.so
cleanall : clean
	@echo cleaning executable file
	@rm -f ${SNAME}
