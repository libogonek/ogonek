// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode character database compiler

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Xml.Linq;

[assembly: AssemblyTitle("Ogonek.UcdCompiler")]
[assembly: AssemblyDescription("UCD-to-C++ compiler")]
[assembly: AssemblyProduct("Ogonek.UcdCompiler")]
[assembly: AssemblyCopyright("Written in 2012 by Martinho Fernandes")]
[assembly: AssemblyCulture("")]
[assembly: ComVisible(false)]
[assembly: AssemblyVersion("0.1.0.0")]
[assembly: AssemblyFileVersion("0.1.0.0")]

namespace Ogonek.UcdCompiler
{
    enum UnicodeVersion
    {
        v1_1,
        v2_0, v2_1,
        v3_0, v3_1, v3_2,
        v4_0, v4_1,
        v5_0, v5_1, v5_2,
        v6_0, v6_1, v6_2,
        Unassigned,
    }

    enum WordBreak
    {
        CR, EX, Extend, FO, KA, LE,
        LF, MB, ML, MN, NL, NU, XX,
        RI,
    }

    static class XmlParsingExtensions
    {
        public static double AsNumericValue(this XAttribute at)
        {
            if (at.Value == "NaN") return double.NaN;
            var parts = at.Value.Split('/').Select(double.Parse).ToArray();
            if (parts.Length > 1) return parts[0] / parts[1];
            return parts[0];
        }
        public static bool AsBool(this XAttribute at)
        {
            return at.Value == "Y";
        }
        public static bool? AsTriBool(this XAttribute at)
        {
            if (at.Value == "M") return null;
            return at.AsBool();
        }
        public static UnicodeVersion AsVersion(this XAttribute at)
        {
            if (at.Value == "unassigned") return UnicodeVersion.Unassigned;
            return (UnicodeVersion)Enum.Parse(typeof(UnicodeVersion), "v" + at.Value.Replace(".", "_"));
        }
        public static TEnum AsEnum<TEnum>(this XAttribute at)
        {
            return (TEnum)Enum.Parse(typeof(TEnum), at.Value);
        }
        public static TEnum[] AsEnumArray<TEnum>(this XAttribute at)
        {
            return at.Value.Split(' ')
                .Select(s => (TEnum)Enum.Parse(typeof(TEnum), s))
                .ToArray();
        }
        public static int? AsOptionalCodepoint(this XAttribute at)
        {
            if (at == null) return null;
            if (string.IsNullOrEmpty(at.Value)) return null;
            return at.AsCodepoint();
        }
        static int ParseHex(string s)
        {
            var result = 0;
            foreach (var c in s)
            {
                result *= 16;
                if (c >= '0' && c <= '9')
                {
                    result += c - '0';
                }
                else if (c >= 'A' && c <= 'F')
                {
                    result += c - 'A' + 10;
                }
                else if (c >= 'a' && c <= 'f')
                {
                    result += c - 'a' + 10;
                }
                else if (c == '#')
                {
                    return -1;
                }
                else
                {
                    throw new FormatException();
                }
            }
            return result;
        }
        public static int AsCodepoint(this XAttribute at)
        {
            return ParseHex(at.Value);
        }
        public static int[] AsCodepointArray(this XAttribute at)
        {
            if (at == null) return new int[0];
            return at.Value.Split(' ')
                .Select(ParseHex)
                .ToArray();
        }
    }

    enum SentenceBreak
    {
        AT, CL, CR, EX, FO, LE, LF, LO,
        NU, SC, SE, SP, ST, UP, XX,
    }

    enum Script
    {
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
        Samr, Sarb, Saur, Shaw, Shrd, Sinh, Sora, Sund, Sylo, Syrc,
        Tagb, Takr, Tale, Talu, Taml, Tavt, Telu, Tfng,
        Tglg, Thaa, Thai, Tibt,
        Ugar,
        Vaii,
        Xpeo, Xsux,
        Yiii,
        Zinh, Zyyy, Zzzz,
    }

    enum NumericType
    {
        None, De, Di, Nu,
    }

    public static class MoarLinq
    {
        public static IEnumerable<TAccum> Scan<T, TAccum>(this IEnumerable<T> source, TAccum seed, Func<TAccum, T, TAccum> accumulator)
        {
            if (source == null)
                throw new ArgumentNullException("source");
            if (accumulator == null)
                throw new ArgumentNullException("accumulator");
            return ScanImpl(source, seed, accumulator);
        }
        private static IEnumerable<TAccum> ScanImpl<T, TAccum>(IEnumerable<T> source, TAccum seed, Func<TAccum, T, TAccum> accumulator)
        {
            var current = seed;
            foreach (var x in source)
            {
                current = accumulator(current, x);
                yield return current;
            }
        }
        public static IEnumerable<T> CoalesceRanges<T>(this IEnumerable<T> source, Func<T, T, bool> predicate, Func<T, T, T> merge)
        {
            if (source == null)
                throw new ArgumentNullException("source");
            if (predicate == null)
                throw new ArgumentNullException("predicate");
            if (merge == null)
                throw new ArgumentNullException("merge");
            return CoalesceRangesImpl(source, predicate, merge);
        }
        private static IEnumerable<T> CoalesceRangesImpl<T>(IEnumerable<T> source, Func<T, T, bool> predicate, Func<T, T, T> merge)
        {
            var enumerator = source.GetEnumerator();
            bool moved = enumerator.MoveNext();
            if (!moved) throw new ArgumentException("source");
            var current = enumerator.Current;
            while (enumerator.MoveNext())
            {
                if (predicate(current, enumerator.Current))
                {
                    current = merge(current, enumerator.Current);
                }
                else
                {
                    yield return current;
                    current = enumerator.Current;
                }
            }
            yield return current;
        }

    }

