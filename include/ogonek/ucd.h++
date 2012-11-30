// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode character database data structures

#ifndef OGONEK_UCD_HPP
#define OGONEK_UCD_HPP

#include <ogonek/types.h++>
#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>
#include <ogonek/detail/array_slice.h++>
#include <ogonek/visibility.h++>

#include <boost/logic/tribool.hpp>

#include <vector>
#include <string>

namespace ogonek {
    // Forward declare for text properties
    template <typename Encoding, typename Container>
    class basic_text;
    class utf8;

    namespace ucd {
        enum class version {
            v1_1,
            v2_0, v2_1,
            v3_0, v3_1, v3_2,
            v4_0, v4_1,
            v5_0, v5_1, v5_2,
            v6_0, v6_1, v6_2,
            unassigned = 0xFF,
        };
        enum class alias_type {
            abbreviation, alternate, control, correction, figment,
        };
        struct alias {
            alias_type type;
            char const* name;
        };
        enum class block {
            Aegean_Numbers, Alchemical, Alphabetic_PF, Ancient_Greek_Music, Ancient_Greek_Numbers,
            Ancient_Symbols, Arabic, Arabic_Ext_A, Arabic_Math, Arabic_PF_A, Arabic_PF_B, Arabic_Sup,
            Armenian, Arrows, ASCII, Avestan, Balinese, Bamum, Bamum_Sup, Batak, Bengali, Block_Elements,
            Bopomofo, Bopomofo_Ext, Box_Drawing, Brahmi, Braille, Buginese, Buhid, Byzantine_Music,
            Carian, Chakma, Cham, Cherokee, CJK, CJK_Compat, CJK_Compat_Forms, CJK_Compat_Ideographs,
            CJK_Compat_Ideographs_Sup, CJK_Ext_A, CJK_Ext_B, CJK_Ext_C, CJK_Ext_D, CJK_Radicals_Sup,
            CJK_Strokes, CJK_Symbols, Compat_Jamo, Control_Pictures, Coptic, Counting_Rod, Cuneiform,
            Cuneiform_Numbers, Currency_Symbols, Cypriot_Syllabary, Cyrillic, Cyrillic_Ext_A, Cyrillic_Ext_B,
            Cyrillic_Sup, Deseret, Devanagari, Devanagari_Ext, Diacriticals, Diacriticals_For_Symbols,
            Diacriticals_Sup, Dingbats, Domino, Egyptian_Hieroglyphs, Emoticons, Enclosed_Alphanum,
            Enclosed_Alphanum_Sup, Enclosed_CJK, Enclosed_Ideographic_Sup, Ethiopic, Ethiopic_Ext,
            Ethiopic_Ext_A, Ethiopic_Sup, Geometric_Shapes, Georgian, Georgian_Sup, Glagolitic, Gothic, Greek,
            Greek_Ext, Gujarati, Gurmukhi, Half_And_Full_Forms, Half_Marks, Hangul, Hanunoo, Hebrew,
            High_PU_Surrogates, High_Surrogates, Hiragana, IDC, Imperial_Aramaic, Indic_Number_Forms,
            Inscriptional_Pahlavi, Inscriptional_Parthian, IPA_Ext, Jamo, Jamo_Ext_A, Jamo_Ext_B, Javanese,
            Kaithi, Kana_Sup, Kanbun, Kangxi, Kannada, Katakana, Katakana_Ext, Kayah_Li, Kharoshthi, Khmer,
            Khmer_Symbols, Lao, Latin_1_Sup, Latin_Ext_A, Latin_Ext_Additional, Latin_Ext_B, Latin_Ext_C,
            Latin_Ext_D, Lepcha, Letterlike_Symbols, Limbu, Linear_B_Ideograms, Linear_B_Syllabary, Lisu,
            Low_Surrogates, Lycian, Lydian, Mahjong, Malayalam, Mandaic, Math_Alphanum, Math_Operators,
            Meetei_Mayek, Meetei_Mayek_Ext, Meroitic_Cursive, Meroitic_Hieroglyphs, Miao, Misc_Arrows,
            Misc_Math_Symbols_A, Misc_Math_Symbols_B, Misc_Pictographs, Misc_Symbols, Misc_Technical,
            Modifier_Letters, Modifier_Tone_Letters, Mongolian, Music, Myanmar, Myanmar_Ext_A, NB,
            New_Tai_Lue, NKo, Number_Forms, OCR, Ogham, Ol_Chiki, Old_Italic, Old_Persian, Old_South_Arabian,
            Old_Turkic, Oriya, Osmanya, Phags_Pa, Phaistos, Phoenician, Phonetic_Ext, Phonetic_Ext_Sup,
            Playing_Cards, PUA, Punctuation, Rejang, Rumi, Runic, Samaritan, Saurashtra, Sharada, Shavian,
            Sinhala, Small_Forms, Sora_Sompeng, Specials, Sundanese, Sundanese_Sup, Sup_Arrows_A, Sup_Arrows_B,
            Sup_Math_Operators, Sup_PUA_A, Sup_PUA_B, Sup_Punctuation, Super_And_Sub, Syloti_Nagri, Syriac,
            Tagalog, Tagbanwa, Tags, Tai_Le, Tai_Tham, Tai_Viet, Tai_Xuan_Jing, Takri, Tamil, Telugu, Thaana,
            Thai, Tibetan, Tifinagh, Transport_And_Map, UCAS, UCAS_Ext, Ugaritic, Vai, Vedic_Ext,
            Vertical_Forms, VS, VS_Sup, Yi_Radicals, Yi_Syllables, Yijing,
        };
        enum class category {
            Lu, Ll, Lt, Lm, Lo,
            Mn, Mc, Me,
            Nd, Nl, No,
            Pc, Pd, Ps, Pe, Pi, Pf, Po,
            Sm, Sc, Sk, So,
            Zs, Zl, Zp,
            Cc, Cf, Cs, Co, Cn,
        };
        enum class bidi_category {
            AL, AN,
            B, BN,
            CS,
            EN, ES, ET,
            L, LRE, LRO,
            NSM,
            ON,
            PDF,
            R, RLE, RLO,
            S,
            WS,
        };
        enum class decomposition_type {
            can, com, enc, fin, font, fra,
            init, iso, med, nar, nb, sml,
            sqr, sub, sup, vert, wide, none,
        };
        enum class yes_no_maybe {
            y, n, m,
        };
        enum class numeric_type {
            None, De, Di, Nu,
        };
        enum class joining_class {
            U, C, T, D, L, R,
        };
        enum class joining_group {
            Ain, Alaph, Alef, Alef_Maqsurah,
            Beh, Beth, Burushaski_Yeh_Barree,
            Dal, Dalath_Rish, E,
            Farsi_Yeh, Fe, Feh, Final_Semkath,
            Gaf, Gamal,
            Hah, Hamza_On_Heh_Goal, He,
            Heh, Heh_Goal, Heth,
            Kaf, Kaph, Khaph, Knotted_Heh,
            Lam, Lamadh, Meem, Mim,
            No_Joining_Group, Noon, Nun, Nya,
            Pe, Qaf, Qaph, Reh, Reversed_Pe,
            Rohingya_Yeh,
            Sad, Sadhe, Seen, Semkath, Shin,
            Swash_Kaf, Syriac_Waw, Tah, Taw,
            Teh_Marbuta, Teh_Marbuta_Goal, Teth, Waw, Yeh,
            Yeh_Barree, Yeh_With_Tail, Yudh,
            Yudh_He, Zain, Zhain,
        };
        enum class linebreak {
            AI, AL,
            B2, BA, BB, BK,
            CB, CJ, CL, CM, CP, CR,
            EX,
            GL,
            H2, H3, HL, HY,
            ID, IN, IS,
            JL, JT, JV,
            LF,
            NL, NS, NU,
            OP,
            PO, PR,
            QU,
            SA, SG, SP, SY,
            WJ,
            XX,
            ZW,
            RI,
        };
        enum class east_asian_width {
            A, F, H, N, Na, W,
        };
        enum class script {
            Arab, Armi, Armn, Avst,
            Bali, Bamu, Batk, Beng, Bopo, Brah, Brai, Bugi, Buhd,
            Cakm, Cans, Cari, Cham, Cher, Copt, Cprt,
            Cyrl,
            Deva, Dsrt,
            Egyp, Ethi,
            Geor, Glag, Goth, Grek, Gujr, Guru,
            Hang, Hani, Hano, Hebr, Hira, Hrkt,
            Ital,
            Java,
            Kali, Kana, Khar, Khmr, Knda, Kthi,
            Lana, Laoo, Latn, Lepc, Limb, Linb, Lisu, Lyci,
            Lydi,
            Mand, Merc, Mero, Mlym, Mong, Mtei, Mymr,
            Nkoo,
            Ogam, Olck, Orkh, Orya, Osma,
            Phag, Phli, Phnx, Plrd, Prti,
            Qaai,
            Rjng, Runr,
            Samr, Sarb, Saur, Shaw, Shrd,  Sinh, Sora, Sund, Sylo, Syrc,
            Tagb, Takr, Tale, Talu, Taml, Tavt, Telu, Tfng,
            Tglg, Thaa, Thai, Tibt,
            Ugar,
            Vaii,
            Xpeo, Xsux,
            Yiii,
            Zinh, Zyyy, Zzzz,
        };
        enum class hangul_syllable_type {
            L, LV, LVT, T, V, NA,
        };
        enum class indic_syllable_category {
            Bindu,
            Visarga,
            Avagraha,
            Nukta,
            Virama,
            Vowel_Independent,
            Vowel_Dependent,
            Vowel,
            Consonant_Placeholder,
            Consonant,
            Consonant_Dead,
            Consonant_Repha,
            Consonant_Subjoined,
            Consonant_Medial,
            Consonant_Final,
            Consonant_Head_Letter,
            Modifying_Letter,
            Tone_Letter,
            Tone_Mark,
            Register_Shifter,
            Other,
        };
        enum class indic_matra_category {
            Right,
            Left,
            Visual_Order_Left,
            Left_And_Right,
            Top,
            Bottom,
            Top_And_Bottom,
            Top_And_Right,
            Top_And_Left,
            Top_And_Left_And_Right,
            Bottom_And_Right,
            Top_And_Bottom_And_Right,
            Overstruck,
            Invisible,
            NA,
        };
        enum class grapheme_cluster_break : unsigned {
            CN  = 1u << 0,
            CR  = 1u << 1,
            EX  = 1u << 2,
            L   = 1u << 3,
            LF  = 1u << 4,
            LV  = 1u << 5,
            LVT = 1u << 6,
            PP  = 1u << 7,
            SM  = 1u << 8,
            T   = 1u << 9,
            V   = 1u << 10,
            XX  = 1u << 11,
            RI  = 1u << 12,
        };
        enum class word_break {
            CR, EX, Extend, FO, KA, LE,
            LF, MB, ML, MN, NL, NU, XX,
            RI,
        };
        enum class sentence_break {
            AT, CL, CR, EX, FO, LE, LF, LO,
            NU, SC, SE, SP, ST, UP, XX,
        };

