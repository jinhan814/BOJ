import sys
input = lambda: sys.stdin.readline().rstrip()

class EquationParser:
    def F(self, s):
        x = y = c = 0; v = s.split(); flag = 0
        for i in range(len(v)):
            if i & 1: flag = int(v[i] == "-")
            else:
                t = v[i][:-1]; t = "1" if t == "" else "-1" if t == "-" else t
                if v[i][-1] == 'x': x += int(t) * (-1 if flag else 1)
                elif v[i][-1] == 'y': y += int(t) * (-1 if flag else 1)
                else: c += int(v[i]) * (-1 if flag else 1)
        return (x, y, c)

    def __call__(self, s):
        pos = s.find('=')
        lx, ly, lc = self.F(s[:pos])
        rx, ry, rc = self.F(s[pos + 2:])
        return (lx - rx, ly - ry, rc - lc)

Parser = EquationParser()

def _Sol(a, b):
    ax, ay, ac = Parser(a)
    bx, by, bc = Parser(b)

    if ax == 0 and ay == 0 or bx == 0 and by == 0: # case 1. 0 = c
        if bx == 0 and by == 0: ax, ay, ac, bx, by, bc = bx, by, bc, ax, ay, ac
        if ac: return (0, 0, 0, 0)
        if bx and by == 0: return (bc, bx, 0, 0)
        if by and bx == 0: return (0, 0, bc, by)
        return (0, 0, 0, 0)

    elif ay == 0 or by == 0: # case 2. x = c
        if by == 0: ax, ay, ac, bx, by, bc = bx, by, bc, ax, ay, ac
        if by == 0:
            if bx * ac == ax * bc: return (ac, ax, 0, 0)
            return (0, 0, 0, 0)

    elif ax == 0 or bx == 0: # case 3. y = c
        if bx == 0: ax, ay, ac, bx, by, bc = bx, by, bc, ax, ay, ac
        if bx == 0:
            if by * ac == ay * bc: return (0, 0, ac, ay)
            return (0, 0, 0, 0)

    # case 4. x + y = c
    if ax * by == bx * ay: return (0, 0, 0, 0)
    return (by * ac - ay * bc, by * ax - ay * bx, bx * ac - ax * bc, bx * ay - ax * by)

def GCD(a, b): return GCD(b, a % b) if b else a

def Sol(a, b):
    x1, x2, y1, y2 = _Sol(a, b)
    if x2 < 0: x1, x2 = -x1, -x2
    if y2 < 0: y1, y2 = -y1, -y2
    g1 = GCD(abs(x1), abs(x2))
    g2 = GCD(abs(y1), abs(y2))
    if g1 > 1: x1, x2 = x1 // g1, x2 // g1
    if g2 > 1: y1, y2 = y1 // g2, y2 // g2
    return (x1, x2, y1, y2)

def Print(a, b):
    if b:
        if a == 0: print(0)
        elif b > 1: print(a, '/', b, sep='')
        else: print(a)
    else: print("don\'t know")

for _ in range(int(input())):
    a, b, _ = input(), input(), input()
    x1, x2, y1, y2 = Sol(a, b)
    Print(x1, x2), Print(y1, y2), print()
