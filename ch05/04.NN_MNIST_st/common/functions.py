# -*- coding: utf-8 -*-
"""
Created on Tue Sep 11 14:56:58 2018

@author: shkim
"""

import numpy as np

def step_func(x):
    return np.array(x>0, dtype=np.int)
	
def sigmoid(x):
    return 1/(1 + np.exp(-x))
	
def relu(x):
    return np.maximum(0, x)
	
def softmax(a):
    c = np.max(a)
    exp_a = np.exp(a - c)
    sum_exp_a = np.sum(exp_a)
    y = exp_a/sum_exp_a
    return y

# MSE, Root Mean Square Error
def mse(p, t):
    return 0.5 * np.sum( (p-t)**2 )

# CEE, Cross Entropy Error
def cee(p, t):	
    delta = 1e-7
    return -np.sum(t * np.log(p + delta) )  # delta : -log0이 -inf가 되는 것을 방지
	





