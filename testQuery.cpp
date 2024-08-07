#define CATCH_CONFIG_MAIN
#include "catch_setup.h"
#include "catch.hpp"
#include "UserInterface.h"

using namespace std;

TEST_CASE("Check that we get the correct results", "[AVLTree]")
{
    SECTION("testing german") {
        UserInterface ui;
        ui.createIndex("../sample_data");
        ui.enterQuery("german", false);
        vector<pair<string, int>> results = ui.readQueryResults();
        REQUIRE(results.size() == 1);
        REQUIRE(results[0].first == "e17252151a2d36344b7104d14805414a55042abe");
    }
    //all need to be in this format
    SECTION("testing january") { //test for january
        UserInterface ui;
        ui.createIndex("../sample_data");
        ui.enterQuery("january", false);
        vector<pair<string, int>> results = ui.readQueryResults();
        REQUIRE(results.size() == 1);
        REQUIRE(results[0].first == "4ad75456ae0bc42beeee2ff65fa58fa1cc503be2");
    }

        SECTION("testing non-words") { // Test for non-words
        UserInterface ui;
        ui.createIndex("../sample_data");
        ui.enterQuery("1234", false); // Example query with non-words
        vector<pair<string, int>> results = ui.readQueryResults();
        
        REQUIRE(results.size() == 1);
        REQUIRE(results[0].first == "e17252151a2d36344b7104d14805414a55042abe");
    }

      SECTION("testing orgs") { // Test for organizations (orgs)
        UserInterface ui;
        ui.createIndex("../sample_data");
        ui.enterQuery("org:example_org", false); // Example query with organization
        vector<pair<string, int>> results = ui.readQueryResults();
        
        REQUIRE(results.size() == 1);
        REQUIRE(results[0].first == "e17252151a2d36344b7104d14805414a55042abe");
    }

    SECTION("testing people") { // Test for people
        UserInterface ui;
        ui.createIndex("../sample_data");
        ui.enterQuery("person:john_doe", false); // Example query with person
        vector<pair<string, int>> results = ui.readQueryResults();
        
        REQUIRE(results.size() == 1);
        REQUIRE(results[0].first == "e17252151a2d36344b7104d14805414a55042abe");
    }
}

   