        template <typename T>
        struct simple_properties {
            codepoint start;
            T data;
        };
        using version_properties = simple_properties<version>;
        struct name_properties {
            codepoint start;
            bool variable; // whether # needs to be replaced
            char const* name;
        };
        struct alias_properties {
            codepoint start;
            alias const* first;
            int count;
        };
        using block_properties = simple_properties<block>;
        using category_properties = simple_properties<category>;
        using combining_class_properties = simple_properties<int>;
        struct bidi_properties {
            codepoint start;
            bidi_category category;
            bool mirrored;
            codepoint mirrored_glyph;
            bool control;
        };
        struct composition_entry {
            codepoint other;
            codepoint precomposed;
        };
        struct composition_properties {
            codepoint starter;
            std::initializer_list<composition_entry> compositions;
        };
        struct decomposition_properties {
            codepoint start;
            decomposition_type type;
            codepoint const* mapping;
            bool composition_exclusion;
            bool full_composition_exclusion;
            yes_no_maybe nfc_quick_check;
            bool nfd_quick_check;
            yes_no_maybe nfkc_quick_check;
            bool nfkd_quick_check;
            bool expands_on_nfc;
            bool expands_on_nfd;
            bool expands_on_nfkc;
            bool expands_on_nfkd;
            codepoint const* fc_nfkc_closure;
        };
        struct numeric_properties {
            codepoint start;
            numeric_type type;
            double value;
        };
        struct joining_properties {
            codepoint start;
            joining_class class_;
            joining_group group;
            bool control;
        };
        using linebreak_properties = simple_properties<linebreak>;
        using east_asian_properties = simple_properties<east_asian_width>;
        struct case_properties {
            codepoint start;
            bool is_uppercase, is_lowercase, other_uppercase, other_lowercase;
            codepoint simple_uppercase, simple_lowercase, simple_titlecase;
            codepoint const* uppercase;
            codepoint const* lowercase;
            codepoint const* titlecase;
            codepoint simple_case_folding;
            codepoint const* case_folding;
            bool case_ignorable;
            bool cased;
            bool changes_when_casefolded, changes_when_casemapped, changes_when_lowercased,
                 changes_when_nfkc_casefolded, changes_when_titlecased, changes_when_uppercased;
            codepoint const* nfkc_casefold;
        };
        struct script_properties {
            codepoint start;
            ucd::script script;
            ucd::script const* first_script_extension;
            int script_extension_count;
        };
        using iso_comment_properties = simple_properties<codepoint const*>;
        struct hangul_properties {
            codepoint start;
            hangul_syllable_type syllable_type;
            char const jamo_short_name[4];
        };
        struct indic_properties {
            codepoint start;
            indic_syllable_category syllable_category;
            indic_matra_category matra_category;
        };
        struct identifier_properties {
            codepoint start;
            bool id_start, other_id_start, xid_start;
            bool id_continue, other_id_continue, xid_continue;
        };
        struct pattern_properties {
            codepoint start;
            bool syntax;
            bool white_space;
        };
        struct function_properties {
            codepoint start;
            bool dash, hyphen, quotation_mark, terminal_punctuation, sterm, diacritic,
                 extender, soft_dotted, alphabetic, other_alphabetic, math, other_math,
                 hex_digit, ascii_hex_digit, default_ignorable, other_default_ignorable,
                 logical_order_exception, white_space;
        };
        struct boundary_properties {
            codepoint start;
            bool grapheme_base, grapheme_extend, other_grapheme_extend, grapheme_link;
            ucd::grapheme_cluster_break grapheme_cluster_break;
            ucd::word_break word_break;
            ucd::sentence_break sentence_break;
        };
        struct ideograph_properties {
            codepoint start;
            bool ideographic;
            bool unified_ideograph;
            bool ids_binary_operator;
            bool ids_trinary_operator;
            bool radical;
        };
        struct miscellaneous_properties {
            codepoint start;
            bool deprecated;
            bool variant_selector;
            bool noncharacter;
        };

