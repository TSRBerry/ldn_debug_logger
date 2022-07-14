THIS_MAKEFILE := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIRECTORY := $(abspath $(dir $(THIS_MAKEFILE)))

PROJECT_NAME := $(shell basename $(CURRENT_DIRECTORY))
DLOG_TID := 42000000DE306106

GIT_BRANCH := $(shell git branch --show-current)
GIT_HASH := $(shell git rev-parse --short HEAD)
BUILD_VERSION := $(GIT_BRANCH)-$(GIT_HASH)

TARGETS := dlog_module

dist: all
	rm -rf dist

	mkdir -p dist/atmosphere/contents/$(DLOG_TID)
	cp out/nintendo_nx_arm64_armv8a/release/$(PROJECT_NAME).nsp dist/atmosphere/contents/$(DLOG_TID)/exefs.nsp

	cp mitm.lst dist/atmosphere/contents/$(DLOG_TID)/mitm.lst
	mkdir -p dist/config/ldn_debug_logger
	cp config_template.ini dist/config/ldn_debug_logger/dlog.ini

	mkdir -p dist/atmosphere/contents/$(DLOG_TID)/flags
	touch dist/atmosphere/contents/$(DLOG_TID)/flags/boot2.flag

release: dist
	cd dist; zip -r $(PROJECT_NAME)-$(BUILD_VERSION).zip ./*; cd ../;

all: $(TARGETS)

dlog_module:
	$(MAKE) -f system_module.mk

clean:
	$(MAKE) -f system_module.mk clean
	$(MAKE) -C Atmosphere-libs clean
	rm -rf dist build out

.PHONY: dist release all $(TARGETS) clean
