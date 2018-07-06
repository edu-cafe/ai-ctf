# Linear Regression (w=2)

import tensorflow as tf

x = [1., 2., 3., 4.]
y = [2., 4., 6., 8.]
m = n_samples = len(x)

w = tf.________(tf.float32)
hypo = tf._______(x, w)        # H(x) = wx
cost = tf._________(tf.pow(hypo - y, 2))/(m)

init = tf.initialize_all_variables()
sess = tf.Session()
sess.run(init);

for i in range(-20, 30):
    print("i:%d, w:%.1f, cost:%f" % (i, i*0.1, sess.run(cost, ______={w: i*0.1})))
