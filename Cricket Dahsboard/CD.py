class Players:
    def __init__(self, Position, balls, runs, fours, sixes, player_id):
        self.id = player_id
        self.Position = Position
        self.balls = balls
        self.runs = runs
        self.fours = fours
        self.sixes = sixes

    def set_runs(self, Runs):
        self.runs += Runs
        if Runs == 6:
            self.sixes += 1
        if Runs == 4:
            self.fours += 1

    def played_balls(self):
        self.balls += 1

    def get_runs(self):
        return self.runs

    def get_played_balls(self):
        return self.balls

    def get_id(self):
        return self.id

    def get_sixes(self):
        return self.sixes

    def get_fours(self):
        return self.fours

    def get_position(self):
        return self.Position


class Cricket:
    def __init__(self, players, overs):
        self.players = players
        self.overs = overs

    def print_score_card(self, players, score, over, balls, p1, p2, wickets):
        print("Name Runs Balls 4's 6's")
        for player in players:
            print(player.get_id(), '*' if player.get_id() == p1 or player.get_id() == p2 else ' ',
                  player.get_runs(), player.get_played_balls(), player.get_fours(), player.get_sixes())

        print(f"Score: {score}/{wickets}")
        if balls == 0:
            print(f"Overs: {over}")
        else:
            print(f"Overs: {over}.{balls}")

    def innings(self):
        Score = 0
        team = []
        score_card = []

        lineup = list(map(int, input("Enter Batting line up: ").split()))

        for i, player_id in enumerate(lineup):
            team.append(Players(i, 0, 0, 0, 0, player_id))
            score_card.append(Players(i, 0, 0, 0, 0, player_id))

        p1 = team.pop(0)
        p2 = team.pop(0)

        on_strike = p1
        wickets = 0

        for i in range(1, self.overs + 1):
            balls = 6

            while balls > 0:
                run_on_this_ball = input("Run on this ball: ")

                if run_on_this_ball in "0123456":
                    val = int(run_on_this_ball)
                    on_strike.set_runs(val)
                    on_strike.played_balls()
                    Score += val

                    if on_strike.get_id() == p1.get_id():
                        p1 = on_strike
                        on_strike = p2 if val % 2 else on_strike
                    else:
                        p2 = on_strike
                        on_strike = p1 if val % 2 else on_strike

                    balls -= 1

                elif run_on_this_ball == "W":
                    wickets += 1
                    on_strike.played_balls()
                    score_card[on_strike.get_position()] = on_strike

                    if on_strike.get_id() == p1.get_id():
                        if team:
                            p1 = team.pop(0)
                            on_strike = p1
                        else:
                            score_card[p2.get_position()] = on_strike
                            self.print_score_card(score_card, Score, i, (6 - balls) + 1, p2.get_position(), -1, wickets)
                            return Score, wickets

                    else:
                        if team:
                            p2 = team.pop(0)
                            on_strike = p2
                        else:
                            score_card[p1.get_position()] = on_strike
                            self.print_score_card(score_card, Score, i, (6 - balls) + 1, p1.get_position(), -1, wickets)
                            return Score, wickets

                    balls -= 1

                elif run_on_this_ball == "WD":
                    Score += 1

                print(f"Score: {Score} - {wickets}")

            if on_strike.get_id() == p1.get_id():
                p1 = on_strike
                on_strike = p2
            else:
                p2 = on_strike
                on_strike = p1

            score_card[p1.get_position()] = p1
            score_card[p2.get_position()] = p2
            self.print_score_card(score_card, Score, i, 0, p1.get_position(), p2.get_position(), wickets)

        return Score, wickets


if __name__ == "__main__":
    test_case = int(input("Test Cases: "))

    while test_case > 0:
        overs = int(input("Overs: "))
        players = int(input("Players in each team: "))

        match = Cricket(players, overs)
        team1_score, team1_wickets = match.innings()
        team2_score, team2_wickets = match.innings()

        if team1_score > team2_score:
            print("Team 1 won the match")
        else:
            print("Team 2 won the match")

        test_case -= 1
