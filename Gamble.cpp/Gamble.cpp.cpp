#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Game {
private:
    int lossCount;
    int token;
    double baseWinRate;
    double maxWinRate;

public:
    // 생성자: 초기 값 설정
    Game() : lossCount(0), token(10000), baseWinRate(0.43), maxWinRate(0.9) {}

    // 메뉴 표시
    void showMenu() {
        cout << "\n===== Game Menu =====" << endl;
        cout << "1. Bet (도박하기)" << endl;
        cout << "2. Mine Tokens (채굴하기)" << endl;
        cout << "3. Exit (게임 종료)" << endl;
        cout << "Choose an option: ";
    }

    // 사용자가 배팅할 금액 입력
    int betMoney() {
        int betting;
        cout << "You have " << token << " tokens" << endl;
        cout << "Enter the bet money: ";
        cin >> betting;

        if (betting == 0) return 0;
        while (betting > token) {
            cout << "Money is not enough. Enter again: ";
            cin >> betting;
        }

        return betting;
    }

    // 도박 플레이
    void playGame() {
        int betting = betMoney();
        if (betting == 0) {
            cout << "Game over!" << endl;
            exit(0);
        }

        double winProbability = baseWinRate;
        double seed = (double)rand() / RAND_MAX;
        bool checkWin = seed < winProbability;

        if (checkWin) {
            double rewardSeed = (double)rand() / RAND_MAX;
            int multiplier = (rewardSeed >= 0.97) ? 5 : (rewardSeed >= 0.87) ? 3 : 2;
            token += betting * multiplier;

            baseWinRate = 0.43;  // 승률 초기화
            lossCount = 0;

            cout << "You win! Multiplier: " << multiplier << "x\n";
            cout << "You now have " << token << " tokens" << endl;
        }
        else {
            token -= betting;
            lossCount++;

            double randomIncrease = 0.0035 + (double)(rand() % 13) / 1000.0;
            baseWinRate += randomIncrease;
            if (baseWinRate > maxWinRate) baseWinRate = maxWinRate;

            cout << "You lose... You now have " << token << " tokens" << endl;
            cout << "Your win probability has increased by " << randomIncrease * 100 << "%p" << endl;
            cout << "New win probability: " << baseWinRate * 100 << "%\n";

            if (token <= 0) {
                cout << "You have no tokens left! Game over!" << endl;
                exit(0);
            }
        }
    }

    // 채굴 시스템 추가
    void mineTokens() {
        int minedAmount = rand() % 100 + 1;
        cout << "You mined " << minedAmount << " tokens!" << endl;
        token += minedAmount;
    }
};

int main() {
    srand(time(0)); // 랜덤 시드 설정
    Game game;

    while (true) {
        game.showMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            game.playGame();
        }
        else if (choice == 2) {
            game.mineTokens();
        }
        else if (choice == 3) {
            cout << "Exiting game. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please enter again." << endl;
        }
    }

    return 0;
}
