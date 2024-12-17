import sys
from typing import List

def nextPermutation(lst: List[int], min_: int, max_: int) -> bool:
    for i in range(len(lst) - 1, -1, -1):
        if lst[i] < max_:
            lst[i] += 1
            for j in range(i + 1, len(lst)):
                lst[j] = min_
            return True
    return False

def isValid(lst: List[int]) -> bool:
    rows  = [0] * (len(lst) + 1)
    diag1 = [0] * (2 * len(lst))
    diag2 = [0] * (2 * len(lst))
    
    valid = True
    for i in range(len(lst)):
        rows[lst[i]] += 1
        diag1[i - lst[i] + len(lst)] += 1
        diag2[i + lst[i]] += 1
        
        if rows[lst[i]] > 1 or \
           diag1[i - lst[i] + len(lst)] > 1 or \
           diag2[i + lst[i]] > 1:
            valid = False
            break
    
    return valid

def main() -> None:
    n = int(sys.argv[1])
    lst = [1] * n

    validSolutions = 0
    
    while True:
        if isValid(lst):
            print(*lst)
            validSolutions += 1
        
        if not nextPermutation(lst, 1, n):
            break

    print(f'Number of solutions: {validSolutions}')

if __name__ == "__main__": main()