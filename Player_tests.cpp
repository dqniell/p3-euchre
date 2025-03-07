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

TEST(test_player_with_no_name) { 
    Player *noname = Player_factory("", "Simple"); 
    ASSERT_EQUAL("", noname->get_name()); 
    delete noname; 
}


TEST(test_player_add_card) {
    Player *alice = Player_factory("Alice", "Simple");
    Card test_card(NINE, SPADES);
    
    alice->add_card(test_card);

    delete alice;
}

TEST(player_add_card_default) { 
    Player *alice = Player_factory("Alice", "Simple");
    Card test_card; 

    alice->add_card(test_card);

    delete alice;
}

TEST(test_simple_make_trump_exactly_two_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(QUEEN, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(KING, HEARTS));
    simple->add_card(Card(ACE, HEARTS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS); 

    delete simple;
}

TEST(test_simple_make_trump_one_trump_card) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(KING, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(QUEEN, HEARTS));
    
    ASSERT_FALSE(simple->make_trump(upcard, false, 1, order_up_suit));

    delete simple;
}

TEST(test_simple_make_trump_with_left_bower) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(TEN, SPADES);
    Suit order_up_suit;

    simple->add_card(Card(JACK, SPADES));  
    simple->add_card(Card(KING, SPADES));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, SPADES);  

    delete simple;
}

TEST(test_simple_make_trump_round2_one_same_color_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(KING, DIAMONDS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS);  

    delete simple;
}

TEST(test_simple_make_trump_round2_no_same_color_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(NINE, CLUBS));
    simple->add_card(Card(TEN, SPADES));

    ASSERT_FALSE(simple->make_trump(upcard, false, 2, order_up_suit));  

    delete simple;
}

TEST(test_simple_make_trump_force_dealer) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    ASSERT_TRUE(simple->make_trump(upcard, true, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS);  

    delete simple;
}


TEST(test_simple_add_and_discard) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    
    simple->add_card(Card(TEN, SPADES));
    simple->add_card(Card(QUEEN, HEARTS));

    simple->add_and_discard(Card(NINE, DIAMONDS));

    delete simple;
}

TEST(test_simple_add_discard_default) { 
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card card;
    simple->add_card(card); 
    simple->add_and_discard(card);
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

TEST(test_simple_lead_card_default) { 
    Player *simple = Player_factory("SimplePlayer", "Simple"); 
    
    simple->add_card(Card());
    Card lead = simple->lead_card(HEARTS);
    ASSERT_EQUAL(lead, Card());
}

TEST(test_simple_play_card) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, CLUBS));
    simple->add_card(Card(KING, DIAMONDS));

    Card played = simple->play_card(Card(KING, DIAMONDS), HEARTS);
    ASSERT_EQUAL(played, Card(KING, DIAMONDS));

    delete simple;
}

TEST(test_simple_play_card_default) { 
    Player *simple = Player_factory("SimplePlayer", "Simple");
    
    simple->add_card(Card());
    simple->add_card(Card());

    Card played = simple->play_card(Card(), HEARTS);
    ASSERT_EQUAL(played, Card());

    delete simple;
}

TEST(test_simple_add_and_discard_lowest_card) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(TEN, SPADES));
    simple->add_card(Card(QUEEN, HEARTS));
    simple->add_and_discard(Card(NINE, DIAMONDS));

    delete simple;
}

TEST(test_simple_add_and_discard_only_one_card) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(ACE, CLUBS)); 
    simple->add_and_discard(Card(KING, DIAMONDS));

    delete simple;
}

TEST(test_simple_lead_card_no_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, CLUBS));
    simple->add_card(Card(KING, DIAMONDS));

    Card lead = simple->lead_card(HEARTS);
    ASSERT_EQUAL(lead, Card(KING, DIAMONDS)); 

    delete simple;
}

