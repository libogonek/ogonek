// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode codepage compiler

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Text;

[assembly: AssemblyTitle("Ogonek.CodepageCompiler")]
[assembly: AssemblyDescription("Codepage-to-C++ compiler")]
[assembly: AssemblyProduct("Ogonek.CodepageCompiler")]
[assembly: AssemblyCopyright("Written in 2013 by Martinho Fernandes")]
[assembly: AssemblyCulture("")]
[assembly: ComVisible(false)]
[assembly: AssemblyVersion("0.1.0.0")]
[assembly: AssemblyFileVersion("0.1.0.0")]

namespace Ogonek.CodepageCompiler
{
    static class Program
    {
        static int Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;

            if(args.Length != 5)
            {
                Console.WriteLine("Usage: codepage2c++ <codepage source> <name> <code name> <ppsymbol> <output file>");
                return 1;
            }
            string source = args[0];
            string name = args[1];
            string codename = args[2];
            string ppsymbol = args[3];
            string header = args[4];

            var entries = GetEntries(File.ReadLines(source)).ToList();
            File.WriteAllLines(header, new []{ string.Format(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), name) });
            File.AppendAllLines(header, new []{ string.Format(HeaderTemplate, codename, ppsymbol, ToUnicode(entries), FromUnicode(entries), entries.Count) });

            return 0;
        }

        static string ToUnicode(IEnumerable<Tuple<int, int>> entries)
        {
            var dic = entries.ToDictionary(e => e.Item1, e => e.Item2);
            var sb = new StringBuilder();
            for(int i = 0; i < 0x100; ++i) {
                if(dic.ContainsKey(i)) {
                    sb.AppendLine("            0x" + dic[i].ToString("X") + ",");
                } else {
                    sb.AppendLine("            0xFFFFFFFF,");
                }
            }
            return sb.ToString();
        }
        static string FromUnicode(IEnumerable<Tuple<int, int>> entries)
        {
            return string.Join("\n", entries
                        .OrderBy(e => e.Item2)
                        .Select(e => "            { char(0x" + e.Item1.ToString("X") + "), 0x" + e.Item2.ToString("X") + " },"));
        }
        static int GetNumber(string hex)
        {
            return int.Parse(hex.Substring(2), NumberStyles.HexNumber);
        }
        static IEnumerable<Tuple<int, int>> GetEntries(IEnumerable<string> lines)
        {
            return lines.Where(l => !l.StartsWith("#"))
                        .Where(l => !string.IsNullOrEmpty(l.Trim()))
                        .Select(l => l.Split('#')[0].Trim())
                        .Select(l => l.Split('\t').Select(GetNumber).ToArray())
                        .Where(a => a.Length == 2)
                        .Select(a => Tuple.Create(a[0], a[1]));
        }

        const string HeaderTemplate = @"
#ifndef OGONEK_{1}_HPP
#define OGONEK_{1}_HPP

#include <ogonek/types.h++>
#include <ogonek/encoding/codepage_encoding.h++>

namespace ogonek {{
    struct {0}_codepage {{
        static constexpr code_point to_unicode[256] = {{
{2}
        }};
        static constexpr codepage_entry from_unicode[] = {{
{3}
        }};
    }};
    constexpr code_point {0}_codepage::to_unicode[256];
    constexpr codepage_entry {0}_codepage::from_unicode[{4}];

    using {0} = codepage_encoding<{0}_codepage>;
}} // namespace ogonek
#endif // OGONEK_{1}_HPP
";
        
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

// {1} encoding form
";
    }
}
