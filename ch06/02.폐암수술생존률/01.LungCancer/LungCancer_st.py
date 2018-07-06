# -*- coding: utf-8 -*-
# 코드 내부에 한글을 사용가능 하게 해주는 부분입니다.

# 딥러닝을 구동하는 데 필요한 케라스 함수를 불러옵니다.
from keras.models import Sequential
from keras.layers import Dense

# 필요한 라이브러리를 불러옵니다.
import numpy
import tensorflow as tf
import pandas as pd

# 실행할 때마다 같은 결과를 출력하기 위해 설정하는 부분입니다.
seed = 0
numpy.random.seed(seed)
tf.set_random_seed(seed)

# 준비된 수술 환자 데이터를 불러들입니다.
df = pd.read_csv("../ThoraricSurgery.csv", names=['p1','p2','p3','p4','p5',
    'p6','p7','p8','p9','p10','p11','p12','p13','p14','pp15','p16','p17','생존여부'])
Data_set = df.values

#df.info()
#df.head(5)
#df.describe()
#df[['p2', 'p14', '생존여부']]
#df[['p2', 'p14', '생존여부']].groupby(['p2'], as_index=False).mean().sort_values(by='p2', ascending=True)


# 환자의 기록과 수술 결과를 X와 Y로 구분하여 저장합니다.
X = Data_set[:,0:17]
Y = Data_set[:,17]

# 딥러닝 구조를 결정합니다(모델을 설정하고 실행하는 부분입니다).
model = Sequential()
model.add(Dense(30, input_dim=17, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

# 딥러닝을 실행합니다.
model.compile(loss='mean_squared_error', optimizer='adam', metrics=['accuracy'])
model.fit(X, Y, epochs=30, batch_size=10)

# 모델을 평가합니다
rst = model.evaluate(X, Y)

# 평가 결과를 출력합니다.
print("\n Loss : %.4f, Accuracy: %.4f" % (rst[0], rst[1]))