TEST(test_simple_lead_card_all_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, HEARTS)); 
    simple->add_card(Card(KING, HEARTS));

    Card lead = simple->lead_card(HEARTS);
    ASSERT_EQUAL(lead, Card(KING, HEARTS)); 

    delete simple;
}

TEST(test_simple_lead_card_tiebreaker) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(KING, DIAMONDS));

    Card lead = simple->lead_card(HEARTS);
    ASSERT_TRUE(lead == Card(KING, CLUBS) || lead == Card(KING, DIAMONDS)); 

    delete simple;
}

TEST(test_simple_play_card_follow_suit) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(TEN, CLUBS));
    simple->add_card(Card(KING, CLUBS));

    Card played = simple->play_card(Card(NINE, CLUBS), HEARTS);
    ASSERT_EQUAL(played, Card(TEN, CLUBS));  

    delete simple;
}

TEST(test_simple_play_card_no_match) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(NINE, SPADES));
    simple->add_card(Card(TEN, HEARTS));

    Card played = simple->play_card(Card(NINE, CLUBS), HEARTS);
    ASSERT_EQUAL(played, Card(NINE, SPADES));  

    delete simple;
}

TEST(test_simple_play_card_trump_edge_case) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, HEARTS)); 
    simple->add_card(Card(QUEEN, HEARTS));

    Card played = simple->play_card(Card(NINE, SPADES), HEARTS);
    ASSERT_EQUAL(played, Card(JACK, HEARTS));  

    delete simple;
}

TEST(test_simple_make_trump_zero_trump_cards_round1) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(QUEEN, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(NINE, CLUBS));
    simple->add_card(Card(TEN, DIAMONDS));
    simple->add_card(Card(TWO, SPADES));
    simple->add_card(Card(THREE, CLUBS));
    simple->add_card(Card(FOUR, DIAMONDS));

    ASSERT_FALSE(simple->make_trump(upcard, false, 1, order_up_suit));

    delete simple;
}

TEST(test_simple_make_trump_one_trump_card_round1) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(KING, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(QUEEN, HEARTS));
    simple->add_card(Card(TEN, CLUBS));
    simple->add_card(Card(NINE, DIAMONDS));
    simple->add_card(Card(JACK, SPADES));
    simple->add_card(Card(THREE, HEARTS));

    ASSERT_FALSE(simple->make_trump(upcard, false, 1, order_up_suit));

    delete simple;
}

TEST(test_simple_make_trump_exactly_two_trump_round1) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(TEN, SPADES);
    Suit order_up_suit;

    simple->add_card(Card(QUEEN, SPADES));  
    simple->add_card(Card(KING, SPADES));
    simple->add_card(Card(THREE, HEARTS));
    simple->add_card(Card(FOUR, CLUBS));
    simple->add_card(Card(FIVE, DIAMONDS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, SPADES);

    delete simple;
}

TEST(test_simple_make_trump_more_than_two_trump_round1) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(ACE, CLUBS);
    Suit order_up_suit;

    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(QUEEN, CLUBS));
    simple->add_card(Card(ACE, CLUBS));
    simple->add_card(Card(JACK, SPADES));  
    simple->add_card(Card(TEN, HEARTS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);

    delete simple;
}

TEST(test_simple_make_trump_one_trump_card_round2) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(KING, DIAMONDS));
    simple->add_card(Card(QUEEN, CLUBS));
    simple->add_card(Card(ACE, CLUBS));
    simple->add_card(Card(TEN, SPADES));
    simple->add_card(Card(NINE, HEARTS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS); 

    delete simple;
}

TEST(test_simple_make_trump_no_trump_cards_round2) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(NINE, CLUBS));
    simple->add_card(Card(TEN, SPADES));
    simple->add_card(Card(QUEEN, CLUBS));
    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(ACE, SPADES));

    ASSERT_FALSE(simple->make_trump(upcard, false, 2, order_up_suit));

    delete simple;
}

