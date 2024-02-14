#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <tuple>
#include <climits>
#include <cstdlib>
#include <algorithm>

int rand_pick() {
    //The following line has been written in order to cahnge the seed of 
    //randomness everytime that the algorithm is executed
    int RandIndex = rand() % 52;
    return RandIndex;
};


std::string find_symbol(int i) {
    static char syms[14][3] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A","n" };
    std::string stri = syms[i];
    return stri;
}

int find_value(std::string k) {
    static char syms[14][3] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A","n" };
    for (int i = 0; i < 13; ++i) {
        if (k == syms[i]) {
            return i;
        }
    }
}

struct Card
{
    int value, suit;
};
struct Hand {
    std::string symbol;
    int suit, value;
};

int main() {

    srand(time(NULL));

    auto draw_cards = [](std::vector<Hand> phand, Card deck[52]) {
        int size = phand.size();
        for (int j = 0; j < size; ++j) {
            int player_picked;
            std::string player_card;
            player_picked = rand_pick();
            player_card = find_symbol(deck[player_picked].value);
            while (deck[player_picked].value == 13) {
                player_picked = rand_pick();
                player_card = find_symbol(deck[player_picked].value);

            };
            deck[player_picked].value = 13;
            phand.at(j).suit = deck[player_picked].suit;
            phand.at(j).symbol = player_card;
            phand.at(j).value = deck[player_picked].value;
        }
        return phand;

        };

    auto deck_size = [](Card deck[52]) {
        int count = 0;
        for (int i = 0; i < 52; ++i) {
            if (deck[i].value != 13) {
                count += 1;
            }
        };
        return count;
        };
    auto factorial = [](int i) {
        long double count = 1;
        for (int j = i; j > 0; --j) {
            count = j * count;
        }
        return count;
        };
    auto binomial_bracket = [&](int i, int j) {
        long double res;
        res = factorial(i) / (factorial(j) * factorial(i - j));
        return res;
        };
    auto count_in_deck = [&](std::string symb, Card deck[52]) {
        int cnt = 0;
        for (int i = 0; i <52; ++i) {
            if (find_symbol(deck[i].value) == symb) {
                cnt += 1;
            }
        }
        return cnt;
        };
    auto probability_straight_flush = [&](std::vector<Hand> phand, std::vector<Hand> floor, Card deck[52]) {
        int phand_size = phand.size();
        int d_size = deck_size(deck);
        std::vector <std::vector<std::string >> hands_vec;
        hands_vec = { { "A", "2", "3", "4", "5" },
        { "2", "3", "4", "5", "6" },
        { "3", "4", "5", "6", "7" },
        { "4", "5", "6", "7", "8" },
        { "5", "6", "7", "8", "9" },
        { "6", "7", "8", "9", "10" },
        { "7", "8", "9", "10", "J" },
        { "8", "9", "10", "J", "Q" },
        { "9", "10", "J", "Q", "K" },
        { "10", "J", "Q", "K", "A" } };
        std::vector <std::vector<std::string >> pvec;
        for (int i = 0; i < hands_vec.size(); ++i) {
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < phand_size; ++k) {
                    if (phand[k].symbol == hands_vec.at(i).at(j)) {
                        pvec.push_back(hands_vec.at(i));
                    }
                }
            }
        }
        pvec.erase(std::unique(pvec.begin(), pvec.end()), pvec.end());
        for (int i = 0; i < phand.size(); ++i) {
            //std::cout << phand.at(i).suit << " card drawn" << '\n';
        }
        long double probability = 0;
        for (int i = 0; i < pvec.size(); ++i) {
            std::vector<std::string> count;
            std::vector <std::string> ignore;
            for (int l = 0; l < 5; ++l) {
                for (int kl = 0; kl < phand_size; ++kl) {
                    if (phand[kl].symbol == pvec.at(i).at(l)
                        && (not(std::find(ignore.begin(), ignore.end(), phand[kl].symbol) != ignore.end()))) {
                        ignore.push_back(phand[kl].symbol);
                    }
                }
                for (int riv = 0; riv < floor.size(); ++riv) {
                    if (floor[riv].symbol == pvec.at(i).at(l)
                        && (not(std::find(ignore.begin(), ignore.end(), floor[riv].symbol) != ignore.end()))) {
                        ignore.push_back(floor[riv].symbol);

                    }
                }
            }
            bool fl = true;
            for (int han = 0; han < phand.size(); ++han) {
                for (int flo = 0; flo < floor.size(); flo++) {
                    if (phand[han].suit != floor[flo].suit) {
                        fl = false;
                    }
                }
            }
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < 52; ++k) {
                    if (fl && (phand[0].suit != deck[k].suit)) {
                        fl = false;
                    }
                    if (pvec.at(i).at(j) == find_symbol(deck[k].value) && fl
                        && deck[k].value != 13 && (not(std::find(ignore.begin(), ignore.end(), pvec.at(i).at(j)) != ignore.end()))) {
                        count.push_back(pvec.at(i).at(j));
                        
                    }
                }
            }

            std::vector <int> counting(5 - ignore.size(), 1);
            int k = 0;
            for (int j = 1; j < count.size(); ++j) {
                if (count.at(j) == count.at(j - 1)) {
                    counting.at(k) += 1;
                }
                else if (k < counting.size()) {
                    k += 1;
                }
            }
            long double kirk = 1;
            int mult = 0;
            for (int j = 0; j < counting.size(); ++j) {
                mult += counting.at(j);
                kirk *= binomial_bracket(counting.at(j), 1);
            }
            if (counting.size() <= 5 - floor.size() && count.size()>0) {
                probability += kirk * binomial_bracket(d_size - mult, 5 - floor.size() - counting.size()) / binomial_bracket(d_size, 5 - floor.size());
            }

        }
        return probability;
        };

    auto probability_straight = [&](std::vector<Hand> phand, std::vector<Hand> floor, Card deck[52]) {
        int phand_size = phand.size();
        int d_size = deck_size(deck);
        std::vector <std::vector<std::string >> hands_vec;
        hands_vec = { { "A", "2", "3", "4", "5" },
        { "2", "3", "4", "5", "6" },
        { "3", "4", "5", "6", "7" },
        { "4", "5", "6", "7", "8" },
        { "5", "6", "7", "8", "9" },
        { "6", "7", "8", "9", "10" },
        { "7", "8", "9", "10", "J" },
        { "8", "9", "10", "J", "Q" },
        { "9", "10", "J", "Q", "K" },
        { "10", "J", "Q", "K", "A" } };
        std::vector <std::vector<std::string >> pvec;
        for (int i = 0; i < hands_vec.size(); ++i) {
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < phand_size; ++k) {
                    if (phand[k].symbol == hands_vec.at(i).at(j)) {
                        pvec.push_back(hands_vec.at(i));
                    }
                }
            }
        }
        pvec.erase(std::unique(pvec.begin(), pvec.end()), pvec.end());
        for (int i = 0; i < phand.size(); ++i) {
            //std::cout << phand.at(i).symbol<<" card drawn"<<'\n';
        }
        long double probability = 0;
        for (int i = 0; i < pvec.size(); ++i) {
            std::vector<std::string> count;
            std::vector <std::string> ignore;
            for (int l = 0; l < 5; ++l) {
                for (int kl = 0; kl < phand_size; ++kl) {
                    if (phand[kl].symbol == pvec.at(i).at(l)
                        && (not(std::find(ignore.begin(), ignore.end(), phand[kl].symbol) != ignore.end()))) {
                        ignore.push_back(phand[kl].symbol);
                    }
                }
                for (int riv = 0; riv < floor.size(); ++riv) {
                    if (floor[riv].symbol == pvec.at(i).at(l)
                        && (not(std::find(ignore.begin(), ignore.end(), floor[riv].symbol) != ignore.end()))) {
                        ignore.push_back(floor[riv].symbol);

                    }
                }
            }
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < 52; ++k) {
                    if (pvec.at(i).at(j) == find_symbol(deck[k].value) && deck[k].value != 13
                        && (not(std::find(ignore.begin(), ignore.end(), pvec.at(i).at(j)) != ignore.end()))) {
                        count.push_back(pvec.at(i).at(j));
                    }
                }
            }

            std::vector <int> counting(5 - ignore.size(), 1);
            int k = 0;
            for (int j = 1; j < count.size(); ++j) {
                if (count.at(j) == count.at(j - 1)) {
                    counting.at(k) += 1;
                }
                else if (k < counting.size()) {
                    k += 1;
                }
            }
            
            long double kirk = 1;
            int mult = 0;
            for (int j = 0; j < counting.size(); ++j) {
                mult += counting.at(j);
                kirk *= binomial_bracket(counting.at(j), 1);
            }
            if (counting.size() <= 5 - floor.size()) {
                //std::cout << ignore.size() << " ignore size" << '\n';
                //std::cout << counting.size() << " need size" << '\n';
                //std::cout << pvec.at(i).at(0) << " starting " << mult<< " mult "<< '\n';
                //std::cout << 5 - floor.size() - counting.size() << " excess " << '\n';
                probability += kirk * binomial_bracket(d_size - mult, 5 -floor.size() - counting.size()) / binomial_bracket(d_size, 5-floor.size());
            }
            
        }        
        return probability;
        };
    auto count_suits = [](int sut, std::vector<Hand> floor) {
        int cnts = 0;
        for (int i = 0; i < floor.size(); ++i) {
            if (sut == floor[i].suit) {
                cnts += 1;
            }
        }
        return cnts;
        };

    auto probability_flush = [&](std::vector<Hand> phand, std::vector<Hand> floor, Card deck[52]) {
        long double probability=0;
        int d_size = deck_size(deck);
        std::vector< int> pvec;
        std:: vector< int>ignore;
        std::vector <int> suits = { 0,1,2,3 };
        for (int i = 0; i < phand.size(); ++i) {
            ignore.push_back(phand[i].suit);
        }
        for (int i = 0; i < floor.size(); ++i) {
            ignore.push_back(floor[i].suit);
        }
        long double kirk = 0;
        for (int i = 0; i < suits.size(); ++i) {
            int count_ignore = 0, count_deck;
            for (int j = 0; j < ignore.size(); j++) {
                if (ignore[j] == suits[i]) {
                    count_ignore += 1;
                }
            }           
            count_deck = 13 - count_ignore;
            
            if (5 - count_ignore <= 5 - floor.size()) {
                kirk += binomial_bracket(count_deck, 5 - count_ignore) * binomial_bracket(d_size - count_deck, 5-floor.size()-(5-count_ignore))
                    / binomial_bracket(d_size, 5 - floor.size());
            }
                        
        }
        probability = kirk;
        for (int i = 0; i < phand.size(); ++i) {
            if ((count_suits(phand[i].suit, floor) > 2 and count_suits(phand[i].suit, phand) > 1) 
                || (count_suits(phand[i].suit, floor) > 3 and count_suits(phand[i].suit, phand) > 0)) {
                probability = 1;
            }
        }
        return probability;
        };

    auto probability_high_card = [&](std::vector<Hand> phand, std::vector<std::vector <Hand>> opp, std::vector<Hand> floor, Card deck[52]) {
        int hand_max = 0, hand_second_max=0, opp_max=0, opp_second_max=0;
        long double d_size, hand_cnt = 0, opp_cnt=0, probability=0;
        bool skip = true;
        d_size = deck_size(deck);
        for (int i = 0; i < phand.size(); ++i) {
            if (find_value(phand[i].symbol) > hand_max) {
                hand_max = find_value(phand[i].symbol);
            }
        }
        for (int i = 0; i < opp.size(); ++i) {
            for (int j = 0; j < opp.at(i).size(); ++j) {
                if (find_value(opp.at(i).at(j).symbol) > opp_max) {
                    opp_max = find_value(opp.at(i).at(j).symbol);                        
                }
            }
        }
        if (opp_max == hand_max) {
            for (int i = 0; i < opp.size(); ++i) {
                for (int j = 0; j < opp.at(i).size(); ++j) {
                    if (find_value(opp.at(i).at(j).symbol) != opp_max and find_value(opp.at(i).at(j).symbol) > opp_second_max) {
                        opp_second_max = find_value(opp.at(i).at(j).symbol);
                    }
                }
            }
            for (int i = 0; i < phand.size(); ++i) {
                if (find_value(phand[i].symbol) != hand_max && find_value(phand[i].symbol) > hand_second_max) {
                    hand_second_max = find_value(phand[i].symbol);
                }
            }
            if (hand_second_max == opp_second_max) {
                probability = 0.5;
                skip = false;
            }
            opp_max = opp_second_max;
            hand_max = hand_second_max;
        }        
        for (int i = 0; i < 52; ++i) {
            if (deck[i].value != 13 && deck[i].value < hand_max) {
                hand_cnt += 1;
            }
            if (deck[i].value != 13 && deck[i].value < opp_max) {
                opp_cnt += 1;
            }
        }
        if (hand_max > opp_max and skip) {
            probability = 1 - binomial_bracket(d_size-hand_cnt, 5-floor.size())/binomial_bracket(d_size, 5-floor.size());
        }
        else if (hand_max < opp_max and skip) {
            probability =binomial_bracket(d_size - opp_cnt, 5 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());
        }
        return probability;
        };

    auto count_vector = [](std:: string symb, std::vector <Hand> floor) {
        int cnts = 0;
        for (int i = 0; i < floor.size(); ++i) {
            if (symb == floor[i].symbol) {
                cnts += 1;
            }
        }
        return cnts;
        };

    auto probability_one_pair = [&](std::vector<Hand> phand, std:: vector <Hand > floor, Card deck[52]) {
        int d_size = deck_size(deck);
        long double prop=0, cnts = 0;
        for (int i = 0; i < phand.size(); i++) {
            cnts = count_in_deck(phand[i].symbol, deck);
            prop += binomial_bracket(cnts, 1) * binomial_bracket(d_size - cnts, 4 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());            
        }
        if (5 - floor.size() > 2) {
            for (int i = 0; i < 52; ++i) {
                if (deck[i].value != 13) {
                    prop += binomial_bracket(count_in_deck(find_symbol(deck[i].value), deck), 2) / binomial_bracket(d_size, 5 - floor.size());
                }
            }
        }
        if (phand[0].symbol == phand[1].symbol) {
            prop = 1;
        }
        for (int i = 0; i < floor.size(); i++) {
            if (count_vector(floor[i].symbol, floor) > 1) {
                prop = 1;
            }
        }
        for (int i = 0; i < phand.size(); ++i) {
            if (count_vector(phand[i].symbol, floor) > 0) {
                prop = 1;
            }
        }
        return prop;
        };

    auto probability_two_pair = [&](std::vector<Hand> phand, std::vector <Hand > floor, Card deck[52]) {
        int d_size = deck_size(deck);
        long double prop = 1, cnts = 0;
        for (int i = 0; i < phand.size(); i++) {
            cnts = count_in_deck(phand[i].symbol, deck);
            prop *= binomial_bracket(cnts, 1) * binomial_bracket(d_size - cnts, 4 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());
        }         
        if (5 - floor.size() > 4) {
            for (int j = 0; j < phand.size(); j++) {
                cnts = count_in_deck(phand[0].symbol, deck);
                prop += binomial_bracket(cnts, 1) * binomial_bracket(d_size -cnts, 3-floor.size())/binomial_bracket(d_size, 5-floor.size());
            }
        }
        if (count_vector(phand[0].symbol,phand)>1) {
            prop = 0;
            if (5 - floor.size() > 2) {
                for (int i = 0; i < 52; ++i) {
                    if (deck[i].value != 13) {
                        prop += binomial_bracket(count_in_deck(find_symbol(deck[i].value), deck), 2) / binomial_bracket(d_size, 5 - floor.size());
                    }
                }
            }
            for (int i = 0; i < floor.size(); i++) {
                if (count_vector(floor[i].symbol, floor) > 2) {
                    prop = 1;
                }
            }
        }
        for (int i = 0; i < floor.size(); i++) {
            if (count_vector(floor[i].symbol, floor) > 2) {
                prop = 0;
                if (5 - floor.size() > 2) {
                    for (int i = 0; i < 52; ++i) {
                        if (deck[i].value != 13) {
                            prop += binomial_bracket(count_in_deck(find_symbol(deck[i].value), deck), 2) / binomial_bracket(d_size, 5 - floor.size());
                        }
                    }
                }
            }
        }
        return prop;
        };

    auto probability_triple = [&](std::vector<Hand> phand, std::vector <Hand > floor, Card deck[52]) {
        int d_size = deck_size(deck);
        long double prop = 0, cnts = 0;
        for (int i = 0; i < phand.size(); i++) {
            cnts = count_in_deck(phand[i].symbol, deck);
            prop += binomial_bracket(cnts, 2) * binomial_bracket(d_size - cnts, 3 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());
        }
        if (count_vector(phand[0].symbol, phand)>1) {
            cnts = count_in_deck(phand[0].symbol, deck);
            prop = binomial_bracket(cnts, 1) * binomial_bracket(d_size - cnts, 4 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());
        }  
        for (int i = 0; i < floor.size(); ++i) {
            if (count_vector(floor[i].symbol, floor)>1 && 5-floor.size()>1) {
                prop = 0;
                cnts = count_in_deck(floor[i].symbol, deck);
                prop= binomial_bracket(cnts, 1) * binomial_bracket(d_size - cnts, 4 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());
            }
        }
        for (int i = 0; i < phand.size(); i++) {
            if (count_vector(phand[i].symbol, floor) > 0 && 5 - floor.size() > 1 ) {
                cnts = count_in_deck(phand[i].symbol, deck);
                prop += binomial_bracket(cnts, 1) * binomial_bracket(d_size - cnts, 4 - floor.size()) / binomial_bracket(d_size, 5 - floor.size());
            }
        }
        for (int i = 0; i < phand.size(); ++i) {
            if (count_vector(phand[i].symbol, floor) > 1 || (count_vector(phand[i].symbol, floor) > 0 && count_vector(phand[0].symbol, phand) > 1)) {
                prop = 1;
            }
        }
        return prop;
        };
    auto input_hand = [](std::vector <Hand> &playerhand) {
        std::string first_symbol, second_symbol;
        int first_suit, second_suit;
        std::cout << "Input first card symbol" << '\n';
        std::cin >> first_symbol;
        playerhand[0].symbol = first_symbol;
        playerhand[0].value = find_value(first_symbol);
        std::cout << "Input first card suit" << '\n';
        std::cin >> first_suit;
        playerhand[0].suit = first_suit;
        std::cout << "Input second symbol" << '\n';
        std::cin >> second_symbol;
        playerhand[1].symbol = second_symbol;
        std::cout << "Input second card suit" << '\n';
        std::cin >> second_suit;
        playerhand[1].suit = second_suit;
        playerhand[1].value = find_value(second_symbol);
        };

    auto input_floor = [](std::vector<Hand> &floor) {
        for (int i = 0; i < floor.size(); ++i) {
            std::string first_symbol;
            int first_suit, second_suit;
            std::cout << "Input card symbol" << '\n';
            std::cin >> first_symbol;
            floor[i].symbol = first_symbol;
            floor[i].value = find_value(first_symbol);
            std::cout << "Input card suit" << '\n';
            std::cin >> first_suit;
            floor[i].suit = first_suit;
        }
        };

    //Initialize Deck of Cards
    Card cards[52];
    for (int i = 0; i < 52; ++i) {
        cards[i].suit = i % 4;
        cards[i].value = i % 13;
    };

    //Initialize Hand of Player
    std::vector<Hand> playerhand(2);
    
    std::cout << "Would you like to input your own values? Answer with y/n: "<<'\n';
    std::string player_answer;
    std::cin >> player_answer;
    if (player_answer == "y") {
        std::cout << "Input card symbols and suits."<< '\n' << "Suits can be inputed as (0, 1, 2, 3) for (spades, clubs, hearts, diamonds)"
            << "Symbols can be inputed as (2, 3, 4, 5, 6, 7, 8, 9, 10 ,J ,Q ,K ,A )" << '\n';
        input_hand(playerhand);
    }
    else {
        playerhand = draw_cards(playerhand, cards);
    }   
    int num;
    std::cout << "How many opponents would you like? For no oppononets input 0." << '\n';
    std::cin >> num;

    //Initialize number of opponents and their cards
    int number_of_opponents = num;
    std::vector <std::vector <Hand>> opponents;
    std::string opp_answer;
    for (int i = 0; i < number_of_opponents; ++i) {
        std::vector<Hand> opp(2);
        opponents.push_back(opp);
    }
    if (num != 0) {
        std::cout << "Would you like to input the cards of your opponents. Answer with y/n." << '\n';
        std::cin >> opp_answer;
        if (opp_answer == "y") {
            for (int i = 0; i < num; i++) {
                input_hand(opponents.at(i));
            }
        }
        else {
            for (int i = 0; i < num; i++) {
                std::vector<Hand> opp(2);
                opp = draw_cards(opp, cards);
                opponents.at(i)=opp;
            }
        }
    }
    
    int floor_size;
    std::cout << "How many cards have been dealt?" << '\n';
    std::cin >> floor_size;
    std::vector <Hand> floor(floor_size);
    
    std::string answer_floor;
    std::cout << "Would you like to input the cards dealt? Answer with y/n." << '\n';
    std:: cin >> answer_floor;
    if (answer_floor == "y") {
        input_floor(floor);
    }
    else {
        floor = draw_cards(floor, cards);
    }
    system("cls");
    

    for (int j = 0; j < playerhand.size(); j++) {
        std::cout << playerhand[j].symbol << " symbol " << playerhand[j].suit << " suit player drawn " << '\n';
    }
    for (int j = 0; j < 2; j++) { std::cout << '\n'; }


    for (int i = 0; i < number_of_opponents; ++i) {
        for (int j = 0; j < opponents[i].size(); j++) {
            std::cout << opponents.at(i).at(j).symbol << " symbol " << opponents.at(i).at(j).suit << " suit opponent" << i + 1 << " drawn " << '\n';
        }
        for (int j = 0; j < 2; j++) { std::cout << '\n'; }
    }

    for (int j = 0; j < floor.size(); ++j) {
        std::cout << floor.at(j).symbol << " floor symbol " << floor.at(j).suit << " suit " << '\n';
    }
    for (int j = 0; j < 1; j++) { std::cout << '\n'; }

    long double player_straight_prop, player_straight_flush_prop , player_flush_prop, player_high_prop
        , player_one_pair, player_two_pair, player_triple;

    player_straight_prop = probability_straight(playerhand, floor, cards);
    player_straight_flush_prop = probability_straight_flush(playerhand, floor, cards);
    player_flush_prop = probability_flush(playerhand, floor, cards);
    player_high_prop = probability_high_card(playerhand, opponents, floor, cards);
    player_one_pair= probability_one_pair(playerhand, floor, cards);
    player_two_pair = probability_two_pair(playerhand, floor, cards);
    player_triple = probability_triple(playerhand, floor, cards);

    std::cout << player_straight_prop * 100 << "%" << " player probability for straight" << '\n';
    std::cout << player_straight_flush_prop * 100 << "%" << " player probability for straight-flush" << '\n';
    std::cout << player_flush_prop * 100 << "%" << " player probability for flush" << '\n';
    std::cout << player_high_prop * 100 << "%" << " player probability for higher card" << '\n';
    std::cout << player_one_pair * 100 << "%" << " player probability for one pair" << '\n';
    std::cout << player_two_pair * 100 << "%" << " player probability for two pair" << '\n';
    std::cout << player_triple * 100 << "%" << " player probability for triple" << '\n';

    
    for (int j = 0; j < number_of_opponents; ++j) {
        for (int j = 0; j < 2; j++) { std::cout << '\n'; }
        std::vector <std::vector <Hand >> player_vector;
        player_vector.push_back(playerhand);
        for(int i = 0; i < number_of_opponents; ++i) {
            if(i != j) {
                player_vector.push_back(opponents.at(i));
            }
        }
        std::cout << probability_straight(opponents.at(j), floor, cards) * 100 << "%" << " for opponent number "<<  j+1 << " probability for straight" << '\n';
        std::cout << probability_straight_flush(opponents.at(j), floor, cards) * 100 << "%" << " for opponent number " << j + 1 << " probability for straight-flush" << '\n';
        std::cout << probability_flush(opponents.at(j), floor, cards) * 100 << "%" << " for opponent number " << j + 1 << " probability for flush" << '\n';
        std::cout << probability_high_card(opponents.at(j),player_vector , floor, cards) * 100 << "%" << " for opponent number " << j + 1 << " probability for higher card" << '\n';
        std::cout << probability_one_pair(opponents.at(j), floor, cards) * 100 << "%" << " for opponent number " << j + 1 << " probability for one pair" << '\n';
        std::cout << probability_two_pair(opponents.at(j), floor, cards) * 100 << "%" << " for opponent number " << j + 1 << " probability for two pair" << '\n';
        std::cout << probability_triple(opponents.at(j), floor, cards) * 100 << "%" << " for opponent number " << j + 1 << " probability for triple" << '\n';
    }

    return 0;
}