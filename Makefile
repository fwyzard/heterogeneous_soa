CC_SRC := $(shell find src/ -name '*.cc' -not -path '*/alpaka/*')
CC_OBJ := $(CC_SRC:%=%.o)
CC_DEP := $(CC_OBJ:%.o=%.d)

ALPAKA_SRC := $(shell find src/ -name '*.cc' -path '*/alpaka/*')
ALPAKA_OBJ := $(ALPAKA_SRC:%=%.serial.o) $(ALPAKA_SRC:%=%.cuda.o) $(ALPAKA_SRC:%=%.hip.o)
ALPAKA_DEP := $(ALPAKA_OBJ:%.o=%.d)

SRC := $(CC_SRC) $(ALPAKA_SRC)
OBJ := $(CC_OBJ) $(ALPAKA_OBJ)
DEP := $(CC_DEP) $(ALPAKA_DEP)

CXX := g++

CXXFLAGS := -std=c++17 -O2 -flto -g -Wall -fPIC -MMD -march=native -mtune=native -Isrc -Iexternal/alpaka/include -Iexternal/boost/include

ALPAKA_SERIAL_CXXFLAGS := -DALPAKA_ACC_CPU_B_SEQ_T_SEQ_ENABLED -DALPAKA_HOST_ONLY
ALPAKA_CUDA_CXXFLAGS   := -DALPAKA_ACC_GPU_CUDA_ENABLED -DALPAKA_HOST_ONLY -I/usr/local/cuda/include
ALPAKA_HIP_CXXFLAGS    := -DALPAKA_ACC_GPU_HIP_ENABLED -DALPAKA_HOST_ONLY -I/opt/rocm/include -I/opt/rocm/include/hip -I/opt/rocm/include/hiprand -D__HIP_PLATFORM_AMD__ -D__HIP_PLATFORM_HCC__

LD := g++
LDFLAGS := -L/usr/local/cuda/lib64 -Wl,-rpath,/usr/local/cuda/lib64 -lcudart -lcuda -L/opt/rocm/lib -L/opt/rocm/lib64 -Wl,-rpath,/opt/rocm/lib -Wl,-rpath,/opt/rocm/lib64 -lamdhip64 -lrt

.PHONY: all clean distclean dump

all: test


clean:
	rm -f $(OBJ) $(DEP)

distclean:
	rm -f test $(OBJ) $(DEP)

%.cc.o: %.cc Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.cc.serial.o: %.cc Makefile
	$(CXX) $(CXXFLAGS) $(ALPAKA_SERIAL_CXXFLAGS) -c $< -o $@

%.cc.cuda.o: %.cc Makefile
	$(CXX) $(CXXFLAGS) $(ALPAKA_CUDA_CXXFLAGS) -c $< -o $@

%.cc.hip.o: %.cc Makefile
	$(CXX) $(CXXFLAGS) $(ALPAKA_HIP_CXXFLAGS) -c $< -o $@

test: $(OBJ) Makefile
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

-include $(DEP)
