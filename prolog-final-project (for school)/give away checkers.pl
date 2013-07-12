/*
--------------------------------------------------------------------   
File Name: "give away checkers.pl"
Description:  The program plays give-away checkers with the user,
	      according to the rules in the attached document.
Synopsis:     Move the attached pictures to pl->xpce->bitmaps.
              Write "play." and press enter, in the command line.

	      For more explanation, see tne attached document.
--------------------------------------------------------------------
*/
% start_again(window)/1
% start_again: starts a new game.
start_again(Window):-
	new(D,dialog('Give-Away Checkers')),
	send_list(D,append,
                      [
		       text('Do you want to play again?'),
		       button(yes,and(message(D,destroy),message(Window,destroy),message(@prolog,
				 play)
				 )),
		       button(no,and(
				 message(D,destroy),message(Window,destroy)))
		      ]),
	send(D,open).

% play/0
% play: plays the game.
play:-
	new(D,dialog('Give-Away Checkers')),
	send_list(D,append,
                      [
		       text('choose level:'),
		       button(beginner,and(message(D,destroy),message(@prolog,
				 initial_state,1)
				 )),
		       button(intermediate,and(message(D,destroy),message(@prolog,
				 initial_state,3)
				)),
		       button(expert,and(message(D,destroy),message(@prolog,
				 initial_state,5)
				 ))
		  ]),
	send(D,open).

% initial_state(level)/1
% initial_state: builds the initial state for the game with the given level.
initial_state(Level):-
	new(Window, window('Give-away Checkers', size(8*50, 8*50))),
        new(B,bitmap('background.bmp')),
	send(Window, recogniser,
	     click_gesture(left, '', single,
			   message(@prolog, player_choose,
				   @event?position))),
	send(Window,background,B),
	initialise(StartState,First),
	build(Window,StartState,First),
	send(Window, open),
	play_game(Window,StartState,First,Level).

% player_choose(point)/1
% player_choose: responses to every click of the player.
player_choose(Point):-
	% first meaningful press.
	locked(no),
	middle(no),
	options(0,[]),
	pos(Position,Window,_),
	point_to_place(Point,Place),
	find_moves(Place,Position,ListOfOptions),
	ListOfOptions \= [],!,
	player_first_choose(Position,Window,Place,ListOfOptions).

player_choose(Point):-
	% first press on eat option.
	locked(no),
	middle(eat),
	options(Place,List),
	point_to_place(Point,Place1),
	pos(Position,Window,Depth),
	member(Place1,List),!,
	retractall(middle(_)),
	assert(middle(eating)),
	eatOnce(Position,Place,Place1,Dir,NewPos),
	player_choose_eat(NewPos,Window,Place1,Dir,Depth).

player_choose(Point):-
	% already eating and choosed the next eating step.
	locked(no),
	middle(eating),
	options(Place,List),
	point_to_place(Point,Place1),
	pos(Position,Window,Depth),
	member(Place1,List),!,
	eatOnce(Position,Place,Place1,Dir,NewPos),
	player_choose_eat(NewPos,Window,Place1,Dir,Depth).

player_choose(_):-
	% already eating but choosed wrong.
	locked(no),
	middle(eating),
	!.

player_choose(Point):-
	% choosed to move.
	locked(no),
	middle(move),
	options(Place,List),
	point_to_place(Point,Place1),
	pos(Position,Window,Depth),
	member(Place1,List),!,
	moveAll(Position,Place,Place1,_,NewPos),
	build(Window,NewPos,player),
	retractall(locked(_)),
	assert(locked(yes)),
	reverse_position(NewPos, NextPosition),
	send(timer(0.1),delay),
	play_game(Window,NextPosition,computer,Depth).

player_choose(_):-
	% clicked wrong while moving or started to eat.
	locked(no),
	(middle(move);middle(eat);middle(no)),
	options(_,_),
	pos(Position,Window,_),!,
	build(Window,Position,player),
	retractall(middle(_)),
	retractall(options(_,_)),
	assert(middle(no)),
	assert(options(0,[])).

% player_first_choose(position,window,place,list_of_options)/4
% player_first_choose: responses to the first choose in every torn of the player.
player_first_choose(Position,Window,Place,ListOfOptions):-
	% must eat and press on eat option.
	eatPart(Position,_,_,_,_),
	middle(eat),!,
	update_for_player(1,ListOfOptions,Position,MarkedPos),
	retractall(options(_,_)),
	assert(options(Place,ListOfOptions)),
	build(Window,MarkedPos,player).

player_first_choose(Position,_,_,_):-
	% must eat but didnt press right.
	eatPart(Position,_,_,_,_),!,
	retractall(middle(_)),
        assert(middle(no)),
	new(Wr, dialog('wrong move')),
	send_list(Wr,append,text('you must eat when you have an option.')),
	send(Wr,open).


player_first_choose(Position,Window,Place,ListOfOptions):-
	% can move, and shows the options for the current click.
	update_for_player(1,ListOfOptions,Position,MarkedPos),
	retractall(options(_,_)),
	assert(options(Place,ListOfOptions)),
	build(Window,MarkedPos,player).