        extern OGONEK_PUBLIC version_properties const* version_data;
        extern OGONEK_PUBLIC std::size_t version_data_size;
        extern OGONEK_PUBLIC name_properties const* name_data;
        extern OGONEK_PUBLIC std::size_t name_data_size;
        extern OGONEK_PUBLIC name_properties const* v1name_data;
        extern OGONEK_PUBLIC std::size_t v1name_data_size;
        extern OGONEK_PUBLIC alias_properties const* aliases_data;
        extern OGONEK_PUBLIC std::size_t aliases_data_size;
        extern OGONEK_PUBLIC block_properties const* block_data;
        extern OGONEK_PUBLIC std::size_t block_data_size;
        extern OGONEK_PUBLIC category_properties const* category_data;
        extern OGONEK_PUBLIC std::size_t category_data_size;
        extern OGONEK_PUBLIC combining_class_properties const* combining_class_data;
        extern OGONEK_PUBLIC std::size_t combining_class_data_size;
        extern OGONEK_PUBLIC bidi_properties const* bidi_data;
        extern OGONEK_PUBLIC std::size_t bidi_data_size;
        extern OGONEK_PUBLIC composition_properties const* composition_data;
        extern OGONEK_PUBLIC std::size_t composition_data_size;
        extern OGONEK_PUBLIC decomposition_properties const* decomposition_data;
        extern OGONEK_PUBLIC std::size_t decomposition_data_size;
        extern OGONEK_PUBLIC numeric_properties const* numeric_data;
        extern OGONEK_PUBLIC std::size_t numeric_data_size;
        extern OGONEK_PUBLIC joining_properties const* joining_data;
        extern OGONEK_PUBLIC std::size_t joining_data_size;
        extern OGONEK_PUBLIC linebreak_properties const* linebreak_data;
        extern OGONEK_PUBLIC std::size_t linebreak_data_size;
        extern OGONEK_PUBLIC east_asian_properties const* east_asian_data;
        extern OGONEK_PUBLIC std::size_t east_asian_data_size;
        extern OGONEK_PUBLIC case_properties const* case_data;
        extern OGONEK_PUBLIC std::size_t case_data_size;
        extern OGONEK_PUBLIC script_properties const* script_data;
        extern OGONEK_PUBLIC std::size_t script_data_size;
        extern OGONEK_PUBLIC iso_comment_properties const* iso_comment_data;
        extern OGONEK_PUBLIC std::size_t iso_comment_data_size;
        extern OGONEK_PUBLIC hangul_properties const* hangul_data;
        extern OGONEK_PUBLIC std::size_t hangul_data_size;
        extern OGONEK_PUBLIC indic_properties const* indic_data;
        extern OGONEK_PUBLIC std::size_t indic_data_size;
        extern OGONEK_PUBLIC identifier_properties const* identifier_data;
        extern OGONEK_PUBLIC std::size_t identifier_data_size;
        extern OGONEK_PUBLIC pattern_properties const* pattern_data;
        extern OGONEK_PUBLIC std::size_t pattern_data_size;
        extern OGONEK_PUBLIC function_properties const* function_data;
        extern OGONEK_PUBLIC std::size_t function_data_size;
        extern OGONEK_PUBLIC boundary_properties const* boundary_data;
        extern OGONEK_PUBLIC std::size_t boundary_data_size;
        extern OGONEK_PUBLIC ideograph_properties const* ideograph_data;
        extern OGONEK_PUBLIC std::size_t ideograph_data_size;
        extern OGONEK_PUBLIC miscellaneous_properties const* miscellaneous_data;
        extern OGONEK_PUBLIC std::size_t miscellaneous_data_size;

