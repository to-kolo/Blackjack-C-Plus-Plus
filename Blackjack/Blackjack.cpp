#include "Blackjack.h"

void beginGame(int numOfPlayers) {
    Player* players = new Player[numOfPlayers];
	Dealer d = Dealer();
    bool isStillPlaying = true;
	while (isStillPlaying) {
        Card firstCard = dealCards(d, players, numOfPlayers, 17);
        for (int i = 0; i < numOfPlayers; i++) {
			std::cout << "It is now Player " << i + 1 << "'s turn.\n";
			std::cout << "The dealer's face up card is the ";
			firstCard.readCard();
            players[i].readHand(i + 1);
			displaySum(players[i]);			
			bool doneWithTurn = false;
            while ((players[i].getSum() <= 21 || players[i].getAceSum() <= 21) && !doneWithTurn) {
				if (players[i].getSum() == 21 || players[i].getAceSum() == 21) {
					std::cout << "Blackjack! You win!\n";
					doneWithTurn = true;
					players[i].isIn = false;
				}
				else {
			    	std::cout << "Would you like to hit or stand?" << std::endl;
			    	std::string hitOrStand;
			    	std::cin >> hitOrStand;
			    	if (hitOrStand == "Hit") {
				    	Card nextCard = givePlayerCardFromDealer(players[i], d);
				    	std::cout << "The next card is the ";
				    	nextCard.readCard();
				    	if (players[i].getSum() > 21 && players[i].getAceSum() == 0 || players[i].getSum() > 21 && players[i].getAceSum() > 21) {
							std::cout << "Busted!" << std::endl;
							players[i].isIn = false;
							doneWithTurn = true;
				    	}
						else if (players[i].getSum() == 21) {
							std::cout << "Blackjack! You win!\n";
							players[i].isIn = false;
							doneWithTurn = true;
						}
				    	else {
					    	displaySum(players[i]);
				    	}
			    	}
			    	else if (hitOrStand == "Stand") {
						doneWithTurn = true;
					}
				}
		    }
        }
		bool dealerCondition = d.performDealerTurn();
		if (dealerCondition) {
			for (int i = 0; i < numOfPlayers; i++) {
				if (players[i].isIn && ((players[i].getAceSum() > d.getAceSum()) || (players[i].getSum() > d.getSum()))) {
					std::cout << "Player " << i + 1 << " has won! Their bid is doubled!" << std::endl;
					//TODO: Increase their bid here.
				}
				else if (players[i].isIn && ((players[i].getAceSum() < d.getAceSum()) || (players[i].getSum() < d.getSum()))) {
					std::cout << "Too Bad! Player " << i + 1 << " has lost!\n";
				}
			}
		}
		else {
			std::cout << "Everyone who didn't break wins!\n";
		}
		std::cout << "Would you like to play again? (Type No or N to quit)";
		std::string playAgain;
		std::cin >> playAgain;
		if (playAgain == "N" || playAgain == "No") {
			isStillPlaying = false;
		}
		else {
			for (int i = 0; i < numOfPlayers; i++) {
				players[i].reset();
			}
			d.reset();
		}
	}
    delete[] players;
}

int main() {
	std::cout << "Welcome To Blackjack!" << std::endl;
	std::cout << "Please select an option: " << std::endl;
	std::cout << "1. Single Player" << std::endl;
	std::cout << "2. Multiplayer" << std::endl;
	std::string firstOption;
	std::cin >> firstOption;
	int numOfPlayers;
	if (firstOption == "1") {
		numOfPlayers = 1;
		std::cout << " \n";
    	beginGame(numOfPlayers);
	}
	else if (firstOption == "2") {
		std::cout << "Please enter the number of players: " << std::endl;
		std::string stringOfPlayers;
		std::cin >> stringOfPlayers;
        numOfPlayers = std::stoi(stringOfPlayers);
		std::cout << " \n";
        beginGame(numOfPlayers);
	}
	return 0; 
}