    enum Linebreak
    {
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
    }

    enum JoiningGroup
    {
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
    }

    enum JoiningClass
    {
        U, C, T, D, L, R,
    }

    enum IndicSyllableCategory
    {
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
    }

    enum IndicMatraCategory
    {
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
    }

    enum HangulSyllableType
    {
        L, LV, LVT, T, V, NA,
    }

    enum GraphemeClusterBreak
    {
        CN, CR, EX, L, LF, LV, LVT, PP,
        SM, T, V, XX, RI,
    }

    enum GeneralCategory
    {
        Lu, Ll, Lt, Lm, Lo,
        Mn, Mc, Me,
        Nd, Nl, No,
        Pc, Pd, Ps, Pe, Pi, Pf, Po,
        Sm, Sc, Sk, So,
        Zs, Zl, Zp,
        Cc, Cf, Cs, Co, Cn,
    }

    enum EastAsianWidth
    {
        A, F, H, N, Na, W,
    }

    enum DecompositionType
    {
        can, com, enc, fin, font, fra,
        init, iso, med, nar, nb, sml,
        sqr, sub, sup, vert, wide, none,
    }

    class CodepointSet
    {
        public int From, To;
        public UnicodeVersion Version;
        public string Name;
        public string V1Name;
        public Alias[] Aliases;
        public Block Block;
        public GeneralCategory GeneralCategory;
        public int CombiningClass;
        public BidiCategory BidiCategory;
        public bool BidiMirrored;
        public int? BidiMirroredGlyph;
        public bool BidiControl;
        public DecompositionType DecompositionType;
        public int[] DecompositionMapping;
        public bool CompositionExclusion;
        public bool FullCompositionExclusion;
        public bool? NfcQuickCheck;
        public bool NfdQuickCheck;
        public bool? NfkcQuickCheck;
        public bool NfkdQuickCheck;
        public bool ExpandsOnNfc;
        public bool ExpandsOnNfd;
        public bool ExpandsOnNfkc;
        public bool ExpandsOnNfkd;
        public int[] FcNfkcClosure;
        public NumericType NumericType;
        public double NumericValue; // TODO fractions?
        public JoiningClass JoiningClass;
        public JoiningGroup JoiningGroup;
        public bool JoinControl;
        public Linebreak Linebreak;
        public EastAsianWidth EastAsianWidth;
        public bool IsUppercase;
        public bool IsLowercase;
        public bool IsOtherUppercase;
        public bool IsOtherLowercase;
        public int SimpleUppercase;
        public int SimpleLowercase;
        public int SimpleTitlecase;
        public int[] Uppercase;
        public int[] Lowercase;
        public int[] Titlecase;
        public int SimpleCaseFolding;
        public int[] CaseFolding;
        public bool CaseIgnorable;
        public bool Cased;
        public bool ChangesWhenCasefolded;
        public bool ChangesWhenCasemapped;
        public bool ChangesWhenLowercased;
        public bool ChangesWhenNfkcCasefolded;
        public bool ChangesWhenTitlecased;
        public bool ChangesWhenUppercased;
        public int[] NfkcCasefold;
        public Script Script;
        public Script[] ScriptExtension;
        public string IsoComment;
        public HangulSyllableType HangulSyllableType;
        public string JamoShortName;
        public IndicSyllableCategory IndicSyllableCategory;
        public IndicMatraCategory IndicMatraCategory;
        public bool IdStart;
        public bool OtherIdStart;
        public bool XidStart;
        public bool IdContinue;
        public bool OtherIdContinue;
        public bool XidContinue;
        public bool PatternSyntax;
        public bool PatternWhiteSpace;
        public bool Dash;
        public bool Hyphen;
        public bool QuotationMark;
        public bool TerminalPunctuation;
        public bool STerm;
        public bool Diacritic;
        public bool Extender;
        public bool SoftDotted;
        public bool Alphabetic;
        public bool OtherAlphabetic;
        public bool Math;
        public bool OtherMath;
        public bool HexDigit;
        public bool AsciiHexDigit;
        public bool DefaultIgnorable;
        public bool OtherDefaultIgnorable;
        public bool LogicalOrderException;
        public bool WhiteSpace;
        public bool GraphemeBase;
        public bool GraphemeExtend;
        public bool OtherGraphemeExtend;
        public bool GraphemeLink;
        public GraphemeClusterBreak GraphemeClusterBreak;
        public WordBreak WordBreak;
        public SentenceBreak SentenceBreak;
        public bool Ideographic;
        public bool UnifiedIdeograph;
        public bool IdsBinaryOperator;
        public bool IdsTrinaryOperator;
        public bool Radical;
        public bool Deprecated;
        public bool VariationSelector;
        public bool Noncharacter;
    }

