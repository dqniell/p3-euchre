#include "Pack.hpp"
#include <array>
#include <string>
#include <iostream> 
using namespace std;
#include <cassert>
#include <algorithm>
#include <vector>




Pack::Pack() {
    next = 0; 
    int index = 0;
    for (int i = 0; i < 4; i++) {
        Suit suit = static_cast<Suit>(i);
        for (int j = static_cast<int>(NINE); j <= static_cast<int>(ACE); j++) { 
            Rank rank = static_cast<Rank>(j); 
            cards[index] = Card(rank, suit);
            index++;
        }
    }
}

Pack::Pack(std::istream& pack_input) {
    next = 0; 
    string rank, of, suit;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> rank >> of >> suit;
        cards[i] = Card(string_to_rank(rank), string_to_suit(suit));
    }
}

Card Pack::deal_one() {
    Card card = cards[next];
    next++;
    return card;
}

void Pack::reset() {
    next = 0; 
}

void Pack::shuffle() {
    vector<Card> temp(cards.begin(), cards.end());
    for (int i = 0; i < 7; ++i) {
        vector<Card> first_half(temp.begin(), temp.begin() + PACK_SIZE / 2);
        vector<Card> second_half(temp.begin() + PACK_SIZE / 2, temp.end());
        vector<Card> final;
        
        for (int j = 0; j < first_half.size(); ++j) {
            final.push_back(second_half[j]);
            final.push_back(first_half[j]);
        }
        
        temp = final;
    } 

    copy(temp.begin(), temp.end(), cards.begin());
}

bool Pack::empty() const {
    return next >= PACK_SIZE; 
}