TEST(test_simple_make_trump_force_dealer_with_no_trump_cards) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(NINE, CLUBS));
    simple->add_card(Card(TEN, SPADES));
    simple->add_card(Card(QUEEN, CLUBS));
    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(ACE, SPADES));

    ASSERT_TRUE(simple->make_trump(upcard, true, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS); 

    delete simple;
}

TEST(test_simple_make_trump_force_dealer_with_some_trump_cards) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(JACK, SPADES);
    Suit order_up_suit;

    simple->add_card(Card(KING, CLUBS)); 
    simple->add_card(Card(ACE, CLUBS)); 
    simple->add_card(Card(QUEEN, DIAMONDS));
    simple->add_card(Card(TEN, HEARTS));
    simple->add_card(Card(NINE, DIAMONDS));

    ASSERT_TRUE(simple->make_trump(upcard, true, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS); 

    delete simple;
}

TEST(test_simple_make_trump_with_right_bower_round1) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(TEN, HEARTS);
    Suit order_up_suit;

    simple->add_card(Card(JACK, HEARTS));  
    simple->add_card(Card(KING, HEARTS));
    simple->add_card(Card(ACE, CLUBS));
    simple->add_card(Card(QUEEN, DIAMONDS));
    simple->add_card(Card(NINE, SPADES));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);

    delete simple;
}

TEST(test_simple_make_trump_with_left_bower_round1) {
    Player *simple = Player_factory("SimplePlayer", "Simple");
    Card upcard(TEN, CLUBS);
    Suit order_up_suit;

    simple->add_card(Card(JACK, SPADES));  
    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(ACE, HEARTS));
    simple->add_card(Card(QUEEN, DIAMONDS));
    simple->add_card(Card(NINE, HEARTS));

    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);

    delete simple;
}

TEST(test_simple_play_card_follow_suit_one_option) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(QUEEN, SPADES));
    simple->add_card(Card(JACK, DIAMONDS));

    Card played = simple->play_card(Card(NINE, SPADES), HEARTS);
    
    ASSERT_EQUAL(played, Card(QUEEN, SPADES));

    delete simple;
}

TEST(test_simple_play_card_follow_suit_multiple_options) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(KING, SPADES));
    simple->add_card(Card(QUEEN, SPADES));
    simple->add_card(Card(JACK, DIAMONDS));

    Card played = simple->play_card(Card(NINE, SPADES), HEARTS);

    ASSERT_EQUAL(played, Card(QUEEN, SPADES));

    delete simple;
}

TEST(test_simple_play_card_no_led_suit_play_lowest_non_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(QUEEN, DIAMONDS));
    simple->add_card(Card(JACK, CLUBS));

    Card played = simple->play_card(Card(NINE, SPADES), HEARTS);

    ASSERT_EQUAL(played, Card(JACK, CLUBS));

    delete simple;
}

TEST(test_simple_play_card_no_led_suit_but_trump_available) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(JACK, HEARTS));
    simple->add_card(Card(KING, CLUBS));
    simple->add_card(Card(QUEEN, DIAMONDS));

    Card played = simple->play_card(Card(NINE, SPADES), HEARTS);

    ASSERT_EQUAL(played, Card(JACK, HEARTS));

    delete simple;
}

TEST(test_simple_play_card_all_trump) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(KING, HEARTS));
    simple->add_card(Card(QUEEN, HEARTS));
    simple->add_card(Card(JACK, HEARTS));

    Card played = simple->play_card(Card(NINE, HEARTS), HEARTS);

    ASSERT_EQUAL(played, Card(JACK, HEARTS));

    delete simple;
}

TEST(test_simple_play_card_only_one_card_left) {
    Player *simple = Player_factory("SimplePlayer", "Simple");

    simple->add_card(Card(KING, CLUBS));

    Card played = simple->play_card(Card(NINE, DIAMONDS), HEARTS);

    ASSERT_EQUAL(played, Card(KING, CLUBS));

    delete simple;
}



TEST_MAIN()




