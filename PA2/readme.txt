1. Did you use the 'suit', 'type' and 'value' arrays? What functions are easier
to implement when using these arrays? How do you use them?

I used the suit, type, and value arrays. In the printCard function, the suit
and type arrays are used to more easily match the card number with readable id's
in type-suit format. I used these array by moding the id by
13 (aligning with number of cards in each suit) and assigning cards suit
based on what range their array position was in and a type based on its relation
to other cards in the suit. For example, if a card had the number 26, it would
be the "first" card in the third suit, its id is A-D (3rd value in 
the suit array-the first value in the type array). I used the value array 
in the cardValue function by using bounds of 13 to assign each card a value. 
The first 13 card numbers (0-12) were assigned values (2-11) from the value 
array. The next thirteen cards (13-25) after then were assigned values starting 
at the beginning of the value array (2-11) and the cycle repeated for the 
next two sets of 13 cards.

2. There are many ways to shuffle the deck of cards. The method used in our
implementation generates a permutaion of the cards to shuffle. For an array of
size N, how many swap (exchange) operations does this algorithm do? Does the
algorithm require any extra memory to generate a permutation?

It does (N-1) number of swaps. It needs extra memory to store the original number
stored in the array position that is part of the swap.
