BUILD_DIR := build
TEST_EXE := $(BUILD_DIR)/test/nox-test

CMAKE := cmake
CTEST := ctest

all:	test
.PHONY:	all

test:
	$(MAKE) build
	cd $(BUILD_DIR) && $(CTEST) -V
.PHONY:	test

build:
	$(MAKE) init
	$(CMAKE) --build $(BUILD_DIR)
.PHONY:	build

init:
	if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
		cd $(BUILD_DIR); \
		$(CMAKE) -G Ninja \
		    -DCMAKE_CXX_COMPILER=clang++ \
		    -DCMAKE_CXX_FLAGS="-fcolor-diagnostics" \
		    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
		    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		    ..; \
	fi
.PHONY:	init
