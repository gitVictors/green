#include "post_v2.h"

#include <iostream>
#include <cassert>

void TestEmpty() {
    Post post;
    post.SetPostCapacity(0);
    assert(post.CalculateAverageWeight() == 0);
    assert(post.FindHeaviestPackage() == std::nullopt);
    assert(post.FindLightestPackage() == std::nullopt);
    assert(post.FindFirstSenderByAddress("Addr") == std::nullopt);
    assert(post.CalculatePackageForAddress("Addr") == 0);
}

void TestFindPackageByWeight() {
    Post post;
    post.SetPostCapacity(5);
    post.AddPackage("p1", "m1", 1);
    post.AddPackage("p2", "m2", 12);
    post.AddPackage("p3", "m3", 7);
    post.AddPackage("p3", "m1", 7);

    assert(post.FindHeaviestPackage().has_value());
    assert(post.FindHeaviestPackage().value().weight == 12);

    assert(post.FindLightestPackage().has_value());
    assert(post.FindLightestPackage().value().weight == 1);
}

void TestCalculateAverageWeight() {
    {
        Post post;
        post.SetPostCapacity(5);
        assert(post.CalculateAverageWeight() == 0);
    }
    {
        Post post;
        post.SetPostCapacity(5);
        post.AddPackage("p1", "m1", 1);
        post.AddPackage("p2", "m2", 12);
        post.AddPackage("p3", "m3", 7);
        post.AddPackage("p3", "m1", 7);
        assert(post.CalculateAverageWeight() == 6.75);
    }
}

void TestCalculateHowManyPackages() {
    Post post;
    post.SetPostCapacity(5);
    post.AddPackage("p1", "m1", 1);
    post.AddPackage("p2", "m2", 12);
    post.AddPackage("p3", "m3", 7);
    post.AddPackage("p3", "m1", 7);
    assert(post.CalculatePackageForAddress("m1") == 2);
    assert(post.CalculatePackageForAddress("m2") == 1);
    assert(post.CalculatePackageForAddress("m3") == 1);
    assert(post.CalculatePackageForAddress("m4") == 0);
}

void TestFirstSenderByAddrespost_s() {
    Post post;
    post.SetPostCapacity(5);
    post.AddPackage("p1", "m1", 1);
    post.AddPackage("p2", "m2", 12);
    post.AddPackage("p3", "m3", 7);
    post.AddPackage("p3", "m1", 7);
    assert(post.FindFirstSenderByAddress("m1").has_value());
    assert(post.FindFirstSenderByAddress("m1").value().sender == "p1");

    assert(post.FindFirstSenderByAddress("m2").has_value());
    assert(post.FindFirstSenderByAddress("m2").value().sender == "p2");

    assert(post.FindFirstSenderByAddress("m3").has_value());
    assert(post.FindFirstSenderByAddress("m3").value().sender == "p3");

    assert(!post.FindFirstSenderByAddress("m4").has_value());
}

int main() {
    Post post;
    post.SetPostCapacity(10);
    post.AddPackage("p1", "m1", 10);
    post.AddPackage("p2", "m2", 12);
    post.AddPackage("p3", "m3", 10);
    post.AddPackage("p4", "m2", 10);
    post.AddPackage("p5", "m4", 14);
    post.AddPackage("p6", "m5", 10);
    post.AddPackage("p7", "m6", 17);

    std::cout << post.CalculateAverageWeight() << std::endl;
    std::cout << post.FindHeaviestPackage()->weight << std::endl;
    std::cout << post.FindLightestPackage()->weight << std::endl;
    std::cout << post.CalculateTotalWeight() << std::endl;
    std::cout << post.FindFirstSenderByAddress("m3")->sender << std::endl;
    std::cout << post.CalculatePackageForAddress("m2") << std::endl;
    std::cout << post.CalculatePackageForAddress("m7") << std::endl;

    TestEmpty();
    TestFindPackageByWeight();
    TestCalculateAverageWeight();
    TestCalculateHowManyPackages();
  //  TestFirstSenderByAddress();
}
