from typing import List, Tuple

def compare(correct: List[int], guess: List[int]) -> Tuple[int, int]:
  hits = 0
  misplaced = 0

  remaining_pin = []
  remaining_guess = []

  for p, g in zip(correct, guess):
    if p == g:
      hits += 1
    else:
      remaining_pin.append(p)
      remaining_guess.append(g)

  for g in remaining_guess:
    if g in remaining_pin:
      misplaced += 1
      remaining_pin.remove(g)

  return (hits, misplaced)

def main():
    min_, max_ = 1, 6
    guess = [min_] * 4
    
    combinations = [
        [a, b, c, d]
        for a in range(min_, max_ + 1)
        for b in range(min_, max_ + 1)
        for c in range(min_, max_ + 1)
        for d in range(min_, max_ + 1)
    ]

    hits = 0
    attempt = 0
    while hits != 4:
        attempt += 1
        print(f"{attempt}: {' '.join(map(str, guess))} ?")
        
        hits      = int(input("Na swoim miejscu: "))
        misplaced = int(input("Nie na swoim miejscu: "))
        
        combinations = [
            c for c in combinations
            if compare(c, guess) == (hits, misplaced)
        ]
        
        if len(combinations) > 0:
            guess = combinations[0] 
        else:
            print("Oszukujesz!")
            break
    else:
        print(f"Wygralem.")

if __name__ == "__main__": main()