% player_choose_eat(position, window, place, direction, depth)/5
% player_choose_eat: responses to the player choose when he is in the middle of eating.

player_choose_eat(Position,Window,Place,Dir,Depth):-
	eatOnce(Position,Place,_,Dir2,_),
	not(opposite(Dir2,Dir)),!,
	findall(Next,(eatOnce(Position,Place,Next,Dir1,_),not(opposite(Dir1,Dir))),ListOfOptions),
	retractall(options(_,_)),
	retractall(pos(_,_,_)),
	assert(pos(Position,Window,Depth)),
	assert(options(Place,ListOfOptions)),
	update_for_player(1,ListOfOptions,Position,MarkedPos),
	build(Window,MarkedPos,player).

player_choose_eat(Position,Window,_,_,Depth):-
	build(Window,Position,player),
	reverse_position(Position, NextPosition),
	retractall(locked(_)),
	assert(locked(yes)),
	send(timer(0.1),delay),
	play_game(Window,NextPosition,computer,Depth).

% find_moves(place,position,List_of_optional_moves)/3
% find_moves: returns all optional moves to the player in the current situation.
find_moves(CurrentPlace,Position,ListOfOptions):-
	eatOnce(Position,CurrentPlace,_,_,_),
	retractall(middle(_)),
	assert(middle(eat)),
	findall(Next,eatOnce(Position,CurrentPlace,Next,_,_),ListOfOptions).

find_moves(CurrentPlace,Position,ListOfOptions):-
	moveAll(Position,CurrentPlace,_,_,_),!,
	findall(Next,moveAll(Position,CurrentPlace,Next,_,_),ListOfOptions),
	ListOfOptions \= [],!,
	retractall(middle(_)),
	assert(middle(move)).

find_moves(_,_,[]).

% play_game(window,position,player,depth)/4
% play_game: plays the game between the computer and the player.
play_game(Window,Position,Player,_):-
	game_won(Position),!,
	send(timer(1.0), delay),
	new(Win, dialog('')),
	send_list(Win,append,
		  [text(Player),
		   text('won!!!'),
		   button(ok,and(message(Win,destroy),message(@prolog,
							      start_again,Window)))]),
	send(Win,open).

play_game(Window,Position,player,Depth):-
	retractall(locked(yes)),!,
	retractall(pos(_,_,_)),
	retractall(middle(_)),
	retractall(options(_,_)),
	assert(middle(no)),
	assert(locked(no)),
	assert(options(0,[])),
	assert(pos(Position,Window,Depth)).

play_game(Window,Position,computer,Depth):-
	retractall(locked(no)),
	assert(locked(yes)),
	winning_move(Position,Move),!,
	send(timer(1.0),delay),
	show_move(Position,Window,Move,computer),
	reverse_position(Move, NextPosition),
	play_game(Window, NextPosition, player,Depth).

play_game(Window,Position,computer,Depth):-
	retractall(locked(no)),
	assert(locked(yes)),!,
	alpha_beta(Depth, Position, -32767, 32767, Move, _),
	send(timer(1.0),delay),
	show_move(Position,Window,Move,computer),
	reverse_position(Move, NextPosition),
	play_game(Window, NextPosition, player,Depth).

% update_for_player(place_for_update,list_of_updates,position,updated_position)/3
% update_for_player: updates the options for the player when he chooses a piece.
update_for_player(Num,Updates,[0|Position],[3|MarkedPos]):-
	place(Place,Num),
	member(Place,Updates),!,
	Num1 is Num+1,
	update_for_player(Num1,Updates,Position,MarkedPos).

update_for_player(Num,Updates,[A|Position],[A|MarkedPos]):-
	Num1 is Num+1,
	update_for_player(Num1,Updates,Position,MarkedPos),!.

update_for_player(33,_,[],[]).

% show_move(position,window,move,player)/4
% show_move: shows the move for the computer by steps.
show_move(Position,Window,Move,Player):-
	eatAll(Position,_,_,_, Move,List),
	build_by_steps(Window,Position,List,Player),!.

show_move(_,Window,Move,Player):-
	build(Window,Move,Player).


% build_by_steps(window,position,list_of_moves,player)
% build_by_steps: builds the board according to the list.
build_by_steps(Window,Position,[A|List],Player):-
	eatPart(Position,_,A,_,NewPos),
	build(Window,NewPos,Player),
	send(timer(0.8), delay),
	build_by_steps(Window,NewPos,List,Player),!.

build_by_steps(_,_,[],_).

% build(window,position,player)/3
% build: builds the board of the position.
build(Window,List,computer):-
	add_squares(Window,1,0,List).

build(Window,List,player):-
	reverse_position(List,Rev),
	add_squares(Window,1,0,Rev).

% add_squares(window,x_value,y_value,position)/4
% add_squares: builds the board of the position, square by square.
add_squares(_,_,8,_):-!.

add_squares(Window,X,Y,List):-
	X >= 8,
	Y1 is Y+1,
	Mod is Y mod 2,
        Mod == 0,!,
	add_squares(Window,0,Y1,List).

add_squares(Window,X,Y,List):-
	X >= 8,!,
	Y1 is Y+1,
	add_squares(Window,1,Y1,List).

