#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <random>

struct Card
{
    int value1, value2, sum, extraCardValue;
};

enum Decision { BANKER = 1, PLAYER = 2 };
enum Result { BANKER_WIN = 1, PLAYER_WIN = 2, DRAW = 3 };

void printCard(Card& card, bool isNaturalWin);
bool playAgain(char x, int money);
Result determineWinner(int bankerSum, int playerSum);
int declareOutcome(Result winner, Decision decision, int bet);
Card drawCard();

int main() 
{
    std::system("Color 2F");
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::string name;
    int bet, prize, money = 10000;
    Decision decision;
    char play;
    bool continuePlaying = true;

    std::cout << "==============================" << std::endl;
    std::cout << "To Start, please enter your name" << std::endl;
    getline(std::cin, name);
    std::cout << "\nGood evening, " << name << std::endl;
    std::cout << "==============================\n\n";
    std::cout << "WELCOME TO VIRTUAL BACCARAT TABLE" << std::endl;
    std::cout << "=================================" << std::endl;

    do 
    {
        std::cout << "Current balance, PHP " << money << std::endl;
        std::cout << "1-BANKER \n2-PLAYER \nChoose your bet ";

        int userInput;
        std::cin >> userInput;

        while (!std::cin || userInput < BANKER || userInput > PLAYER) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter 1 for BANKER or 2 for PLAYER:";
            std::cin >> userInput;
        }

        Decision decision = static_cast<Decision>(userInput);

        do 
        {
            std::cout << "Place your bet, PHP: ";
            std::cin >> bet;

            if (std::cin.fail() || bet <= 0 || bet > money) 
            {
                std::cout << "Invalid input. Please enter a positive number not exceeding your balance." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (std::cin.fail() || bet <= 0 || bet > money);


        Card banker = drawCard();
        printCard(banker, banker.sum == 8 || banker.sum == 9);

        Card player = drawCard();
        printCard(player, player.sum == 8 || player.sum == 9);

        Result winner = determineWinner(banker.sum, player.sum);
        prize = declareOutcome(winner, decision, bet);
        std::cout << "PHP " << prize << std::endl;
        money += prize;
        std::cout << "Current Money, PHP " << money << "\n\n";

        std::cout << "PLAY AGAIN? Y/N ";
        std::cin >> play;
        continuePlaying = playAgain(play, money);

    } while (continuePlaying);

    return 0;
}

void printCard(Card& card, bool isNaturalWin) 
{
    std::cout << "=======\n|     |\n|  " << card.sum << "  |\n|     |\n=======" << "\n";
    std::cout << "First Card " << card.value1 << "\nSecond Card " << card.value2 << "\n";

    if (isNaturalWin) 
    {
        std::cout << "This is a natural win 8/9 \n";
    }
    else 
    {
        std::cout << "Extra Card " << card.extraCardValue << "\n";
    }
}

bool playAgain(char x, int money) 
{
    if (money <= 0) 
    {
        std::cout << "Insufficient fund!";
        return false;
    }

    if (x == 'Y' || x == 'y') 
    {
        return true;
    }
    else if (x == 'N' || x == 'n') 
    {
        std::cout << "THANK YOU FOR PLAYING!";
        return false;
    }

    return false;
}

Result determineWinner(int bankerSum, int playerSum) 
{
    std::cout << "\n==================================\n";
    if (bankerSum > playerSum) 
    {
        std::cout << "\nBANKER WIN, ";
        return BANKER_WIN;
    }
    else if (bankerSum < playerSum) 
    {
        std::cout << "\nPLAYER WIN, ";
        return PLAYER_WIN;
    }
    else 
    {
        std::cout << "\nDRAW, ";
        return DRAW;
    }
}

int declareOutcome(Result winner, Decision decision, int bet) 
{
    if (static_cast<int>(winner) == static_cast<int>(decision) || winner == DRAW) 
    {
        std::cout << (winner == DRAW ? "Tie Game!\n" : "YOU WIN!\n");
        return (winner == DRAW ? 0 : bet);
    }
    else 
    {
        std::cout << "YOU LOSE!\n";
        return -bet;
    }
}

Card drawCard() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    Card card;
    card.value1 = dis(gen);
    card.value2 = dis(gen);
    card.sum = (card.value1 + card.value2) % 10;

    if (card.sum != 8 && card.sum != 9) 
    {
        card.extraCardValue = dis(gen);
        card.sum = (card.sum + card.extraCardValue) % 10;
    }

    return card;
}