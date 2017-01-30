// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated.

// Unicode character database - East_Asian_Width property

#include <ogonek/ucd/east_asian_width.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            east_asian_width_properties const east_asian_width_data_raw[] {
                { 0x0, east_asian_width::n },
                { 0x20, east_asian_width::na },
                { 0x7F, east_asian_width::n },
                { 0xA1, east_asian_width::a },
                { 0xA2, east_asian_width::na },
                { 0xA4, east_asian_width::a },
                { 0xA5, east_asian_width::na },
                { 0xA7, east_asian_width::a },
                { 0xA9, east_asian_width::n },
                { 0xAA, east_asian_width::a },
                { 0xAB, east_asian_width::n },
                { 0xAC, east_asian_width::na },
                { 0xAD, east_asian_width::a },
                { 0xAF, east_asian_width::na },
                { 0xB0, east_asian_width::a },
                { 0xB5, east_asian_width::n },
                { 0xB6, east_asian_width::a },
                { 0xBB, east_asian_width::n },
                { 0xBC, east_asian_width::a },
                { 0xC0, east_asian_width::n },
                { 0xC6, east_asian_width::a },
                { 0xC7, east_asian_width::n },
                { 0xD0, east_asian_width::a },
                { 0xD1, east_asian_width::n },
                { 0xD7, east_asian_width::a },
                { 0xD9, east_asian_width::n },
                { 0xDE, east_asian_width::a },
                { 0xE2, east_asian_width::n },
                { 0xE6, east_asian_width::a },
                { 0xE7, east_asian_width::n },
                { 0xE8, east_asian_width::a },
                { 0xEB, east_asian_width::n },
                { 0xEC, east_asian_width::a },
                { 0xEE, east_asian_width::n },
                { 0xF0, east_asian_width::a },
                { 0xF1, east_asian_width::n },
                { 0xF2, east_asian_width::a },
                { 0xF4, east_asian_width::n },
                { 0xF7, east_asian_width::a },
                { 0xFB, east_asian_width::n },
                { 0xFC, east_asian_width::a },
                { 0xFD, east_asian_width::n },
                { 0xFE, east_asian_width::a },
                { 0xFF, east_asian_width::n },
                { 0x101, east_asian_width::a },
                { 0x102, east_asian_width::n },
                { 0x111, east_asian_width::a },
                { 0x112, east_asian_width::n },
                { 0x113, east_asian_width::a },
                { 0x114, east_asian_width::n },
                { 0x11B, east_asian_width::a },
                { 0x11C, east_asian_width::n },
                { 0x126, east_asian_width::a },
                { 0x128, east_asian_width::n },
                { 0x12B, east_asian_width::a },
                { 0x12C, east_asian_width::n },
                { 0x131, east_asian_width::a },
                { 0x134, east_asian_width::n },
                { 0x138, east_asian_width::a },
                { 0x139, east_asian_width::n },
                { 0x13F, east_asian_width::a },
                { 0x143, east_asian_width::n },
                { 0x144, east_asian_width::a },
                { 0x145, east_asian_width::n },
                { 0x148, east_asian_width::a },
                { 0x14C, east_asian_width::n },
                { 0x14D, east_asian_width::a },
                { 0x14E, east_asian_width::n },
                { 0x152, east_asian_width::a },
                { 0x154, east_asian_width::n },
                { 0x166, east_asian_width::a },
                { 0x168, east_asian_width::n },
                { 0x16B, east_asian_width::a },
                { 0x16C, east_asian_width::n },
                { 0x1CE, east_asian_width::a },
                { 0x1CF, east_asian_width::n },
                { 0x1D0, east_asian_width::a },
                { 0x1D1, east_asian_width::n },
                { 0x1D2, east_asian_width::a },
                { 0x1D3, east_asian_width::n },
                { 0x1D4, east_asian_width::a },
                { 0x1D5, east_asian_width::n },
                { 0x1D6, east_asian_width::a },
                { 0x1D7, east_asian_width::n },
                { 0x1D8, east_asian_width::a },
                { 0x1D9, east_asian_width::n },
                { 0x1DA, east_asian_width::a },
                { 0x1DB, east_asian_width::n },
                { 0x1DC, east_asian_width::a },
                { 0x1DD, east_asian_width::n },
                { 0x251, east_asian_width::a },
                { 0x252, east_asian_width::n },
                { 0x261, east_asian_width::a },
                { 0x262, east_asian_width::n },
                { 0x2C4, east_asian_width::a },
                { 0x2C5, east_asian_width::n },
                { 0x2C7, east_asian_width::a },
                { 0x2C8, east_asian_width::n },
                { 0x2C9, east_asian_width::a },
                { 0x2CC, east_asian_width::n },
                { 0x2CD, east_asian_width::a },
                { 0x2CE, east_asian_width::n },
                { 0x2D0, east_asian_width::a },
                { 0x2D1, east_asian_width::n },
                { 0x2D8, east_asian_width::a },
                { 0x2DC, east_asian_width::n },
                { 0x2DD, east_asian_width::a },
                { 0x2DE, east_asian_width::n },
                { 0x2DF, east_asian_width::a },
                { 0x2E0, east_asian_width::n },
                { 0x300, east_asian_width::a },
                { 0x370, east_asian_width::n },
                { 0x391, east_asian_width::a },
                { 0x3A2, east_asian_width::n },
                { 0x3A3, east_asian_width::a },
                { 0x3AA, east_asian_width::n },
                { 0x3B1, east_asian_width::a },
                { 0x3C2, east_asian_width::n },
                { 0x3C3, east_asian_width::a },
                { 0x3CA, east_asian_width::n },
                { 0x401, east_asian_width::a },
                { 0x402, east_asian_width::n },
                { 0x410, east_asian_width::a },
                { 0x450, east_asian_width::n },
                { 0x451, east_asian_width::a },
                { 0x452, east_asian_width::n },
                { 0x1100, east_asian_width::w },
                { 0x1160, east_asian_width::n },
                { 0x2010, east_asian_width::a },
                { 0x2011, east_asian_width::n },
                { 0x2013, east_asian_width::a },
                { 0x2017, east_asian_width::n },
                { 0x2018, east_asian_width::a },
                { 0x201A, east_asian_width::n },
                { 0x201C, east_asian_width::a },
                { 0x201E, east_asian_width::n },
                { 0x2020, east_asian_width::a },
                { 0x2023, east_asian_width::n },
                { 0x2024, east_asian_width::a },
                { 0x2028, east_asian_width::n },
                { 0x2030, east_asian_width::a },
                { 0x2031, east_asian_width::n },
                { 0x2032, east_asian_width::a },
                { 0x2034, east_asian_width::n },
                { 0x2035, east_asian_width::a },
                { 0x2036, east_asian_width::n },
                { 0x203B, east_asian_width::a },
                { 0x203C, east_asian_width::n },
                { 0x203E, east_asian_width::a },
                { 0x203F, east_asian_width::n },
                { 0x2074, east_asian_width::a },
                { 0x2075, east_asian_width::n },
                { 0x207F, east_asian_width::a },
                { 0x2080, east_asian_width::n },
                { 0x2081, east_asian_width::a },
                { 0x2085, east_asian_width::n },
                { 0x20A9, east_asian_width::h },
                { 0x20AA, east_asian_width::n },
                { 0x20AC, east_asian_width::a },
                { 0x20AD, east_asian_width::n },
                { 0x2103, east_asian_width::a },
                { 0x2104, east_asian_width::n },
                { 0x2105, east_asian_width::a },
                { 0x2106, east_asian_width::n },
                { 0x2109, east_asian_width::a },
                { 0x210A, east_asian_width::n },
                { 0x2113, east_asian_width::a },
                { 0x2114, east_asian_width::n },
                { 0x2116, east_asian_width::a },
                { 0x2117, east_asian_width::n },
                { 0x2121, east_asian_width::a },
                { 0x2123, east_asian_width::n },
                { 0x2126, east_asian_width::a },
                { 0x2127, east_asian_width::n },
                { 0x212B, east_asian_width::a },
                { 0x212C, east_asian_width::n },
                { 0x2153, east_asian_width::a },
                { 0x2155, east_asian_width::n },
                { 0x215B, east_asian_width::a },
                { 0x215F, east_asian_width::n },
                { 0x2160, east_asian_width::a },
                { 0x216C, east_asian_width::n },
                { 0x2170, east_asian_width::a },
                { 0x217A, east_asian_width::n },
                { 0x2189, east_asian_width::a },
                { 0x218A, east_asian_width::n },
                { 0x2190, east_asian_width::a },
                { 0x219A, east_asian_width::n },
                { 0x21B8, east_asian_width::a },
                { 0x21BA, east_asian_width::n },
                { 0x21D2, east_asian_width::a },
                { 0x21D3, east_asian_width::n },
                { 0x21D4, east_asian_width::a },
                { 0x21D5, east_asian_width::n },
                { 0x21E7, east_asian_width::a },
                { 0x21E8, east_asian_width::n },
                { 0x2200, east_asian_width::a },
                { 0x2201, east_asian_width::n },
                { 0x2202, east_asian_width::a },
                { 0x2204, east_asian_width::n },
                { 0x2207, east_asian_width::a },
                { 0x2209, east_asian_width::n },
                { 0x220B, east_asian_width::a },
                { 0x220C, east_asian_width::n },
                { 0x220F, east_asian_width::a },
                { 0x2210, east_asian_width::n },
                { 0x2211, east_asian_width::a },
                { 0x2212, east_asian_width::n },
                { 0x2215, east_asian_width::a },
                { 0x2216, east_asian_width::n },
                { 0x221A, east_asian_width::a },
                { 0x221B, east_asian_width::n },
                { 0x221D, east_asian_width::a },
                { 0x2221, east_asian_width::n },
                { 0x2223, east_asian_width::a },
                { 0x2224, east_asian_width::n },
                { 0x2225, east_asian_width::a },
                { 0x2226, east_asian_width::n },
                { 0x2227, east_asian_width::a },
                { 0x222D, east_asian_width::n },
                { 0x222E, east_asian_width::a },
                { 0x222F, east_asian_width::n },
                { 0x2234, east_asian_width::a },
                { 0x2238, east_asian_width::n },
                { 0x223C, east_asian_width::a },
                { 0x223E, east_asian_width::n },
                { 0x2248, east_asian_width::a },
                { 0x2249, east_asian_width::n },
                { 0x224C, east_asian_width::a },
                { 0x224D, east_asian_width::n },
                { 0x2252, east_asian_width::a },
                { 0x2253, east_asian_width::n },
                { 0x2260, east_asian_width::a },
                { 0x2262, east_asian_width::n },
                { 0x2264, east_asian_width::a },
                { 0x2268, east_asian_width::n },
                { 0x226A, east_asian_width::a },
                { 0x226C, east_asian_width::n },
                { 0x226E, east_asian_width::a },
                { 0x2270, east_asian_width::n },
                { 0x2282, east_asian_width::a },
                { 0x2284, east_asian_width::n },
                { 0x2286, east_asian_width::a },
                { 0x2288, east_asian_width::n },
                { 0x2295, east_asian_width::a },
                { 0x2296, east_asian_width::n },
                { 0x2299, east_asian_width::a },
                { 0x229A, east_asian_width::n },
                { 0x22A5, east_asian_width::a },
                { 0x22A6, east_asian_width::n },
                { 0x22BF, east_asian_width::a },
                { 0x22C0, east_asian_width::n },
                { 0x2312, east_asian_width::a },
                { 0x2313, east_asian_width::n },
                { 0x231A, east_asian_width::w },
                { 0x231C, east_asian_width::n },
                { 0x2329, east_asian_width::w },
                { 0x232B, east_asian_width::n },
                { 0x23E9, east_asian_width::w },
                { 0x23ED, east_asian_width::n },
                { 0x23F0, east_asian_width::w },
                { 0x23F1, east_asian_width::n },
                { 0x23F3, east_asian_width::w },
                { 0x23F4, east_asian_width::n },
                { 0x2460, east_asian_width::a },
                { 0x24EA, east_asian_width::n },
                { 0x24EB, east_asian_width::a },
                { 0x254C, east_asian_width::n },
                { 0x2550, east_asian_width::a },
                { 0x2574, east_asian_width::n },
                { 0x2580, east_asian_width::a },
                { 0x2590, east_asian_width::n },
                { 0x2592, east_asian_width::a },
                { 0x2596, east_asian_width::n },
                { 0x25A0, east_asian_width::a },
                { 0x25A2, east_asian_width::n },
                { 0x25A3, east_asian_width::a },
                { 0x25AA, east_asian_width::n },
                { 0x25B2, east_asian_width::a },
                { 0x25B4, east_asian_width::n },
                { 0x25B6, east_asian_width::a },
                { 0x25B8, east_asian_width::n },
                { 0x25BC, east_asian_width::a },
                { 0x25BE, east_asian_width::n },
                { 0x25C0, east_asian_width::a },
                { 0x25C2, east_asian_width::n },
                { 0x25C6, east_asian_width::a },
                { 0x25C9, east_asian_width::n },
                { 0x25CB, east_asian_width::a },
                { 0x25CC, east_asian_width::n },
                { 0x25CE, east_asian_width::a },
                { 0x25D2, east_asian_width::n },
                { 0x25E2, east_asian_width::a },
                { 0x25E6, east_asian_width::n },
                { 0x25EF, east_asian_width::a },
                { 0x25F0, east_asian_width::n },
                { 0x25FD, east_asian_width::w },
                { 0x25FF, east_asian_width::n },
                { 0x2605, east_asian_width::a },
                { 0x2607, east_asian_width::n },
                { 0x2609, east_asian_width::a },
                { 0x260A, east_asian_width::n },
                { 0x260E, east_asian_width::a },
                { 0x2610, east_asian_width::n },
                { 0x2614, east_asian_width::w },
                { 0x2616, east_asian_width::n },
                { 0x261C, east_asian_width::a },
                { 0x261D, east_asian_width::n },
                { 0x261E, east_asian_width::a },
                { 0x261F, east_asian_width::n },
                { 0x2640, east_asian_width::a },
                { 0x2641, east_asian_width::n },
                { 0x2642, east_asian_width::a },
                { 0x2643, east_asian_width::n },
                { 0x2648, east_asian_width::w },
                { 0x2654, east_asian_width::n },
                { 0x2660, east_asian_width::a },
                { 0x2662, east_asian_width::n },
                { 0x2663, east_asian_width::a },
                { 0x2666, east_asian_width::n },
                { 0x2667, east_asian_width::a },
                { 0x266B, east_asian_width::n },
                { 0x266C, east_asian_width::a },
                { 0x266E, east_asian_width::n },
                { 0x266F, east_asian_width::a },
                { 0x2670, east_asian_width::n },
                { 0x267F, east_asian_width::w },
                { 0x2680, east_asian_width::n },
                { 0x2693, east_asian_width::w },
                { 0x2694, east_asian_width::n },
                { 0x269E, east_asian_width::a },
                { 0x26A0, east_asian_width::n },
                { 0x26A1, east_asian_width::w },
                { 0x26A2, east_asian_width::n },
                { 0x26AA, east_asian_width::w },
                { 0x26AC, east_asian_width::n },
                { 0x26BD, east_asian_width::w },
                { 0x26BF, east_asian_width::a },
                { 0x26C0, east_asian_width::n },
                { 0x26C4, east_asian_width::w },
                { 0x26C6, east_asian_width::a },
                { 0x26CE, east_asian_width::w },
                { 0x26CF, east_asian_width::a },
                { 0x26D4, east_asian_width::w },
                { 0x26D5, east_asian_width::a },
                { 0x26E2, east_asian_width::n },
                { 0x26E3, east_asian_width::a },
                { 0x26E4, east_asian_width::n },
                { 0x26E8, east_asian_width::a },
                { 0x26EA, east_asian_width::w },
                { 0x26EB, east_asian_width::a },
                { 0x26F2, east_asian_width::w },
                { 0x26F4, east_asian_width::a },
                { 0x26F5, east_asian_width::w },
                { 0x26F6, east_asian_width::a },
                { 0x26FA, east_asian_width::w },
                { 0x26FB, east_asian_width::a },
                { 0x26FD, east_asian_width::w },
                { 0x26FE, east_asian_width::a },
                { 0x2700, east_asian_width::n },
                { 0x2705, east_asian_width::w },
                { 0x2706, east_asian_width::n },
                { 0x270A, east_asian_width::w },
                { 0x270C, east_asian_width::n },
                { 0x2728, east_asian_width::w },
                { 0x2729, east_asian_width::n },
                { 0x273D, east_asian_width::a },
                { 0x273E, east_asian_width::n },
                { 0x274C, east_asian_width::w },
                { 0x274D, east_asian_width::n },
                { 0x274E, east_asian_width::w },
                { 0x274F, east_asian_width::n },
                { 0x2753, east_asian_width::w },
                { 0x2756, east_asian_width::n },
                { 0x2757, east_asian_width::w },
                { 0x2758, east_asian_width::n },
                { 0x2776, east_asian_width::a },
                { 0x2780, east_asian_width::n },
                { 0x2795, east_asian_width::w },
                { 0x2798, east_asian_width::n },
                { 0x27B0, east_asian_width::w },
                { 0x27B1, east_asian_width::n },
                { 0x27BF, east_asian_width::w },
                { 0x27C0, east_asian_width::n },
                { 0x27E6, east_asian_width::na },
                { 0x27EE, east_asian_width::n },
                { 0x2985, east_asian_width::na },
                { 0x2987, east_asian_width::n },
                { 0x2B1B, east_asian_width::w },
                { 0x2B1D, east_asian_width::n },
                { 0x2B50, east_asian_width::w },
                { 0x2B51, east_asian_width::n },
                { 0x2B55, east_asian_width::w },
                { 0x2B56, east_asian_width::a },
                { 0x2B5A, east_asian_width::n },
                { 0x2E80, east_asian_width::w },
                { 0x2E9A, east_asian_width::n },
                { 0x2E9B, east_asian_width::w },
                { 0x2EF4, east_asian_width::n },
                { 0x2F00, east_asian_width::w },
                { 0x2FD6, east_asian_width::n },
                { 0x2FF0, east_asian_width::w },
                { 0x2FFC, east_asian_width::n },
                { 0x3000, east_asian_width::f },
                { 0x3001, east_asian_width::w },
                { 0x303F, east_asian_width::n },
                { 0x3041, east_asian_width::w },
                { 0x3097, east_asian_width::n },
                { 0x3099, east_asian_width::w },
                { 0x3100, east_asian_width::n },
                { 0x3105, east_asian_width::w },
                { 0x312E, east_asian_width::n },
                { 0x3131, east_asian_width::w },
                { 0x318F, east_asian_width::n },
                { 0x3190, east_asian_width::w },
                { 0x31BB, east_asian_width::n },
                { 0x31C0, east_asian_width::w },
                { 0x31E4, east_asian_width::n },
                { 0x31F0, east_asian_width::w },
                { 0x321F, east_asian_width::n },
                { 0x3220, east_asian_width::w },
                { 0x3248, east_asian_width::a },
                { 0x3250, east_asian_width::w },
                { 0x32FF, east_asian_width::n },
                { 0x3300, east_asian_width::w },
                { 0x4DC0, east_asian_width::n },
                { 0x4E00, east_asian_width::w },
                { 0xA48D, east_asian_width::n },
                { 0xA490, east_asian_width::w },
                { 0xA4C7, east_asian_width::n },
                { 0xA960, east_asian_width::w },
                { 0xA97D, east_asian_width::n },
                { 0xAC00, east_asian_width::w },
                { 0xD7A4, east_asian_width::n },
                { 0xE000, east_asian_width::a },
                { 0xF900, east_asian_width::w },
                { 0xFB00, east_asian_width::n },
                { 0xFE00, east_asian_width::a },
                { 0xFE10, east_asian_width::w },
                { 0xFE1A, east_asian_width::n },
                { 0xFE30, east_asian_width::w },
                { 0xFE53, east_asian_width::n },
                { 0xFE54, east_asian_width::w },
                { 0xFE67, east_asian_width::n },
                { 0xFE68, east_asian_width::w },
                { 0xFE6C, east_asian_width::n },
                { 0xFF01, east_asian_width::f },
                { 0xFF61, east_asian_width::h },
                { 0xFFBF, east_asian_width::n },
                { 0xFFC2, east_asian_width::h },
                { 0xFFC8, east_asian_width::n },
                { 0xFFCA, east_asian_width::h },
                { 0xFFD0, east_asian_width::n },
                { 0xFFD2, east_asian_width::h },
                { 0xFFD8, east_asian_width::n },
                { 0xFFDA, east_asian_width::h },
                { 0xFFDD, east_asian_width::n },
                { 0xFFE0, east_asian_width::f },
                { 0xFFE7, east_asian_width::n },
                { 0xFFE8, east_asian_width::h },
                { 0xFFEF, east_asian_width::n },
                { 0xFFFD, east_asian_width::a },
                { 0xFFFE, east_asian_width::n },
                { 0x16FE0, east_asian_width::w },
                { 0x16FE1, east_asian_width::n },
                { 0x17000, east_asian_width::w },
                { 0x187ED, east_asian_width::n },
                { 0x18800, east_asian_width::w },
                { 0x18AF3, east_asian_width::n },
                { 0x1B000, east_asian_width::w },
                { 0x1B002, east_asian_width::n },
                { 0x1F004, east_asian_width::w },
                { 0x1F005, east_asian_width::n },
                { 0x1F0CF, east_asian_width::w },
                { 0x1F0D0, east_asian_width::n },
                { 0x1F100, east_asian_width::a },
                { 0x1F10B, east_asian_width::n },
                { 0x1F110, east_asian_width::a },
                { 0x1F12E, east_asian_width::n },
                { 0x1F130, east_asian_width::a },
                { 0x1F16A, east_asian_width::n },
                { 0x1F170, east_asian_width::a },
                { 0x1F18E, east_asian_width::w },
                { 0x1F18F, east_asian_width::a },
                { 0x1F191, east_asian_width::w },
                { 0x1F19B, east_asian_width::a },
                { 0x1F1AD, east_asian_width::n },
                { 0x1F200, east_asian_width::w },
                { 0x1F203, east_asian_width::n },
                { 0x1F210, east_asian_width::w },
                { 0x1F23C, east_asian_width::n },
                { 0x1F240, east_asian_width::w },
                { 0x1F249, east_asian_width::n },
                { 0x1F250, east_asian_width::w },
                { 0x1F252, east_asian_width::n },
                { 0x1F300, east_asian_width::w },
                { 0x1F321, east_asian_width::n },
                { 0x1F32D, east_asian_width::w },
                { 0x1F336, east_asian_width::n },
                { 0x1F337, east_asian_width::w },
                { 0x1F37D, east_asian_width::n },
                { 0x1F37E, east_asian_width::w },
                { 0x1F394, east_asian_width::n },
                { 0x1F3A0, east_asian_width::w },
                { 0x1F3CB, east_asian_width::n },
                { 0x1F3CF, east_asian_width::w },
                { 0x1F3D4, east_asian_width::n },
                { 0x1F3E0, east_asian_width::w },
                { 0x1F3F1, east_asian_width::n },
                { 0x1F3F4, east_asian_width::w },
                { 0x1F3F5, east_asian_width::n },
                { 0x1F3F8, east_asian_width::w },
                { 0x1F43F, east_asian_width::n },
                { 0x1F440, east_asian_width::w },
                { 0x1F441, east_asian_width::n },
                { 0x1F442, east_asian_width::w },
                { 0x1F4FD, east_asian_width::n },
                { 0x1F4FF, east_asian_width::w },
                { 0x1F53E, east_asian_width::n },
                { 0x1F54B, east_asian_width::w },
                { 0x1F54F, east_asian_width::n },
                { 0x1F550, east_asian_width::w },
                { 0x1F568, east_asian_width::n },
                { 0x1F57A, east_asian_width::w },
                { 0x1F57B, east_asian_width::n },
                { 0x1F595, east_asian_width::w },
                { 0x1F597, east_asian_width::n },
                { 0x1F5A4, east_asian_width::w },
                { 0x1F5A5, east_asian_width::n },
                { 0x1F5FB, east_asian_width::w },
                { 0x1F650, east_asian_width::n },
                { 0x1F680, east_asian_width::w },
                { 0x1F6C6, east_asian_width::n },
                { 0x1F6CC, east_asian_width::w },
                { 0x1F6CD, east_asian_width::n },
                { 0x1F6D0, east_asian_width::w },
                { 0x1F6D3, east_asian_width::n },
                { 0x1F6EB, east_asian_width::w },
                { 0x1F6ED, east_asian_width::n },
                { 0x1F6F4, east_asian_width::w },
                { 0x1F6F7, east_asian_width::n },
                { 0x1F910, east_asian_width::w },
                { 0x1F91F, east_asian_width::n },
                { 0x1F920, east_asian_width::w },
                { 0x1F928, east_asian_width::n },
                { 0x1F930, east_asian_width::w },
                { 0x1F931, east_asian_width::n },
                { 0x1F933, east_asian_width::w },
                { 0x1F93F, east_asian_width::n },
                { 0x1F940, east_asian_width::w },
                { 0x1F94C, east_asian_width::n },
                { 0x1F950, east_asian_width::w },
                { 0x1F95F, east_asian_width::n },
                { 0x1F980, east_asian_width::w },
                { 0x1F992, east_asian_width::n },
                { 0x1F9C0, east_asian_width::w },
                { 0x1F9C1, east_asian_width::n },
                { 0x20000, east_asian_width::w },
                { 0x2FFFE, east_asian_width::n },
                { 0x30000, east_asian_width::w },
                { 0x3FFFE, east_asian_width::n },
                { 0xE0100, east_asian_width::a },
                { 0xE01F0, east_asian_width::n },
                { 0xF0000, east_asian_width::a },
                { 0xFFFFE, east_asian_width::n },
                { 0x100000, east_asian_width::a },
                { 0x10FFFE, east_asian_width::n },
            };
        } // namespace
        inline namespace abiv0 {
            east_asian_width_properties const* east_asian_width_data = east_asian_width_data_raw;
            std::size_t east_asian_width_data_size = detail::size(east_asian_width_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek
