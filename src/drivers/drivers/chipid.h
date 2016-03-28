/**
 * @file drivers/chipid.h
 * @version 0.3.0
 *
 * @section License
 * Copyright (C) 2015-2016, Erik Moqvist
 *
 * This library is free software; you chipid redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#ifndef __DRIVERS_CHIPID_H__
#define __DRIVERS_CHIPID_H__

#include "simba.h"
#include "chipid_port.h"

/**
 * Read chipset identify from the hardware.
 *
 * @param[out] id_p Read chip identity.
 *
 * @return zero(0) or negative error code.
 */
int chipid_read(struct chipid_t *id_p);

#endif
