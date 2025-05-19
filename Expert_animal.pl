% Initialization directive - this tells Prolog what to run when the program starts
:- initialization(start).

% Facts about animals and their classifications
is_mammal(dog).
is_mammal(cat).
is_mammal(cow).
is_mammal(horse).

is_bird(eagle).
is_bird(sparrow).
is_bird(penguin).
is_bird(ostrich).

is_reptile(snake).
is_reptile(lizard).
is_reptile(turtle).
is_reptile(crocodile).

is_fish(salmon).
is_fish(tuna).
is_fish(shark).
is_fish(goldfish).

% Classification rules
is_animal(X) :- is_mammal(X).
is_animal(X) :- is_bird(X).
is_animal(X) :- is_reptile(X).
is_animal(X) :- is_fish(X).

% Characteristics of animals
has_fur(X) :- is_mammal(X).
has_feathers(X) :- is_bird(X).
has_scales(X) :- is_reptile(X); is_fish(X).
lives_in_water(X) :- is_fish(X).
lays_eggs(X) :- is_bird(X); is_reptile(X); is_fish(X).
gives_birth(X) :- is_mammal(X).

% Query predicates
classify(Animal) :-
    is_mammal(Animal),
    write(Animal), write(' is a mammal.'), nl.
classify(Animal) :-
    is_bird(Animal),
    write(Animal), write(' is a bird.'), nl.
classify(Animal) :-
    is_reptile(Animal),
    write(Animal), write(' is a reptile.'), nl.
classify(Animal) :-
    is_fish(Animal),
    write(Animal), write(' is a fish.'), nl.
classify(Animal) :-
    \+ is_animal(Animal),
    write(Animal), write(' is not in the database.'), nl.

% Main predicate to classify all animals
start :-
    write('Animal Classification System'), nl,
    write('-------------------------'), nl,
    classify(dog),
    classify(eagle),
    classify(snake),
    classify(salmon),
    classify(elephant).