add_squares(Window,X,Y,[I|List]):-!,
	color(Const),
	Val is Const*I,
	new(A, box(1*50, 1*50)),
	image_name(Val,Name),
	send(A,fill_pattern,Name),
	send(Window,display,A,point(X*50-1,Y*50-1)),
	X1 is X+2,
	add_squares(Window,X1,Y,List).

% winning_move(position,winning_move)/2
% winning_move: returns a winning move for the current move.
winning_move(Position,Move):-
	recommended_moves(Position, Moves),
	member(Move,Moves),
	reverse_position(Move,Rev),
	eatAll(Rev,_,_,_,End,_),
	reverse_position(End,RevEnd),
	game_won(RevEnd),!.

% alpha_beta(depth, position, alpha_value, beta_value, best_move, returned_value)/6
% alpha_beta: returns the best move for the current position, according to the alpha-beta algorithm.
alpha_beta(_, Position, _, _, Position, 10000):-
	game_won(Position), !.

alpha_beta(Depth, Position, Alpha, Beta, BestMove, Value):-
	Depth > 0,
	recommended_moves(Position, Moves),
	Moves = [_|_], !,
	% if there is recommended moves, and the depth is not zero, check next possible moves by calling best_move
	NewDepth is Depth - 1,
	Alpha1 is -Beta,
	Beta1 is -Alpha,
	best_move(Moves, Position, NewDepth, Alpha1, Beta1, [], BestMove, Value).

alpha_beta(_, Position, _, _, Position, Value):-
	% otherwise, return the value from the heuristic function.
	heuristic_function(Position, Value),!.

% best_move(recommended_moves, position, depth, alpha_value, beta_value, checked_move, best_Move, value_for_the_best_move)/8
% best_move: returns the best move for the current position, according to the alpha-beta algorithm, after reversing position.
best_move([Move|Moves],Position, Depth, Alpha, Beta, CheckedMove, BestMove, ValueOfBest):-
	reverse_position(Move, NewPosition),
	alpha_beta(Depth, NewPosition, Alpha, Beta, _, MinusValue),
	Value is -MinusValue,
	cut_off(Move, Value, Depth, Alpha, Beta, Moves, Position, CheckedMove, BestMove, ValueOfBest).

best_move([], _, _, Alpha, _, Move, Move, Alpha).

% cut_off(move, position, value, depth, alpha_value, beta_value, rest_moves, checked_move, best_Move, value_for_the_best_move)/10
% cut_off: returns the best move for the current position, according to the alpha-beta algorithm, after cut off.
cut_off(_, Value, Depth, Alpha, Beta, Moves, Position, CheckedMove, BestMove, ValueOfBest):-
	Value =< Alpha, !,
	best_move(Moves, Position, Depth, Alpha, Beta, CheckedMove, BestMove, ValueOfBest).
cut_off(Move, Value, Depth, _, Beta, Moves, Position, _, BestMove, ValueOfBest):-
	Value < Beta, !,
	% the new alpha is upgraded to value
	best_move(Moves, Position, Depth, Value, Beta, Move, BestMove, ValueOfBest).
cut_off(Move, Value, _, _, _, _, _, _, Move, Value):-!.

% initialise(initial_position,first_player)/2
% initialise: returns an optional initial state.
initialise([1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],computer):-
	retractall(color(_)),
	random(A),
	A<0.5,!,assert(color(1)).

initialise([1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],player):-
	assert(color(-1)).

% heuristic_function(position,value)/2
% heuristic_function: returns the heuristic value for current position.
heuristic_function(Position,10000):-
	game_won(Position),!.

heuristic_function(Position,Value):-
	count_pawns(Position,Pawns),
	findall(X,(moveAll(Position,Z,X,_,Next),reverse_position(Next,RevN),eatPart(RevN,Z,_,_,_)),GiveAwayMove),
	findall(M,(eatAll(Position,T,M,_,Next1,_),reverse_position(Next1,RevN1),eatPart(RevN1,T,_,_,_)),GiveAwayEat),
	findall(Y,eatPart(Position,_,Y,_,_),EatList),
	length(GiveAwayMove,GiveMoveLeng),
	length(GiveAwayEat,GiveEatLeng),
	length(EatList,EatLeng),
	Value is 2*Pawns - EatLeng + GiveMoveLeng + GiveEatLeng.

% count_pawns(position,value)/2
% count_pawns: returns the difference in number of pieces (queen = 2, pown = 1) on the board between two sides.
count_pawns([X|Last],Value):-!,
	count_pawns(Last,Value1),
	Value is Value1 - X.

count_pawns([],0):-!.

% recommended_moves(position,list_of_recommended_moves)/2
% recommended_moves: returns a list of recommended moves for current position.
recommended_moves(Position, Moves):-
	% If optional eating move, recommends all the eating moves
	eatAll(Position,_,_,_,_,_),!,
	findall(Move, (place(A,_), eatAll(Position,A,_,_,Move,_)), Moves).

recommended_moves(Position, Moves):-
	moveAll(Position,_,_,_,_),!,
	% Otherwise, recommends all valid non-eating moves
	findall(Move, (place(A,_), moveAll(Position,A,_,_,Move)), Moves).

