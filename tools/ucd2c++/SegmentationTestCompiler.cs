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

            if(args.Length != 3)
            {
                Console.WriteLine("Usage: segtest2c++ <test source> <output file> <description>");
                return 1;
            }
            string source = args[0];
            string destination = args[1];
            string kind = args[2];

            var tests = GetTests(File.ReadLines(source))
                            .ToList();
            var strings = tests.Select(GetString);
            var breaks = tests.Select(GetBreaks);
            File.WriteAllLines(destination, new []{ string.Format(CopyrightNotice, DateTime.Now.ToUniversalTime().ToString("O"), kind) });
            File.AppendAllLines(destination, strings.Zip(breaks, (s,b) => "{ " + s + ", { " + string.Join(", ", b) + " } },"));

            return 0;
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

// This file was automatically generated on {0}

// Unicode segmentation test data - {1}
";
    }
}
