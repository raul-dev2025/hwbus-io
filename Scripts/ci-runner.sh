#!/usr/bin/env bash
#
# ci-runner.sh - Runner de compilación y test remoto para hwbus-io
#

set -e

# Configuración de entornos y rutas
REMOTE_HOST="builder@buildlab"
REMOTE_ROOT="/mnt/build-output/Repos/hwbus-io.git"
MODULE_SUBDIR="tests"                                   # Módulo a probar
REMOTE_SRC_DIR="${REMOTE_ROOT}/${MODULE_SUBDIR}"        # Directorio del Makefile modular

# === MÓDULO ÚNICO A COMPILAR Y PROBAR ===
TARGET_MODULE="hello"
REMOTE_KO="${REMOTE_SRC_DIR}/${TARGET_MODULE}.ko"
TEST_RUNNER="${REMOTE_ROOT}/Scripts/test-runner.sh"     # === Ruta al runner de prueba

# Rutas de logs (WS y Lab)
LOCAL_LOG_DIR="/mnt/datos_raul/Logs/Buildlab/hwbus-io"
REMOTE_LOG_DIR="/var/log/BuilderLogs/hwbus-io"

LOCAL_BUILD_LOG="${LOCAL_LOG_DIR}/build_latest.log"
LOCAL_TEST_LOG="${LOCAL_LOG_DIR}/test_latest.log"

REMOTE_BUILD_LOG="${REMOTE_LOG_DIR}/build_latest.log"
REMOTE_TEST_LOG="${REMOTE_LOG_DIR}/test_latest.log"

# 1. Purgado defensivo previo de logs anteriores (WS y Lab)
mkdir -p "${LOCAL_LOG_DIR}"
rm -f "${LOCAL_BUILD_LOG}" "${LOCAL_TEST_LOG}"
ssh "${REMOTE_HOST}" "mkdir -p ${REMOTE_LOG_DIR} && rm -f ${REMOTE_BUILD_LOG} ${REMOTE_TEST_LOG}"

echo "============================================="
echo "🧹 Limpiando y Compilando módulo: ${TARGET_MODULE}.ko..."
echo "============================================="

# 2. Invocación de compilación específica para el módulo del Kernel
if ssh "${REMOTE_HOST}" "{ make -C ${REMOTE_SRC_DIR} clean && make -C ${REMOTE_SRC_DIR} MODULE=${TARGET_MODULE}.ko; } > ${REMOTE_BUILD_LOG} 2>&1; cat ${REMOTE_BUILD_LOG}" > "${LOCAL_BUILD_LOG}" 2>&1; then
    echo "✅ BUILD SUCCESSFUL --> ${LOCAL_BUILD_LOG}"
else
    echo "❌ BUILD FAILED -> Ver: ${LOCAL_BUILD_LOG}"
    exit 1
fi

echo "=================================================="
echo "🚀 Ejecutando test de módulo con test-runner.sh..."
echo "=================================================="

# 3. Invocación remota del script de gestión y prueba
if ssh "${REMOTE_HOST}" "cd ${REMOTE_SRC_DIR} && bash ${TEST_RUNNER} ${TARGET_MODULE} > ${REMOTE_TEST_LOG} 2>&1; cat ${REMOTE_TEST_LOG}" > "${LOCAL_TEST_LOG}" 2>&1; then
    echo "✅ TEST FINISHED -> Ver: ${LOCAL_TEST_LOG}"
else
    echo "⚠️ TEST FAILED / BROKEN -> Ver: ${LOCAL_TEST_LOG}"
    exit 2
fi