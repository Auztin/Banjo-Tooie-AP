all: n64 pc

.PHONY: n64
n64:
	$(MAKE) -C n64

.PHONY: pc
pc:
	$(MAKE) -C pc

clean:
	$(MAKE) -C n64 clean
	$(MAKE) -C pc clean
