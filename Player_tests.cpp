#include "Player.hpp"
#include "unit_test_framework.hpp"
#include "Card.hpp"

#include <iostream>
#include <sstream>

using namespace std;

TEST(test_player_get_name) {
    Player *alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    Player *bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());

    delete alice;
    delete bob;
}

TEST(test_player_add_card) {
    Player *alice = Player_factory("Alice", "Simple");
    Card test_card(NINE, SPADES);
    
    alice->add_card(test_card);

    delete alice;
}

TEST(test_simple_make_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(KING, HEARTS));
    simple->add_card(Card(ACE, HEARTS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);

    delete simple;
}

TEST(test_simple_add_and_discard) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    
    simple->add_card(Card(TEN, SPADES));
    simple->add_card(Card(QUEEN, HEARTS));

    simple->add_and_discard(Card(NINE, DIAMONDS));

    delete simple;
}

TEST(test_simple_lead_card) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, CLUBS));
    simple->add_card(Card(KING, DIAMONDS));

    Card lead = simple->lead_card(HEARTS);
    ASSERT_EQUAL(lead, Card(KING, DIAMONDS));

    delete simple;
}

TEST(test_simple_play_card) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, CLUBS));
    simple->add_card(Card(KING, DIAMONDS));

    Card played = simple->play_card(Card(KING, DIAMONDS), HEARTS);
    ASSERT_EQUAL(played, Card(KING, DIAMONDS));

    delete simple;
}



TEST_MAIN()
