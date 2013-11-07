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

// Unicode normalization tests compiler

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;

[assembly: AssemblyTitle("Ogonek.NormalizationTestCompiler")]
[assembly: AssemblyDescription("Unicode normalization test-to-C++ compiler")]
[assembly: AssemblyProduct("Ogonek.NormalizationTestCompiler")]
[assembly: AssemblyCopyright("Written in 2013 by Martinho Fernandes")]
[assembly: AssemblyCulture("")]
[assembly: ComVisible(false)]
[assembly: AssemblyVersion("0.1.0.0")]
[assembly: AssemblyFileVersion("0.1.0.0")]

namespace Ogonek.SegmentationTestCompiler
{
    static class Program
    {
        static int Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;

            if(args.Length != 2)
            {
                Console.WriteLine("Usage: normtest2c++ <test source> <output folder>");
                return 1;
            }
            string source = args[0];
            string destination = args[1];

            var tests = GetTests(File.ReadLines(source))
                            .ToList();
            var forms = GetForms(tests);
            File.WriteAllLines(Path.Combine(destination, "normalization.g.h++"), new []{ string.Format(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O")) });
            File.AppendAllLines(Path.Combine(destination, "normalization.g.h++"), new []{ string.Format(HeaderTemplate, tests.Count) });

            File.WriteAllLines(Path.Combine(destination, "normalization_test_data.g.c++"), new []{ string.Format(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O")) });
            var lines = string.Join("\n        ", forms.Select(f => string.Format("{{ {0}, {1}, {2}, {3}, {4} }},", f)));
            File.AppendAllLines(Path.Combine(destination, "normalization_test_data.g.c++"), new []{ string.Format(ImplTemplate, lines) });

            return 0;
        }

        static IEnumerable<string> GetTests(IEnumerable<string> lines) {
            return lines.Where(l => !l.StartsWith("#") && !l.StartsWith("@"))
                        .Select(l => l.Split('#')[0])
                        .Where(l => !string.IsNullOrWhiteSpace(l));
        }

        static IEnumerable<string[]> GetForms(IEnumerable<string> lines) {
            return lines.Select(l => l.Split(';')
                                        .Select(u => "U\"" + GetForm(u) + "\"")
                                        .ToArray());
        }

        static string GetForm(string item) {
            return string.Join("",
                    item.Trim().Split(new[]{' '}, StringSplitOptions.RemoveEmptyEntries)
                        .Select(u => @"\x" + u.Trim()));
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

// Unicode normalization test data";

        const string ImplTemplate = @"
#include ""normalization.g.h++""

namespace test {{
    normalization_test normalization_test_data[] = {{
        {0}
    }};
}} // namespace test
";
        const string HeaderTemplate = @"
#ifndef OGONEK_TEST_NORMALIZATION_HPP
#define OGONEK_TEST_NORMALIZATION_HPP

#include <ogonek/types.h++>

#include ""utils.h++""

namespace test {{
    struct normalization_test {{
        ogonek::code_point const* input;
        ogonek::code_point const* nfc;
        ogonek::code_point const* nfd;
        ogonek::code_point const* nfkc;
        ogonek::code_point const* nfkd;
    }};

    extern normalization_test normalization_test_data[{0}];
}} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP
";

    }
}
