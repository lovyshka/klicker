#include <doctest.h>
#include "struct.h"

TEST_CASE("Testing timer")
{
    Game g;
    g.timer.restart();
    REQUIRE(g.end() == false);
    REQUIRE((g.timer.getElapsedTime().asSeconds() >= 0 and g.timer.getElapsedTime().asSeconds() < 5));
}

