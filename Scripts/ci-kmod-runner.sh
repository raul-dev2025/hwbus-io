#!/usr/bin/env bash
# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# ELA - Ejecutor Local Autónomo
# ci-kmod-runner.sh - ELA para desarrollo de módulos.
#
set -e

MANIFEST_FILE="${1:-/mnt/build-output/Repos/hwbus-io.git/build_state.env}"

LOG_DIR="/var/log/Sandbox/hwbus-io"
RUN_LOG="${LOG_DIR}/ltp_latest.log"

# 1. Validar existencia del manifiesto
if [ ! -f "${MANIFEST_FILE}" ]; then
    echo "❌ Error: No se encontró el manifiesto de build en ${MANIFEST_FILE}"
    exit 1
fi

# 2. Cargar variables del manifiesto
source "${MANIFEST_FILE}"

mkdir -p "${LOG_DIR}"
rm -f "${RUN_LOG}"
