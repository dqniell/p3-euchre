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

TEST(test_card_default_ctor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_card_comparison) {
    Card ace_hearts(ACE, HEARTS);
    Card ace_diamonds(ACE, DIAMONDS);
    Card king_spades(KING, SPADES);

    ASSERT_TRUE(ace_hearts < ace_diamonds);
    ASSERT_TRUE(king_spades < ace_hearts);  
}

TEST(test_card_is_face_or_ace) {
    Card ace(ACE, HEARTS);
    Card jack(JACK, SPADES);
    Card nine(NINE, DIAMONDS);

    ASSERT_TRUE(ace.is_face_or_ace());
    ASSERT_TRUE(jack.is_face_or_ace());
    ASSERT_FALSE(nine.is_face_or_ace());
}

TEST(test_card_bower_detection) {
    Card jack_hearts(JACK, HEARTS);
    Card jack_diamonds(JACK, DIAMONDS);

    ASSERT_TRUE(jack_hearts.is_right_bower(HEARTS));
    ASSERT_FALSE(jack_diamonds.is_right_bower(HEARTS));

    ASSERT_TRUE(jack_diamonds.is_left_bower(HEARTS));
    ASSERT_FALSE(jack_hearts.is_left_bower(CLUBS));
}

TEST(test_card_is_trump) {
    Card card1(TEN, SPADES);
    Card right_bower(JACK, HEARTS);
    Card left_bower(JACK, DIAMONDS);

    ASSERT_TRUE(card1.is_trump(SPADES));
    ASSERT_TRUE(right_bower.is_trump(HEARTS));
    ASSERT_TRUE(left_bower.is_trump(HEARTS));
    ASSERT_FALSE(card1.is_trump(DIAMONDS));
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
}

TEST(test_card_less_trump) {
    Card card1(QUEEN, HEARTS);
    Card card2(JACK, HEARTS);
    Card card3(KING, DIAMONDS);

    ASSERT_TRUE(Card_less(card2, card1, HEARTS));
    ASSERT_FALSE(Card_less(card1, card3, HEARTS)); // Left bower is trump
}

TEST(test_card_less_led) {
    Card card1(QUEEN, CLUBS);
    Card card2(JACK, DIAMONDS);
    Card card3(NINE, CLUBS);
    Card led_card(NINE, CLUBS);

    ASSERT_TRUE(Card_less(card3, card1, led_card, HEARTS));
    ASSERT_FALSE(Card_less(card2, card1, led_card, HEARTS));
}

TEST_MAIN()
