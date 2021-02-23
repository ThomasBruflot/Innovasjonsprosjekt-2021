import sys
sys.path=['', '/Users/thomasbruflot/opt/anaconda3/lib/python37.zip', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7/lib-dynload', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7/site-packages', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7/site-packages/aeosa']
import matplotlib.pyplot as plt
import pyimgur

f = open("/Users/thomasbruflot/Documents/nettsider/Curling/arduinotofile/data.txt")
data = f.read()
data = data.split('\n')
for i in range(0,9):
    data.remove(data[0])
for i in data:
    if i == '':
        data.remove(i)
data.remove(data[len(data)-1])
ykor = [int(i) for i in data]
xkor =  [i for i in range(0,len(data))]

"""
data.remove(data[len(data)-1])
listexy = [data[i].split(',') for i in range(0,len(data))]

listex =[float(i[0]) for i in listexy]
listey = [float(i[1]) for i in listexy]"""

fig = plt.figure()
plt.yticks
plt.autoscale(enable=True, axis='y')
plt.plot(xkor,ykor)
plt.title('Ditt støt')

fig.savefig('DetFunker.png')

CLIENT_ID = "2043cba6776e29d"
PATH = "/Users/thomasbruflot/Documents/nettsider/Curling/DetFunker.png"

im = pyimgur.Imgur(CLIENT_ID)
uploaded_image = im.upload_image(PATH, title="Uploaded with PyImgur")
link = uploaded_image.link

print(link)
"""
f = open('linktilimgur.txt', 'w')
f.write(link)
f.close()
"""