    enum Block
    {
        Aegean_Numbers,
        Alchemical,
        Alphabetic_PF,
        Ancient_Greek_Music,
        Ancient_Greek_Numbers,
        Ancient_Symbols,
        Arabic,
        Arabic_Ext_A,
        Arabic_Math,
        Arabic_PF_A,
        Arabic_PF_B,
        Arabic_Sup,
        Armenian,
        Arrows,
        ASCII,
        Avestan,
        Balinese,
        Bamum,
        Bamum_Sup,
        Batak,
        Bengali,
        Block_Elements,
        Bopomofo,
        Bopomofo_Ext,
        Box_Drawing,
        Brahmi,
        Braille,
        Buginese,
        Buhid,
        Byzantine_Music,
        Carian,
        Chakma,
        Cham,
        Cherokee,
        CJK,
        CJK_Compat,
        CJK_Compat_Forms,
        CJK_Compat_Ideographs,
        CJK_Compat_Ideographs_Sup,
        CJK_Ext_A,
        CJK_Ext_B,
        CJK_Ext_C,
        CJK_Ext_D,
        CJK_Radicals_Sup,
        CJK_Strokes,
        CJK_Symbols,
        Compat_Jamo,
        Control_Pictures,
        Coptic,
        Counting_Rod,
        Cuneiform,
        Cuneiform_Numbers,
        Currency_Symbols,
        Cypriot_Syllabary,
        Cyrillic,
        Cyrillic_Ext_A,
        Cyrillic_Ext_B,
        Cyrillic_Sup,
        Deseret,
        Devanagari,
        Devanagari_Ext,
        Diacriticals,
        Diacriticals_For_Symbols,
        Diacriticals_Sup,
        Dingbats,
        Domino,
        Egyptian_Hieroglyphs,
        Emoticons,
        Enclosed_Alphanum,
        Enclosed_Alphanum_Sup,
        Enclosed_CJK,
        Enclosed_Ideographic_Sup,
        Ethiopic,
        Ethiopic_Ext,
        Ethiopic_Ext_A,
        Ethiopic_Sup,
        Geometric_Shapes,
        Georgian,
        Georgian_Sup,
        Glagolitic,
        Gothic,
        Greek,
        Greek_Ext,
        Gujarati,
        Gurmukhi,
        Half_And_Full_Forms,
        Half_Marks,
        Hangul,
        Hanunoo,
        Hebrew,
        High_PU_Surrogates,
        High_Surrogates,
        Hiragana,
        IDC,
        Imperial_Aramaic,
        Indic_Number_Forms,
        Inscriptional_Pahlavi,
        Inscriptional_Parthian,
        IPA_Ext,
        Jamo,
        Jamo_Ext_A,
        Jamo_Ext_B,
        Javanese,
        Kaithi,
        Kana_Sup,
        Kanbun,
        Kangxi,
        Kannada,
        Katakana,
        Katakana_Ext,
        Kayah_Li,
        Kharoshthi,
        Khmer,
        Khmer_Symbols,
        Lao,
        Latin_1_Sup,
        Latin_Ext_A,
        Latin_Ext_Additional,
        Latin_Ext_B,
        Latin_Ext_C,
        Latin_Ext_D,
        Lepcha,
        Letterlike_Symbols,
        Limbu,
        Linear_B_Ideograms,
        Linear_B_Syllabary,
        Lisu,
        Low_Surrogates,
        Lycian,
        Lydian,
        Mahjong,
        Malayalam,
        Mandaic,
        Math_Alphanum,
        Math_Operators,
        Meetei_Mayek,
        Meetei_Mayek_Ext,
        Meroitic_Cursive,
        Meroitic_Hieroglyphs,
        Miao,
        Misc_Arrows,
        Misc_Math_Symbols_A,
        Misc_Math_Symbols_B,
        Misc_Pictographs,
        Misc_Symbols,
        Misc_Technical,
        Modifier_Letters,
        Modifier_Tone_Letters,
        Mongolian,
        Music,
        Myanmar,
        Myanmar_Ext_A,
        NB,
        New_Tai_Lue,
        NKo,
        Number_Forms,
        OCR,
        Ogham,
        Ol_Chiki,
        Old_Italic,
        Old_Persian,
        Old_South_Arabian,
        Old_Turkic,
        Oriya,
        Osmanya,
        Phags_Pa,
        Phaistos,
        Phoenician,
        Phonetic_Ext,
        Phonetic_Ext_Sup,
        Playing_Cards,
        PUA,
        Punctuation,
        Rejang,
        Rumi,
        Runic,
        Samaritan,
        Saurashtra,
        Sharada,
        Shavian,
        Sinhala,
        Small_Forms,
        Sora_Sompeng,
        Specials,
        Sundanese,
        Sundanese_Sup,
        Sup_Arrows_A,
        Sup_Arrows_B,
        Sup_Math_Operators,
        Sup_PUA_A,
        Sup_PUA_B,
        Sup_Punctuation,
        Super_And_Sub,
        Syloti_Nagri,
        Syriac,
        Tagalog,
        Tagbanwa,
        Tags,
        Tai_Le,
        Tai_Tham,
        Tai_Viet,
        Tai_Xuan_Jing,
        Takri,
        Tamil,
        Telugu,
        Thaana,
        Thai,
        Tibetan,
        Tifinagh,
        Transport_And_Map,
        UCAS,
        UCAS_Ext,
        Ugaritic,
        Vai,
        Vedic_Ext,
        Vertical_Forms,
        VS,
        VS_Sup,
        Yi_Radicals,
        Yi_Syllables,
        Yijing,
    }

    enum BidiCategory
    {
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
    }

    enum AliasType
    {
        abbreviation, alternate, control, correction, figment,
    }

    class Alias
    {
        public AliasType Type;
        public string Name;
    }

    static class Program
    {
        static int Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;

            if (args.Length != 2)
            {
                Console.WriteLine("Usage: ucd2c++ <XML source> <destination directory>");
                return 1;
            }
            string source = args[0];
            string destination = args[1];

