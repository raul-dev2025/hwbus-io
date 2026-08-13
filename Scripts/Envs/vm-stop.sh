#!/usr/bin/env bash
#
# vm-stop.sh - Apaga una VM con espera activa
#

set -e

VM_TARGET="$1"
DEBUG="${DEBUG:-1}"

iv_virsh() {
    sudo -u virt-admin virsh --connect qemu:///system "$@"
}

