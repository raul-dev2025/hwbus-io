#!/usr/bin/env bash
#
# ci-runLauncher.sh - Lanzador de script remoto ci-runner.sh
#

VM_NAME="acme-sandbox"
SANDBOX_HOST="sandbox"
REMOTE_SCRIPTS="/mnt/build-output/Repos/hwbus-io.git/Scripts"
MANIFEST_FILE="/mnt/build-output/Repos/hwbus-io.git/build_state.env"

LOCAL_LOG_DIR="/mnt/datos_raul/Logs/Sandbox/hwbus-io"

echo "==============================================="
echo "🚀 Arrancando entorno de pruebas (ACME, CIA)..."
echo "==============================================="

# 1. Arrancar vm y comprobar puerto 22
Scripts/Envs/vm-start.sh "${VM_NAME}"

if ! Scripts/Envs/vm-poll.sh "${SANDBOX_HOST}" 22 30; then
    echo "❌ Error: La VM no levantó el servicio SSH a tiempo."
    echo "=============================================="
    echo "🛑 Liberando infraestructura..."
    echo "=============================================="
    Scripts/Envs/vm-stop.sh "${VM_NAME}"
    exit 1
fi

# 2. Consultar el manifiesto para determinar el log KO/LTP
TARGET_TYPE=$(ssh "${SANDBOX_HOST}" "grep '^TARGET_TYPE=' '${MANIFEST_FILE}' | cut -d'=' -f2 | tr -d '\"'")
if [ "${TARGET_TYPE}" = "LTP" ]; then
  LOG_FILENAME="ltp_latest.log"
elif [ "${TARGET_TYPE}" = "KO" ]; then
  LOG_FILENAME="ko_latest.log"
else
  LOG_FILENAME="runner_latest.log"
fi

LOCAL_RUN_LOG="${LOCAL_LOG_DIR}/${LOG_FILENAME}"
REMOTE_LOG_PATH="/var/log/Sandbox/hwbus-io/${LOG_FILENAME}"

echo "ℹ️ Target detectado: [${TARGET_TYPE:-DESCONOCIDO}]"

# 3. Purgado defensivo de logs locales
mkdir -p "${LOCAL_LOG_DIR}"
rm -f "${LOCAL_RUN_LOG}"

# 4. Invocación SSH con captura de salida y evaluación de retorno
EXEC_STATUS=0
if ssh "${SANDBOX_HOST}" "${REMOTE_SCRIPTS}/ci-runner.sh"; then
    echo "✅ TEST RUNNER SUCCESSFUL"
else
    echo "❌ TEST RUNNER FAILED"
    EXEC_STATUS=1
fi

# Extraemos el log nativo generado dentro de la Sandbox
if ssh "${SANDBOX_HOST}" "cat '${REMOTE_LOG_PATH}'" > "${LOCAL_RUN_LOG}" 2>/dev/null; then
    echo "📄 Log guardado correctamente en: ${LOCAL_RUN_LOG}"
else
    echo "⚠️ No se pudo obtener el archivo de log remoto desde ${REMOTE_LOG_PATH}."
fi

echo "=============================================="
echo "🛑 Liberando infraestructura de compilación..."
echo "=============================================="

STOP_OUTPUT=$(Scripts/Envs/vm-stop.sh "${VM_NAME}")
echo "${STOP_OUTPUT}"

if echo "${STOP_OUTPUT}" | grep -q "apagada con éxito"; then
    echo "✅ Infraestructura ACME liberada correctamente."
else
    echo "⚠️ Advertencia: Revisa el estado de la VM mediante ./vm-status.sh"
fi

exit ${EXEC_STATUS}