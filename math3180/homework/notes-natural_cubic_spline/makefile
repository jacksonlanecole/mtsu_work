SRCDIR   := src
BUILDDIR := build

SOURCES  := $(shell find $(SRCDIR) -type f -name \*.$(SRCEXT))

SRCEXT   := tex
TEXSRCS := $(shell find $(SRCDIR) -maxdepth 1 -type f -name \*.$(SRCEXT))
TEXBUILDDIRS = $(SRCDIR)/build
PDFDOCS = $(shell find $(TEXBUILDDIRS) -type f -name \*.pdf)
PDFDOCSDIR := pdf

RM = rm -rf


docs: $(TEXSRCS)
	@latexmk -pdf -cd -use-make -outdir=build -pdflatex="pdflatex" $(TEXSRCS)
	@make movepdfs
	@$(RM) $(TEXBUILDDIRS)

movepdfs: $(PDFDOCS)
	@mkdir -p $(PDFDOCSDIR)
	@mv $< $(PDFDOCSDIR)
