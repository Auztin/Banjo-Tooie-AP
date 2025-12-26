GAME      :=Banjo_Tooie
GAME_NAME :=Banjo-Tooie
GAME_LOWER:=banjo_tooie
GAME_SHORT:=bt
PYTHON=$(shell realpath "tools/archipelago/venv/bin/")

.PHONY: all
all: n64patch pc

.PHONY: tools
tools:
	@$(MAKE) --no-print-directory -C tools

.PHONY: n64
n64: tools
	@$(MAKE) --no-print-directory -C n64

.PHONY: n64patch
n64patch: tools
	@$(MAKE) --no-print-directory -C n64 patch

.PHONY: pc
pc:
	@$(MAKE) --no-print-directory -C pc/Flashcart

.PHONY: release
release: clean .WAIT all
	mkdir -p release ap/assets
	$(RM) release/* ap/assets/*
	cp n64/rom/$(GAME).patch ap/assets/
	cp n64/rom/$(GAME)_Patched.z64-md5 ap/assets/
	cp pc/Bizhawk.lua ap/assets/connector_$(GAME_LOWER)_bizhawk.lua
	cd tools/archipelago/repo && "$(PYTHON)/python" Launcher.py "Build APWorlds" $(GAME_NAME)
	mv tools/archipelago/repo/build/apworlds/$(GAME_LOWER).apworld release/
	7z d release/$(GAME_LOWER).apworld $(GAME_LOWER)/.git $(GAME_LOWER)/.gitignore $(GAME_LOWER)/README.md $(GAME_LOWER)/template.yaml
	cp pc/Bizhawk.lua release/connector_$(GAME_LOWER)_bizhawk.lua
	cp pc/Project64.js release/connector_$(GAME_LOWER)_pj64.js
	cp pc/Flashcart/Flashcart release/connector_$(GAME_LOWER)_flashcart_linux
	cp pc/Flashcart/Flashcart.exe release/connector_$(GAME_LOWER)_flashcart.exe

clean:
	@$(MAKE) --no-print-directory -C tools clean
	@$(MAKE) --no-print-directory -C n64 clean
	@$(MAKE) --no-print-directory -C pc/Flashcart clean
