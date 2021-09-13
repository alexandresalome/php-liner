.DEFAULT_GOAL := help
PROJECT_DIR=$(shell pwd)

.PHONY help:
	@printf "\033[32;1m# php-liner\033[0m\n"
	@printf "\n"
	@printf "  Use environment variable PHP_VERSION: 7.1 to 8.1\n"
	@printf "  Don't forget to clean and rebuild before running compile, shell, or test\n"
	@printf "\n"
	@grep -Eh '^\.PHONY: [a-zA-Z_-]+[^#]*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = "(:| ## )"}; {printf "  \033[36m%-20s\033[0m %s\n", $$2, $$3}'
	@printf "\n"

PHP_VERSION ?= 7.3
IMAGE="php-liner:${PHP_VERSION}-cli"
RUN=docker run \
	--rm \
	--volume "${PROJECT_DIR}:/php-liner" \
	--workdir "/php-liner/ext" \
	--interactive \
	--tty \
	${IMAGE} \


.PHONY: build ## build docker image
build:
	docker build \
		--file docker/Dockerfile-php-${PHP_VERSION} \
		--tag ${IMAGE} \
		docker

.PHONY: clean ## cleans project
clean:
	git clean -fdx ext || true

.PHONY: compile ## compiles the extension
compile:
	${RUN} bash -c "phpize; ./configure; make"

.PHONY: shell ## starts a shell
shell:
		${RUN} bash

.PHONY: test ## runs tests
test:
		${RUN} make test TESTS=-q
