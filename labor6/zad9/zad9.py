from typing import List, Tuple

def nextPermutation(lst: List[int], min_: int, max_: int) -> bool:
    for i in range(len(lst) - 1, -1, -1):
        if lst[i] < max_:
            lst[i] += 1
            for j in range(i + 1, len(lst)):
                lst[j] = min_
            return True
    return False

def correctGuesses(guess1: List[int], guess2: List[int]) -> Tuple[int, int]:
    corrPlace = sum(1 for i in range(4) if guess1[i] == guess2[i])
    corrVal = sum(min(guess1.count(x), guess2.count(x)) for x in set(guess1))
    return (corrPlace, corrVal - corrPlace)

def main():
    #? Mozna zmienic wartosci min_, max_ na 0, 9. Program bedzie
    #? dzialac tak samo, ale bedzie potrzebowal wiecej prob.
     
    min_, max_ = 1, 6
    guess = [min_] * 4
    
    combinations = [
        [a, b, c, d]
        for a in range(min_, max_ + 1)
        for b in range(min_, max_ + 1)
        for c in range(min_, max_ + 1)
        for d in range(min_, max_ + 1)
    ]

    corrPlace = 0
    attempt = 0
    while corrPlace != 4:
        attempt += 1
        print(f"{attempt}: {' '.join(map(str, guess))} ?")
        
        corrPlace = int(input("Na swoim miejscu: "))
        corrVal   = int(input("Nie na swoim miejscu: "))
        
        combinations = [
            c for c in combinations
            if correctGuesses(c, guess) == (corrPlace, corrVal)
        ]
        
        if len(combinations) > 0:
            guess = combinations[0] 
        else:
            print("Oszukujesz!")
            break
    else:
        print(f"Wygralem.")

if __name__ == "__main__": main()