#!/usr/bin/env bash
#
# vm-status.sh - Helper de consulta para virt-admin
#

set -e

iv_user() {
    sudo -u virt-admin virsh --connect qemu:///system "$@"
}

