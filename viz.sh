printf "import matplotlib.pyplot as plt\ndata = [0] * 1000\n" > viz.py
./build/mr-async-pool-tests >> viz.py
printf "plt.plot(range(len(data)), data)\nplt.title('CGSGFOREVER')\nplt.xlabel('Indices')\nplt.ylabel('Values in array')\nplt.show()" >> viz.py

python viz.py
