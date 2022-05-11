#include <gtest/gtest.h>
#include "../../Clipper2Lib/clipper.h"

TEST(Clipper2Tests, TestBasicUnion) {
    Clipper2Lib::Clipper clipper;

    const Clipper2Lib::Path64 a = {
        Clipper2Lib::Point64::construct(0, 0),
        Clipper2Lib::Point64::construct(0, 5),
        Clipper2Lib::Point64::construct(5, 5),
        Clipper2Lib::Point64::construct(5, 0)
    };

    const Clipper2Lib::Path64 b = {
        Clipper2Lib::Point64::construct(1, 1),
        Clipper2Lib::Point64::construct(1, 6),
        Clipper2Lib::Point64::construct(6, 6),
        Clipper2Lib::Point64::construct(6, 1)
    };

    clipper.AddSubject({ a, b });

    Clipper2Lib::PolyTree64 solution;
    Clipper2Lib::Paths64 open_paths;

    clipper.Execute(Clipper2Lib::ClipType::Union, Clipper2Lib::FillRule::Positive, solution, open_paths);

    EXPECT_EQ(open_paths.size(), 0);
    ASSERT_EQ(solution.ChildCount(), 1);
    EXPECT_EQ(solution.childs.front()->Path().size(), 8);
}