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


VM_RUNNING=${virsh list --name}

sudo -u virt-admin /usr/bin/bash
echo "==============================="
echo "🚀 Comprobando actividad vm ..."
echo "==============================="
virsh list --all --title
# aqui podríamos pedir pulsar la barra espaciadora para continuar

if [ ${VM_RUNNING} = "buildlab" ]; then
    echo "=============================="
    echo "🛑 Cerrando el laboratorio ..."
    echo "=============================="
    virsh shutdown buildlab
    sleep 15  
elif [ ${VM_RUNNING} = "acme-sandbox" ]; then
    echo "====================================="
    echo "🧪 Vm ${VM_RUNNING} en funcionamiento"
    echo "====================================="
else
    echo "❌ Error: No hay ninguna vm activa"
    echo "${VM_RUNNING}"
    exit 1
fi

# Hay que comprobar que no haya ninguna vm en marcha antes 
# de encender el sandbox
virsh start acme-sandbox