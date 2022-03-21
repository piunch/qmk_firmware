// Copyright 2022 Jorge Munoz (@Jorge Munoz)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER Jorge Munoz
#define PRODUCT      9teclas

#define MATRIX_ROWS 3
#define MATRIX_COLS 3

#define MATRIX_ROW_PINS { F4, F5, F6 }
#define MATRIX_COL_PINS { D1, D0, D4 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define TAPPING_TERM 200
