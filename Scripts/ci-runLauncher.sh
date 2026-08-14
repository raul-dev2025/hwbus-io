#!/usr/bin/env bash
#
# ci-runLauncher.sh - Lanzador de script remoto ci-runner.sh
#

SANDBOX_HOST="sandbox"
REMOTE_SCRIPTS="/mnt/build-output/Repos/hwbus-io.git/Scripts"
MANIFEST_FILE="/mnt/build-output/Repos/hwbus-io.git/build_state.env"

LOCAL_LOG_DIR="/mnt/datos_raul/Logs/Sandbox/hwbus-io"
LOCAL_LTP_LOG="ltp_latest.log"
LOCAL_KO_LOG="ko_latest.log"


echo "==============================================="
echo "🚀 Arrancando entorno de pruebas (ACME, CIA)..."
echo "==============================================="

# 1. Arrancar vm y comprobar puerto 22
Scripts/Envs/vm-start.sh acme-sandbox
Scripts/Envs/vm-poll.sh acme-sandbox 22 30

# Consultar el manifiesto para determinar el log KO/LTP
TARGET_TYPE=$(ssh "${SANDBOX_HOST}" "grep '^TARGET_TYPE=' '${MANIFEST_FILE}' | cut -d'=' -f2 | tr -d '\"'")
if [ "${TARGET_TYPE}" = "LTP" ]; then
  LOCAL_RUN_LOG="${LOCAL_LOG_DIR}/${LOCAL_LTP_LOG}"
elif [ "${TARGET_TYPE}" = "KO" ]; then
  LOCAL_RUN_LOG="${LOCAL_LOG_DIR}/${LOCAL_KO_LOG}"
else
  LOCAL_RUN_LOG="${LOCAL_LOG_DIR}/runner_latest.log"
fi

# 1. Purgado defensivo de logs locales
mkdir -p "${LOCAL_LOG_DIR}"
rm -f "${LOCAL_RUN_LOG}"

# 2. Invocación SSH con captura de salida y evaluación de retorno
if ssh "${SANDBOX_HOST}" "${REMOTE_SCRIPTS}/Envs/ci-runner.sh" > "${LOCAL_RUN_LOG}" 2>&1; then
    echo "✅ TEST RUNNER SUCCESSFUL --> ${LOCAL_RUN_LOG}"
else
    echo "❌ TEST RUNNER FAILED -> Ver: ${LOCAL_RUN_LOG}"
    exit 1
fi

echo "=============================================="
echo "🛑 Liberando infraestructura de compilación..."
echo "=============================================="

STOP_OUTPUT=$(Scripts/Envs/vm-stop.sh acme-sandbox)
echo "${STOP_OUTPUT}"

if echo "${STOP_OUTPUT}" | grep -q "apagada con éxito"; then
    echo "✅ Infraestructura ACME liberada correctamente."
else
    echo "⚠️ Advertencia: Revisa el estado de la VM mediante ./vm-status.sh"
fi