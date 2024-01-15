#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Players
{

private:
    int Position, balls, runs, fours, sixes;

    int id;

public:
    Players(int Position, int balls, int runs, int fours, int sixes, int id)
    {
        this->id = id;
        this->Position = Position;
        this->balls = balls;
        this->runs = runs;
        this->fours = fours;
        this->sixes = sixes;
    }
    void setRuns(int Runs)
    {
        runs += Runs;
        if (Runs == 6)
            sixes++;
        if (Runs == 4)
            fours++;
    }

    void PlayedBalls()
    {
        balls++;
    }

    int getruns()
    {
        return runs;
    }

    int getPlayedballs()
    {
        return balls;
    }

    int getid()
    {
        return id;
    }

    int getsixes()
    {
        return sixes;
    }

    int getfours()
    {
        return fours;
    }

    int getposition()
    {
        return Position;
    }
};

class Cricket
{
    int players;
    int Overs;

public:
    Cricket(int players, int Overs)
    {
        this->players = players;
        this->Overs = Overs;
    }
    void PrintScoreCard(vector<Players> palyers, int score, int over, int balls, int p1, int p2, int wickets)
    {
        cout << "Name"
             << " "
             << "Runs"
             << " "
             << "Balls"
             << " "
             << "4's"
             << " "
             << "6's" << endl;
        for (int i = 0; i < palyers.size(); i++)
        {
            Players Item = palyers[i];
            cout << Item.getid();

            if (Item.getid() == p1 || Item.getid() == p2)
            {
                cout << "*"
                     << "  "; // On_strike
            }
            else
            {
                cout << "    ";
            }

            cout << "  " << Item.getruns() << "   " << Item.getPlayedballs() << "     " << Item.getfours() << "    " << Item.getsixes() << endl;
        }

        cout << "Score:" << score << "/" << wickets << endl;
        if (balls == 0)
        {
            cout << "Overs:" << over << endl;
        }
        else
        {
            cout << "Overs" << over << "." << balls << endl;
        }
    }

    pair<long, int> innings()
    {
        long Score = 0;
        queue<Players> team; // Declaring queue of Players Object
        vector<Players> scoreCard;

        // set the batting line up of players
        vector<int> lineup(players);
        cout << "Enter Batting line up:"
             << " ";
        for (int i = 0; i < players; i++)
        {
            cin >> lineup[i];
        }

        for (int i = 0; i < lineup.size(); i++)
        {

            team.push(Players(i, 0, 0, 0, 0, lineup[i]));
            scoreCard.push_back(Players(i, 0, 0, 0, 0, lineup[i]));
        }

        Players p1 = team.front(); // Creating object of two player
        team.pop();
        Players p2 = team.front();
        team.pop();

        Players On_Strike = p1; // creating object for striker end batsman for updaing the score.
        int Wickets = 0;
        for (int i = 1; i <= Overs; i++)
        {

            int balls = 6;

            while (balls > 0)
            {
                string run_on_this_ball;
                cout << "run_on_this_ball"
                     << " - ";
                cin >> run_on_this_ball;
                string runs = "0123456";

                if (runs.find(run_on_this_ball) != string::npos)
                {
                    long long val = stoi(run_on_this_ball);

                    On_Strike.setRuns(val);
                    On_Strike.PlayedBalls();
                    Score += val;

                    if (On_Strike.getid() == p1.getid())
                    {
                        p1 = On_Strike;

                        if (val % 2)
                            On_Strike = p2;
                    }
                    else
                    {
                        p2 = On_Strike;
                        if (val % 2)
                            On_Strike = p1;
                    }
                    balls--;
                }
                else if (run_on_this_ball == "W")
                {
                    Wickets++;
                    On_Strike.PlayedBalls();
                    scoreCard[On_Strike.getposition()] = On_Strike; // storing all the details for who got out in vector
                    if (On_Strike.getid() == p1.getid())
                    {
                        if (!team.empty())
                        {
                            p1 = team.front(); // new batsmam always takes strike.
                            team.pop();
                            On_Strike = p1;
                        }
                        // if team got all out
                        else
                        {

                            scoreCard[p2.getposition()] = On_Strike; // storing non striker batsam details;
                            PrintScoreCard(scoreCard, Score, i, (6 - balls) + 1, p2.getposition(), -1, Wickets);
                            return {Score, Wickets};
                        }
                    }
                    else
                    {
                        if (!team.empty())
                        {
                            p2 = team.front(); // new batsmam coming out on striker end
                            team.pop();
                            On_Strike = p2; // new batsman alwasy take strike
                        }
                        // if team got all out
                        else
                        {

                            scoreCard[p1.getposition()] = On_Strike; // storing non striker batsam details;
                            PrintScoreCard(scoreCard, Score, i, (6 - balls) + 1, p1.getposition(), -1, Wickets);
                            return {Score, Wickets};
                        }
                    }
                    balls--;
                }
                else if (run_on_this_ball == "WD")
                {
                    Score++;
                }
                cout << "Score:" << Score << "-" << Wickets << endl;
            }
            // Rotating the strike after an over
            if (On_Strike.getid() == p1.getid())
            {
                p1 = On_Strike;
                On_Strike = p2;
            }
            else
            {
                p2 = On_Strike;
                On_Strike = p1;
            }
            cout << "Over Completed:" << endl;
            scoreCard[p1.getposition()] = p1;
            scoreCard[p2.getposition()] = p2;
            PrintScoreCard(scoreCard, Score, i, 0, p1.getposition(), p2.getposition(), Wickets);
        }

        return {Score, Wickets};
    }
};

int main()
{

    int test_case;
    cout << "Test_Cases:-";
    cin >> test_case;

    while (test_case--)
    {

        int Overs, players;

        cout << "Overs"
             << ":";
        cin >> Overs;

        cout << "Players in each team"
             << ":";
        cin >> players;

        Cricket match(players, Overs);

        pair<long, int> team1 = match.innings();
        pair<long, int> team2 = match.innings();

        if (team1.first > team2.first)
        {
            cout << "team1 won the match";
        }
        else
        {
            cout << "team2 won the match";
        }
    }
};