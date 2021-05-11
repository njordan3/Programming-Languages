
/*
 Your job is to convert the 9 logical statements below into prolog rules. 
 The facts are given to you. The one query to test your knowledge base is:
      likes(X,Y): meaning X likes Y                                       

 The universe of discourse is a set of animals, U={fido,kitty,tweety,ratatat}. 
 Predicates are some characteristics of animals. The rules determine what kind
 of animal a member is. The inference engine infers which animal likes another
 animal.

 Prolog variables (X,Y,etc.) begin with uppercase and predicate names or 
 literals (loves, dog, animal, etc.) in lowercase.       

 Note that discontiguous predicates are ignored - put like predicates together. 

 Hint: If you make a change to your knowledge base, the safest thing to do is
 to exit prolog and reload the code from scratch.  
*/

% comment the next two lines out when testing - put back in to submit

:- initialization(q1).
:- initialization(q2).
:- initialization(q3).
:- initialization(end).


% FACTS. 
mammal(kitty).
mammal(ratatat).
mammal(fido).
claws(kitty).
tail(ratatat).
bestfriend(fido).
feathers(tweety).

% PART A: 9 RULES. 
% If X is a mammal then X has fur. 
fur(X) :- mammal(X).
% If X has fur and X has a tail then X is a rat. 
rat(X) :- fur(X), tail(X).
% If X has claws and X has fur then X is a cat.
cat(X) :- claws(X), fur(X).
% If X is a cat then X meows.
meows(X) :- cat(X).
% If X has feathers then X is a bird.
bird(X) :- feathers(X).
% If X is a bestfriend and X has fur then X is a dog.
dog(X) :- bestfriend(X), fur(X).
% If X is a dog and Y meows then X likes Y.
likes(X, Y) :- dog(X), meows(Y).
% If X is a cat and Y is a bird then X likes Y.
likes(X, Y) :- cat(X), bird(Y).
% If X is a cat and Y is a rat then X likes Y.
likes(X, Y) :- cat(X), rat(Y).

% PART B: 2 RULES.
% Max of 3 numbers.
max2(A, B, R) :- 
    A > B -> R is A; R is B.

max3(A, B, C, R) :-
    max2(A, B, Temp),
    max2(Temp, C, R).

% Towers of Hanoi move count.
moves(N, R) :-
    % explicit pattern: 2^n -1; where n is number of disks
    R is round(2**N - 1).

writeln(T) :- write(T), nl.

% QUERIES
q1 :- writeln('Who likes whom? '), 
    findall(X, (likes(X,Y), format('~w ~w~n',[X,Y])),_).
q2 :- write('Move count for 5: '),
    findall(X, (moves(5,X), format('~w',[X])),_).
q3 :- nl, write('Max(7,3,9)? '),
    findall(X, (max3(7,3,9,X), format('~w ~n',[X])),_).
end :- writeln('done.'), halt. 
