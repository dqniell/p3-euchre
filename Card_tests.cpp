#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_getters) {
    Card card(ACE, DIAMONDS);
    ASSERT_EQUAL(card.get_rank(), ACE);
    ASSERT_EQUAL(card.get_suit(), DIAMONDS);
}

TEST(test_card_getters_default) { 
    Card card; 
    ASSERT_EQUAL(card.get_rank(), TWO);
}

TEST(get_suit) {
    Card left_bower(JACK, DIAMONDS);
    ASSERT_EQUAL(left_bower.get_suit(HEARTS), HEARTS); 

    Card normal(TEN, CLUBS);
    ASSERT_EQUAL(normal.get_suit(SPADES), CLUBS); 
}

TEST(get_suit_default) { 
    Card card; 
    ASSERT_EQUAL(card.get_suit(), SPADES); 
    ASSERT_EQUAL(card.get_suit(), SPADES);
}

TEST(test_card_get_suit_normal) {
    Card card(KING, CLUBS);
    ASSERT_EQUAL(card.get_suit(HEARTS), CLUBS); 
}

TEST(test_card_get_suit_trump) {
    Card trump_card(ACE, HEARTS);
    ASSERT_EQUAL(trump_card.get_suit(HEARTS), HEARTS); 
}

TEST(test_card_get_suit_right_bower) {
    Card right_bower(JACK, SPADES);  
    ASSERT_EQUAL(right_bower.get_suit(SPADES), SPADES); 
}

TEST(test_card_get_suit_left_bower) {
    Card left_bower(JACK, DIAMONDS);  
    ASSERT_EQUAL(left_bower.get_suit(HEARTS), HEARTS); 
}

TEST(test_card_get_suit_left_bower_clubs) {
    Card left_bower(JACK, CLUBS);  
    ASSERT_EQUAL(left_bower.get_suit(SPADES), SPADES); 
}

TEST(test_card_get_suit_left_bower_diamonds) {
    Card left_bower(JACK, DIAMONDS);  
    ASSERT_EQUAL(left_bower.get_suit(HEARTS), HEARTS);  
}


TEST(test_card_is_face_or_ace) {
    ASSERT_TRUE(Card(JACK, SPADES).is_face_or_ace());
    ASSERT_TRUE(Card(QUEEN, HEARTS).is_face_or_ace());
    ASSERT_TRUE(Card(KING, CLUBS).is_face_or_ace());
    ASSERT_TRUE(Card(ACE, DIAMONDS).is_face_or_ace());
    ASSERT_FALSE(Card(TEN, CLUBS).is_face_or_ace());
}

TEST(test_card_is_right_bower) {
    Card right_bower(JACK, CLUBS);
    ASSERT_TRUE(right_bower.is_right_bower(CLUBS));
    ASSERT_FALSE(right_bower.is_right_bower(SPADES));
}

TEST(test_card_is_left_bower) {
    Card left_bower(JACK, DIAMONDS);
    ASSERT_TRUE(left_bower.is_left_bower(HEARTS));
    ASSERT_FALSE(left_bower.is_left_bower(DIAMONDS)); 
}

TEST(test_card_is_trump) {
    Card trump_card(QUEEN, HEARTS);
    ASSERT_TRUE(trump_card.is_trump(HEARTS));

    Card left_bower(JACK, DIAMONDS);
    ASSERT_TRUE(left_bower.is_trump(HEARTS)); 

    Card non_trump_card(NINE, SPADES);
    ASSERT_TRUE(non_trump_card.is_trump(SPADES));
}

TEST(test_card_operators) {
    Card card1(TEN, HEARTS);
    Card card2(JACK, HEARTS);
    Card card3(TEN, CLUBS);
    Card card4(JACK, CLUBS);

    ASSERT_TRUE(card1 < card2);   
    ASSERT_TRUE(card2 > card1);   
    ASSERT_TRUE(card1 <= card2);
    ASSERT_TRUE(card2 >= card1);  
    ASSERT_TRUE(card1 != card2);  
    ASSERT_TRUE(card1 == Card(TEN, HEARTS)); 

    ASSERT_TRUE(card3 < card4);   
    ASSERT_TRUE(card4 > card3);   

    ASSERT_TRUE(Card(JACK, DIAMONDS) < Card(KING, HEARTS)); 
    ASSERT_FALSE(card1 > card2); 
}

TEST(test_card_stream_operators) {
    Card card(KING, DIAMONDS);
    
    stringstream ss;
    ss << card;
    ASSERT_EQUAL(ss.str(), "King of Diamonds");

    stringstream input("Queen of Spades");
    Card read_card;
    input >> read_card;
    ASSERT_EQUAL(read_card, Card(QUEEN, SPADES));
}


