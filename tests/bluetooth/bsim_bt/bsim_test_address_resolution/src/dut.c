/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bs_bt_utils.h"

#include <stdint.h>

#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/bluetooth.h>

#include <sdc_hci_cmd_le.h>

DECLARE_FLAG(flag_connected);

void dut_procedure(void)
{
	int err;

	err = bt_enable(NULL);
	ASSERT(!err, "bt_enable failed. (%d)\n", err);

	scan_connect_to_first_result();
	wait_connected();

	set_security_l2();
	wait_resolved();

	disconnect();
	wait_disconnected();

	start_periodic_sync();

	// while(1)
	// 	k_sleep(K_MSEC(1));

	PASS("PASS\n");
}
