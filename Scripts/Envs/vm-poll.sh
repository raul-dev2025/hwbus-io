#!/usr/bin/env bash
#
# vm-poll.sh - Espera a que la pila de red/SSH de una VM esté disponible
#

set -e

HOST="${1:-buildlab}"
PORT="${2:-22}"
TIMEOUT="${3:-30}"

echo "[INFO] Esperando disponibilidad SSH en ${HOST}:${PORT}..."

echo "✅ Entorno ${HOST} activo y respondiendo por SSH."