TEST(test_card_less_trump_vs_nontrump) {
    Card trump_card(KING, HEARTS);
    Card non_trump_card(TEN, CLUBS);

    ASSERT_FALSE(Card_less(trump_card, non_trump_card, HEARTS)); 
    ASSERT_TRUE(Card_less(non_trump_card, trump_card, HEARTS));  
}

TEST(test_card_less_right_bower_vs_trump) {
    Card right_bower(JACK, HEARTS);
    Card ace_trump(ACE, HEARTS);

    ASSERT_TRUE(Card_less(right_bower, ace_trump, HEARTS)); 
    ASSERT_FALSE(Card_less(ace_trump, right_bower, HEARTS));  
}

TEST(test_card_less_left_bower_vs_trump) {
    Card left_bower(JACK, DIAMONDS);  
    Card king_trump(KING, HEARTS);

    ASSERT_TRUE(Card_less(left_bower, king_trump, HEARTS)); 
    ASSERT_FALSE(Card_less(king_trump, left_bower, HEARTS)); 
}

TEST(test_card_less_right_bower_vs_left_bower) {
    Card right_bower(JACK, HEARTS);
    Card left_bower(JACK, DIAMONDS);

    ASSERT_TRUE(Card_less(right_bower, left_bower, HEARTS)); 
    ASSERT_FALSE(Card_less(left_bower, right_bower, HEARTS));  
}

TEST(test_card_less_same_suit_different_rank) {
    Card low_card(NINE, CLUBS);
    Card high_card(KING, CLUBS);

    ASSERT_TRUE(Card_less(low_card, high_card, HEARTS));  
    ASSERT_FALSE(Card_less(high_card, low_card, HEARTS));
}


TEST(test_card_less_default) { 
    Card card; 
    ASSERT_FALSE(Card_less(card, card, SPADES)); 
}

TEST(test_card_less_trump_vs_led_suit) {
    Card led_card(TEN, CLUBS);
    Card trump_card(QUEEN, HEARTS);
    Card non_trump_card(KING, CLUBS);

    ASSERT_FALSE(Card_less(trump_card, non_trump_card, led_card, HEARTS));  
    ASSERT_TRUE(Card_less(non_trump_card, trump_card, led_card, HEARTS));
}

TEST(test_card_less_led_suit_vs_non_led) {
    Card led_card(TEN, CLUBS);
    Card matching_led(KING, CLUBS);
    Card non_matching(TEN, SPADES);

    ASSERT_FALSE(Card_less(matching_led, non_matching, led_card, HEARTS));
    ASSERT_TRUE(Card_less(non_matching, matching_led, led_card, HEARTS));
}

TEST(test_card_less_same_suit_tiebreaker) {
    Card card1(KING, DIAMONDS);
    Card card2(KING, SPADES);
    Card led_card(KING, DIAMONDS);

    ASSERT_TRUE(Card_less(card2, card1, led_card, HEARTS));
    ASSERT_FALSE(Card_less(card1, card2, led_card, HEARTS));
}

TEST(test_card_less_trump_vs_left_bower) {
    Card left_bower(JACK, DIAMONDS);
    Card normal_trump_card(ACE, HEARTS);
    
    ASSERT_TRUE(Card_less(left_bower, normal_trump_card, HEARTS));  
    ASSERT_FALSE(Card_less(normal_trump_card, left_bower, HEARTS));  
}

TEST(test_card_less_led_suit_same_rank) {
    Card card1(KING, DIAMONDS);
    Card card2(KING, SPADES);
    Card led_card(KING, DIAMONDS);

    ASSERT_TRUE(Card_less(card2, card1, led_card, HEARTS));  
    ASSERT_FALSE(Card_less(card1, card2, led_card, HEARTS));
}

TEST(test_card_less_nontrump_same_suit) {
    Card low_card(TEN, SPADES);
    Card high_card(QUEEN, SPADES);
    Card led_card(TEN, SPADES);

    ASSERT_TRUE(Card_less(low_card, high_card, led_card, HEARTS));
    ASSERT_FALSE(Card_less(high_card, low_card, led_card, HEARTS));
}

TEST(test_card_less_lowest_trump_vs_highest_non_trump) {
    Card lowest_trump(NINE, HEARTS);
    Card highest_non_trump(ACE, CLUBS);

    ASSERT_FALSE(Card_less(lowest_trump, highest_non_trump, HEARTS));
    ASSERT_TRUE(Card_less(highest_non_trump, lowest_trump, HEARTS));

    Card low_card(TWO, CLUBS);
    Card high_card(ACE, SPADES);

    ASSERT_TRUE(Card_less(low_card, high_card, HEARTS));
    ASSERT_FALSE(Card_less(high_card, low_card, HEARTS));
}

TEST(test_card_less_equal_cards) {
    Card card1(KING, HEARTS);
    Card card2(KING, HEARTS);

    ASSERT_FALSE(Card_less(card1, card2, HEARTS));
    ASSERT_FALSE(Card_less(card2, card1, HEARTS));
}



TEST_MAIN()