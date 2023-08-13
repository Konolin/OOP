#pragma once

#include <memory>

namespace Test {
    class Tests{
    private:
        static void testDomain();

        void testInMemoryRepository();

        void testCSVRepository();

        void testController();

    public:
        void testAll();
    };
}
