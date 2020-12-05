#include <iostream>
#include "hash_map.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("allocator constructors", "[allocator]") {
    SECTION("allocate") {
        {
            fefu::allocator<int> alloc;
            int* place = alloc.allocate();
            *place = 2;
            REQUIRE(*place == 2);
        }
    }
    SECTION("deallocate") {
        {
            fefu::allocator<int> alloc;
            auto ptr = alloc.allocate(100);
            alloc.deallocate(ptr, 100);
        }
    }
}


TEST_CASE("constructors", "[hash_map]") {
    SECTION("default") {
        {
            fefu::hash_map<int, int> hm;
            REQUIRE(hm.empty() == true);
            REQUIRE(hm.bucket_count() == 0);
            REQUIRE(hm.size() == 0);
        }
    }
    SECTION("with parameters") {
        {
            fefu::hash_map<int, int> hm(13);
            REQUIRE(hm.empty() == true);
            REQUIRE(hm.bucket_count() == 13);
            REQUIRE(hm.size() == 0);
        }
        {
            fefu::hash_map<int, int> hm({ {1, -1}, {3, -80}, {2, 7} }, 3);

            REQUIRE(hm.empty() == false);
            REQUIRE(hm.bucket_count() == 3);
            REQUIRE(hm.size() == 3);
            REQUIRE(hm.find(1)->second == -1);
            REQUIRE(hm.find(3)->second == -80);
        }
    }
}

TEST_CASE("insert an element", "[hash_map]") {
    {
        fefu::hash_map<int, int> hm(13);
        hm.insert(std::make_pair(1, 2));

        REQUIRE(hm.find(1)->second == 2);
        REQUIRE(hm.empty() == false);
        REQUIRE(hm.bucket_count() == 13);
        REQUIRE(hm.size() == 1);
    }
}