recommended_moves(_, []).

% reverse_position(position,reversed_position)/2
% reverse_position: returns a reversed position for the current position.
reverse_position(Position,NewPosition):-
	reverse(Position,Reversed),
	negative(Reversed,NewPosition).

% negative(list,negative_list)/2
% negative: returns a list with negative values to the current list.
negative([],[]):-!.
negative([X|Xs],[Y|Ys]):-
	Y is -X,
	negative(Xs,Ys).

% game_won(position)/1
% game_won: returns true if the game is won for the positive side.
game_won(Position):-
	not(moveAll(Position,_,_,_,_)),
	not(eatAll(Position,_,_,_,_,_)),!.

% eatAll(current_position,from_place,to_place,direction,next_position,history_of_eating)/6
% eatAll: returns true if there is a valid eating move with this history on the board.
eatAll(From,A,B,Dir,To,[B]):-
	eatPart(From,A,B,Dir,To),
	not((eatPart(From,A,C,Dir,To1),eatPart(To1,C,_,Dir1,_),not(opposite(Dir1,Dir)))).

eatAll(From,A,C,Dir,To,[B|List]):-
	eatPart(From,A,B,Dir,To1),
	eatAll(To1,B,C,Dir1,To,List),
	not(opposite(Dir1,Dir)).

% eatOnce(current_position,from_place,to_place,direction,next_position)/5
% eatOnce: returns true if there is a valid partial eating move with a piece.
eatOnce(From,A,B,Dir,To):-
	eatPart(From,A,B,Dir,To),
	eatPart(To,B,_,Dir1,_),not(opposite(Dir1,Dir)),!.

eatOnce(From,A,B,Dir,To):-
	eatPart(From,A,B,Dir,To),
	not((eatPart(To,B,_,Dir1,_),not(opposite(Dir1,Dir)))).

% eatPart(current_position,from_place,to_place,direction,next_position)/5
% eatPart: returns true if there is a valid one direction eating move with a queen or a pawn on the board.
eatPart(From,A,B,Dir,To):-
	eat(From,A,B,Dir,To).

eatPart(From,A,D,Dir,To):-
	place(A,P),
	nth1(P,From,2),
	eat(From,A,C,Dir,To2),
	moveAll(To2,C,D,Dir,To).

eatPart(From,A,D,Dir,To):-
	place(A,P),
	nth1(P,From,2),
	moveAll(From,A,B,Dir,To1),
	eat(To1,B,D,Dir,To).

eatPart(From,A,D,Dir,To):-
	place(A,P),
	nth1(P,From,2),
	moveAll(From,A,B,Dir,To1),
	eat(To1,B,C,Dir,To2),
	moveAll(To2,C,D,Dir,To).

% opposite(one_direction,second_direction)/2
% opposite: returns true if the two direction are opposite
opposite(Dir1,Dir2):-
	Dir1 == -Dir2;
	Dir2 == -Dir1.

