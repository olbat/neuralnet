# Standard things

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

# Local variables

OBJS_$(d)	:= \
	$(d)/af_identity.o \
	$(d)/af_sigmoid.o \
	$(d)/data.o \
	$(d)/example.o \
	$(d)/example_list.o \
	$(d)/layer.o \
	$(d)/layer_list.o \
	$(d)/layer_perceptron.o \
	$(d)/multi_layer_network.o \
	$(d)/neuralnet.o \
	$(d)/neuron.o \
	$(d)/perceptron.o 


DEPS_$(d)	:= $(OBJS_$(d):%=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))


# Local rules

$(OBJS_$(d)):	CF_TGT := -I$(d)
$(d)/neuralnet.a: $(OBJS_$(d))
	$(ARCH)
		

# Standard things

-include	$(DEPS_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))

