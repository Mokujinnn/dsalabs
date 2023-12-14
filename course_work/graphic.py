import pandas
import matplotlib.pyplot as plt

data = pandas.read_csv("./output.txt") #../build/Release/output.txt
data1 = pandas.read_csv("./output1.txt")
data2 = pandas.read_csv("./output2.txt")

plt.plot(data['n'], data['t'], color='b', label='p=0.5')
plt.plot(data2['n'], data2['t'], color='r', label='p=0.35')
plt.plot(data1['n'], data1['t'], color='g', label='p=0.25')
plt.xlabel('Количество добавленных ключей')
plt.ylabel('Время поиска. сек.')
# plt.ylim(bottom=0, top=0.000005)
plt.title('Время поиска ключа')
plt.legend()
plt.grid(True)



plt.savefig("./graphic/search_time.png", dpi=300)