% eat(current_position,from_place,to_place,direction,next_position)/5
% eat: returns true if there is a valid eating move of one pawn on the board.
eat([I,A4,A6,A8,B1,J,B5,B7,C2,0,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a2,c4,y,
    [0,A4,A6,A8,B1,0,B5,B7,C2,I,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,I,A6,A8,B1,J,B5,B7,0,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a4,c2,x,
    [A2,0,A6,A8,B1,0,B5,B7,I,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,I,A6,A8,B1,B3,J,B7,C2,C4,0,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a4,c6,y,
    [A2,0,A6,A8,B1,B3,0,B7,C2,C4,I,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,I,A8,B1,B3,J,B7,C2,0,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a6,c4,x,
    [A2,A4,0,A8,B1,B3,0,B7,C2,I,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,I,A8,B1,B3,B5,J,C2,C4,C6,0,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a6,c8,y,
    [A2,A4,0,A8,B1,B3,B5,0,C2,C4,C6,I,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,I,B1,B3,B5,J,C2,C4,0,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a8,c6,x,
    [A2,A4,A6,0,B1,B3,B5,0,C2,C4,I,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,I,B3,B5,B7,J,C4,C6,C8,D1,0,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b1,d3,y,
    [A2,A4,A6,A8,0,B3,B5,B7,0,C4,C6,C8,D1,I,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,I,B5,B7,J,C4,C6,C8,0,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b3,d1,x,
    [A2,A4,A6,A8,B1,0,B5,B7,0,C4,C6,C8,I,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,I,B5,B7,C2,J,C6,C8,D1,D3,0,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b3,d5,y,
    [A2,A4,A6,A8,B1,0,B5,B7,C2,0,C6,C8,D1,D3,I,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,I,B7,C2,J,C6,C8,D1,0,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b5,d3,x,
    [A2,A4,A6,A8,B1,B3,0,B7,C2,0,C6,C8,D1,I,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,I,B7,C2,C4,J,C8,D1,D3,D5,0,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b5,d7,y,
    [A2,A4,A6,A8,B1,B3,0,B7,C2,C4,0,C8,D1,D3,D5,I,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,I,C2,C4,J,C8,D1,D3,0,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b7,d5,x,
    [A2,A4,A6,A8,B1,B3,B5,0,C2,C4,0,C8,D1,D3,I,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,I,C4,C6,C8,D1,J,D5,D7,E2,0,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c2,e4,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,0,C4,C6,C8,D1,0,D5,D7,E2,I,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,I,C6,C8,D1,J,D5,D7,0,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c4,e2,x,
   [A2,A4,A6,A8,B1,B3,B5,B7,C2,0,C6,C8,D1,0,D5,D7,I,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,I,C6,C8,D1,D3,J,D7,E2,E4,0,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c4,e6,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,0,C6,C8,D1,D3,0,D7,E2,E4,I,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,I,C8,D1,D3,J,D7,E2,0,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c6,e4,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,0,C8,D1,D3,0,D7,E2,I,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,I,C8,D1,D3,D5,J,E2,E4,E6,0,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c6,e8,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,0,C8,D1,D3,D5,0,E2,E4,E6,I,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,I,D1,D3,D5,J,E2,E4,0,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c8,e6,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,0,D1,D3,D5,0,E2,E4,I,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,I,D3,D5,D7,J,E4,E6,E8,F1,0,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d1,f3,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,0,D3,D5,D7,0,E4,E6,E8,F1,I,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,I,D5,D7,J,E4,E6,E8,0,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d3,f1,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,0,D5,D7,0,E4,E6,E8,I,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,I,D5,D7,E2,J,E6,E8,F1,F3,0,F7,G2,G4,G6,G8,H1,H3,H5,H7],d3,f5,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,0,D5,D7,E2,0,E6,E8,F1,F3,I,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,I,D7,E2,J,E6,E8,F1,0,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d5,f3,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,0,D7,E2,0,E6,E8,F1,I,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,I,D7,E2,E4,J,E8,F1,F3,F5,0,G2,G4,G6,G8,H1,H3,H5,H7],d5,f7,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,0,D7,E2,E4,0,E8,F1,F3,F5,I,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,I,E2,E4,J,E8,F1,F3,0,F7,G2,G4,G6,G8,H1,H3,H5,H7],d7,f5,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,0,E2,E4,0,E8,F1,F3,I,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,I,E4,E6,E8,F1,J,F5,F7,G2,0,G6,G8,H1,H3,H5,H7],e2,g4,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,0,E4,E6,E8,F1,0,F5,F7,G2,I,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,I,E6,E8,F1,J,F5,F7,0,G4,G6,G8,H1,H3,H5,H7],e4,g2,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,0,E6,E8,F1,0,F5,F7,I,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,I,E6,E8,F1,F3,J,F7,G2,G4,0,G8,H1,H3,H5,H7],e4,g6,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,0,E6,E8,F1,F3,0,F7,G2,G4,I,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,I,E8,F1,F3,J,F7,G2,0,G6,G8,H1,H3,H5,H7],e6,g4,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,0,E8,F1,F3,0,F7,G2,I,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,I,E8,F1,F3,F5,J,G2,G4,G6,0,H1,H3,H5,H7],e6,g8,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,0,E8,F1,F3,F5,0,G2,G4,G6,I,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,I,F1,F3,F5,J,G2,G4,0,G8,H1,H3,H5,H7],e8,g6,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,0,F1,F3,F5,0,G2,G4,I,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,I,F3,F5,F7,J,G4,G6,G8,H1,0,H5,H7],f1,h3,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,0,F3,F5,F7,0,G4,G6,G8,H1,2,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,I,F5,F7,J,G4,G6,G8,0,H3,H5,H7],f3,h1,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,0,F5,F7,0,G4,G6,G8,2,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,I,F5,F7,G2,J,G6,G8,H1,H3,0,H7],f3,h5,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,0,F5,F7,G2,0,G6,G8,H1,H3,2,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,I,F7,G2,J,G6,G8,H1,0,H5,H7],f5,h3,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,0,F7,G2,0,G6,G8,H1,2,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,I,F7,G2,G4,J,G8,H1,H3,H5,0],f5,h7,y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,0,F7,G2,G4,0,G8,H1,H3,H5,2]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,I,G2,G4,J,G8,H1,H3,0,H7],f7,h5,x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,0,G2,G4,0,G8,H1,H3,2,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,0,F3,F5,F7,J,G4,G6,G8,H1,I,H5,H7],h3,f1,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,I,F3,F5,F7,0,G4,G6,G8,H1,0,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,0,F5,F7,J,G4,G6,G8,I,H3,H5,H7],h1,f3,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,I,F5,F7,0,G4,G6,G8,0,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,0,F5,F7,G2,J,G6,G8,H1,H3,I,H7],h5,f3,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,I,F5,F7,G2,0,G6,G8,H1,H3,0,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,0,F7,G2,J,G6,G8,H1,I,H5,H7],h3,f5,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,I,F7,G2,0,G6,G8,H1,0,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,0,F7,G2,G4,J,G8,H1,H3,H5,I],h7,f5,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,I,F7,G2,G4,0,G8,H1,H3,H5,0]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,0,G2,G4,J,G8,H1,H3,I,H7],h5,f7,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,I,G2,G4,0,G8,H1,H3,0,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,0,D3,D5,D7,J,E4,E6,E8,F1,I,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],f3,d1,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,I,D3,D5,D7,0,E4,E6,E8,F1,0,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,0,D5,D7,J,E4,E6,E8,I,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],f1,d3,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,I,D5,D7,0,E4,E6,E8,0,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,0,D5,D7,E2,J,E6,E8,F1,F3,I,F7,G2,G4,G6,G8,H1,H3,H5,H7],f5,d3,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,I,D5,D7,E2,0,E6,E8,F1,F3,0,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,0,D7,E2,J,E6,E8,F1,I,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],f3,d5,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,I,D7,E2,0,E6,E8,F1,0,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,0,D7,E2,E4,J,E8,F1,F3,F5,I,G2,G4,G6,G8,H1,H3,H5,H7],f7,d5,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,I,D7,E2,E4,0,E8,F1,F3,F5,0,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,0,E2,E4,J,E8,F1,F3,I,F7,G2,G4,G6,G8,H1,H3,H5,H7],f5,d7,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,I,E2,E4,0,E8,F1,F3,0,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,0,C4,C6,C8,D1,J,D5,D7,E2,I,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e4,c2,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,I,C4,C6,C8,D1,0,D5,D7,E2,0,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,0,C6,C8,D1,J,D5,D7,I,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e2,c4,-x,
   [A2,A4,A6,A8,B1,B3,B5,B7,C2,I,C6,C8,D1,0,D5,D7,0,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,0,C6,C8,D1,D3,J,D7,E2,E4,I,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e6,c4,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,I,C6,C8,D1,D3,0,D7,E2,E4,0,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,0,C8,D1,D3,J,D7,E2,I,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e4,c6,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,I,C8,D1,D3,0,D7,E2,0,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,0,C8,D1,D3,D5,J,E2,E4,E6,I,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e8,c6,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,I,C8,D1,D3,D5,0,E2,E4,E6,0,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,0,D1,D3,D5,J,E2,E4,I,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e6,c8,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,I,D1,D3,D5,0,E2,E4,0,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([0,A4,A6,A8,B1,J,B5,B7,C2,I,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c4,a2,-y,
    [I,A4,A6,A8,B1,0,B5,B7,C2,0,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,0,A6,A8,B1,J,B5,B7,I,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c2,a4,-x,
    [A2,I,A6,A8,B1,0,B5,B7,0,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,0,A6,A8,B1,B3,J,B7,C2,C4,I,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c6,a4,-y,
    [A2,I,A6,A8,B1,B3,0,B7,C2,C4,0,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,0,A8,B1,B3,J,B7,C2,I,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c4,a6,-x,
    [A2,A4,I,A8,B1,B3,0,B7,C2,0,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,0,A8,B1,B3,B5,J,C2,C4,C6,I,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c8,a6,-y,
    [A2,A4,I,A8,B1,B3,B5,0,C2,C4,C6,0,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,0,B1,B3,B5,J,C2,C4,I,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c6,a8,-x,
    [A2,A4,A6,I,B1,B3,B5,0,C2,C4,0,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,0,B3,B5,B7,J,C4,C6,C8,D1,I,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d3,b1,-y,
    [A2,A4,A6,A8,I,B3,B5,B7,0,C4,C6,C8,D1,0,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,0,B5,B7,J,C4,C6,C8,I,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d1,b3,-x,
    [A2,A4,A6,A8,B1,I,B5,B7,0,C4,C6,C8,0,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,0,B5,B7,C2,J,C6,C8,D1,D3,I,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d5,b3,-y,
    [A2,A4,A6,A8,B1,I,B5,B7,C2,0,C6,C8,D1,D3,0,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,0,B7,C2,J,C6,C8,D1,I,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d3,b5,-x,
    [A2,A4,A6,A8,B1,B3,I,B7,C2,0,C6,C8,D1,0,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,0,B7,C2,C4,J,C8,D1,D3,D5,I,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d7,b5,-y,
    [A2,A4,A6,A8,B1,B3,I,B7,C2,C4,0,C8,D1,D3,D5,0,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,0,C2,C4,J,C8,D1,D3,I,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d5,b7,-x,
    [A2,A4,A6,A8,B1,B3,B5,I,C2,C4,0,C8,D1,D3,0,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,0,E4,E6,E8,F1,J,F5,F7,G2,I,G6,G8,H1,H3,H5,H7],g4,e2,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,I,E4,E6,E8,F1,0,F5,F7,G2,0,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,0,E6,E8,F1,J,F5,F7,I,G4,G6,G8,H1,H3,H5,H7],g2,e4,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,I,E6,E8,F1,0,F5,F7,0,G4,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,0,E6,E8,F1,F3,J,F7,G2,G4,I,G8,H1,H3,H5,H7],g6,e4,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,I,E6,E8,F1,F3,0,F7,G2,G4,0,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,0,E8,F1,F3,J,F7,G2,I,G6,G8,H1,H3,H5,H7],g4,e6,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,I,E8,F1,F3,0,F7,G2,0,G6,G8,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,0,E8,F1,F3,F5,J,G2,G4,G6,I,H1,H3,H5,H7],g8,e6,-y,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,I,E8,F1,F3,F5,0,G2,G4,G6,0,H1,H3,H5,H7]):-
	J<0,I>0.
eat([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,0,F1,F3,F5,J,G2,G4,I,G8,H1,H3,H5,H7],g6,e8,-x,
    [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,I,F1,F3,F5,0,G2,G4,0,G8,H1,H3,H5,H7]):-
	J<0,I>0.

% moveAll(current_position,from_place,to_place,direction,next_position)/5
% moveAll: returns true if there is a valid move of one piece (queen or pawn) on the board.
moveAll(From,A,C,Dir,To):-
	place(A,P),
	nth1(P,From,2),!,
	movePart(From,A,C,Dir,To).

moveAll(From,A,B,Dir,To):-
	moveTwoDir(From,A,B,Dir,To).

% movePart(current_position,from_place,to_place,direction,next_position)/5
% movePart: returns true if there is a valid move of one queen on the board.
movePart(From,A,B,Dir,To):-
	moveTwoDir(From,A,B,Dir,To).

movePart(From,A,C,Dir,To):-
	moveTwoDir(From,A,B,Dir,To1),
	movePart(To1,B,C,Dir,To).

% moveTwoDir(current_position,from_place,to_place,direction,next_position)/5
% moveTwoDir: returns true if there is a valid one-step move of one piece (queen or pawn) on the board.
moveTwoDir(To,B,A,-x,From):-
	place(B,P),
	P =< 28,
	nth1(P,To,2),
	move(From,A,B,x,To).

moveTwoDir(To,B,A,-y,From):-
	place(B,P),
	P =< 28, % not in the last line
	nth1(P,To,2),
	move(From,A,B,y,To).

moveTwoDir(From,A,B,Dir,To):-
	move(From,A,B,Dir,To).

% move(current_position,from_place,to_place,direction,next_position)/5
% move: returns true if there is a valid move of one pawn on the board.
move([I,A4,A6,A8,0,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a2,b1,x,
     [0,A4,A6,A8,I,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([I,A4,A6,A8,B1,0,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a2,b3,y,
     [0,A4,A6,A8,B1,I,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,I,A6,A8,B1,0,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a4,b3,x,
     [A2,0,A6,A8,B1,I,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,I,A6,A8,B1,B3,0,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a4,b5,y,
     [A2,0,A6,A8,B1,B3,I,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,I,A8,B1,B3,0,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a6,b5,x,
     [A2,A4,0,A8,B1,B3,I,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,I,A8,B1,B3,B5,0,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a6,b7,y,
     [A2,A4,0,A8,B1,B3,B5,I,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,I,B1,B3,B5,0,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],a8,b7,x,
     [A2,A4,A6,0,B1,B3,B5,I,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,I,B3,B5,B7,0,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b1,c2,y,
     [A2,A4,A6,A8,0,B3,B5,B7,I,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,I,B5,B7,0,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b3,c2,x,
     [A2,A4,A6,A8,B1,0,B5,B7,I,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,I,B5,B7,C2,0,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b3,c4,y,
     [A2,A4,A6,A8,B1,0,B5,B7,C2,I,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,I,B7,C2,0,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b5,c4,x,
     [A2,A4,A6,A8,B1,B3,0,B7,C2,I,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,I,B7,C2,C4,0,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b5,c6,y,
     [A2,A4,A6,A8,B1,B3,0,B7,C2,C4,I,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,I,C2,C4,0,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b7,c6,x,
     [A2,A4,A6,A8,B1,B3,B5,0,C2,C4,I,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,I,C2,C4,C6,0,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],b7,c8,y,
     [A2,A4,A6,A8,B1,B3,B5,0,C2,C4,C6,I,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,I,C4,C6,C8,0,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c2,d1,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,0,C4,C6,C8,I,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,I,C4,C6,C8,D1,0,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c2,d3,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,0,C4,C6,C8,D1,I,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,I,C6,C8,D1,0,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c4,d3,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,0,C6,C8,D1,I,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,I,C6,C8,D1,D3,0,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c4,d5,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,0,C6,C8,D1,D3,I,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,I,C8,D1,D3,0,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c6,d5,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,0,C8,D1,D3,I,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,I,C8,D1,D3,D5,0,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c6,d7,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,0,C8,D1,D3,D5,I,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,I,D1,D3,D5,0,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],c8,d7,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,0,D1,D3,D5,I,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,I,D3,D5,D7,0,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d1,e2,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,0,D3,D5,D7,I,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,I,D5,D7,0,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d3,e2,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,0,D5,D7,I,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,I,D5,D7,E2,0,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d3,e4,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,0,D5,D7,E2,I,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,I,D7,E2,0,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d5,e4,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,0,D7,E2,I,E6,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,I,D7,E2,E4,0,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d5,e6,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,0,D7,E2,E4,I,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,I,E2,E4,0,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d7,e6,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,0,E2,E4,I,E8,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,I,E2,E4,E6,0,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],d7,e8,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,0,E2,E4,E6,I,F1,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,I,E4,E6,E8,0,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e2,f1,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,0,E4,E6,E8,I,F3,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,I,E4,E6,E8,F1,0,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e2,f3,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,0,E4,E6,E8,F1,I,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,I,E6,E8,F1,0,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7],e4,f3,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,0,E6,E8,F1,I,F5,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,I,E6,E8,F1,F3,0,F7,G2,G4,G6,G8,H1,H3,H5,H7],e4,f5,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,0,E6,E8,F1,F3,I,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,I,E8,F1,F3,0,F7,G2,G4,G6,G8,H1,H3,H5,H7],e6,f5,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,0,E8,F1,F3,I,F7,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,I,E8,F1,F3,F5,0,G2,G4,G6,G8,H1,H3,H5,H7],e6,f7,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,0,E8,F1,F3,F5,I,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,I,F1,F3,F5,0,G2,G4,G6,G8,H1,H3,H5,H7],e8,f7,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,0,F1,F3,F5,I,G2,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,I,F3,F5,F7,0,G4,G6,G8,H1,H3,H5,H7],f1,g2,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,0,F3,F5,F7,I,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,I,F5,F7,0,G4,G6,G8,H1,H3,H5,H7],f3,g2,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,0,F5,F7,I,G4,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,I,F5,F7,G2,0,G6,G8,H1,H3,H5,H7],f3,g4,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,0,F5,F7,G2,I,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,I,F7,G2,0,G6,G8,H1,H3,H5,H7],f5,g4,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,0,F7,G2,I,G6,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,I,F7,G2,G4,0,G8,H1,H3,H5,H7],f5,g6,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,0,F7,G2,G4,I,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,I,G2,G4,0,G8,H1,H3,H5,H7],f7,g6,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,0,G2,G4,I,G8,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,I,G2,G4,G6,0,H1,H3,H5,H7],f7,g8,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,0,G2,G4,G6,I,H1,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,I,G4,G6,G8,0,H3,H5,H7],g2,h1,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,0,G4,G6,G8,2,H3,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,I,G4,G6,G8,H1,0,H5,H7],g2,h3,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,0,G4,G6,G8,H1,2,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,I,G6,G8,H1,0,H5,H7],g4,h3,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,0,G6,G8,H1,2,H5,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,I,G6,G8,H1,H3,0,H7],g4,h5,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,0,G6,G8,H1,H3,2,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,I,G8,H1,H3,0,H7],g6,h5,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,0,G8,H1,H3,2,H7]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,I,G8,H1,H3,H5,0],g6,h7,y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,0,G8,H1,H3,H5,2]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,I,H1,H3,H5,0],g8,h7,x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,0,H1,H3,H5,2]):-I>0.
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,0,G4,G6,G8,2,H3,H5,H7],h1,g2,-x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,2,G4,G6,G8,0,H3,H5,H7]).
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,0,G4,G6,G8,H1,2,H5,H7],h3,g2,-y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,2,G4,G6,G8,H1,0,H5,H7]).
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,0,G6,G8,H1,2,H5,H7],h3,g4,-x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,2,G6,G8,H1,0,H5,H7]).
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,0,G6,G8,H1,H3,2,H7],h5,g4,-y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,2,G6,G8,H1,H3,0,H7]).
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,0,G8,H1,H3,2,H7],h5,g6,-x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,2,G8,H1,H3,0,H7]).
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,0,G8,H1,H3,H5,2],h7,g6,-y,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,2,G8,H1,H3,H5,0]).
move([A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,0,H1,H3,H5,2],h7,g8,-x,
     [A2,A4,A6,A8,B1,B3,B5,B7,C2,C4,C6,C8,D1,D3,D5,D7,E2,E4,E6,E8,F1,F3,F5,F7,G2,G4,G6,2,H1,H3,H5,0]).


