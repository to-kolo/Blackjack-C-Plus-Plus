// Blackjack.h : Include file for standard system include files,
// or project specific include files.

#include <iostream>
#include <queue>
#include <array>
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

class Dealer : public Player {
	std::queue<Card> deck;
	std::queue<Card> hands;
	public:
		Card giveCardToDealer() {
			Card c = this->removeCard();
			this->addCard(c);
			return c;
		}

		Card removeCard() {
			Card c = deck.front();
			deck.pop();
			return c;
		}

		Dealer(int seed) {
			std::array<Card, 312> cards;
			std::string cardNums[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
			"Nine", "Ten", "Jack", "Queen", "King", "Ace"};
			std::string suits[] = { "Hearts", "Spades", "Diamonds", "Clubs" };
			int i = 0;
			for (int index = 0; i < 6; i++) {
				for (std::string suit : suits) {
					for (std::string num : cardNums) {
						Card c(suit, num);
						cards[i++] = c;
					}
				}
			}
			std::shuffle(cards.begin(), cards.end(), seed);
			std::queue<Card> deck;
			for (int j = 0; j < cards.size(); j++) {
				Card c = cards[i];
				deck.push(c);
			}
			this->deck = deck;
		}
};

class Player {
	int sum;
	int aceSum;
	float money;
	bool isIn;
	std::queue<Card> hand;

	public:
		Player(float money) {
			this->sum = 0;
			this->money = money;
			this->isIn = true;
			this->hand = std::queue<Card>();
			this->aceSum = 0;
		}
		
		Player() {
			this->sum = 0;
			this->money = 0;
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

		bool getStatus() {
			return this->isIn;
		}

		Card getCard() {
			Card c = hand.front();
			hand.pop();
			return c;
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

};
