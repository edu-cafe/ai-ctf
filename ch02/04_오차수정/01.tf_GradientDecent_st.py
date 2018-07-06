# Gradient Decent Example
import tensorflow as tf
tf.set_random_seed(666)

data = [[2,81],[4,93],[6,91],[8,97]]
x_data = [x_row[0] for x_row in data]
y_data = [y_row[1] for y_row in data]

learning_rate = 0.1
a = tf.Variable(tf.random_uniform([1], 0, 10, dtype=tf.float64, seed=0))
b = tf.Variable(tf.random_uniform([1], 0, 100, dtype=tf.float64, seed=0))

y = a*x_data + b
rmse = tf.sqrt(tf.reduce_mean(tf.square(y - y_data)))
gradient_decent = tf.train.GradientDescentOptimizer(learning_rate).minimize(rmse)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for step in range(4001):
        sess.run(gradient_decent)
        if step % 100 == 0:
            print("Epoch_%4d -> RMSE=%.4f, 기울기(a)=%.4f, 절편(b)=%.4f" 
                  % (step, sess.run(rmse), sess.run(a), sess.run(b)))

    sess.close()

