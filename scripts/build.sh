#!/usr/bin/env bash
set -euo pipefail

case "${1:-deb}" in
    deb)    BUILD_TYPE=Debug ;;
    rel)    BUILD_TYPE=Release ;;
    reldeb) BUILD_TYPE=RelWithDebInfo ;;
    *)
        echo "Usage: $0 [deb|rel|reldeb] [cmake-args...]" >&2
        exit 1
        ;;
esac

BUILD_DIR="build/$BUILD_TYPE"

echo ">> Building $BUILD_TYPE in $BUILD_DIR" >&2

cmake -S . -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    "${@:2}"

cmake --build "$BUILD_DIR" -j"$(nproc)"

ln -sf "$(realpath "$BUILD_DIR/compile_commands.json")" \
    build/compile_commands.json
