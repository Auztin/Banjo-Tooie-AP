all: gen_constants/short_constants.txt

DATA:= $(shell find ../ap/data -type f -name '*.py' | sed 's/ /\\ /g')
gen_constants/short_constants.txt: gen_constants/gen_constants.py $(DATA) ../ap/options.py ../ap/archipelago.json gen_constants/template_header.yaml
	python $<

.PHONY: clean
clean:
	$(RM) gen_constants/short_constants.txt
