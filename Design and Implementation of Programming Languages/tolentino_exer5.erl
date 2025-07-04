% MARY GWYNETH A. TOLENTINO
% 2021-02990
% CMSC 124 S-4L

-module(tolentino_exer5).
-export([pascals_triangle/1, generate_rows/2, generate_row/1, generate_elements/1, print_row/1,  print_rest/1,  isPrime/1, isOddPrime/2, primeOrNot/1]).


% PART 1
% Function to generate Pascal's Triangle up to the Nth row
pascals_triangle(N) -> 
    generate_rows(0, N).

% Recursive function to generate and print each row
generate_rows(CurrentRow, N) when CurrentRow =< N ->
    Row = generate_row(CurrentRow),
    print_row(Row),
    generate_rows(CurrentRow + 1, N);
generate_rows(_, _) -> ok.

% Function to generate a single row of Pascal's Triangle
generate_row(0) -> [1];         % The 0th row is always [1]
generate_row(Row) ->
    PrevRow = generate_row(Row - 1),
    [1|generate_elements(PrevRow)] ++ [1].

% Function to generate the inner elements of a row based on the previous row
generate_elements([X, Y|Rest]) -> [X + Y|generate_elements([Y|Rest])];
generate_elements(_) -> [].

% Function to print a row
print_row([H|T]) -> 
    io:format("~w", [H]),
    print_rest(T),
    io:format("~n").

% Helper function to print the remaining elements in a row
print_rest([H|T]) -> 
    io:format(" ~w", [H]),
    print_rest(T);
print_rest([]) -> ok.



% PART 2
isPrime(N) when N < 0 -> false;
isPrime(0)-> false;
isPrime(1)-> false;
isPrime(2)-> true;

isPrime(N) when N > 2 ->
    case (N rem 2) =/= 0 of
        true -> isOddPrime(N, 3);
        false -> false
    end.

% Helper function to check if odd numbers greater than 2 are prime
isOddPrime(N, D) when D * D > N -> true;        % If D exceeds sqrt(N), N is prime
isOddPrime(N, D) when N rem D =:= 0 -> false;   % If divisible by D, not prime
isOddPrime(N, D) -> isOddPrime(N, D + 2).       % Only check odd divisors

% Main Function to check each element of the list whether it is prime or not
primeOrNot(List) when length(List) > 0 -> 
    [H|T] = List,

    case (isPrime(H)) of
        true -> io:format("~w - prime~n", [H]);
        false -> io:format("~w - no~n", [H])
    end,

    primeOrNot(T);

primeOrNot([])->ok.




    



