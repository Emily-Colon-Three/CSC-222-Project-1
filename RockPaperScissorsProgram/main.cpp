#include <iostream>
#include <random>

using namespace std;

const int QUIT = 4;
const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

int getUserInput();

void updateScores(int&, int&, int);

int determineWinner(int);

void finalResults(int, int);

int main()
{
    int humanScore = 0;
    int cpuScore = 0;

    int playerChoice;

    bool gameEnded = false;

    do {
            playerChoice = getUserInput();

            if (playerChoice != 4) // No need to determine outcomes and add to score when player quits
            {
                updateScores(humanScore, cpuScore, playerChoice); // Updates scores by simulating a round between the player's move and a computer's random one.
            }
            else
            {
                gameEnded = true; // Game will end
            }

    } while (gameEnded == 0);

    cout << humanScore << endl;
    cout << cpuScore << endl;

    return 0;
}

/*
    Summary: Prompts user for a choice between four options, returning their input if it is valid (between 1 and 4). If not, the user is asked again to give input.
    Parameters: None
    Return: integer between 1 and 4 representing user choice
    Preconditions: None
    Postconditions: Console will be printed to for prompting, and the input buffer will be used. Output will be limited only to valid inputs.
*/
int getUserInput()
{
    int input;
    bool valid = false;

    cout << "Choose from the following options:\n";
    cout << "1. Rock\n";
    cout << "2. Paper\n";
    cout << "3. Scissors\n";
    cout << "4. Quit\n";

    do {
        cin >> input;

        if (input >= 1 && input <= 4)
        {
            valid = true;
        }
        else
        {
            valid = false;
            cout << "ERROR: Invalid Input. Please Try Again.\n"; // Error message for invalid inputs
        }

    } while (!valid);

    return input;
}

/*
    Summary: Using references to the human and computer scores, along with the integer value for the player's choice, scores are updated.
    Parameters: Reference to human score (integer), &hs, reference to computer score (also integer), &cs, integer variable for the player's choice.
    Return: None
    Preconditions: choice MUST be valid (between 1 and 3), both referenced scores should be accurate.
    Postconditions: The referenced human score and computer score will be updated to reflect the outcome of a round. determineWinner() is called.
*/
void updateScores(int &hs, int &cs, int choice)
{
    int outcome = determineWinner(choice);

    if (outcome == 1) // Human player wins
    {
        hs += 1; // Human point
    }
    else if (outcome == 2)
    {
        cs += 1; // CPU point
    }
    else
    {
        return; // No points
    }
}

/*
    Summary: Takes the move made by a player, then compares it to a randomly generated CPU move. An integer is returned to indicate the outcome of the round.
    Parameters: integer variable for the human player's move, which is 1 for rock, 2 for paper, and 3 for scissors.
    Return: 0 is returned for a draw, 1 for a human victory, and 2 for a CPU victory.
    Preconditions: The input MUST be valid, between 1 and 3, for this function to work properly. Additionally, random library is used for number generation.
    Postconditions: A random number will have been generated with <random>, and the variables for the random engine and device remain static.
*/
int determineWinner(int humanMove)
{
    static random_device cpu;
    static mt19937 engine(cpu());

    uniform_int_distribution<int> dist(1, 3);

    int cpuMove = dist(engine);

    if (humanMove == cpuMove)
    {
        return 0; // Draw
    }
    else if ((humanMove == ROCK && cpuMove == SCISSORS) || (humanMove == PAPER && cpuMove == ROCK) || (humanMove == SCISSORS && cpuMove == PAPER))
    {
        return 1; // Human win
    }
    else // If it's not a draw and the human player hasn't won, it leaves only bot victory as the outcome
    {
        return 2; // CPU win
    }
}
