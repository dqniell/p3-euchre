#include "Player.hpp"
#include <cassert>  
using namespace std;
#include <algorithm>


class SimplePlayer : public Player { 
    private: 
        string name; 
        vector<Card> hand;
    public: 

        SimplePlayer(const std::string &simple_name) {
            name = simple_name;
        }
        const string & get_name() const override { 
            return name; 
        }

        void add_card(const Card &c) override { 
            hand.push_back(c); 
        }
        
        bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override{
            int num_trump = 0;
            Suit suit_trump = upcard.get_suit();
            Suit same_next = Suit_next(suit_trump);

            if (round == 1) { 
                for (int i = 0; i < hand.size(); i++) { 
                    if (hand[i].is_trump(suit_trump) && hand[i].is_face_or_ace()) {
                        num_trump++;
                    } else if (hand[i].is_right_bower(suit_trump) || hand[i].is_left_bower(suit_trump)) {
                        num_trump++;
                    }
                }

                if (num_trump >= 2) {
                    order_up_suit = suit_trump;
                    return true;
                }

            } else if (round == 2) { 
                num_trump = 0;
                for (int i = 0; i < hand.size(); i++) { 
                    if (hand[i].is_trump(same_next) && hand[i].is_face_or_ace()) {
                        num_trump++;
                    } else if (hand[i].is_right_bower(same_next) || hand[i].is_left_bower(same_next)) {
                        num_trump++;
                    }
                }

                if (num_trump >= 1) {
                    order_up_suit = same_next;
                    return true;
                }


                if (is_dealer) {
                    order_up_suit = same_next; 
                    return true;
                }
            }
            return false; 
        }

        void add_and_discard(const Card &upcard) override {
            hand.push_back(upcard);
            Card lowest = hand[0];
            int index_of_lowest = 0;
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i] < lowest) {
                    lowest = hand[i];
                    index_of_lowest = i;
                }
            }
            hand.erase(hand.begin() + index_of_lowest);
        }
    //When a Simple Player leads a trick, they play the highest non-trump card in their hand. If they have only trump cards, they play the highest trump card in their hand.


        Card lead_card(Suit trump) override {
            Card highest = hand[0];
            int index_of_highest = 0; 
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].get_suit(trump) == trump) {
                    if (hand[i] > highest) {
                        highest = hand[i]; 
                        index_of_highest = i; 
                    }
                } else { 
                    if (hand[i] > highest && hand[i].get_suit(trump) != trump) {
                        highest = hand[i];
                        index_of_highest = i; 
                    }
                }
            }
            hand.erase(hand.begin() + index_of_highest);
            return highest;
        }

        Card play_card(const Card &led_card, Suit trump) override {
            Suit lead_suit = led_card.get_suit(); 
            vector<Card> lead_suit_cards;
            for (int i = 0; i < hand.size(); i++) { 
                if (hand[i].get_suit() == lead_suit) { 
                    lead_suit_cards.push_back(hand[i]);
                }
            }

            Card chose; 
            if (lead_suit_cards.size() > 0) {
                chose = lead_suit_cards[0];
                int index_of_lowest = 0;
                for (int i = 0; i < lead_suit_cards.size(); i++) {
                    if (lead_suit_cards[i] < chose) {
                        chose = lead_suit_cards[i];
                        index_of_lowest = i;
                    }
                }
                hand.erase(hand.begin() + index_of_lowest);
                return chose;
            } else {
                chose = hand[0];
                int index_of_lowest = 0;
                for (int i = 0; i < hand.size(); i++) {
                    if (hand[i] < chose) {
                        chose = hand[i];
                        index_of_lowest = i;
                    }
                }
                hand.erase(hand.begin() + index_of_lowest);
                return chose;
            }
        }

}; 

class HumanPlayer : public Player { 
    private: 
        string name; 
        vector<Card> hand;
    public: 
        HumanPlayer(const std::string &human_name) {
            name = human_name;
        }

        const string & get_name() const override { 
            return name; 
        }

        void add_card(const Card &c) override { 
            hand.push_back(c); 
        }

        bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override {
            print_hand(); 

            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

            string decision;
            cin >> decision;

            if (decision != "pass") {
                order_up_suit = string_to_suit(decision);
                return true;  
            }

            return false; 
    }

    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
                << "[" << i << "] " << hand[i] << "\n";
    }

    void add_and_discard(const Card &upcard) override {
        hand.push_back(upcard); 
        sort(hand.begin(), hand.end());
        print_hand(); 

        cout << "Discard upcard: [-1]\n" << upcard << "\n";
        cout << "Human player " << name << ", please select a card to discard:\n";

        int index;
        cin >> index;

        if (index != -1) {
            hand.pop_back();
        } else if (index >= 0 && index < hand.size()) {
            hand.erase(hand.begin() + index);
        }
    }

    Card lead_card(Suit trump) override {
        print_hand();
        
        cout << "Human player " << name << ", please select a card:\n";
        
        int lead_index;
        cin >> lead_index;

        if (lead_index >= 0 && lead_index < static_cast<int>(hand.size())) {
            Card chosen_card = hand[lead_index];
            hand.erase(hand.begin() + lead_index);
            return chosen_card;
        }

        return hand[0]; 
    }

        Card play_card(const Card &led_card, Suit trump) override {
            print_hand();

            cout << "Human player " << name << ", please select a card:\n";

            int play_index;
            cin >> play_index;

            if (play_index >= 0 && play_index < static_cast<int>(hand.size())) {
                Card chosen_card = hand[play_index];
                hand.erase(hand.begin() + play_index);
                return chosen_card;
            }
            
            return hand[0]; 

        }

};


Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  if (strategy == "Human") {
    return new HumanPlayer(name);
  }

  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}