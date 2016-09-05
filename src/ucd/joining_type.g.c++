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

// This file was automatically generated on 2016-09-05T11:29:13.441694Z

// Unicode character database - Joining_Type property

#include <ogonek/ucd/joining_type.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            joining_type_properties const joining_type_data_raw[] {
                { 0x0, joining_type::u },
                { 0xAD, joining_type::t },
                { 0xAE, joining_type::u },
                { 0x300, joining_type::t },
                { 0x370, joining_type::u },
                { 0x483, joining_type::t },
                { 0x48A, joining_type::u },
                { 0x591, joining_type::t },
                { 0x5BE, joining_type::u },
                { 0x5BF, joining_type::t },
                { 0x5C0, joining_type::u },
                { 0x5C1, joining_type::t },
                { 0x5C3, joining_type::u },
                { 0x5C4, joining_type::t },
                { 0x5C6, joining_type::u },
                { 0x5C7, joining_type::t },
                { 0x5C8, joining_type::u },
                { 0x610, joining_type::t },
                { 0x61B, joining_type::u },
                { 0x61C, joining_type::t },
                { 0x61D, joining_type::u },
                { 0x620, joining_type::d },
                { 0x621, joining_type::u },
                { 0x622, joining_type::r },
                { 0x626, joining_type::d },
                { 0x627, joining_type::r },
                { 0x628, joining_type::d },
                { 0x629, joining_type::r },
                { 0x62A, joining_type::d },
                { 0x62F, joining_type::r },
                { 0x633, joining_type::d },
                { 0x640, joining_type::c },
                { 0x641, joining_type::d },
                { 0x648, joining_type::r },
                { 0x649, joining_type::d },
                { 0x64B, joining_type::t },
                { 0x660, joining_type::u },
                { 0x66E, joining_type::d },
                { 0x670, joining_type::t },
                { 0x671, joining_type::r },
                { 0x674, joining_type::u },
                { 0x675, joining_type::r },
                { 0x678, joining_type::d },
                { 0x688, joining_type::r },
                { 0x69A, joining_type::d },
                { 0x6C0, joining_type::r },
                { 0x6C1, joining_type::d },
                { 0x6C3, joining_type::r },
                { 0x6CC, joining_type::d },
                { 0x6CD, joining_type::r },
                { 0x6CE, joining_type::d },
                { 0x6CF, joining_type::r },
                { 0x6D0, joining_type::d },
                { 0x6D2, joining_type::r },
                { 0x6D4, joining_type::u },
                { 0x6D5, joining_type::r },
                { 0x6D6, joining_type::t },
                { 0x6DD, joining_type::u },
                { 0x6DF, joining_type::t },
                { 0x6E5, joining_type::u },
                { 0x6E7, joining_type::t },
                { 0x6E9, joining_type::u },
                { 0x6EA, joining_type::t },
                { 0x6EE, joining_type::r },
                { 0x6F0, joining_type::u },
                { 0x6FA, joining_type::d },
                { 0x6FD, joining_type::u },
                { 0x6FF, joining_type::d },
                { 0x700, joining_type::u },
                { 0x70F, joining_type::t },
                { 0x710, joining_type::r },
                { 0x711, joining_type::t },
                { 0x712, joining_type::d },
                { 0x715, joining_type::r },
                { 0x71A, joining_type::d },
                { 0x71E, joining_type::r },
                { 0x71F, joining_type::d },
                { 0x728, joining_type::r },
                { 0x729, joining_type::d },
                { 0x72A, joining_type::r },
                { 0x72B, joining_type::d },
                { 0x72C, joining_type::r },
                { 0x72D, joining_type::d },
                { 0x72F, joining_type::r },
                { 0x730, joining_type::t },
                { 0x74B, joining_type::u },
                { 0x74D, joining_type::r },
                { 0x74E, joining_type::d },
                { 0x759, joining_type::r },
                { 0x75C, joining_type::d },
                { 0x76B, joining_type::r },
                { 0x76D, joining_type::d },
                { 0x771, joining_type::r },
                { 0x772, joining_type::d },
                { 0x773, joining_type::r },
                { 0x775, joining_type::d },
                { 0x778, joining_type::r },
                { 0x77A, joining_type::d },
                { 0x780, joining_type::u },
                { 0x7A6, joining_type::t },
                { 0x7B1, joining_type::u },
                { 0x7CA, joining_type::d },
                { 0x7EB, joining_type::t },
                { 0x7F4, joining_type::u },
                { 0x7FA, joining_type::c },
                { 0x7FB, joining_type::u },
                { 0x816, joining_type::t },
                { 0x81A, joining_type::u },
                { 0x81B, joining_type::t },
                { 0x824, joining_type::u },
                { 0x825, joining_type::t },
                { 0x828, joining_type::u },
                { 0x829, joining_type::t },
                { 0x82E, joining_type::u },
                { 0x840, joining_type::r },
                { 0x841, joining_type::d },
                { 0x846, joining_type::r },
                { 0x848, joining_type::d },
                { 0x849, joining_type::r },
                { 0x84A, joining_type::d },
                { 0x854, joining_type::r },
                { 0x855, joining_type::d },
                { 0x856, joining_type::u },
                { 0x859, joining_type::t },
                { 0x85C, joining_type::u },
                { 0x8A0, joining_type::d },
                { 0x8AA, joining_type::r },
                { 0x8AD, joining_type::u },
                { 0x8AE, joining_type::r },
                { 0x8AF, joining_type::d },
                { 0x8B1, joining_type::r },
                { 0x8B3, joining_type::d },
                { 0x8B5, joining_type::u },
                { 0x8B6, joining_type::d },
                { 0x8B9, joining_type::r },
                { 0x8BA, joining_type::d },
                { 0x8BE, joining_type::u },
                { 0x8D4, joining_type::t },
                { 0x8E2, joining_type::u },
                { 0x8E3, joining_type::t },
                { 0x903, joining_type::u },
                { 0x93A, joining_type::t },
                { 0x93B, joining_type::u },
                { 0x93C, joining_type::t },
                { 0x93D, joining_type::u },
                { 0x941, joining_type::t },
                { 0x949, joining_type::u },
                { 0x94D, joining_type::t },
                { 0x94E, joining_type::u },
                { 0x951, joining_type::t },
                { 0x958, joining_type::u },
                { 0x962, joining_type::t },
                { 0x964, joining_type::u },
                { 0x981, joining_type::t },
                { 0x982, joining_type::u },
                { 0x9BC, joining_type::t },
                { 0x9BD, joining_type::u },
                { 0x9C1, joining_type::t },
                { 0x9C5, joining_type::u },
                { 0x9CD, joining_type::t },
                { 0x9CE, joining_type::u },
                { 0x9E2, joining_type::t },
                { 0x9E4, joining_type::u },
                { 0xA01, joining_type::t },
                { 0xA03, joining_type::u },
                { 0xA3C, joining_type::t },
                { 0xA3D, joining_type::u },
                { 0xA41, joining_type::t },
                { 0xA43, joining_type::u },
                { 0xA47, joining_type::t },
                { 0xA49, joining_type::u },
                { 0xA4B, joining_type::t },
                { 0xA4E, joining_type::u },
                { 0xA51, joining_type::t },
                { 0xA52, joining_type::u },
                { 0xA70, joining_type::t },
                { 0xA72, joining_type::u },
                { 0xA75, joining_type::t },
                { 0xA76, joining_type::u },
                { 0xA81, joining_type::t },
                { 0xA83, joining_type::u },
                { 0xABC, joining_type::t },
                { 0xABD, joining_type::u },
                { 0xAC1, joining_type::t },
                { 0xAC6, joining_type::u },
                { 0xAC7, joining_type::t },
                { 0xAC9, joining_type::u },
                { 0xACD, joining_type::t },
                { 0xACE, joining_type::u },
                { 0xAE2, joining_type::t },
                { 0xAE4, joining_type::u },
                { 0xB01, joining_type::t },
                { 0xB02, joining_type::u },
                { 0xB3C, joining_type::t },
                { 0xB3D, joining_type::u },
                { 0xB3F, joining_type::t },
                { 0xB40, joining_type::u },
                { 0xB41, joining_type::t },
                { 0xB45, joining_type::u },
                { 0xB4D, joining_type::t },
                { 0xB4E, joining_type::u },
                { 0xB56, joining_type::t },
                { 0xB57, joining_type::u },
                { 0xB62, joining_type::t },
                { 0xB64, joining_type::u },
                { 0xB82, joining_type::t },
                { 0xB83, joining_type::u },
                { 0xBC0, joining_type::t },
                { 0xBC1, joining_type::u },
                { 0xBCD, joining_type::t },
                { 0xBCE, joining_type::u },
                { 0xC00, joining_type::t },
                { 0xC01, joining_type::u },
                { 0xC3E, joining_type::t },
                { 0xC41, joining_type::u },
                { 0xC46, joining_type::t },
                { 0xC49, joining_type::u },
                { 0xC4A, joining_type::t },
                { 0xC4E, joining_type::u },
                { 0xC55, joining_type::t },
                { 0xC57, joining_type::u },
                { 0xC62, joining_type::t },
                { 0xC64, joining_type::u },
                { 0xC81, joining_type::t },
                { 0xC82, joining_type::u },
                { 0xCBC, joining_type::t },
                { 0xCBD, joining_type::u },
                { 0xCBF, joining_type::t },
                { 0xCC0, joining_type::u },
                { 0xCC6, joining_type::t },
                { 0xCC7, joining_type::u },
                { 0xCCC, joining_type::t },
                { 0xCCE, joining_type::u },
                { 0xCE2, joining_type::t },
                { 0xCE4, joining_type::u },
                { 0xD01, joining_type::t },
                { 0xD02, joining_type::u },
                { 0xD41, joining_type::t },
                { 0xD45, joining_type::u },
                { 0xD4D, joining_type::t },
                { 0xD4E, joining_type::u },
                { 0xD62, joining_type::t },
                { 0xD64, joining_type::u },
                { 0xDCA, joining_type::t },
                { 0xDCB, joining_type::u },
                { 0xDD2, joining_type::t },
                { 0xDD5, joining_type::u },
                { 0xDD6, joining_type::t },
                { 0xDD7, joining_type::u },
                { 0xE31, joining_type::t },
                { 0xE32, joining_type::u },
                { 0xE34, joining_type::t },
                { 0xE3B, joining_type::u },
                { 0xE47, joining_type::t },
                { 0xE4F, joining_type::u },
                { 0xEB1, joining_type::t },
                { 0xEB2, joining_type::u },
                { 0xEB4, joining_type::t },
                { 0xEBA, joining_type::u },
                { 0xEBB, joining_type::t },
                { 0xEBD, joining_type::u },
                { 0xEC8, joining_type::t },
                { 0xECE, joining_type::u },
                { 0xF18, joining_type::t },
                { 0xF1A, joining_type::u },
                { 0xF35, joining_type::t },
                { 0xF36, joining_type::u },
                { 0xF37, joining_type::t },
                { 0xF38, joining_type::u },
                { 0xF39, joining_type::t },
                { 0xF3A, joining_type::u },
                { 0xF71, joining_type::t },
                { 0xF7F, joining_type::u },
                { 0xF80, joining_type::t },
                { 0xF85, joining_type::u },
                { 0xF86, joining_type::t },
                { 0xF88, joining_type::u },
                { 0xF8D, joining_type::t },
                { 0xF98, joining_type::u },
                { 0xF99, joining_type::t },
                { 0xFBD, joining_type::u },
                { 0xFC6, joining_type::t },
                { 0xFC7, joining_type::u },
                { 0x102D, joining_type::t },
                { 0x1031, joining_type::u },
                { 0x1032, joining_type::t },
                { 0x1038, joining_type::u },
                { 0x1039, joining_type::t },
                { 0x103B, joining_type::u },
                { 0x103D, joining_type::t },
                { 0x103F, joining_type::u },
                { 0x1058, joining_type::t },
                { 0x105A, joining_type::u },
                { 0x105E, joining_type::t },
                { 0x1061, joining_type::u },
                { 0x1071, joining_type::t },
                { 0x1075, joining_type::u },
                { 0x1082, joining_type::t },
                { 0x1083, joining_type::u },
                { 0x1085, joining_type::t },
                { 0x1087, joining_type::u },
                { 0x108D, joining_type::t },
                { 0x108E, joining_type::u },
                { 0x109D, joining_type::t },
                { 0x109E, joining_type::u },
                { 0x135D, joining_type::t },
                { 0x1360, joining_type::u },
                { 0x1712, joining_type::t },
                { 0x1715, joining_type::u },
                { 0x1732, joining_type::t },
                { 0x1735, joining_type::u },
                { 0x1752, joining_type::t },
                { 0x1754, joining_type::u },
                { 0x1772, joining_type::t },
                { 0x1774, joining_type::u },
                { 0x17B4, joining_type::t },
                { 0x17B6, joining_type::u },
                { 0x17B7, joining_type::t },
                { 0x17BE, joining_type::u },
                { 0x17C6, joining_type::t },
                { 0x17C7, joining_type::u },
                { 0x17C9, joining_type::t },
                { 0x17D4, joining_type::u },
                { 0x17DD, joining_type::t },
                { 0x17DE, joining_type::u },
                { 0x1807, joining_type::d },
                { 0x1808, joining_type::u },
                { 0x180A, joining_type::c },
                { 0x180B, joining_type::t },
                { 0x180E, joining_type::u },
                { 0x1820, joining_type::d },
                { 0x1878, joining_type::u },
                { 0x1885, joining_type::t },
                { 0x1887, joining_type::d },
                { 0x18A9, joining_type::t },
                { 0x18AA, joining_type::d },
                { 0x18AB, joining_type::u },
                { 0x1920, joining_type::t },
                { 0x1923, joining_type::u },
                { 0x1927, joining_type::t },
                { 0x1929, joining_type::u },
                { 0x1932, joining_type::t },
                { 0x1933, joining_type::u },
                { 0x1939, joining_type::t },
                { 0x193C, joining_type::u },
                { 0x1A17, joining_type::t },
                { 0x1A19, joining_type::u },
                { 0x1A1B, joining_type::t },
                { 0x1A1C, joining_type::u },
                { 0x1A56, joining_type::t },
                { 0x1A57, joining_type::u },
                { 0x1A58, joining_type::t },
                { 0x1A5F, joining_type::u },
                { 0x1A60, joining_type::t },
                { 0x1A61, joining_type::u },
                { 0x1A62, joining_type::t },
                { 0x1A63, joining_type::u },
                { 0x1A65, joining_type::t },
                { 0x1A6D, joining_type::u },
                { 0x1A73, joining_type::t },
                { 0x1A7D, joining_type::u },
                { 0x1A7F, joining_type::t },
                { 0x1A80, joining_type::u },
                { 0x1AB0, joining_type::t },
                { 0x1ABF, joining_type::u },
                { 0x1B00, joining_type::t },
                { 0x1B04, joining_type::u },
                { 0x1B34, joining_type::t },
                { 0x1B35, joining_type::u },
                { 0x1B36, joining_type::t },
                { 0x1B3B, joining_type::u },
                { 0x1B3C, joining_type::t },
                { 0x1B3D, joining_type::u },
                { 0x1B42, joining_type::t },
                { 0x1B43, joining_type::u },
                { 0x1B6B, joining_type::t },
                { 0x1B74, joining_type::u },
                { 0x1B80, joining_type::t },
                { 0x1B82, joining_type::u },
                { 0x1BA2, joining_type::t },
                { 0x1BA6, joining_type::u },
                { 0x1BA8, joining_type::t },
                { 0x1BAA, joining_type::u },
                { 0x1BAB, joining_type::t },
                { 0x1BAE, joining_type::u },
                { 0x1BE6, joining_type::t },
                { 0x1BE7, joining_type::u },
                { 0x1BE8, joining_type::t },
                { 0x1BEA, joining_type::u },
                { 0x1BED, joining_type::t },
                { 0x1BEE, joining_type::u },
                { 0x1BEF, joining_type::t },
                { 0x1BF2, joining_type::u },
                { 0x1C2C, joining_type::t },
                { 0x1C34, joining_type::u },
                { 0x1C36, joining_type::t },
                { 0x1C38, joining_type::u },
                { 0x1CD0, joining_type::t },
                { 0x1CD3, joining_type::u },
                { 0x1CD4, joining_type::t },
                { 0x1CE1, joining_type::u },
                { 0x1CE2, joining_type::t },
                { 0x1CE9, joining_type::u },
                { 0x1CED, joining_type::t },
                { 0x1CEE, joining_type::u },
                { 0x1CF4, joining_type::t },
                { 0x1CF5, joining_type::u },
                { 0x1CF8, joining_type::t },
                { 0x1CFA, joining_type::u },
                { 0x1DC0, joining_type::t },
                { 0x1DF6, joining_type::u },
                { 0x1DFB, joining_type::t },
                { 0x1E00, joining_type::u },
                { 0x200B, joining_type::t },
                { 0x200C, joining_type::u },
                { 0x200D, joining_type::c },
                { 0x200E, joining_type::t },
                { 0x2010, joining_type::u },
                { 0x202A, joining_type::t },
                { 0x202F, joining_type::u },
                { 0x2060, joining_type::t },
                { 0x2065, joining_type::u },
                { 0x206A, joining_type::t },
                { 0x2070, joining_type::u },
                { 0x20D0, joining_type::t },
                { 0x20F1, joining_type::u },
                { 0x2CEF, joining_type::t },
                { 0x2CF2, joining_type::u },
                { 0x2D7F, joining_type::t },
                { 0x2D80, joining_type::u },
                { 0x2DE0, joining_type::t },
                { 0x2E00, joining_type::u },
                { 0x302A, joining_type::t },
                { 0x302E, joining_type::u },
                { 0x3099, joining_type::t },
                { 0x309B, joining_type::u },
                { 0xA66F, joining_type::t },
                { 0xA673, joining_type::u },
                { 0xA674, joining_type::t },
                { 0xA67E, joining_type::u },
                { 0xA69E, joining_type::t },
                { 0xA6A0, joining_type::u },
                { 0xA6F0, joining_type::t },
                { 0xA6F2, joining_type::u },
                { 0xA802, joining_type::t },
                { 0xA803, joining_type::u },
                { 0xA806, joining_type::t },
                { 0xA807, joining_type::u },
                { 0xA80B, joining_type::t },
                { 0xA80C, joining_type::u },
                { 0xA825, joining_type::t },
                { 0xA827, joining_type::u },
                { 0xA840, joining_type::d },
                { 0xA872, joining_type::l },
                { 0xA873, joining_type::u },
                { 0xA8C4, joining_type::t },
                { 0xA8C6, joining_type::u },
                { 0xA8E0, joining_type::t },
                { 0xA8F2, joining_type::u },
                { 0xA926, joining_type::t },
                { 0xA92E, joining_type::u },
                { 0xA947, joining_type::t },
                { 0xA952, joining_type::u },
                { 0xA980, joining_type::t },
                { 0xA983, joining_type::u },
                { 0xA9B3, joining_type::t },
                { 0xA9B4, joining_type::u },
                { 0xA9B6, joining_type::t },
                { 0xA9BA, joining_type::u },
                { 0xA9BC, joining_type::t },
                { 0xA9BD, joining_type::u },
                { 0xA9E5, joining_type::t },
                { 0xA9E6, joining_type::u },
                { 0xAA29, joining_type::t },
                { 0xAA2F, joining_type::u },
                { 0xAA31, joining_type::t },
                { 0xAA33, joining_type::u },
                { 0xAA35, joining_type::t },
                { 0xAA37, joining_type::u },
                { 0xAA43, joining_type::t },
                { 0xAA44, joining_type::u },
                { 0xAA4C, joining_type::t },
                { 0xAA4D, joining_type::u },
                { 0xAA7C, joining_type::t },
                { 0xAA7D, joining_type::u },
                { 0xAAB0, joining_type::t },
                { 0xAAB1, joining_type::u },
                { 0xAAB2, joining_type::t },
                { 0xAAB5, joining_type::u },
                { 0xAAB7, joining_type::t },
                { 0xAAB9, joining_type::u },
                { 0xAABE, joining_type::t },
                { 0xAAC0, joining_type::u },
                { 0xAAC1, joining_type::t },
                { 0xAAC2, joining_type::u },
                { 0xAAEC, joining_type::t },
                { 0xAAEE, joining_type::u },
                { 0xAAF6, joining_type::t },
                { 0xAAF7, joining_type::u },
                { 0xABE5, joining_type::t },
                { 0xABE6, joining_type::u },
                { 0xABE8, joining_type::t },
                { 0xABE9, joining_type::u },
                { 0xABED, joining_type::t },
                { 0xABEE, joining_type::u },
                { 0xFB1E, joining_type::t },
                { 0xFB1F, joining_type::u },
                { 0xFE00, joining_type::t },
                { 0xFE10, joining_type::u },
                { 0xFE20, joining_type::t },
                { 0xFE30, joining_type::u },
                { 0xFEFF, joining_type::t },
                { 0xFF00, joining_type::u },
                { 0xFFF9, joining_type::t },
                { 0xFFFC, joining_type::u },
                { 0x101FD, joining_type::t },
                { 0x101FE, joining_type::u },
                { 0x102E0, joining_type::t },
                { 0x102E1, joining_type::u },
                { 0x10376, joining_type::t },
                { 0x1037B, joining_type::u },
                { 0x10A01, joining_type::t },
                { 0x10A04, joining_type::u },
                { 0x10A05, joining_type::t },
                { 0x10A07, joining_type::u },
                { 0x10A0C, joining_type::t },
                { 0x10A10, joining_type::u },
                { 0x10A38, joining_type::t },
                { 0x10A3B, joining_type::u },
                { 0x10A3F, joining_type::t },
                { 0x10A40, joining_type::u },
                { 0x10AC0, joining_type::d },
                { 0x10AC5, joining_type::r },
                { 0x10AC6, joining_type::u },
                { 0x10AC7, joining_type::r },
                { 0x10AC8, joining_type::u },
                { 0x10AC9, joining_type::r },
                { 0x10ACB, joining_type::u },
                { 0x10ACD, joining_type::l },
                { 0x10ACE, joining_type::r },
                { 0x10AD3, joining_type::d },
                { 0x10AD7, joining_type::l },
                { 0x10AD8, joining_type::d },
                { 0x10ADD, joining_type::r },
                { 0x10ADE, joining_type::d },
                { 0x10AE1, joining_type::r },
                { 0x10AE2, joining_type::u },
                { 0x10AE4, joining_type::r },
                { 0x10AE5, joining_type::t },
                { 0x10AE7, joining_type::u },
                { 0x10AEB, joining_type::d },
                { 0x10AEF, joining_type::r },
                { 0x10AF0, joining_type::u },
                { 0x10B80, joining_type::d },
                { 0x10B81, joining_type::r },
                { 0x10B82, joining_type::d },
                { 0x10B83, joining_type::r },
                { 0x10B86, joining_type::d },
                { 0x10B89, joining_type::r },
                { 0x10B8A, joining_type::d },
                { 0x10B8C, joining_type::r },
                { 0x10B8D, joining_type::d },
                { 0x10B8E, joining_type::r },
                { 0x10B90, joining_type::d },
                { 0x10B91, joining_type::r },
                { 0x10B92, joining_type::u },
                { 0x10BA9, joining_type::r },
                { 0x10BAD, joining_type::d },
                { 0x10BAF, joining_type::u },
                { 0x11001, joining_type::t },
                { 0x11002, joining_type::u },
                { 0x11038, joining_type::t },
                { 0x11047, joining_type::u },
                { 0x1107F, joining_type::t },
                { 0x11082, joining_type::u },
                { 0x110B3, joining_type::t },
                { 0x110B7, joining_type::u },
                { 0x110B9, joining_type::t },
                { 0x110BB, joining_type::u },
                { 0x110BD, joining_type::t },
                { 0x110BE, joining_type::u },
                { 0x11100, joining_type::t },
                { 0x11103, joining_type::u },
                { 0x11127, joining_type::t },
                { 0x1112C, joining_type::u },
                { 0x1112D, joining_type::t },
                { 0x11135, joining_type::u },
                { 0x11173, joining_type::t },
                { 0x11174, joining_type::u },
                { 0x11180, joining_type::t },
                { 0x11182, joining_type::u },
                { 0x111B6, joining_type::t },
                { 0x111BF, joining_type::u },
                { 0x111CA, joining_type::t },
                { 0x111CD, joining_type::u },
                { 0x1122F, joining_type::t },
                { 0x11232, joining_type::u },
                { 0x11234, joining_type::t },
                { 0x11235, joining_type::u },
                { 0x11236, joining_type::t },
                { 0x11238, joining_type::u },
                { 0x1123E, joining_type::t },
                { 0x1123F, joining_type::u },
                { 0x112DF, joining_type::t },
                { 0x112E0, joining_type::u },
                { 0x112E3, joining_type::t },
                { 0x112EB, joining_type::u },
                { 0x11300, joining_type::t },
                { 0x11302, joining_type::u },
                { 0x1133C, joining_type::t },
                { 0x1133D, joining_type::u },
                { 0x11340, joining_type::t },
                { 0x11341, joining_type::u },
                { 0x11366, joining_type::t },
                { 0x1136D, joining_type::u },
                { 0x11370, joining_type::t },
                { 0x11375, joining_type::u },
                { 0x11438, joining_type::t },
                { 0x11440, joining_type::u },
                { 0x11442, joining_type::t },
                { 0x11445, joining_type::u },
                { 0x11446, joining_type::t },
                { 0x11447, joining_type::u },
                { 0x114B3, joining_type::t },
                { 0x114B9, joining_type::u },
                { 0x114BA, joining_type::t },
                { 0x114BB, joining_type::u },
                { 0x114BF, joining_type::t },
                { 0x114C1, joining_type::u },
                { 0x114C2, joining_type::t },
                { 0x114C4, joining_type::u },
                { 0x115B2, joining_type::t },
                { 0x115B6, joining_type::u },
                { 0x115BC, joining_type::t },
                { 0x115BE, joining_type::u },
                { 0x115BF, joining_type::t },
                { 0x115C1, joining_type::u },
                { 0x115DC, joining_type::t },
                { 0x115DE, joining_type::u },
                { 0x11633, joining_type::t },
                { 0x1163B, joining_type::u },
                { 0x1163D, joining_type::t },
                { 0x1163E, joining_type::u },
                { 0x1163F, joining_type::t },
                { 0x11641, joining_type::u },
                { 0x116AB, joining_type::t },
                { 0x116AC, joining_type::u },
                { 0x116AD, joining_type::t },
                { 0x116AE, joining_type::u },
                { 0x116B0, joining_type::t },
                { 0x116B6, joining_type::u },
                { 0x116B7, joining_type::t },
                { 0x116B8, joining_type::u },
                { 0x1171D, joining_type::t },
                { 0x11720, joining_type::u },
                { 0x11722, joining_type::t },
                { 0x11726, joining_type::u },
                { 0x11727, joining_type::t },
                { 0x1172C, joining_type::u },
                { 0x11C30, joining_type::t },
                { 0x11C37, joining_type::u },
                { 0x11C38, joining_type::t },
                { 0x11C3E, joining_type::u },
                { 0x11C3F, joining_type::t },
                { 0x11C40, joining_type::u },
                { 0x11C92, joining_type::t },
                { 0x11CA8, joining_type::u },
                { 0x11CAA, joining_type::t },
                { 0x11CB1, joining_type::u },
                { 0x11CB2, joining_type::t },
                { 0x11CB4, joining_type::u },
                { 0x11CB5, joining_type::t },
                { 0x11CB7, joining_type::u },
                { 0x16AF0, joining_type::t },
                { 0x16AF5, joining_type::u },
                { 0x16B30, joining_type::t },
                { 0x16B37, joining_type::u },
                { 0x16F8F, joining_type::t },
                { 0x16F93, joining_type::u },
                { 0x1BC9D, joining_type::t },
                { 0x1BC9F, joining_type::u },
                { 0x1BCA0, joining_type::t },
                { 0x1BCA4, joining_type::u },
                { 0x1D167, joining_type::t },
                { 0x1D16A, joining_type::u },
                { 0x1D173, joining_type::t },
                { 0x1D183, joining_type::u },
                { 0x1D185, joining_type::t },
                { 0x1D18C, joining_type::u },
                { 0x1D1AA, joining_type::t },
                { 0x1D1AE, joining_type::u },
                { 0x1D242, joining_type::t },
                { 0x1D245, joining_type::u },
                { 0x1DA00, joining_type::t },
                { 0x1DA37, joining_type::u },
                { 0x1DA3B, joining_type::t },
                { 0x1DA6D, joining_type::u },
                { 0x1DA75, joining_type::t },
                { 0x1DA76, joining_type::u },
                { 0x1DA84, joining_type::t },
                { 0x1DA85, joining_type::u },
                { 0x1DA9B, joining_type::t },
                { 0x1DAA0, joining_type::u },
                { 0x1DAA1, joining_type::t },
                { 0x1DAB0, joining_type::u },
                { 0x1E000, joining_type::t },
                { 0x1E007, joining_type::u },
                { 0x1E008, joining_type::t },
                { 0x1E019, joining_type::u },
                { 0x1E01B, joining_type::t },
                { 0x1E022, joining_type::u },
                { 0x1E023, joining_type::t },
                { 0x1E025, joining_type::u },
                { 0x1E026, joining_type::t },
                { 0x1E02B, joining_type::u },
                { 0x1E8D0, joining_type::t },
                { 0x1E8D7, joining_type::u },
                { 0x1E900, joining_type::d },
                { 0x1E944, joining_type::t },
                { 0x1E94B, joining_type::u },
                { 0xE0001, joining_type::t },
                { 0xE0002, joining_type::u },
                { 0xE0020, joining_type::t },
                { 0xE0080, joining_type::u },
                { 0xE0100, joining_type::t },
                { 0xE01F0, joining_type::u },
            };
        } // namespace
        inline namespace abiv0 {
            joining_type_properties const* joining_type_data = joining_type_data_raw;
            std::size_t joining_type_data_size = detail::size(joining_type_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek
