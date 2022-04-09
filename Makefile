CC_SRC=$(wildcard *.cc */*.cc */*/*.cc)
CC_OBJ=$(CC_SRC:%=%.o)
CC_DEP=$(SRC:%=%.d)

CU_SRC=$(wildcard *.cu */*.cu */*/*.cu)
CU_OBJ=$(CU_SRC:%=%.o)
CU_DEP=$(SRC:%=%.d)

SRC=$(CC_SRC) $(CU_SRC)
OBJ=$(CC_OBJ) $(CU_OBJ)
DEP=$(CC_DEP) $(CU_DEP)

CXX=g++

CXXFLAGS=-std=c++17 -O2 -flto -g -Wall -fPIC -MMD -march=native -mtune=native -I. -I/usr/local/cuda/include -D__HIP_PLATFORM_AMD__ -I/opt/rocm/include -I/opt/rocm/include/hip

NVCC=/usr/local/cuda/bin/nvcc
NVCC_FLAGS=-std=c++17 -O3

LD=g++
LDFLAGS=-L/usr/local/cuda/lib64 -Wl,-rpath,/usr/local/cuda/lib64 -lcudart -lcuda -L/opt/rocm/lib -L/opt/rocm/lib64 -Wl,-rpath,/opt/rocm/lib -Wl,-rpath,/opt/rocm/lib64 -lamdhip64 -lrt

.PHONY: all clean distclean dump

all: test


clean:
	rm -f $(OBJ) $(DEP)

distclean:
	rm -f test $(OBJ) $(DEP)

dump: $(OBJ:%.o=%.asm)


test: $(OBJ) Makefile
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

%.cc.o: %.cc Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.cu.o: %.cu Makefile
	$(NVCC) $(NVCC_FLAGS) -ccbin $(CXX) -Xcompiler '$(CXXFLAGS)' -c $< -o $@

%.cc.asm: %.cc.o
	objdump --demangle --disassemble --disassembler-options=intel-mnemonic,x86-64 --no-show-raw-insn --reloc $< > $@

-include $(DEP)