            var data = Parse(XDocument.Load(source)).ToArray();
            var compositions = GetCompositions(data);
            Decompose(data);

            WriteData(data, File.CreateText(Path.Combine(destination, "age.g.inl")), "version data",
                x => x.Version,
                x => string.Format("{{ {0}, version::{1} }}", FormatCodepoint(x.From), x.Version.ToString().ToLower()));
            WriteData(data, File.CreateText(Path.Combine(destination, "name.g.inl")), "name data",
                x => x.Name,
                x => string.Format("{{ {0}, {1}, \"{2}\" }}", FormatCodepoint(x.From), Format(x.Name.Contains("#")), x.Name));
            WriteData(data, File.CreateText(Path.Combine(destination, "v1name.g.inl")), "Unicode 1.0 name data",
                x => x.Name,
                x => string.Format("{{ {0}, false, \"{1}\" }}", FormatCodepoint(x.From), x.Name));
            WriteAliases(data, File.CreateText(Path.Combine(destination, "aliases.g.inl")), File.CreateText(Path.Combine(destination, "alias_map.g.inl")));
            WriteData(data, File.CreateText(Path.Combine(destination, "block.g.inl")), "block data",
                x => x.Block,
                x => string.Format("{{ {0}, block::{1} }}", FormatCodepoint(x.From), x.Block));
            WriteData(data, File.CreateText(Path.Combine(destination, "category.g.inl")), "general category data",
                x => x.GeneralCategory,
                x => string.Format("{{ {0}, category::{1} }}", FormatCodepoint(x.From), x.GeneralCategory));
            WriteData(data, File.CreateText(Path.Combine(destination, "combining.g.inl")), "combining class data",
                x => x.CombiningClass,
                x => string.Format("{{ {0}, {1} }}", FormatCodepoint(x.From), x.CombiningClass));
            WriteData(data, File.CreateText(Path.Combine(destination, "bidi.g.inl")), "bidirectionality data",
                x => new { x.BidiCategory, x.BidiMirrored, x.BidiMirroredGlyph, x.BidiControl },
                x => string.Format("{{ {0}, bidi_category::{1}, {2}, {3}, {4} }}",
                                FormatCodepoint(x.From), x.BidiCategory, Format(x.BidiMirrored),
                                FormatCodepoint(x.BidiMirroredGlyph),
                                Format(x.BidiControl)));

