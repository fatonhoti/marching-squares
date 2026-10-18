#!/usr/bin/env bash
set -euo pipefail

case "${1:-deb}" in
    deb)    BUILD_TYPE=Debug ;;
    rel)    BUILD_TYPE=Release ;;
    reldeb) BUILD_TYPE=RelWithDebInfo ;;
    *)
        echo "Usage: $0 [deb|rel|reldeb] [program-args...]" >&2
        exit 1
        ;;
esac

BINARY="build/$BUILD_TYPE/marching-squares"

if [[ ! -x "$BINARY" ]]; then
    echo "Binary not found at $BINARY. Run: ./scripts/build.sh ${1:-deb}" >&2
    exit 1
fi

exec "$BINARY" "${@:2}"
