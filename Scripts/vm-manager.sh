#!/usr/bin/env bash
#
# vm-manager.sh - Gestor de ciclo de vida de máquinas virtuales para el laboratorio de CI
#

# --- 3. Funcion de Administración (virt-admin) ---
# vwork() {    
    # sudo -u virt-admin /usr/bin/bash --rcfile /var/lib/virt_storage/scripts/bashrc_virt_admin
# }

iv_user() {
  sudo -u virt-admin "$@"
}

# 1. Comprobar exclusión previa: acme-sandbox NO debe estar encendida
if iv_user virsh list --name | grep -q "^acme-sandbox$"; then
    echo "❌ Error de exclusión: acme-sandbox ya está en ejecución de forma anómala."
    exit 1
fi

# 2. Apagado de buildlab si está activa
if iv_user virsh list --name | grep -q "^buildlab$"; then
    echo "=============================="
    echo "🛑 Cerrando la VM buildlab ..."
    echo "=============================="
    iv_user virsh shutdown buildlab

    # Espera activa a que se apague
    while iv_user virsh list --name | grep -q "^buildlab$"; do
        sleep 1
    done
    echo "✅ VM buildlab apagada con éxito."
fi

# 3. Encendido de acme-sandbox tras confirmar el apagado de buildlab