% point_to_place(point,place)/2
% point_to_place: converts a click to a place on the board.
point_to_place(Point,Place):-
	get(Point,x,X),
	get(Point,y,Y),
	I is X//50+49,
	J is Y//50+97,
	name(RevPlace,[J,I]),
	place(RevPlace,RevNum),
	Num is 33-RevNum,
	place(Place,Num).

% place(place_on_board,place_in_position_list)/2
% place: returns true if the place on board matches to the place in the position list.
place(a2,1).
place(a4,2).
place(a6,3).
place(a8,4).
place(b1,5).
place(b3,6).
place(b5,7).
place(b7,8).
place(c2,9).
place(c4,10).
place(c6,11).
place(c8,12).
place(d1,13).
place(d3,14).
place(d5,15).
place(d7,16).
place(e2,17).
place(e4,18).
place(e6,19).
place(e8,20).
place(f1,21).
place(f3,22).
place(f5,23).
place(f7,24).
place(g2,25).
place(g4,26).
place(g6,27).
place(g8,28).
place(h1,29).
place(h3,30).
place(h5,31).
place(h7,32).

% image_name(number, image_name)/2
% image_name: returns image name for the current value.
image_name(3, 'selectedSquare.bmp').
image_name(0, 'square.bmp').
image_name(1, 'red.bmp').
image_name(-1, 'black.bmp').
image_name(2, 'redQueen.bmp').
image_name(-2, 'blackQueen.bmp').
image_name(-3, 'selectedSquare.bmp').

