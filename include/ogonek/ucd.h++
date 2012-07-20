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

#include "types.h++"
#include "detail/array_slice.h++"

#include <boost/logic/tribool.hpp>

#include <vector>

namespace ogonek {
    namespace ucd {
        enum class version {
            v1_1,
            v2_0, v2_1,
            v3_0, v3_1, v3_2,
            v4_0, v4_1,
            v5_0, v5_1, v5_2,
            v6_0, v6_1,
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
            CN  = 1 << 0,
            CR  = 1 << 1,
            EX  = 1 << 2,
            L   = 1 << 3,
            LF  = 1 << 4,
            LV  = 1 << 5,
            LVT = 1 << 6,
            PP  = 1 << 7,
            SM  = 1 << 8,
            T   = 1 << 9,
            V   = 1 << 10,
            XX  = 1 << 11,
        };
        enum class word_break {
            CR, EX, Extend, FO, KA, LE,
            LF, MB, ML, MN, NL, NU, XX,
        };
        enum class sentence_break {
            AT, CL, CR, EX, FO, LE, LF, LO,
            NU, SC, SE, SP, ST, UP, XX,
        };

        version get_age(codepoint u);
        // TODO: implement when text is working
        //text get_name(codepoint u);
        //text get_unicode1_name(codepoint u);
        //text get_alias(alias_type a, codepoint u);
        //std::get_vector<text> aliases(codepoint u);
        block get_block(codepoint u);
        category get_general_category(codepoint u);
        int get_combining_class(codepoint u);
        bidi_category get_bidi_category(codepoint u);
        bool is_bidi_mirrored(codepoint u);
        codepoint get_bidi_mirrored_glyph(codepoint u);
        bool is_bidi_control(codepoint u);
        decomposition_type get_decomposition_type(codepoint u);
        std::vector<codepoint> get_decomposition_mapping(codepoint u);
        bool is_excluded_from_composition(codepoint u);
        boost::tribool is_nfc_quick_check(codepoint u);
        bool is_nfd_quick_check(codepoint u);
        boost::tribool is_nfkc_quick_check(codepoint u);
        bool is_nfkd_quick_check(codepoint u);
        bool expands_on_nfc(codepoint u);
        bool expands_on_nfd(codepoint u);
        bool expands_on_nfkc(codepoint u);
        bool expands_on_nfkd(codepoint u);
        detail::array_slice<codepoint const> get_fc_nfkc_closure(codepoint u);
        numeric_type get_numeric_type(codepoint u);
        double get_numeric_value(codepoint u);
        joining_class get_joining_class(codepoint u);
        joining_group get_joining_group(codepoint u);
        bool is_join_control(codepoint u);
        linebreak get_linebreak_type(codepoint u);
        east_asian_width get_east_asian_width_type(codepoint u);
        bool is_uppercase(codepoint u);
        bool is_lowercase(codepoint u);
        codepoint get_simple_uppercase(codepoint u);
        codepoint get_simple_lowercase(codepoint u);
        codepoint get_simple_titlecase(codepoint u);
        std::vector<codepoint> get_uppercase(codepoint u);
        std::vector<codepoint> get_lowercase(codepoint u);
        std::vector<codepoint> get_titlecase(codepoint u);
        codepoint get_simple_case_folding(codepoint u);
        std::vector<codepoint> get_case_folding(codepoint u);
        bool is_case_ignorable(codepoint u);
        bool is_cased(codepoint u);
        bool changes_when_casefolded(codepoint u);
        bool changes_when_casemapped(codepoint u);
        bool changes_when_lowercased(codepoint u);
        bool changes_when_nfkc_casefolded(codepoint u);
        bool changes_when_titlecased(codepoint u);
        bool changes_when_uppercased(codepoint u);
        std::vector<codepoint> get_nfkc_casefold(codepoint u);
        script get_script(codepoint u);
        detail::array_slice<script const> get_script_extension(codepoint u);
        // text get_iso_comment(codepoint u);
        hangul_syllable_type get_hangul_syllable_type(codepoint u);
        // text get_jamo_short_name(codepoint u);
        indic_syllable_category get_indic_syllable_category(codepoint u);
        indic_matra_category get_indic_matra_category(codepoint u);
        bool is_id_start(codepoint u);
        bool is_other_id_start(codepoint u);
        bool is_xid_start(codepoint u);
        bool is_id_continue(codepoint u);
        bool is_other_id_continue(codepoint u);
        bool is_xid_continue(codepoint u);
        bool is_pattern_syntax(codepoint u);
        bool is_pattern_white_space(codepoint u);
        bool is_dash(codepoint u);
        bool is_hyphen(codepoint u);
        bool is_quotation_mark(codepoint u);
        bool is_terminal_punctuation(codepoint u);
        bool is_sentence_terminal(codepoint u);
        bool is_diacritic(codepoint u);
        bool is_extender(codepoint u);
        bool is_soft_dotted(codepoint u);
        bool is_alphabetic(codepoint u);
        bool is_other_alphabetic(codepoint u);
        bool is_math(codepoint u);
        bool is_other_math(codepoint u);
        bool is_hex_digit(codepoint u);
        bool is_ascii_hex_digit(codepoint u);
        bool is_default_ignorable(codepoint u);
        bool is_other_default_ignorable(codepoint u);
        bool is_logical_order_exception(codepoint u);
        bool is_white_space(codepoint u);
        bool is_grapheme_base(codepoint u);
        bool is_grapheme_extend(codepoint u);
        bool is_other_grapheme_extend(codepoint u);
        bool is_grapheme_link(codepoint u);
        grapheme_cluster_break get_grapheme_cluster_break(codepoint u);
        word_break get_word_break(codepoint u);
        sentence_break get_sentence_break(codepoint u);
        bool is_ideographic(codepoint u);
        bool is_unified_ideograph(codepoint u);
        bool is_ids_binary_operator(codepoint u);
        bool is_ids_trinary_operator(codepoint u);
        bool is_radical(codepoint u);
        bool is_deprecated(codepoint u);
        bool is_variant_selector(codepoint u);
        bool is_noncharacter(codepoint u);
    } //namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_HPP

