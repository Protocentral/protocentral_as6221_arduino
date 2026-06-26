#!/usr/bin/env bash
#
# Compile Example 1 (basic temperature reading) and upload it to a
# connected Arduino UNO R4 Minima.
#
# Usage:
#   ./scripts/build_upload_example1.sh [PORT]
#
# If PORT is omitted, the script auto-detects the UNO R4 Minima via
# `arduino-cli board list`.
#
# Requires: arduino-cli (https://arduino.github.io/arduino-cli/)

set -euo pipefail

FQBN="arduino:renesas_uno:minima"
CORE="arduino:renesas_uno"

# Resolve paths relative to this script so it works from any CWD.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
SKETCH_DIR="${REPO_ROOT}/examples/01-basic-temperature-reading"

if ! command -v arduino-cli >/dev/null 2>&1; then
  echo "Error: arduino-cli not found. Install it from https://arduino.github.io/arduino-cli/" >&2
  exit 1
fi

if [ ! -d "${SKETCH_DIR}" ]; then
  echo "Error: sketch directory not found: ${SKETCH_DIR}" >&2
  exit 1
fi

# Make sure the Renesas UNO core is installed.
if ! arduino-cli core list | grep -q "${CORE}"; then
  echo ">> Installing core ${CORE} ..."
  arduino-cli core update-index
  arduino-cli core install "${CORE}"
fi

# Determine the upload port: use the argument if given, otherwise auto-detect.
PORT="${1:-}"
if [ -z "${PORT}" ]; then
  echo ">> Auto-detecting Arduino UNO R4 Minima ..."
  PORT="$(arduino-cli board list | awk -v fqbn="${FQBN}" '$0 ~ fqbn {print $1; exit}')"
  if [ -z "${PORT}" ]; then
    echo "Error: no board matching ${FQBN} found." >&2
    echo "       Connect the board or pass the port explicitly:" >&2
    echo "       $0 /dev/cu.usbmodemXXXX" >&2
    exit 1
  fi
fi
echo ">> Using port: ${PORT}"

echo ">> Compiling ${SKETCH_DIR} ..."
arduino-cli compile --fqbn "${FQBN}" --library "${REPO_ROOT}" "${SKETCH_DIR}"

echo ">> Uploading to ${PORT} ..."
arduino-cli upload --fqbn "${FQBN}" --port "${PORT}" "${SKETCH_DIR}"

echo ">> Done."
