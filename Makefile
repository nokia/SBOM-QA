.PHONY: install build serve clean help

help:
	@echo "Available targets:"
	@echo "  install  - Install Python dependencies"
	@echo "  build    - Build the MkDocs site (same as GitHub Action)"
	@echo "  serve    - Serve the site locally for development"
	@echo "  clean    - Remove the built site directory"

install:
	pip install -r requirements.txt

build:
	mkdocs build --strict

serve:
	mkdocs serve

clean:
	rm -rf site/