        using text = basic_text<utf8, std::string>;

        namespace detail {
            struct property_group_locator {
                template <typename T>
                bool operator()(codepoint u, T const& g) const {
                    return u >= g.start;
                }
            };
            template <typename It>
            std::reverse_iterator<It> make_reverse(It it) {
                return std::reverse_iterator<It> { it };
            }
            template <typename T>
            T const& find_property_group(T const* first, std::size_t size, codepoint target) {
                return *std::upper_bound(make_reverse(first+size), make_reverse(first), target, property_group_locator{});
            }
            inline boost::tribool to_tribool(yes_no_maybe ynm) {
                if(ynm == yes_no_maybe::y) return true;
                else if(ynm == yes_no_maybe::n) return false;
                else return boost::indeterminate;
            }
        } // namespace detail

        inline version get_age(codepoint u) {
            return detail::find_property_group(version_data, version_data_size, u).data;
        }

        namespace detail {
            inline std::string to_hex(codepoint u) {
                char const hex[] = "0123456789ABCDEF";
                std::string result;
                int factor;
                if(u > 0xFFFFF) factor = 0x100000;
                else if(u > 0xFFFF) factor = 0x10000;
                else factor = 0x1000;
                for(; factor > 0; u %= factor, factor /= 0x10) {
                    result.push_back(hex[u / factor]);
                }
                return result;
            }

