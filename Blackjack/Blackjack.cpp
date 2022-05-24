#include "Blackjack.h"

Card givePlayerCardFromDealer(Player p, Dealer d) {
	Card c = d.removeCard();
	p.addCard(c);
	return c;
}

void dealCards(Dealer d, Player p) {

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

int dealerTurn(Dealer d) {
	Card firstDealerCard = d.giveCardToDealer();
	Card secondDealerCard = d.giveCardToDealer();
	std::cout << "The dealer's first card is the ";
	firstDealerCard.readCard();
	std::cout << "The dealer's second card is the ";
	secondDealerCard.readCard();
	return d.getSum();
}

bool determineGame(int dealerSum, int playerSum) {

}

void beginSinglePlayer() {
	Dealer d(10);
	float money = 50.00;
	Player p(money);
	while (p.getMoney() > 0) {
		Card firstPlayerCard = givePlayerCardFromDealer
		bool isIn = true;
		while (isIn) {
			std::cout << "Would you like to hit or stay?" << std::endl;
			std::string hitOrStay;
			std::cin >> hitOrStay;
			if (hitOrStay == "Hit") {
				Card nextCard = givePlayerCardFromDealer(p, d);
				std::cout << "The next card is the ";
				nextCard.readCard();
				if (p.getSum() > 21) {
					std::cout << "Busted!" << std::endl;
					isIn = false;
				}
				else {
					displaySum(p);
				}
			}
			else if (hitOrStay == "Stay") {
				int dealerSum = dealerTurn(d);
				if (determineGame(dealerSum, p.getSum())) {

				}
			}
		}
	}
}

void beginMultiPlayer() {

}

int main() {
	std::cout << "Welcome To Blackjack!" << std::endl;
	std::cout << "Please select an option: " << std::endl;
	std::cout << "1. Single Player" << std::endl;
	std::cout << "2. Multiplayer" << std::endl;
	std::string firstOption;
	std::cin >> firstOption;
	if (firstOption == "1") {
		beginSinglePlayer();
	}
	else if (firstOption == "2") {
		beginMultiPlayer();
	}
	else {

	}
	return 0; 
}