            WriteCompositions(compositions, File.CreateText(Path.Combine(destination, "composition.g.inl")), "composition data");
            WriteData(data, File.CreateText(Path.Combine(destination, "decomposition.g.inl")), "decomposition data",
                x => new
                {
                    x.DecompositionType,
                    dm = FakeComparable(x.DecompositionMapping),
                    x.CompositionExclusion,
                    x.FullCompositionExclusion,
                    x.NfcQuickCheck,
                    x.NfdQuickCheck,
                    x.NfkcQuickCheck,
                    x.NfkdQuickCheck,
                    x.ExpandsOnNfc,
                    x.ExpandsOnNfd,
                    x.ExpandsOnNfkc,
                    x.ExpandsOnNfkd,
                    fcnfkc = FakeComparable(x.FcNfkcClosure),
                },
                x => string.Format("{{ {0}, decomposition_type::{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}}}",
                                FormatCodepoint(x.From),
                                x.DecompositionType,
                                FormatCodepointArray(x.DecompositionMapping),
                                Format(x.CompositionExclusion),
                                Format(x.FullCompositionExclusion),
                                Format(x.NfcQuickCheck), Format(x.NfdQuickCheck), Format(x.NfkcQuickCheck), Format(x.NfkdQuickCheck),
                                Format(x.ExpandsOnNfc), Format(x.ExpandsOnNfd), Format(x.ExpandsOnNfkc), Format(x.ExpandsOnNfkd),
                                FormatCodepointArray(x.FcNfkcClosure)));
            WriteData(data, File.CreateText(Path.Combine(destination, "numeric.g.inl")), "numeric data",
                x => new { x.NumericType, val = x.NumericValue.ToString() /* string for NaNs */ },
                x => string.Format("{{ {0}, numeric_type::{1}, {2} }}",
                                    FormatCodepoint(x.From),
                                    x.NumericType,
                                    Format(x.NumericValue)));
            WriteData(data, File.CreateText(Path.Combine(destination, "joining.g.inl")), "joining data",
                x => new { x.JoiningClass, x.JoiningGroup, x.JoinControl },
                x => string.Format("{{ {0}, joining_class::{1}, joining_group::{2}, {3} }}",
                                FormatCodepoint(x.From),
                                x.JoiningClass,
                                x.JoiningGroup,
                                Format(x.JoinControl)));
            WriteData(data, File.CreateText(Path.Combine(destination, "linebreak.g.inl")), "linebreak data",
                x => x.Linebreak,
                x => string.Format("{{ {0}, linebreak::{1} }}", FormatCodepoint(x.From), x.Linebreak));
            WriteData(data, File.CreateText(Path.Combine(destination, "east_asian.g.inl")), "east asian width data",
                x => x.EastAsianWidth,
                x => string.Format("{{ {0}, east_asian_width::{1} }}", FormatCodepoint(x.From), x.EastAsianWidth));
            WriteData(data, File.CreateText(Path.Combine(destination, "case.g.inl")), "case data",
                    x => new
                    {
                        x.IsUppercase,
                        x.IsLowercase,
                        x.IsOtherUppercase,
                        x.IsOtherLowercase,
                        x.SimpleUppercase,
                        x.SimpleLowercase,
                        x.SimpleTitlecase,
                        a1 = FakeComparable(x.Uppercase),
                        a2 = FakeComparable(x.Lowercase),
                        a3 = FakeComparable(x.Titlecase),
                        x.SimpleCaseFolding,
                        a4 = FakeComparable(x.CaseFolding),
                        x.CaseIgnorable,
                        x.Cased,
                        x.ChangesWhenCasefolded,
                        x.ChangesWhenCasemapped,
                        x.ChangesWhenLowercased,
                        x.ChangesWhenNfkcCasefolded,
                        x.ChangesWhenTitlecased,
                        x.ChangesWhenUppercased,
                        a5 = FakeComparable(x.NfkcCasefold)
                    },
                x => string.Format("{{ {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21} }}",
                                    FormatCodepoint(x.From),
                                    Format(x.IsUppercase), Format(x.IsLowercase), Format(x.IsOtherUppercase), Format(x.IsOtherLowercase),
                                    FormatCodepoint(x.SimpleUppercase), FormatCodepoint(x.SimpleLowercase), FormatCodepoint(x.SimpleTitlecase),
                                    FormatCodepointArray(x.Uppercase), FormatCodepointArray(x.Lowercase), FormatCodepointArray(x.Titlecase),
                                    FormatCodepoint(x.SimpleCaseFolding), FormatCodepointArray(x.CaseFolding),
                                    Format(x.CaseIgnorable), Format(x.Cased),
                                    Format(x.ChangesWhenCasefolded), Format(x.ChangesWhenCasemapped), Format(x.ChangesWhenLowercased),
                                    Format(x.ChangesWhenNfkcCasefolded), Format(x.ChangesWhenTitlecased), Format(x.ChangesWhenUppercased),
                                    FormatCodepointArray(x.NfkcCasefold)));
            WriteScripts(data, File.CreateText(Path.Combine(destination, "script_ext.g.inl")), File.CreateText(Path.Combine(destination, "script.g.inl")));
            WriteData(data, File.CreateText(Path.Combine(destination, "iso_comment.g.inl")), "ISO comment data",
                x => x.IsoComment,
                x => string.Format("{{ {0}, U\"{1}\" }}", FormatCodepoint(x.From), x.IsoComment)); // TODO escapes?
            WriteData(data, File.CreateText(Path.Combine(destination, "hangul.g.inl")), "Hangul data",
                x => new { x.HangulSyllableType, x.JamoShortName },
                x => string.Format("{{ {0}, hangul_syllable_type::{1}, \"{2}\" }}", FormatCodepoint(x.From), x.HangulSyllableType, x.JamoShortName)); // TODO escapes?
            WriteData(data, File.CreateText(Path.Combine(destination, "indic.g.inl")), "Indic data",
                x => new { x.IndicSyllableCategory, x.IndicMatraCategory },
                x => string.Format("{{ {0}, indic_syllable_category::{1}, indic_matra_category::{2} }}", FormatCodepoint(x.From), x.IndicSyllableCategory, x.IndicMatraCategory));
            WriteData(data, File.CreateText(Path.Combine(destination, "identifier.g.inl")), "identifier data",
                x => new { x.IdStart, x.OtherIdStart, x.XidStart, x.IdContinue, x.OtherIdContinue, x.XidContinue },
                x => string.Format("{{ {0}, {1}, {2}, {3}, {4}, {5}, {6} }}",
                                FormatCodepoint(x.From),
                                Format(x.IdStart), Format(x.OtherIdStart), Format(x.XidStart),
                                Format(x.IdContinue), Format(x.OtherIdContinue), Format(x.XidContinue)));
            WriteData(data, File.CreateText(Path.Combine(destination, "pattern.g.inl")), "pattern data",
                x => new { x.PatternSyntax, x.PatternWhiteSpace },
                x => string.Format("{{ {0}, {1}, {2} }}", FormatCodepoint(x.From), Format(x.PatternSyntax), Format(x.PatternWhiteSpace)));
            WriteData(data, File.CreateText(Path.Combine(destination, "function.g.inl")), "function data",
                         x => new
                         {
                             x.Dash,
                             x.Hyphen,
                             x.QuotationMark,
                             x.TerminalPunctuation,
                             x.STerm,
                             x.Diacritic,
                             x.Extender,
                             x.SoftDotted,
                             x.Alphabetic,
                             x.OtherAlphabetic,
                             x.Math,
                             x.OtherMath,
                             x.HexDigit,
                             x.AsciiHexDigit,
                             x.DefaultIgnorable,
                             x.OtherDefaultIgnorable,
                             x.LogicalOrderException,
                             x.WhiteSpace
                         },
                         x => string.Format("{{ {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18} }}",
                                            FormatCodepoint(x.From),
                                            Format(x.Dash), Format(x.Hyphen), Format(x.QuotationMark), Format(x.TerminalPunctuation), Format(x.STerm),
                                            Format(x.Diacritic), Format(x.Extender), Format(x.SoftDotted), Format(x.Alphabetic), Format(x.OtherAlphabetic),
                                            Format(x.Math), Format(x.OtherMath), Format(x.HexDigit), Format(x.AsciiHexDigit), Format(x.DefaultIgnorable), Format(x.OtherDefaultIgnorable),
                                            Format(x.LogicalOrderException), Format(x.WhiteSpace)));
            WriteData(data, File.CreateText(Path.Combine(destination, "boundary.g.inl")), "boundary data",
                x => new
                {
                    x.GraphemeBase,
                    x.GraphemeExtend,
                    x.OtherGraphemeExtend,
                    x.GraphemeLink,
                    x.GraphemeClusterBreak,
                    x.WordBreak,
                    x.SentenceBreak
                },
                x => string.Format("{{ {0}, {1}, {2}, {3}, {4}, grapheme_cluster_break::{5}, word_break::{6}, sentence_break::{7} }}",
                                FormatCodepoint(x.From),
                                Format(x.GraphemeBase), Format(x.GraphemeExtend), Format(x.OtherGraphemeExtend), Format(x.GraphemeLink),
                                x.GraphemeClusterBreak, x.WordBreak, x.SentenceBreak));
            WriteData(data, File.CreateText(Path.Combine(destination, "ideograph.g.inl")), "ideograph data",
                x => new { x.Ideographic, x.UnifiedIdeograph, x.IdsBinaryOperator, x.IdsTrinaryOperator, x.Radical },
                x => string.Format("{{ {0}, {1}, {2}, {3}, {4}, {5} }}",
                                FormatCodepoint(x.From),
                                Format(x.Ideographic), Format(x.UnifiedIdeograph),
                                Format(x.IdsBinaryOperator), Format(x.IdsTrinaryOperator),
                                Format(x.Radical)));
            WriteData(data, File.CreateText(Path.Combine(destination, "misc.g.inl")), "miscellaneous data",
                x => new { x.Deprecated, x.VariationSelector, x.Noncharacter },
                x => string.Format("{{ {0}, {1}, {2}, {3} }}",
                                FormatCodepoint(x.From),
                                Format(x.Deprecated), Format(x.VariationSelector), Format(x.Noncharacter)));

