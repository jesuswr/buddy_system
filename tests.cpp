#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch_amalgamated.hpp"
#include "buddy_system.hpp"
#include <string>

using namespace std;

TEST_CASE("buddy system test 1") {
    buddy_system my_buddy(16);

    // return 0 meaning reserve succeded
    REQUIRE( my_buddy.reserve("id1", 16) == 0 );

    // return error code meaning no sppace available
    REQUIRE( my_buddy.reserve("id2", 3) < 0 ) ;

    // return 0 meaning free succeded
    REQUIRE( my_buddy.free("id1") == 0 );

    // check if memory was released correctly with another reserve
    REQUIRE( my_buddy.reserve("id1", 3) == 0 );

    // now we should have free a block of size 4 and another of size 8
    // lets check that by asking for one of size 9 and then 8
    REQUIRE( my_buddy.reserve("id2", 9) < 0 );
    REQUIRE( my_buddy.reserve("id2", 8) == 0 );

    // now lets free all blocks and check if it merges into a block of
    // size 16
    REQUIRE( my_buddy.free("id1") == 0 );
    REQUIRE( my_buddy.free("id2") == 0 );
    REQUIRE( my_buddy.reserve("id1", 16) == 0 );

    REQUIRE( my_buddy.free("id1") == 0 );

    // now lets check for some errors
    // reserve with same id
    REQUIRE( my_buddy.reserve("id", 1) == 0 );
    REQUIRE( my_buddy.reserve("id", 1) < 0 );

    // free a non existing id
    REQUIRE( my_buddy.free("no_id") < 0 );

    // reserve a negative number of blocks
    REQUIRE( my_buddy.reserve("nop", -1) < 0 );
}



TEST_CASE("buddy system test 2") {
    // here we will test the show function, sorry but
    // you will have to check it on the console:(
    buddy_system my_b(31);
    my_b.show();

    REQUIRE( my_b.reserve("id1", 15) == 0 );
    REQUIRE( my_b.reserve("id2", 1) == 0 );
    my_b.show();

    REQUIRE( my_b.free("id1") == 0 );
    my_b.show();
    REQUIRE( my_b.free("id2") == 0 );
    my_b.show();
}