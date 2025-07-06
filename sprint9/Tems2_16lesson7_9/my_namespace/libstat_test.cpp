#include "libstat.h"

#include <cassert>
#include <cmath>
#include <sstream>

namespace  stat_agg = statistics::aggregations;
namespace       tst = statistics::tests;

 namespace statistics {
    using std::string;
    using std::ostringstream;
    using namespace std::literals;

     namespace tests {

        using stat_agg::Sum;
        using stat_agg::Max;
        using stat_agg::Mean;
        using stat_agg::StandardDeviation;
        using stat_agg::Mode;
        // using stat_agg::AggregPrinter;


         namespace detail {

            template <typename T>
            string GetPrinterValue(statistics::AggregPrinter<T>& printer) {
                ostringstream out;
                printer.Print(out);

                return std::move(out).str();
            }

        }//detail

            void AggregSum() {
                Sum aggreg;
                assert(*aggreg.Get() == 0);

                aggreg.PutValue(10.);
                aggreg.PutValue(20.);
                aggreg.PutValue(-40.);

                assert(*aggreg.Get() == -10.);
            }

            void AggregMax() {
                Max aggreg;
                assert(!aggreg.Get());

                aggreg.PutValue(10.);
                aggreg.PutValue(20.);
                aggreg.PutValue(-40.);

                assert(*aggreg.Get() == 20.);
            }

            void AggregMean() {
                Mean aggreg;
                assert(!aggreg.Get());

                aggreg.PutValue(10.);
                aggreg.PutValue(20.);
                aggreg.PutValue(-40.);
                aggreg.PutValue(30.);

                assert(*aggreg.Get() == 5.);
            }

            void AggregStandardDeviation() {
                StandardDeviation aggreg;
                assert(!aggreg.Get());

                aggreg.PutValue(10.);
                aggreg.PutValue(10.);
                aggreg.PutValue(10.);
                aggreg.PutValue(10.);

                assert(std::abs(*aggreg.Get()) < 1e-5);

                aggreg.PutValue(20.);
                aggreg.PutValue(20.);
                aggreg.PutValue(20.);
                aggreg.PutValue(20.);

                assert(std::abs(*aggreg.Get() - 5.) < 1e-5);
            }

            void AggregMode() {
                Mode aggreg;
                assert(!aggreg.Get());

                aggreg.PutValue(1.1);
                aggreg.PutValue(0.9);
                aggreg.PutValue(2.1);
                aggreg.PutValue(2.2);
                aggreg.PutValue(2.1);
                aggreg.PutValue(-1.0);
                aggreg.PutValue(3.0);
                aggreg.PutValue(3.0);
                aggreg.PutValue(1000.);

                assert(std::round(*aggreg.Get()) == 2.);
            }

            void AggregPrinter() {
                statistics::AggregPrinter<Max> printer;
                assert(detail::GetPrinterValue(printer) == "max is undefined\n"s);
                printer.PutValue(10.);
                printer.PutValue(20.);
                printer.PutValue(-40.);
                std::ostringstream out;
                out << 20.;
                assert(detail::GetPrinterValue(printer) == "max is "s + out.str() + "\n"s);
            }


    }//tests
}//statistics

// namespace statistics {

//         namespace AggregPrinter {

//             using  stat_agg::AggregPrinter;
//             using stat_agg::Max;
//             using tst::detail::GetPrinterValue;
//             using namespace std::literals;



//         }
// }


