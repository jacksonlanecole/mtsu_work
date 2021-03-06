# Muchas gracias a Hilton Lipschitz por este makefile. Se ecuentra a
# https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
CC = g++
CFLAGS = -std=c++17 -ggdb

SRCDIR   := src
BUILDDIR := build
TARGET   := bin/main

SRCEXT   := cpp
SOURCES  := $(shell find $(SRCDIR) -type f -name \*.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC      := -I include

DOCSDIR := docs
TEXDOCSDIR := $(DOCSDIR)/tex
TEXSRCS := $(shell find $(DOCSDIR) -type f -name \*.tex)
TEXBUILDDIR := $(TEXDOCSDIR)/build
PDFDOCS = $(shell find $(TEXBUILDDIR) -type f -name \*.pdf)
PDFDOCSDIR := docs/pdf

RM = rm -rf
MKDIR = mkdir -p

all: setup $(TARGET)

setup:
	$(MKDIR) bin

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

docs: $(TEXSRCS)
	@mkdir -p $(TEXBUILDDIR)
	@latexmk -pdf -use-make -pdflatex="pdflatex -interaction=nonstopmode" \
		     -outdir=build -cd $(TEXSRCS)
	@make movepdfs
	#@$(RM) $(TEXBUILDDIRS)

movepdfs: $(PDFDOCS)
	@mkdir -p $(PDFDOCSDIR)
	@mv $< $(PDFDOCSDIR)

very_clean:
	make clean
	make clean_docs

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

clean_docs:
	@echo "Cleaning docs..."
	@$(RM) $(TEXBUILDDIR)/*



# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
main: $(TARGET)
	@echo "$(CC) $(CFLAGS) -o $(TARGET) $^"
