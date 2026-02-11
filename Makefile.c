# Makefile.c - C/CPython Extension Makefile
# For building C extensions if needed for obsidian-pub

CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
PYTHON = python3
PYTHON_CONFIG = python3-config

# Python include and library paths
PYTHON_INCLUDES = $(shell $(PYTHON_CONFIG) --includes)
PYTHON_LIBS = $(shell $(PYTHON_CONFIG) --libs)
PYTHON_LDFLAGS = $(shell $(PYTHON_CONFIG) --ldflags)

# Directories
SRC_DIR = c_src
BUILD_DIR = build
DIST_DIR = dist

# Source files
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
C_OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Shared library
SHARED_LIB = $(BUILD_DIR)/obsidian_pub_ext.so

.PHONY: all clean test install c-build c-clean c-test

all: c-build

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(PYTHON_INCLUDES) -c $< -o $@

# Build shared library
$(SHARED_LIB): $(C_OBJECTS)
	$(CC) -shared $(PYTHON_LDFLAGS) $^ -o $@

c-build: $(SHARED_LIB) ## Build C extensions
	@echo "C extension built: $(SHARED_LIB)"

c-clean: ## Clean C build artifacts
	rm -rf $(BUILD_DIR) $(DIST_DIR)
	find . -name "*.o" -delete
	find . -name "*.so" -delete
	find . -name "*.pyc" -delete
	@echo "C build artifacts cleaned"

c-test: $(SHARED_LIB) ## Test C extensions
	@echo "Testing C extensions..."
	@if [ -f tests/test_c_ext.py ]; then \
		$(PYTHON) tests/test_c_ext.py; \
	else \
		echo "No C extension tests found"; \
	fi

c-install: $(SHARED_LIB) ## Install C extensions
	@echo "Installing C extensions..."
	cp $(SHARED_LIB) $(shell $(PYTHON) -c "import site; print(site.getsitepackages()[0])")/

# Example: Static library
LIB_NAME = libobsidian.a
$(LIB_NAME): $(C_OBJECTS)
	ar rcs $@ $^

static-lib: $(LIB_NAME) ## Build static library
	@echo "Static library built: $(LIB_NAME)"

# Help
help: ## Show this help message
	@echo "C/CPython Extension Makefile"
	@echo "============================="
	@echo ""
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  %-15s %s\n", $$1, $$2}'
