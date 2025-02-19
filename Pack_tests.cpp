#include "Pack.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here
const int PACK_SIZE = 24;  

TEST(test_pack_deal_one) {
    Pack pack;

    ASSERT_EQUAL(pack.deal_one(), Card(NINE, SPADES));
    ASSERT_EQUAL(pack.deal_one(), Card(TEN, SPADES));
    ASSERT_EQUAL(pack.deal_one(), Card(JACK, SPADES));
    ASSERT_EQUAL(pack.deal_one(), Card(QUEEN, SPADES));
    ASSERT_EQUAL(pack.deal_one(), Card(KING, SPADES));
    ASSERT_EQUAL(pack.deal_one(), Card(ACE, SPADES));
    ASSERT_EQUAL(pack.deal_one(), Card(NINE, HEARTS));
}

TEST(test_pack_reset) {
    Pack pack;
    pack.deal_one();
    pack.deal_one();
    pack.reset();
    ASSERT_EQUAL(pack.deal_one(), Card(NINE, SPADES));
}

TEST(test_pack_empty) {
    Pack pack;

    for (int i = 0; i < PACK_SIZE; i++) {
        pack.deal_one();
    }

    ASSERT_TRUE(pack.empty());

    pack.reset();
    ASSERT_FALSE(pack.empty());
}

TEST(test_pack_shuffle) {
    Pack pack;
    Pack original_pack;
    vector<Card> original_cards;
    vector<Card> shuffled_cards;

    for (int i = 0; i < PACK_SIZE; i++) {
        original_cards.push_back(original_pack.deal_one());
    }

    pack.shuffle();

    for (int i = 0; i < PACK_SIZE; i++) {
        shuffled_cards.push_back(pack.deal_one());
    }

    pack.reset();

    ASSERT_NOT_EQUAL(original_cards, shuffled_cards);

    // pack.reset();
    // for (int i = 0; i < PACK_SIZE; i++) {
    //     ASSERT_EQUAL(original_cards[i], pack.deal_one());
    // }
}

TEST(test_pack_istream_ctor) {
    stringstream pack_data("Nine of Spades\n"
                           "Ten of Spades\n"
                           "Jack of Spades\n"
                           "Queen of Spades\n"
                           "King of Spades\n"
                           "Ace of Spades\n"
                           "Nine of Hearts\n"
                           "Ten of Hearts\n"
                           "Jack of Hearts\n"
                           "Queen of Hearts\n"
                           "King of Hearts\n"
                           "Ace of Hearts\n"
                           "Nine of Diamonds\n"
                           "Ten of Diamonds\n"
                           "Jack of Diamonds\n"
                           "Queen of Diamonds\n"
                           "King of Diamonds\n"
                           "Ace of Diamonds\n"
                           "Nine of Clubs\n"
                           "Ten of Clubs\n"
                           "Jack of Clubs\n"
                           "Queen of Clubs\n"
                           "King of Clubs\n"
                           "Ace of Clubs\n");

    Pack pack(pack_data);

    // First card should be Nine of Spades
    ASSERT_EQUAL(pack.deal_one(), Card(NINE, SPADES));

    // Second card should be Ten of Spades
    ASSERT_EQUAL(pack.deal_one(), Card(TEN, SPADES));

    // Continue checking the next cards
    ASSERT_EQUAL(pack.deal_one(), Card(JACK, SPADES));
}

TEST_MAIN()