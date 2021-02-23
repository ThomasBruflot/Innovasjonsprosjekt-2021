import sys
sys.path=['', '/Users/thomasbruflot/opt/anaconda3/lib/python37.zip', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7/lib-dynload', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7/site-packages', '/Users/thomasbruflot/opt/anaconda3/lib/python3.7/site-packages/aeosa']
import matplotlib.pyplot as plt
import numpy as np
import pyimgur
import urllib.request as urllib2

f = open("/Users/thomasbruflot/Documents/nettsider/Curling/test.csv")

data = f.read()
data = data.split('\n')

data.remove(data[len(data)-1])
listexy = [data[i].split(',') for i in range(0,len(data))]

listex =[float(i[0]) for i in listexy]
listey = [float(i[1]) for i in listexy]

fig = plt.figure()
ax = plt.subplot()
plt.plot(listex,listey)
plt.title('Ditt støt')

fig.savefig('DetFunker.png')

CLIENT_ID = "2043cba6776e29d"
PATH = "/Users/thomasbruflot/Documents/nettsider/Curling/DetFunker.png"

im = pyimgur.Imgur(CLIENT_ID)
uploaded_image = im.upload_image(PATH, title="Uploaded with PyImgur")
#print(uploaded_image.title)
print(uploaded_image.link) 

lenke = uploaded_image.link
#p = Popen(['/Users/thomasbruflot/Documents/nettsider/Curling','AutoPHP.php',uploaded_image.link],stdout=PIPE)
#print (p.stdout.read())

#req = urllib2.Request(url='http://localhost:8888/Curling/AutoPHP.php?lenke=%s' % uploaded_image.link )
#f = urllib2.urlopen(req)
#print(f.read())