            return 0;
        }

        static IDictionary<int, IEnumerable<Tuple<int, int>>> GetCompositions(CodepointSet[] sets)
        {
            return sets.Where(s => s.DecompositionType == DecompositionType.can && s.DecompositionMapping.Length > 1 && !s.FullCompositionExclusion)
                   .GroupBy(s => s.DecompositionMapping[0], s => Tuple.Create(s.DecompositionMapping[1], s.From))
                   .ToDictionary(g => g.Key, g => (IEnumerable<Tuple<int,int>>) g.ToList());
        }

        static IEnumerable<int> Decompose(int codepoint, CodepointSet[] sets)
        {
            var set = sets.Single(s => s.From <= codepoint && s.To >= codepoint);
            var map = set.DecompositionMapping;
            if (map.Length == 1 && map[0] == -1 || set.DecompositionType != DecompositionType.can)
            {
                return new[] { codepoint };
            }

            return map.SelectMany(c => Decompose(c, sets));
        }

        static IEnumerable<int> Decompose(CodepointSet set, CodepointSet[] sets)
        {
            var map = set.DecompositionMapping;
            if (map.Length == 1 && map[0] == -1)
            {
                return map;
            }
            else
            {
                return map.SelectMany(c => Decompose(c, sets));
            }
        }

        static void Decompose(CodepointSet[] sets)
        {
            foreach (var set in sets)
            {
                set.DecompositionMapping = Decompose(set, sets).ToArray();
            }
        }

