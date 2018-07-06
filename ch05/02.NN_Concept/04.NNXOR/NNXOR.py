# XOR 문제해결 using Multilayer Perceptron
import numpy as np

w11 = np.array([-2, 3])
w12 = np.array([-2, 1])
w2 = np.array([-60, 94])
b1 = -1
b2 = 0.5
b3 = -1

# mutilayer perceptron function
def MLP(x, w, b):
    y = np.sum(w * x) - b
    if y <= 0 :
        return 0
    else:
        return 1

# XOR Gate
def XOR(x1, x2):
    h = np.array([0,0])
    h[0] = MLP(np.array([x1, x2]), w11, b1)
    h[1] = MLP(np.array([x1, x2]), w12, b2)
    return MLP(h, w2, b3)

# output print
if __name__ == '__main__':
    for x in [(0, 0), (1, 0), (0, 1), (1, 1)]:
        y = XOR(x[0], x[1])
        print("xor_input : " + str(x) + "  --> xor_output : " + str(y))



