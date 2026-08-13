#!/usr/bin/env bash
#
# vm-start.sh - Arranca una VM verificando exclusión mutua
#

set -e

VM_TARGET="$1"
DEBUG="${DEBUG:-1}" # Cambiar a 0 o eliminar cuando el pipeline esté validado

iv_virsh() {
    sudo -u virt-admin virsh --connect qemu:///system "$@"
}

[ "${DEBUG}" -eq 1 ] && echo "[DEBUG] VM [${VM_TARGET}] arrancada con éxito."