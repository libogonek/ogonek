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

// Unicode segmentation tests compiler

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;

[assembly: AssemblyTitle("Ogonek.SegmentationTestCompiler")]
[assembly: AssemblyDescription("Unicode segmentation test-to-C++ compiler")]
[assembly: AssemblyProduct("Ogonek.SegmentationTestCompiler")]
[assembly: AssemblyCopyright("Written in 2012-2013 by Martinho Fernandes")]
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
                Console.WriteLine("Usage: segtest2c++ <input folder> <output folder>");
                return 1;
            }
            string source = args[0];
            string destination = args[1];

            var graphemes = GetTests(File.ReadLines(Path.Combine(source, "GraphemeBreakTest.txt")))
                            .ToList();
            var words = GetTests(File.ReadLines(Path.Combine(source, "WordBreakTest.txt")))
                            .ToList();
            var sentences = GetTests(File.ReadLines(Path.Combine(source, "SentenceBreakTest.txt")))
                            .ToList();
            var lines = GetTests(File.ReadLines(Path.Combine(source, "LineBreakTest.txt")))
                            .ToList();

            File.WriteAllLines(Path.Combine(destination, "segmentation.g.h++"), new []{ string.Format(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O")) });
            File.AppendAllLines(Path.Combine(destination, "segmentation.g.h++"), new []{ string.Format(HeaderTemplate, graphemes.Count, words.Count, sentences.Count, lines.Count) });

            WriteData(Path.Combine(destination, "grapheme_test_data.g.c++"), "grapheme", "grapheme clusters", graphemes);
            WriteData(Path.Combine(destination, "word_test_data.g.c++"), "word", "words", words);
            WriteData(Path.Combine(destination, "sentence_test_data.g.c++"), "sentence", "sentences", sentences);
            WriteData(Path.Combine(destination, "line_test_data.g.c++"), "line", "line break opportunities", lines);

            return 0;
        }

        static void WriteData(string path, string kind, string description, IEnumerable<string> tests) {
            var strings = tests.Select(GetString);
            var breaks = tests.Select(GetBreaks);

            File.WriteAllLines(path, new []{ string.Format(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O")) });
            var lines = string.Join("\n        ", strings.Zip(breaks, (s,b) => "{ " + s + ", { " + string.Join(", ", b) + " } },"));
            File.AppendAllLines(path, new []{ string.Format(ImplTemplate, kind, lines, description) });
        }

        static IEnumerable<string> GetTests(IEnumerable<string> lines) {
            return lines.Where(l => !l.StartsWith("#"))
                        .Select(l => l.Split('#')[0]);
        }

        static string GetString(string line) {
            return "U\"" + string.Concat(
                line.Split(new[]{ '×', '÷' })
                    .Select(s => s.Trim())
                    .Where(s => !string.IsNullOrWhiteSpace(s))
                    .Select(s => s.Trim())
                    .Select(s => @"\x" + s))
                + "\"";
        }

        static IEnumerable<int> GetBreaks(string text) { 
            return text.Where(c => c == '×' ||  c == '÷')
                       .Select((c,i) => new{ c, i })
                       .Where(x => x.c == '÷')
                       .Skip(1)
                       .Select(x => x.i);
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

// This file was automatically generated on {0}";

        const string ImplTemplate = @"
// Test data for {2} tests

#include ""segmentation.g.h++""

namespace test {{
    break_test {0}_test_data[] = {{
        {1}
    }};
}} // namespace test
";
        const string HeaderTemplate = @"
// Types for segmentation tests

#ifndef OGONEK_TEST_SEGMENTATION_HPP
#define OGONEK_TEST_SEGMENTATION_HPP

#include ""utils.h++""
#include <vector>

namespace test {{
    struct break_test {{
        test::ustring input;
        std::vector<int> breaks;
    }};

    extern break_test grapheme_test_data[{0}];
    extern break_test word_test_data[{1}];
    extern break_test sentence_test_data[{2}];
    extern break_test line_test_data[{3}];
}} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP
";

    }
}
