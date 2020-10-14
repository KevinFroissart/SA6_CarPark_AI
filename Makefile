FOLDERS=SA6
.PHONY: all $(FOLDERS)
all: $(FOLDERS)

$(FOLDERS) :
	make -C $@