        static void WriteAliases(IEnumerable<CodepointSet> sets, TextWriter listOutput, TextWriter mapOutput)
        {
            var aliasSets = sets.Scan(new { From = 0, Start = 0, Aliases = new Alias[0] },
                                      (acc, s) => new { s.From, Start = acc.Start + acc.Aliases.Length, s.Aliases })
                                .CoalesceRanges((x, y) => x.Aliases.SequenceEqual(y.Aliases),
                                                 (x, y) => x)
                                .ToArray();
            using (listOutput)
            {
                listOutput.Write(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), "name alias data");
                foreach (var alias in aliasSets.SelectMany(s => s.Aliases))
                {
                    listOutput.Write("{{ alias_type::{0}, \"{1}\" }},\n", alias.Type, alias.Name); // TODO escapes?
                }
            }
            using (mapOutput)
            {
                mapOutput.Write(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), "name alias mapping data");
                foreach (var aliasSet in aliasSets)
                {
                    mapOutput.Write("{{ {0}, &aliases[{1}], {2} }},\n", FormatCodepoint(aliasSet.From), aliasSet.Start, aliasSet.Aliases.Length);
                }
            }
        }

        static void WriteScripts(IEnumerable<CodepointSet> sets, TextWriter listOutput, TextWriter mapOutput)
        {
            var scriptSets = sets.Scan(new { From = 0, Start = 0, Script = (Script)0, Extensions = new Script[0] },
                                       (acc, s) => new { s.From, Start = acc.Start + acc.Extensions.Length, s.Script, Extensions = s.ScriptExtension })
                                 .CoalesceRanges((x, y) => x.Script == y.Script && x.Extensions.SequenceEqual(y.Extensions),
                                                 (x, y) => x)
                                 .ToArray();
            using (listOutput)
            {
                listOutput.Write(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), "script extension data");
                foreach (var script in scriptSets.SelectMany(s => s.Extensions))
                {
                    listOutput.Write("script::{0},\n", script);
                }
            }
            using (mapOutput)
            {
                mapOutput.Write(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), "script data");
                foreach (var scriptSet in scriptSets)
                {
                    mapOutput.Write("{{ {0}, script::{1}, &script_ext[{2}], {3} }},\n", FormatCodepoint(scriptSet.From), scriptSet.Script, scriptSet.Start, scriptSet.Extensions.Length);
                }
            }
        }

        static string FormatCodepoint(int? u)
        {
            return u == null ? "char32_t(-1)" : string.Format(@"U'\x{0:X}'", u);
        }

        static string Format(double d)
        {
            if (double.IsNaN(d)) return "std::numeric_limits<double>::quiet_NaN()";
            return d.ToString(CultureInfo.InvariantCulture);
        }

        static string FormatCodepointArray(int[] codepoints)
        {
            if (codepoints.Length == 1 && codepoints[0] == -1)
            {
                return "nullptr";
            }
            return "U\"" +
                 string.Concat(codepoints.Select(c => @"\U" + string.Format("{0:X}", c).PadLeft(8, '0')))
            + "\"";
        }

        static string FakeComparable(IEnumerable<int> codepoints)
        {
            return string.Concat(codepoints.Select(x =>
            {
                if (x < 0)
                {
                    return new string(new[] { (char)0xD800, (char)0xD800 }); // invalid sequence for uniqueness
                }
                return char.ConvertFromUtf32(x);
            }));
        }

        static string Format(bool b)
        {
            return b.ToString().ToLowerInvariant();
        }

        static string Format(bool? b)
        {
            return "yes_no_maybe::" +
                (b == null ? "m" : (bool)b ? "y" : "n");
        }

        static void WriteData<T>(IEnumerable<CodepointSet> sets, TextWriter output, string description, Func<CodepointSet, T> selector, Func<CodepointSet, string> format)
        {
            using (output)
            {
                output.Write(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), description);
                var items = sets.CoalesceRanges((a, b) => selector(a).Equals(selector(b)), (a, b) => a);

                foreach (var item in items)
                {
                    output.Write(format(item) + ",\n");
                }
            }
        }

        static string FormatCompositionEntry(Tuple<int, int> entry)
        {
            return string.Format("{{ {0}, {1} }}", FormatCodepoint(entry.Item1), FormatCodepoint(entry.Item2));
        }
        static void WriteCompositions(IDictionary<int, IEnumerable<Tuple<int, int>>> compositions, TextWriter output, string description)
        {
            using (output)
            {
                output.Write(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), description);

                foreach (var kvp in compositions.OrderBy(kvp => kvp.Key))
                {
                    output.Write("{{ {0}, {{ {1} }} }},\n", FormatCodepoint(kvp.Key), string.Join(", ", kvp.Value.OrderBy(e => e.Item1).Select(FormatCompositionEntry)));
                }
            }
        }

        static readonly XNamespace ucd = "http://www.unicode.org/ns/2003/ucd/1.0";
        static IEnumerable<CodepointSet> Parse(XDocument document)
        {
            var rep = document.Root.Element(ucd + "repertoire");
            return rep.Elements().Select(ParseCodepointSet);
        }
        static CodepointSet ParseCodepointSet(XElement e)
        {
            return new CodepointSet
            {
                From = (e.Attribute("cp") ?? e.Attribute("first-cp")).AsCodepoint(),
                To = (e.Attribute("cp") ?? e.Attribute("last-cp")).AsCodepoint(),
                Version = e.Attribute("age").AsVersion(),
                Name = e.Attribute("na").Value,
                V1Name = e.Attribute("na1").Value,
                Aliases = e.Elements(ucd + "name-alias").Select(ParseAlias).ToArray(),
                Block = e.Attribute("blk").AsEnum<Block>(),
                GeneralCategory = e.Attribute("gc").AsEnum<GeneralCategory>(),
                CombiningClass = int.Parse(e.Attribute("ccc").Value),
                BidiCategory = e.Attribute("bc").AsEnum<BidiCategory>(),
                BidiMirrored = e.Attribute("Bidi_M").AsBool(),
                BidiMirroredGlyph = e.Attribute("bmg").AsOptionalCodepoint(),
                BidiControl = e.Attribute("Bidi_C").AsBool(),
                DecompositionType = e.Attribute("dt").AsEnum<DecompositionType>(),
                DecompositionMapping = e.Attribute("dm").AsCodepointArray(),
                CompositionExclusion = e.Attribute("CE").AsBool(),
                FullCompositionExclusion = e.Attribute("Comp_Ex").AsBool(),
                NfcQuickCheck = e.Attribute("NFC_QC").AsTriBool(),
                NfdQuickCheck = e.Attribute("NFD_QC").AsBool(),
                NfkcQuickCheck = e.Attribute("NFKC_QC").AsTriBool(),
                NfkdQuickCheck = e.Attribute("NFKD_QC").AsBool(),
                ExpandsOnNfc = e.Attribute("XO_NFC").AsBool(),
                ExpandsOnNfkc = e.Attribute("XO_NFKC").AsBool(),
                ExpandsOnNfd = e.Attribute("XO_NFD").AsBool(),
                ExpandsOnNfkd = e.Attribute("XO_NFKD").AsBool(),
                FcNfkcClosure = e.Attribute("FC_NKFC").AsCodepointArray(),
                NumericType = e.Attribute("nt").AsEnum<NumericType>(),
                NumericValue = e.Attribute("nv").AsNumericValue(),
                JoiningClass = e.Attribute("jt").AsEnum<JoiningClass>(),
                JoiningGroup = e.Attribute("jg").AsEnum<JoiningGroup>(),
                JoinControl = e.Attribute("Join_C").AsBool(),
                Linebreak = e.Attribute("lb").AsEnum<Linebreak>(),
                EastAsianWidth = e.Attribute("ea").AsEnum<EastAsianWidth>(),
                IsUppercase = e.Attribute("Upper").AsBool(),
                IsLowercase = e.Attribute("Lower").AsBool(),
                IsOtherUppercase = e.Attribute("OUpper").AsBool(),
                IsOtherLowercase = e.Attribute("OLower").AsBool(),
                SimpleUppercase = e.Attribute("suc").AsCodepoint(),
                SimpleLowercase = e.Attribute("slc").AsCodepoint(),
                SimpleTitlecase = e.Attribute("stc").AsCodepoint(),
                Uppercase = e.Attribute("uc").AsCodepointArray(),
                Lowercase = e.Attribute("lc").AsCodepointArray(),
                Titlecase = e.Attribute("tc").AsCodepointArray(),
                SimpleCaseFolding = e.Attribute("scf").AsCodepoint(),
                CaseFolding = e.Attribute("cf").AsCodepointArray(),
                CaseIgnorable = e.Attribute("CI").AsBool(),
                Cased = e.Attribute("Cased").AsBool(),
                ChangesWhenCasefolded = e.Attribute("CWCF").AsBool(),
                ChangesWhenCasemapped = e.Attribute("CWCM").AsBool(),
                ChangesWhenLowercased = e.Attribute("CWL").AsBool(),
                ChangesWhenNfkcCasefolded = e.Attribute("CWKCF").AsBool(),
                ChangesWhenTitlecased = e.Attribute("CWT").AsBool(),
                ChangesWhenUppercased = e.Attribute("CWU").AsBool(),
                NfkcCasefold = e.Attribute("NFKC_CF").AsCodepointArray(),
                Script = e.Attribute("sc").AsEnum<Script>(),
                ScriptExtension = e.Attribute("scx").AsEnumArray<Script>(),
                IsoComment = e.Attribute("isc").Value,
                HangulSyllableType = e.Attribute("hst").AsEnum<HangulSyllableType>(),
                JamoShortName = e.Attribute("JSN").Value,
                IndicSyllableCategory = e.Attribute("InSC").AsEnum<IndicSyllableCategory>(),
                IndicMatraCategory = e.Attribute("InMC").AsEnum<IndicMatraCategory>(),
                IdStart = e.Attribute("IDS").AsBool(),
                OtherIdStart = e.Attribute("OIDS").AsBool(),
                XidStart = e.Attribute("XIDS").AsBool(),
                IdContinue = e.Attribute("IDC").AsBool(),
                OtherIdContinue = e.Attribute("OIDC").AsBool(),
                XidContinue = e.Attribute("XIDC").AsBool(),
                PatternSyntax = e.Attribute("Pat_Syn").AsBool(),
                PatternWhiteSpace = e.Attribute("Pat_WS").AsBool(),
                Dash = e.Attribute("Dash").AsBool(),
                Hyphen = e.Attribute("Hyphen").AsBool(),
                QuotationMark = e.Attribute("QMark").AsBool(),
                TerminalPunctuation = e.Attribute("Term").AsBool(),
                STerm = e.Attribute("STerm").AsBool(),
                Diacritic = e.Attribute("Dia").AsBool(),
                Extender = e.Attribute("Ext").AsBool(),
                SoftDotted = e.Attribute("SD").AsBool(),
                Alphabetic = e.Attribute("Alpha").AsBool(),
                OtherAlphabetic = e.Attribute("OAlpha").AsBool(),
                Math = e.Attribute("Math").AsBool(),
                OtherMath = e.Attribute("OMath").AsBool(),
                HexDigit = e.Attribute("Hex").AsBool(),
                AsciiHexDigit = e.Attribute("AHex").AsBool(),
                DefaultIgnorable = e.Attribute("DI").AsBool(),
                OtherDefaultIgnorable = e.Attribute("ODI").AsBool(),
                LogicalOrderException = e.Attribute("LOE").AsBool(),
                WhiteSpace = e.Attribute("WSpace").AsBool(),
                GraphemeBase = e.Attribute("Gr_Base").AsBool(),
                GraphemeExtend = e.Attribute("Gr_Ext").AsBool(),
                OtherGraphemeExtend = e.Attribute("OGr_Ext").AsBool(),
                GraphemeLink = e.Attribute("Gr_Link").AsBool(),
                GraphemeClusterBreak = e.Attribute("GCB").AsEnum<GraphemeClusterBreak>(),
                WordBreak = e.Attribute("WB").AsEnum<WordBreak>(),
                SentenceBreak = e.Attribute("SB").AsEnum<SentenceBreak>(),
                Ideographic = e.Attribute("Ideo").AsBool(),
                UnifiedIdeograph = e.Attribute("UIdeo").AsBool(),
                IdsBinaryOperator = e.Attribute("IDSB").AsBool(),
                IdsTrinaryOperator = e.Attribute("IDST").AsBool(),
                Radical = e.Attribute("Radical").AsBool(),
                Deprecated = e.Attribute("Dep").AsBool(),
                VariationSelector = e.Attribute("VS").AsBool(),
                Noncharacter = e.Attribute("NChar").AsBool(),
            };
        }
        static Alias ParseAlias(XElement e)
        {
            return new Alias
            {
                Type = e.Attribute("type").AsEnum<AliasType>(),
                Name = e.Attribute("alias").Value,
            };
        }

        const string CopyrightNotice = @"// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated on {0}

// Unicode character database - {1}

";
    }
}
