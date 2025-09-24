#!/bin/bash

SCRIPTS_DIR="./scripts"

help() {
	echo "Usage: $0 <script_name> [args...]"
	echo "Available scripts:"

	for file in "$SCRIPTS_DIR"/*.py; do
		[ -e "$file" ] || continue
		script_base=$(basename "$file" .py)

		[[ "$script_base" == _* ]] && continue # skip scripts starting with underscore

		echo "  - $script_base"
	done
	exit 0
}

if [ $# -lt 1 ] || [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
	help
fi

SCRIPT_NAME="$SCRIPTS_DIR/$1.py"
shift # remove first argument

python3 "$SCRIPT_NAME" "$@"
