FOLDERS=SA6 Server
.PHONY: all $(FOLDERS)
all: $(FOLDERS)

$(FOLDERS) :
	make -C $@
