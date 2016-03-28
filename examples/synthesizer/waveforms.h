/**
 * @file waveforms.h
 * @version 0.3.0
 *
 * @section License
 * Copyright (C) 2015-2016, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
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

#ifndef __WAVEFORMS_H__
#define __WAVEFORMS_H__

#include "simba.h"

/**
 * A sine wave.
 *
 *   32767   ,--.          ,--.          ,-
 *          /    \        /    \        /
 *         /      \      /      \      /
 *                 \    /        \    /
 *  -32767          `--´          `--´
 */
static int32_t waveform_sine_256[] = {
    0, 804, 1608, 2411, 3212, 4011, 4808, 5602,
    6393, 7179, 7962, 8740, 9512, 10279, 11039, 11793,
    12540, 13279, 14010, 14733, 15446, 16151, 16846, 17531,
    18205, 18868, 19520, 20160, 20787, 21403, 22005, 22595,
    23170, 23732, 24279, 24812, 25330, 25832, 26319, 26790,
    27245, 27684, 28106, 28511, 28898, 29269, 29621, 29956,
    30273, 30572, 30852, 31114, 31357, 31581, 31785, 31971,
    32138, 32285, 32413, 32521, 32610, 32679, 32728, 32758,
    32768, 32758, 32728, 32679, 32610, 32521, 32413, 32285,
    32138, 31971, 31785, 31581, 31357, 31114, 30852, 30572,
    30273, 29956, 29621, 29269, 28898, 28511, 28106, 27684,
    27245, 26790, 26319, 25832, 25330, 24812, 24279, 23732,
    23170, 22595, 22005, 21403, 20787, 20160, 19520, 18868,
    18205, 17531, 16846, 16151, 15446, 14733, 14010, 13279,
    12540, 11793, 11039, 10279, 9512, 8740, 7962, 7179,
    6393, 5602, 4808, 4011, 3212, 2411, 1608, 804,
    0, -804, -1608, -2411, -3212, -4011, -4808, -5602,
    -6393, -7179, -7962, -8740, -9512, -10279, -11039, -11793,
    -12540, -13279, -14010, -14733, -15446, -16151, -16846, -17531,
    -18205, -18868, -19520, -20160, -20787, -21403, -22005, -22595,
    -23170, -23732, -24279, -24812, -25330, -25832, -26319, -26790,
    -27245, -27684, -28106, -28511, -28898, -29269, -29621, -29956,
    -30273, -30572, -30852, -31114, -31357, -31581, -31785, -31971,
    -32138, -32285, -32413, -32521, -32610, -32679, -32728, -32758,
    -32767, -32758, -32728, -32679, -32610, -32521, -32413, -32285,
    -32138, -31971, -31785, -31581, -31357, -31114, -30852, -30572,
    -30273, -29956, -29621, -29269, -28898, -28511, -28106, -27684,
    -27245, -26790, -26319, -25832, -25330, -24812, -24279, -23732,
    -23170, -22595, -22005, -21403, -20787, -20160, -19520, -18868,
    -18205, -17531, -16846, -16151, -15446, -14733, -14010, -13279,
    -12540, -11793, -11039, -10279, -9512, -8740, -7962, -7179,
    -6393, -5602, -4808, -4011, -3212, -2411, -1608, -804
};

/**
 * A square wave.
 *
 *  32767         +--------+        +--------+
 *                |        |        |        |
 *                |        |        |        |
 *                |        |        |        |
 * -32767 --------+        +--------+        +--------
 */
static int32_t waveform_square_256[] = {
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,
    32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768
};

/**
 * A saw wave.
 *
 *  32767         ,       ,       ,       ,        ,
 *              / |     / |     / |     / |      / |
 *            /   |   /   |   /   |   /   |    /   |
 *          /     | /     | /     | /     |  /     |
 * -32767 ´       ´       ´       ´       ´´       ´
 */
static int32_t waveform_saw_256[] = {
    -32767, -32510, -32253, -31996, -31739, -31482, -31225, -30968,
    -30711, -30454, -30197, -29940, -29683, -29426, -29169, -28912,
    -28655, -28398, -28141, -27884, -27627, -27370, -27113, -26856,
    -26599, -26342, -26085, -25828, -25571, -25314, -25057, -24800,
    -24543, -24286, -24029, -23772, -23515, -23258, -23001, -22744,
    -22487, -22230, -21973, -21716, -21459, -21202, -20945, -20688,
    -20431, -20174, -19917, -19660, -19403, -19146, -18889, -18632,
    -18375, -18118, -17861, -17604, -17347, -17090, -16833, -16576,
    -16319, -16062, -15805, -15548, -15291, -15034, -14777, -14520,
    -14263, -14006, -13749, -13492,-13235, -12978, -12721, -12464,
    -12207, -11950, -11693, -11436, -11179, -10922, -10665, -10408,
    -10151, -9894, -9637, -9380, -9123, -8866, -8609, -8352,
    -8095, -7838, -7581, -7324, -7067, -6810, -6553, -6296,
    -6039, -5782, -5525, -5268, -5011, -4754, -4497, -4240,
    -3983, -3726, -3469, -3212, -2955, -2698, -2441, -2184,
    -1927, -1670, -1413, -1156, -899, -642, -385, -128,
    129, 386, 643, 900, 1157, 1414, 1671, 1928,
    2185, 2442, 2699, 2956, 3213, 3470, 3727, 3984,
    4241, 4498, 4755, 5012, 5269, 5526, 5783, 6040,
    6297, 6554, 6811, 7068, 7325, 7582, 7839, 8096,
    8353, 8610, 8867, 9124, 9381, 9638, 9895, 10152,
    10409, 10666, 10923, 11180, 11437, 11694, 11951, 12208,
    12465, 12722, 12979, 13236, 13493, 13750, 14007, 14264,
    14521, 14778, 15035, 15292, 15549, 15806, 16063, 16320,
    16577, 16834, 17091, 17348, 17605, 17862, 18119, 18376,
    18633, 18890, 19147, 19404, 19661, 19918, 20175, 20432,
    20689, 20946, 21203, 21460, 21717, 21974, 22231, 22488,
    22745, 23002, 23259, 23516, 23773, 24030, 24287, 24544,
    24801, 25058, 25315, 25572, 25829, 26086, 26343, 26600,
    26857, 27114, 27371, 27628, 27885, 28142, 28399, 28656,
    28913, 29170, 29427, 29684, 29941, 30198, 30455, 30712,
    30969, 31226, 31483, 31740, 31997, 32254, 32511, 32768
};

#endif