            inline text get_name(name_properties const* data, std::size_t data_size, codepoint u) {
                name_properties const& p = detail::find_property_group(data, data_size, u);
                if(p.variable) {
                    std::string name { p.name };
                    name.reserve(name.size() + 5);
                    name.replace(name.find('#'), 1, to_hex(u));
                    return text { std::move(name) };
                } else {
                    return text {{ p.name }};
                }
            }
        } // namespace detail
        inline text get_name(codepoint u) {
            return detail::get_name(name_data, name_data_size, u);
        }
        inline text get_unicode1_name(codepoint u) {
            return detail::get_name(v1name_data, v1name_data_size, u);
        }
        inline std::vector<alias> get_aliases(codepoint u);

        inline block get_block(codepoint u) {
            return detail::find_property_group(block_data, block_data_size, u).data;
        }
        inline category get_general_category(codepoint u) {
            return detail::find_property_group(category_data, category_data_size, u).data;
        }
        inline int get_combining_class(codepoint u) {
            return detail::find_property_group(combining_class_data, combining_class_data_size, u).data;
        }
        inline bidi_category get_bidi_category(codepoint u) {
            return detail::find_property_group(bidi_data, bidi_data_size, u).category;
        }
        inline bool is_bidi_mirrored(codepoint u) {
            return detail::find_property_group(bidi_data, bidi_data_size, u).mirrored;
        }
        inline codepoint get_bidi_mirrored_glyph(codepoint u) {
            auto glyph = detail::find_property_group(bidi_data, bidi_data_size, u).mirrored_glyph;
            if(glyph == codepoint(-1)) return u;
            else return glyph;
        }
        inline bool is_bidi_control(codepoint u) {
            return detail::find_property_group(bidi_data, bidi_data_size, u).control;
        }
        namespace detail {
            inline composition_properties get_composition_properties(codepoint starter) {
                auto it = std::lower_bound(composition_data, composition_data+composition_data_size, composition_properties { starter, {} },
                           [](composition_properties const& a, composition_properties const& b){
                               return a.starter < b.starter;
                           });
                if(it != composition_data+composition_data_size && it->starter == starter) {
                    return *it;
                } else {
                    return { starter, {} };
                }
            }
            inline composition_entry get_composition_entry(codepoint starter, codepoint other) {
                auto compositions = get_composition_properties(starter).compositions;
                auto it = std::lower_bound(compositions.begin(), compositions.end(), composition_entry { other, 0 },
                           [](composition_entry const& a, composition_entry const& b){
                               return a.other < b.other;
                           });
                if(it != compositions.end() && it->other == other) {
                    return *it;
                } else {
                    return { other, static_cast<codepoint>(-1) };
                }
            }
        } // namespace detail
        inline bool can_compose(codepoint starter) {
            return detail::get_composition_properties(starter).compositions.size() > 0;
        }
        inline bool can_compose(codepoint starter, codepoint other) {
            return detail::get_composition_entry(starter, other).precomposed != static_cast<codepoint>(-1);
        }
        inline codepoint compose(codepoint starter, codepoint other) {
            return detail::get_composition_entry(starter, other).precomposed;
        }
        inline decomposition_type get_decomposition_type(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).type;
        }
        inline std::vector<codepoint> get_decomposition_mapping(codepoint u) {
            auto mapping = detail::find_property_group(decomposition_data, decomposition_data_size, u).mapping;
            if(mapping) return std::vector<codepoint>(mapping, mapping + std::char_traits<codepoint>::length(mapping));
            else return std::vector<codepoint>(1, u);
        }
        inline bool is_excluded_from_composition(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).full_composition_exclusion;
        }
        inline boost::tribool is_nfc_quick_check(codepoint u) {
            return detail::to_tribool(detail::find_property_group(decomposition_data, decomposition_data_size, u).nfc_quick_check);
        }
        inline bool is_nfd_quick_check(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).nfd_quick_check;
        }
        inline boost::tribool is_nfkc_quick_check(codepoint u) {
            return detail::to_tribool(detail::find_property_group(decomposition_data, decomposition_data_size, u).nfkc_quick_check);
        }
        inline bool is_nfkd_quick_check(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).nfkd_quick_check;
        }
        //[[deprecated("since 6.0")]]
        inline bool expands_on_nfc(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfc;
        }
        //[[deprecated("since 6.0")]]
        inline bool expands_on_nfd(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfd;
        }
        //[[deprecated("since 6.0")]]
        inline bool expands_on_nfkc(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfkc;
        }
        //[[deprecated("since 6.0")]]
        inline bool expands_on_nfkd(codepoint u) {
            return detail::find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfkd;
        }
        //[[deprecated("since 6.0")]]
        inline ogonek::detail::array_slice<codepoint const> get_fc_nfkc_closure(codepoint u) {
            auto closure = detail::find_property_group(decomposition_data, decomposition_data_size, u).fc_nfkc_closure;
            return { closure, closure + std::char_traits<codepoint>::length(closure) };
        }
        inline numeric_type get_numeric_type(codepoint u) {
            return detail::find_property_group(numeric_data, numeric_data_size, u).type;
        }
        inline double get_numeric_value(codepoint u) {
            return detail::find_property_group(numeric_data, numeric_data_size, u).value;
        }
        inline joining_class get_joining_class(codepoint u) {
            return detail::find_property_group(joining_data, joining_data_size, u).class_;
        }
        inline joining_group get_joining_group(codepoint u) {
            return detail::find_property_group(joining_data, joining_data_size, u).group;
        }
        inline bool is_join_control(codepoint u) {
            return detail::find_property_group(joining_data, joining_data_size, u).control;
        }
        inline linebreak get_linebreak_type(codepoint u) {
            return detail::find_property_group(linebreak_data, linebreak_data_size, u).data;
        }
        inline east_asian_width get_east_asian_width_type(codepoint u) {
            return detail::find_property_group(east_asian_data, east_asian_data_size, u).data;
        }
        inline bool is_uppercase(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).is_uppercase;
        }
        inline bool is_lowercase(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).is_lowercase;
        }
        inline codepoint get_simple_uppercase(codepoint u) {
            auto result = detail::find_property_group(case_data, case_data_size, u).simple_uppercase;
            if(result == codepoint(-1)) return u;
            return result;
        }
        inline codepoint get_simple_lowercase(codepoint u) {
            auto result = detail::find_property_group(case_data, case_data_size, u).simple_lowercase;
            if(result == codepoint(-1)) return u;
            return result;
        }
        inline codepoint get_simple_titlecase(codepoint u) {
            auto result = detail::find_property_group(case_data, case_data_size, u).simple_titlecase;
            if(result == codepoint(-1)) return u;
            return result;
        }
        inline std::vector<codepoint> get_uppercase(codepoint u) {
            auto uc = detail::find_property_group(case_data, case_data_size, u).uppercase;
            if(uc) return std::vector<codepoint>(uc, uc + std::char_traits<codepoint>::length(uc));
            else return std::vector<codepoint>(1, u);
        }
        inline std::vector<codepoint> get_lowercase(codepoint u) {
            auto lc = detail::find_property_group(case_data, case_data_size, u).lowercase;
            if(lc) return std::vector<codepoint>(lc, lc + std::char_traits<codepoint>::length(lc));
            else return std::vector<codepoint>(1, u);
        }
        inline std::vector<codepoint> get_titlecase(codepoint u) {
            auto tc = detail::find_property_group(case_data, case_data_size, u).titlecase;
            if(tc) return std::vector<codepoint>(tc, tc + std::char_traits<codepoint>::length(tc));
            else return std::vector<codepoint>(1, u);
        }
        inline codepoint get_simple_case_folding(codepoint u) {
            auto result = detail::find_property_group(case_data, case_data_size, u).simple_case_folding;
            if(result == codepoint(-1)) return u;
            return result;
        }
        inline std::vector<codepoint> get_case_folding(codepoint u) {
            auto cf = detail::find_property_group(case_data, case_data_size, u).case_folding;
            if(cf) return std::vector<codepoint>(cf, cf + std::char_traits<codepoint>::length(cf));
            else return std::vector<codepoint>(1, u);
        }
        inline bool is_case_ignorable(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).case_ignorable;
        }
        inline bool is_cased(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).cased;
        }
        inline bool changes_when_casefolded(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).changes_when_casefolded;
        }
        inline bool changes_when_casemapped(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).changes_when_casemapped;
        }
        inline bool changes_when_lowercased(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).changes_when_lowercased;
        }
        inline bool changes_when_nfkc_casefolded(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).changes_when_nfkc_casefolded;
        }
        inline bool changes_when_titlecased(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).changes_when_titlecased;
        }
        inline bool changes_when_uppercased(codepoint u) {
            return detail::find_property_group(case_data, case_data_size, u).changes_when_uppercased;
        }
        inline std::vector<codepoint> get_nfkc_casefold(codepoint u) {
            auto cf = detail::find_property_group(case_data, case_data_size, u).nfkc_casefold;
            if(cf) return std::vector<codepoint>(cf, cf + std::char_traits<codepoint>::length(cf));
            else return std::vector<codepoint>(1, u);
        }
        inline script get_script(codepoint u) {
            return detail::find_property_group(script_data, script_data_size, u).script;
        }
        inline ogonek::detail::array_slice<script const> get_script_extension(codepoint u) {
            auto& prop = detail::find_property_group(script_data, script_data_size, u);
            return { prop.first_script_extension, prop.first_script_extension + prop.script_extension_count };
        }
        inline text get_iso_comment(codepoint u) {
            return text { detail::find_property_group(iso_comment_data, iso_comment_data_size, u).data };
        }
        inline hangul_syllable_type get_hangul_syllable_type(codepoint u) {
            return detail::find_property_group(hangul_data, hangul_data_size, u).syllable_type;
        }
        inline text get_jamo_short_name(codepoint u) {
            return text {{ detail::find_property_group(hangul_data, hangul_data_size, u).jamo_short_name }};
        }
        inline indic_syllable_category get_indic_syllable_category(codepoint u) {
            return detail::find_property_group(indic_data, indic_data_size, u).syllable_category;
        }
        inline indic_matra_category get_indic_matra_category(codepoint u) {
            return detail::find_property_group(indic_data, indic_data_size, u).matra_category;
        }
        inline bool is_id_start(codepoint u) {
            return detail::find_property_group(identifier_data, identifier_data_size, u).id_start;
        }
        inline bool is_other_id_start(codepoint u) {
            return detail::find_property_group(identifier_data, identifier_data_size, u).other_id_start;
        }
        inline bool is_xid_start(codepoint u) {
            return detail::find_property_group(identifier_data, identifier_data_size, u).xid_start;
        }
        inline bool is_id_continue(codepoint u) {
            return detail::find_property_group(identifier_data, identifier_data_size, u).id_continue;
        }
        inline bool is_other_id_continue(codepoint u) {
            return detail::find_property_group(identifier_data, identifier_data_size, u).other_id_continue;
        }
        inline bool is_xid_continue(codepoint u) {
            return detail::find_property_group(identifier_data, identifier_data_size, u).xid_continue;
        }
        inline bool is_pattern_syntax(codepoint u) {
            return detail::find_property_group(pattern_data, pattern_data_size, u).syntax;
        }
        inline bool is_pattern_white_space(codepoint u) {
            return detail::find_property_group(pattern_data, pattern_data_size, u).white_space;
        }
        inline bool is_dash(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).dash;
        }
        inline bool is_hyphen(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).hyphen;
        }
        inline bool is_quotation_mark(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).quotation_mark;
        }
        inline bool is_terminal_punctuation(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).terminal_punctuation;
        }
        inline bool is_sentence_terminal(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).sterm;
        }
        inline bool is_diacritic(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).diacritic;
        }
        inline bool is_extender(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).extender;
        }
        inline bool is_soft_dotted(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).soft_dotted;
        }
        inline bool is_alphabetic(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).alphabetic;
        }
        inline bool is_other_alphabetic(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).other_alphabetic;
        }
        inline bool is_math(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).math;
        }
        inline bool is_other_math(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).other_math;
        }
        inline bool is_hex_digit(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).hex_digit;
        }
        inline bool is_ascii_hex_digit(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).ascii_hex_digit;
        }
        inline bool is_default_ignorable(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).default_ignorable;
        }
        inline bool is_other_default_ignorable(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).other_default_ignorable;
        }
        inline bool is_logical_order_exception(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).logical_order_exception;
        }
        inline bool is_white_space(codepoint u) {
            return detail::find_property_group(function_data, function_data_size, u).white_space;
        }
        inline bool is_grapheme_base(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).grapheme_base;
        }
        //[[deprecated("since 5.0")]]
        inline bool is_grapheme_extend(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).grapheme_link;
        }
        inline bool is_other_grapheme_extend(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).other_grapheme_extend;
        }
        inline bool is_grapheme_link(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).grapheme_link;
        }
        inline grapheme_cluster_break get_grapheme_cluster_break(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).grapheme_cluster_break;
        }
        inline word_break get_word_break(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).word_break;
        }
        inline sentence_break get_sentence_break(codepoint u) {
            return detail::find_property_group(boundary_data, boundary_data_size, u).sentence_break;
        }
        inline bool is_ideographic(codepoint u) {
            return detail::find_property_group(ideograph_data, ideograph_data_size, u).ideographic;
        }
        inline bool is_unified_ideograph(codepoint u) {
            return detail::find_property_group(ideograph_data, ideograph_data_size, u).unified_ideograph;
        }
        inline bool is_ids_binary_operator(codepoint u) {
            return detail::find_property_group(ideograph_data, ideograph_data_size, u).ids_binary_operator;
        }
        inline bool is_ids_trinary_operator(codepoint u) {
            return detail::find_property_group(ideograph_data, ideograph_data_size, u).ids_trinary_operator;
        }
        inline bool is_radical(codepoint u) {
            return detail::find_property_group(ideograph_data, ideograph_data_size, u).radical;
        }
        inline bool is_deprecated(codepoint u) {
            return detail::find_property_group(miscellaneous_data, miscellaneous_data_size, u).deprecated;
        }
        inline bool is_variant_selector(codepoint u) {
            return detail::find_property_group(miscellaneous_data, miscellaneous_data_size, u).variant_selector;
        }
        inline bool is_noncharacter(codepoint u) {
            return detail::find_property_group(miscellaneous_data, miscellaneous_data_size, u).noncharacter;
        }
    } //namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_HPP

