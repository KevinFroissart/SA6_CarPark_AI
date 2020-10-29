FOLDERS=SA6
.PHONY: all $(FOLDERS) doc
all: $(FOLDERS)

$(FOLDERS) :
	make -C $@
