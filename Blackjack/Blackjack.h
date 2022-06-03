// Blackjack.h : Include file for standard system include files,
// or project specific include files.

#include <iostream>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>
/// <summary>
///		Converts the card number into an int for scoring.
/// </summary>
/// <param name="num"></param>
/// <returns>the resulting int value for scoring</returns>
int cardToInt(std::string num) {
	
	if (num == "Two") return 2;
	else if (num == "Three") return 3;
	else if (num == "Four") return 4;
	else if (num == "Five") return 5;
	else if (num == "Six") return 6;
	else if (num == "Seven") return 7;
	else if (num == "Eight") return 8;
	else if (num == "Nine") return 9;
	else if (num == "Ten") return 10;
	else if (num == "Jack") return 10;
	else if (num == "Queen") return 10;
	else if (num == "King") return 10;
	else {
		return 0;
	}
}

class Card {
	std::string suit;
	std::string cardNumber;

	public:
		Card(std::string suit, std::string cardNumber) {
			this->suit = suit;
			this->cardNumber = cardNumber;
		}

		Card() {}
		/// <summary>
		/// Retrieves the suit.
		/// </summary>
		/// <returns>the suit</returns>
		std::string getSuit() {
			return this->suit;
		}
		/// <summary>
		///	Retrieves the cardNumber.
		/// </summary>
		/// <returns>the card number</returns>
		std::string getCardNumber() {
			return this->cardNumber;
		}

		void readCard() {
			std::cout << this->cardNumber << " of " << this->suit << "\n";
		}
};

class Player {
	int sum;
	int aceSum;
	float money;

	public:
        bool isIn;
		std::queue<Card> hand;

		Player(float money) {
			this->sum = 0;
			this->money = money;
			this->isIn = true;
			this->hand = std::queue<Card>();
			this->aceSum = 0;
		}
		
		Player() {
			this->sum = 0;
			this->money = 500;
			this->hand = std::queue<Card>();
			this->aceSum = 0;
		}

		int getSum() {
			return this->sum;
		}

		int getAceSum() {
			return this->aceSum;
		}

		float getMoney() {
			return this->money;
		}

		Card getCard() {
			Card c = hand.front();
			hand.pop();
			return c;
		}

		void reset() {
			while (!this->hand.empty()) {
				this->hand.pop();
			}
			this->sum = 0;
			this->aceSum = 0;
		}

		void addCard(Card c) {
			this->hand.push(c);
			if (c.getCardNumber() != "Ace") {
				int amount = cardToInt(c.getCardNumber());
				this->sum += amount;
			}
			else {
				this->aceSum = this->sum + 1;
				this->sum += 10;
			}
			
		}

        void readHand(int playerIndex) {
            Card c = this->getCard();
            std::cout << "The first card of Player " << playerIndex << " is the ";
            c.readCard();
			this->hand.push(c);
            c = this->getCard();
            std::cout << "The second card of Player " << playerIndex << " is the ";
            c.readCard();
			this->hand.push(c);
        }

};

class Dealer : public Player {
	std::queue<Card> deck;
	public:
		Card giveCardToDealer() {
			Card c = this->removeCard();
			this->addCard(c);
			return c;
		}

		Card removeCard() {
			Card c = this->deck.front();
			this->deck.pop();
			return c;
		}

		Dealer() {
			std::default_random_engine engine;
			//Grabs a seed based off of ms from Jan 1 1970.
			engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
			std::vector<Card> cards;
			const std::string cardNums[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
			"Nine", "Ten", "Jack", "Queen", "King", "Ace"};
			const std::string suits[] = { "Hearts", "Spades", "Diamonds", "Clubs" };
			for (int i = 0; i < 6; i++) {
				for (std::string suit : suits) {
					for (std::string num : cardNums) {
						Card c(suit, num);
						cards.push_back(c);
					}
				}
			}
			std::shuffle(cards.begin(), cards.end(), engine);
			std::queue<Card> deck;
			for (int i = 0; i < cards.size(); i++) {
				Card c = cards[i];
				deck.push(c);
			}
			this->deck = deck;
		}

		bool performDealerTurn() {
			bool dealerCondition;
			int i = 1;
			while (!this->hand.empty()) {
				Card c = this->hand.front();
				this->hand.pop();
				std::cout << "Card Number " << i++ << " of the dealer is the ";
				c.readCard(); 
			}
			if ((this->getAceSum() > 21 && this->getSum() > 21) || (this->getAceSum() == 0 && this->getSum() > 21)) {
				std::cout << "The dealer's sum is " << this->getSum() << " / " << this->getAceSum() << std::endl;
				std::cout << "The dealer lost!\n";
				dealerCondition = false;
			}
			else if (this->getAceSum() < 21 && this->getSum() > 21) {
				std::cout << "The dealer's sum is " << this->getAceSum() << std::endl;
				dealerCondition = true;
			}
			else {
				std::cout << "The dealer's sum is " << this->getSum() << " / " << this->getAceSum() << std::endl;
				dealerCondition = true;
			}

			return dealerCondition;
		}
};

Card givePlayerCardFromDealer(Player &p, Dealer &d) {
	Card c = d.removeCard();
	p.addCard(c);
	return c;
}

Card dealCards(Dealer &d, Player* &players, int numOfPlayers, int softCap) {
	Card c;
	for (int i = 0; i < 2; i++) {
        for (int j = 0; j < numOfPlayers; j++) {
            givePlayerCardFromDealer(players[j], d);
        }
		if (i == 0) {
			c = d.giveCardToDealer();
		}
		else {
			d.giveCardToDealer();
		}
    }
    while (d.getSum() <= softCap && d.getAceSum() <= softCap) {
        d.giveCardToDealer();
	}
	return c;
}

void displaySum(Player p) {
	std::cout << "Sum: ";
	if (p.getAceSum() > 0) {
		std::cout << p.getAceSum() << "/" << p.getSum() << std::endl;
	}
	else {
		std::cout << p.getSum() << std::endl;
	}
}

